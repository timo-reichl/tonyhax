
# Thanks to whoever made https://devhints.io/makefile!

CC=mips-linux-gnu-gcc
CFLAGS=-Wall -Wextra -Wno-main -EL -march=r3000 -mfp32 -nostdlib -mno-abicalls -fno-pic -O2

LD=mips-linux-gnu-ld
LDFLAGS=-EL

OBJCOPY=mips-linux-gnu-objcopy
OBJCOPYFLAGS=-O binary

SAVEFILES=$(patsubst %-tpl.mcs, %.mcs, $(wildcard *-tpl.mcs))

SPL_HEADERS := $(wildcard *.h) orca.inc
SPL_OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c)) bios.o

.PHONY: clean

all: $(SAVEFILES) $(MCS_FILES)

clean:
	rm -f BES* BAS* entry-*.elf entry-*.bin secondary.elf secondary.bin *.o orca.inc

# Entry target

entry-quick.elf: entry.S
	$(CC) $(CFLAGS) entry.S -o entry-quick.elf

entry-full.elf: entry.S
	$(CC) $(CFLAGS) -DMCINIT entry.S -o entry-full.elf

entry-%.bin: entry-%.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -j .text $< $@

%.mcs: %
	python3 bin2mcs.py $<

# Secondary loader

%.o: %.c $(SPL_HEADERS)
	$(CC) $(CFLAGS) -c $<

%.o: %.s $(SPL_HEADERS)
	$(CC) $(CFLAGS) -c $<

orca.inc: orca.img
	bash bin2h.sh ORCA_IMAGE orca.img orca.inc

secondary.elf: secondary.ld $(SPL_OBJECTS)
	$(LD) $(LDFLAGS) -T secondary.ld $(SPL_OBJECTS) -o $@

secondary.bin: secondary.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) secondary.elf secondary.bin

# Tonyhax secondary program loader
tonyhax.mcs: tonyhax-tpl.mcs secondary.bin
	cp tonyhax-tpl.mcs tonyhax.mcs
	dd conv=notrunc if=secondary.bin of=tonyhax.mcs bs=384 seek=1

# Brunswick Circuit Pro Bowling NTSC-US target
brunswick1-us.mcs: brunswick1-us-tpl.mcs entry-full.bin
	cp brunswick1-us-tpl.mcs brunswick1-us.mcs
	dd conv=notrunc if=entry-full.bin of=brunswick1-us.mcs bs=1 seek=2016

# Brunswick Circuit Pro Bowling 2 NTSC-US target
brunswick2-us.mcs: brunswick2-us-tpl.mcs entry-full.bin
	cp brunswick2-us-tpl.mcs brunswick2-us.mcs
	dd conv=notrunc if=entry-full.bin of=brunswick2-us.mcs bs=1 seek=2272

# THPS2 NTSC-US target
thps2-us.mcs: thps2-us-tpl.mcs entry-quick.bin
	cp thps2-us-tpl.mcs thps2-us.mcs
	dd conv=notrunc if=entry-quick.bin of=thps2-us.mcs bs=1 seek=5208

# THPS3 NTSC-US target
thps3-us.mcs: thps3-us-tpl.mcs entry-quick.bin
	cp thps3-us-tpl.mcs thps3-us.mcs
	dd conv=notrunc if=entry-quick.bin of=thps3-us.mcs bs=1 seek=4612

# THPS4 NTSC-US target
thps4-us.mcs: thps4-us-tpl.mcs entry-quick.bin
	cp thps4-us-tpl.mcs thps4-us.mcs
	dd conv=notrunc if=entry-quick.bin of=thps4-us.mcs bs=1 seek=5260

# Brunswick Circuit Pro Bowling PAL-EU target
brunswick1-eu.mcs: brunswick1-eu-tpl.mcs entry-full.bin
	cp brunswick1-eu-tpl.mcs brunswick1-eu.mcs
	dd conv=notrunc if=entry-full.bin of=brunswick1-eu.mcs bs=1 seek=2016

# Brunswick Circuit Pro Bowling 2 PAL-EU target
brunswick2-eu.mcs: brunswick2-eu-tpl.mcs entry-full.bin
	cp brunswick2-eu-tpl.mcs brunswick2-eu.mcs
	dd conv=notrunc if=entry-full.bin of=brunswick2-eu.mcs bs=1 seek=2272

# THPS2 PAL-EU target
thps2-eu.mcs: thps2-eu-tpl.mcs entry-quick.bin
	cp thps2-eu-tpl.mcs thps2-eu.mcs
	dd conv=notrunc if=entry-quick.bin of=thps2-eu.mcs bs=1 seek=5200

# THPS2 PAL-FR target
thps2-fr.mcs: thps2-fr-tpl.mcs entry-quick.bin
	cp thps2-fr-tpl.mcs thps2-fr.mcs
	dd conv=notrunc if=entry-quick.bin of=thps2-fr.mcs bs=1 seek=5200

# THPS2 PAL-DE target
thps2-de.mcs: thps2-de-tpl.mcs entry-quick.bin
	cp thps2-de-tpl.mcs thps2-de.mcs
	dd conv=notrunc if=entry-quick.bin of=thps2-de.mcs bs=1 seek=5200

# THPS3 PAL-EU target
thps3-eu.mcs: thps3-eu-tpl.mcs entry-quick.bin
	cp thps3-eu-tpl.mcs thps3-eu.mcs
	dd conv=notrunc if=entry-quick.bin of=thps3-eu.mcs bs=1 seek=4608

# THPS3 PAL-FR target
thps3-fr.mcs: thps3-fr-tpl.mcs entry-quick.bin
	cp thps3-fr-tpl.mcs thps3-fr.mcs
	dd conv=notrunc if=entry-quick.bin of=thps3-fr.mcs bs=1 seek=4608

# THPS3 PAL-DE target
thps3-de.mcs: thps3-de-tpl.mcs entry-quick.bin
	cp thps3-de-tpl.mcs thps3-de.mcs
	dd conv=notrunc if=entry-quick.bin of=thps3-de.mcs bs=1 seek=4608

# THPS4 PAL-EU target
thps4-eu.mcs: thps4-eu-tpl.mcs entry-quick.bin
	cp thps4-eu-tpl.mcs thps4-eu.mcs
	dd conv=notrunc if=entry-quick.bin of=thps4-eu.mcs bs=1 seek=5252

# THPS4 PAL-DE target
thps4-de.mcs: thps4-de-tpl.mcs entry-quick.bin
	cp thps4-de-tpl.mcs thps4-de.mcs
	dd conv=notrunc if=entry-quick.bin of=thps4-de.mcs bs=1 seek=5252

# THPS4 PAL-FR target
thps4-fr.mcs: thps4-fr-tpl.mcs entry-quick.bin
	cp thps4-fr-tpl.mcs thps4-fr.mcs
	dd conv=notrunc if=entry-quick.bin of=thps4-fr.mcs bs=1 seek=5252
