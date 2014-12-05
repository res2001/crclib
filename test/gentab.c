#include "fast_crc.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
    {
    uint8_t row, col;

    for (row = 0; row < 16; row++)
        {
        printf("    ");
        for (col = 0; col < 16; col++)
            {
            uint8_t data = (row << 4) + col;
            printf("0x%02X%s", CRC8_Add8(0, data), (data == 0xFF) ? "" : ",");
            }
        puts("");
        }

    for (row = 0; row < 16; row++)
        {
        printf("    ");
        for (col = 0; col < 16; col++)
            {
            uint8_t data = (row << 4) + col;
            printf("0x%02X%s", CRC8DS_Add8(0, data), (data == 0xFF) ? "" : ",");
            }
        puts("");
        }

    return 0;
    }
