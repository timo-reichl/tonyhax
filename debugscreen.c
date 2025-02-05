
#include "debugscreen.h"
#include "gpu.h"
#include "bios.h"
#include "str.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define CHAR_HEIGHT 15
#define CHAR_WIDTH 8
#define FONT_X 512
#define CLUT_X 512
#define CLUT_Y 6 * CHAR_HEIGHT

// Orca loaded right next to the font
#define ORCA_WIDTH 40
#define ORCA_HEIGHT 20

// Divided by 4 because each pixel is 4bpp, or 1/4 of a 16-bit short
#define ORCA_VRAM_X (FONT_X + CHAR_WIDTH * 16 / 4)

#define LOG_MARGIN 10
#define LOG_START_Y 35
#define LOG_LINE_HEIGHT 16

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

static uint_fast8_t log_lines;

// Grayscale
static const uint16_t PALETTE[16] = { 0x0000, 0x0842, 0x1084, 0x18C6, 0x2108, 0x294A, 0x318C, 0x39CE, 0x4631, 0x4E73, 0x56B5, 0x5EF7, 0x6739, 0x6F7B, 0x77BD, 0x7FFF };

#include "orca.inc"

void decompressfont() {
	// Font is 1bpp. We have to convert each character to 4bpp.
	const uint8_t * rom_charset = (const uint8_t *) 0xBFC7F8DE;
	uint8_t charbuf[60];

	// Iterate through the 16x6 character table
	for (uint_fast8_t tabley = 0; tabley < 6; tabley++) {
		for (uint_fast8_t tablex = 0; tablex < 16; tablex++) {
			uint8_t * bufferpos = charbuf;

			// Iterate through each line of the 8x15 character
			for (uint_fast8_t chary = 0; chary < 15; chary++) {
				uint_fast8_t char1bpp = *rom_charset;
				rom_charset++;

				// Iterate through each column of the character
				for (uint_fast8_t bpos = 0; bpos < 8; bpos += 2) {
					uint_fast8_t char4bpp = 0;

					if (char1bpp & 0x80) {
						char4bpp |= 0x0F;
					}
					if (char1bpp & 0x40) {
						char4bpp |= 0xF0;
					}

					*bufferpos = char4bpp;
					bufferpos++;
					char1bpp = char1bpp << 2;
				}
			}

			// At 4bpp, each character uses 8 * 4 / 16 = 2 shorts, so the texture width is set to 2.
			GPU_dw(FONT_X + tablex * 2, tabley * CHAR_HEIGHT, 2, CHAR_HEIGHT, (uint16_t *) charbuf);
		}
	}
}

