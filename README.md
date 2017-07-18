# adf4350

A simple example of ADF4350 working with STM32L152 Dev Board. The chip gets initiated with some defautl settings and a 2450MHz tone is generated.

Technical info:
- ADF4350 Reference clock is 25MHz
- Connections are: CLK - SPI2_CLK (PB13), DATA - SPI2_MOSI (PB15), CE - PB14, LE - PB12, PDBRF - PB2, LD - PB11
