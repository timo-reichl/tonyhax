
tonyhax
=======

Software backup loader exploit thing for the Sony PlayStation 1.

For installing on a memory card, you'd need **both** the generic tonyhax SPL save the game-specific save.

When installing:
 * If you are using any sort of visual memory card editor (such as [OrionSoft's PS1 Memory Card Manager](http://onorisoft.free.fr/retro.htm?psx/psx.htm), Dexdrive, etc...), consider using the MCS file.
 * If you are copying it using a PS2 console and uLaunchELF, you'll need to use the raw file. **The name is important - do not rename them**.

These have been tested to work on real hardware:

| Game                                   | Region | Code       | MCS file          | Raw file             |
|----------------------------------------|--------|------------|-------------------|----------------------|
| tonyhax SPL **required**               | -      | -          | tonyhax.mcs       | BESLEM-99999TONYHAX  |
| Brunswick Circuit Pro Bowling          | NTSC-U | SLUS-00571 | brunswick1-us.mcs | BASLUS-00571         |
| Brunswick Circuit Pro Bowling          | PAL-E  | SLES-01376 | brunswick1-eu.mcs | BESLES-01376         |
| Brunswick Circuit Pro Bowling 2        | NTSC-U | SLUS-00856 | brunswick2-us.mcs | BASLUS-00856         |
| Brunswick Circuit Pro Bowling 2        | PAL-E  | SLES-02618 | brunswick2-eu.mcs | BESLES-02618         |
| Cool Boarders 4                        | NTSC-U | SCUS-94559 | coolbrd4-us.mcs   | BASCUS-9455916       |
| Cool Boarders 4                        | PAL-E  | SCES-02283 | coolbrd4-eu.mcs   | BESCES-0228316       |
| Crash Bandicoot 2: Cortex Strikes Back | NTSC-U | SCUS-94154 | crash2-us.mcs     | BASCUS-9415400047975 |
| Crash Bandicoot 2: Cortex Strikes Back | PAL-E  | SCES-00967 | crash2-eu.mcs     | BESCES-0096700765150 |
| Crash Bandicoot 3: Warped              | NTSC-U | SCUS-94244 | crash3-us.mcs     | BASCUS-9424400000000 |
| Crash Bandicoot 3: Warped              | PAL-E  | SCES-01420 | crash3-eu.mcs     | BESCES-0142000000000 |
| Tony Hawk's Pro Skater 2               | NTSC-U | SLUS-01066 | thps2-us.mcs      | BASLUS-01066TNHXG01  |
| Tony Hawk's Pro Skater 2               | PAL-E  | SLES-02908 | thps2-eu.mcs      | BESLES-02908TNHXG01  |
| Tony Hawk's Pro Skater 2               | PAL-DE | SLES-02910 | thps2-de.mcs      | BESLES-02910TNHXG01  |
| Tony Hawk's Pro Skater 2               | PAL-FR | SLES-02909 | thps2-fr.mcs      | BESLES-02909TNHXG01  |
| Tony Hawk's Pro Skater 3               | NTSC-U | SLUS-01419 | thps3-us.mcs      | BASLUS-01419TNHXG01  |
| Tony Hawk's Pro Skater 3               | PAL-E  | SLES-03645 | thps3-eu.mcs      | BESLES-03645TNHXG01  |
| Tony Hawk's Pro Skater 3               | PAL-DE | SLES-03647 | thps3-de.mcs      | BESLES-03647TNHXG01  |
| Tony Hawk's Pro Skater 3               | PAL-FR | SLES-03646 | thps3-fr.mcs      | BESLES-03646TNHXG01  |
| Tony Hawk's Pro Skater 4               | NTSC-U | SLUS-01485 | thps4-us.mcs      | BASLUS-01485TNHXG01  |
| Tony Hawk's Pro Skater 4               | PAL-E  | SLES-03954 | thps4-eu.mcs      | BESLES-03954TNHXG01  |
| Tony Hawk's Pro Skater 4               | PAL-DE | SLES-03955 | thps4-de.mcs      | BESLES-03955TNHXG01  |
| Tony Hawk's Pro Skater 4               | PAL-FR | SLES-03956 | thps4-fr.mcs      | BESLES-03956TNHXG01  |

The following games were thought previously to fully support tonyhax but behave erratically on real hardware ([issue #22](https://github.com/socram8888/tonyhax/issues/22) on GitHub):

| Game                                   | Region | Code       | MCS file          | Raw file             |
|----------------------------------------|--------|------------|-------------------|----------------------|
| Castrol Honda Superbike Racing         | NTSC-U | SLUS-00882 | castrolsb-us.mcs  | BASLUS-00882CHSv1    |
| Castrol Honda Superbike Racing         | PAL-E  | SLES-01182 | castrolsb-eu.mcs  | BESLES_01182CHSv1    |
| Castrol Honda VTR                      | PAL-E  | SLES-02942 | castrolvtr-eu.mcs | BESLES-02942CHSVTRv1 |
| Sports Superbike                       | PAL-E  | SLES-03057 | superbike1-eu.mcs | BESLES-03057SSBv1    |
| Sports Superbike 2                     | PAL-E  | SLES-03827 | superbike2-eu.mcs | BESLES-03827SSII     |
| XS Moto                                | NTSC-U | SLUS-01506 | xsmoto-us.mcs     | BASLUS-01506XSMOTOv1 |
| XS Moto                                | PAL-E  | SLES-04095 | xsmoto-eu.mcs     | BESLES-04095XSMOTO   |

For more information, look at [its section at orca.pet](https://orca.pet/tonyhax/).