void debug_init() {
	bool pal = gpu_is_pal();

	// Restore to sane defaults
	gpu_reset();

	// Configure mode, keeping PAL flag
	uint32_t mode = GPU_DISPLAY_H320 | GPU_DISPLAY_V240 | GPU_DISPLAY_15BPP;
	if (pal) {
		mode |= GPU_DISPLAY_PAL;

		log_lines = 13;
	} else {
		mode |= GPU_DISPLAY_NTSC;

		log_lines = 12;
	}
	gpu_display_mode(mode);

	// Center image on screen
	// Values from THPS2 NTSC and PAL during FMVs
	if (pal) {
		gpu_set_hrange(624, 3260);
		gpu_set_vrange(37, 292);
	} else {
		gpu_set_hrange(600, 3160);
		gpu_set_vrange(16, 256);
	}

	// Clear entire VRAM
	gpu_fill_rectangle(0, 0, 1023, 511, 0x000000);

	// Enable display
	gpu_display_enable();

	// Load font
	decompressfont();

	// Load orca image
	// Again, /4 because each pixels is 1/4 of a 16-bit short
	GPU_dw(ORCA_VRAM_X, 0, ORCA_WIDTH / 4, ORCA_HEIGHT, (const uint16_t *) ORCA_IMAGE);

	// Load the palette to Vram
	GPU_dw(CLUT_X, CLUT_Y, 16, 1, PALETTE);

	// Flush old textures
	gpu_flush_cache();

	// Configure Texpage
	// - Texture page to X=512 Y=0
	// - Colors to 4bpp
	// - Allow drawing to display area (fuck Vsync)
	GPU_cw(0xE1000408);

	// Configure texture window
	GPU_cw(0xE2000000);

	// Set drawing area
	gpu_set_drawing_area(0, 0, 320, 256);

	// Draw border
	debug_text_at(20, 10, "tonyhax " STRINGIFY(TONYHAX_VERSION));
	gpu_fill_rectangle(0, 30, SCREEN_WIDTH, 2, 0xFFFFFF);

	// "orca.pet" website
	debug_text_at(SCREEN_WIDTH - 8 * CHAR_WIDTH - 20, 10, "orca.pet");

	// Draw orca
	struct gpu_tex_rect orca_rect;
	orca_rect.tex_x = 16 * CHAR_WIDTH;
	orca_rect.tex_y = 0;
	orca_rect.width = ORCA_WIDTH;
	orca_rect.height = ORCA_HEIGHT;
	orca_rect.draw_x = SCREEN_WIDTH - 8 * CHAR_WIDTH - 20 - ORCA_WIDTH - 5;
	orca_rect.draw_y = 5;
	orca_rect.clut_x = CLUT_X;
	orca_rect.clut_y = CLUT_Y;
	orca_rect.semi_transp = 0;
	orca_rect.raw_tex = 1;
	gpu_draw_tex_rect(&orca_rect);
}

void debug_text_at(uint_fast16_t x_pos, uint_fast16_t y_pos, const char * text) {
	// Initialize constants of the rect
	struct gpu_tex_rect rect;
	rect.draw_y = y_pos;
	rect.width = CHAR_WIDTH;
	rect.height = CHAR_HEIGHT;
	rect.clut_x = CLUT_X;
	rect.clut_y = CLUT_Y;
	rect.semi_transp = 0;
	rect.raw_tex = 1;

	while (*text != 0) {
		int tex_idx = *text - '!';
		if (tex_idx >= 0 && tex_idx < 96) {
			// Font has a yen symbol where the \ should be
			if (tex_idx == '\\' - '!') {
				tex_idx = 95;
			}

			// Draw text
			rect.draw_x = x_pos;
			rect.tex_x = (tex_idx % 16) * CHAR_WIDTH;
			rect.tex_y = (tex_idx / 16) * CHAR_HEIGHT;

			gpu_draw_tex_rect(&rect);
		}

		text++;
		x_pos += CHAR_WIDTH;
	}
}

void debug_write(const char * str, ...) {
	va_list args;
	va_start(args, str);

	// For a render width of 320 this should be just 40 but let's be generous
	char formatted[64];

	mini_vsprintf(formatted, str, args);

	// Flush old textures
	gpu_flush_cache();

	// Scroll text up
	for (int line = 1; line < log_lines; line++) {
		gpu_copy_rectangle(
				/* source */
				LOG_MARGIN,
				LOG_START_Y + LOG_LINE_HEIGHT * line,
				
				/* destination */
				LOG_MARGIN,
				LOG_START_Y + LOG_LINE_HEIGHT * (line - 1),
				
				/* size */
				SCREEN_WIDTH - LOG_MARGIN,
				LOG_LINE_HEIGHT
		);
	}

	// Clear last line
	gpu_fill_rectangle(0, LOG_START_Y + (log_lines - 1) * LOG_LINE_HEIGHT, SCREEN_WIDTH, CHAR_HEIGHT, 0x000000);

	// Draw text on last line
	debug_text_at(LOG_MARGIN, LOG_START_Y + (log_lines - 1) * LOG_LINE_HEIGHT, formatted);
}
