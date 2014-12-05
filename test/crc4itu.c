#include <stdio.h>
#include <stdint.h>


#if 0   /* no sense, ~same performance as 2x update4 */
#define FASTCRC_CRC4_UPDATE8(crc, data)   do {                              \
    register FASTCRC_U8_TYPE x, t = (data);                                 \
    x = ((crc) ^ (t >> 4)) & 0x0F;                                          \
    t ^= (FASTCRC_U8_TYPE)((x >> 2) ^ ((t >> 3) & 1));                      \
    (crc) = (x ^ (x << 2) ^ t ^ (t << 1)) & 0x0F;                           \
    } while (0)
#endif

uint8_t crc4_tab[16] = 
    {
    0x0, 0x3, 0x6, 0x5, 0xC, 0xF, 0xA, 0x9, 0xB, 0x8, 0xD, 0xE, 0x7, 0x4, 0x1, 0x2
    };

uint8_t crc4_add4(uint8_t crc, uint8_t data)
    {
    uint8_t x = (crc ^ data) & 0x0F;
    x ^= (x >> 3);
    return (x ^ (x << 1)) & 0x0F;
    }

uint8_t crc4_add4_tab(uint8_t crc, uint8_t data)
    {
    uint8_t x = (crc ^ data) & 0x0F;
    return crc4_tab[x];
    }

uint8_t crc4_add8(uint8_t crc, uint8_t data)
    {
    uint8_t x = (crc ^ (data >> 4)) & 0x0F;
    uint8_t t = (uint8_t)((x >> 2) ^ ((data >> 3) & 1) ^ data);
    return (x ^ (x << 2) ^ t ^ (t << 1)) & 0x0F;
    }

int main(void)
    {
    uint8_t crc1 = 0, crc2 = 0, crc3 = 0;
    int d;
    while (scanf("%02X", &d) > 0)
        {
        //printf("%02X\n", d);
        crc1 = crc4_add4(crc1, (uint8_t)d >> 4);
        crc1 = crc4_add4(crc1, (uint8_t)d & 0x0F);

        crc2 = crc4_add8(crc2, (uint8_t)d);

        crc3 = crc4_add4_tab(crc3, (uint8_t)d >> 4);
        crc3 = crc4_add4_tab(crc3, (uint8_t)d & 0x0F);
        }

    printf("CRC by 4   = %02X\n", crc1);
    printf("CRC by 8   = %02X\n", crc2);
    printf("CRC by tab = %02X\n", crc3);

    return 0;
    }
