#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t crc4_add4(uint8_t crc, uint8_t data)
    {
    uint8_t x = (crc ^ data) & 0x0F;
    uint8_t x3 = x >> 3;
    return 0x0F & (x ^ (x << 1) ^ x3 ^ (x3 << 1));
    }

int main(void)
    {
    uint8_t x;

    printf("    ");
    for (x = 0; x < 16; x++)
        {
        printf("0x%X%s", crc4_add4(0, x), (x == 0xF) ? "" : ",");
        }
    puts("");

    return 0;
    }
