#include "fast_crc.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define RANDOMIZE 1

#if RANDOMIZE
#include <time.h>
#endif

#define OK_STR(cond)    ((cond) ? "OK" : "FAIL")

uint8_t crc4_ref_up4(uint8_t crc, uint8_t nyb)
    {
    int i;
    crc ^= nyb;
    for (i = 0; i < 4; i++)
        {
        crc <<= 1;
        if (crc & 0x10) crc ^= 3;
        }
    return crc & 0x0F;
    }

int main(void)
    {
    /* Размер должен быть кратным 4 */
    const size_t DATA_LEN = 4 * 65536;
    size_t i;
    uint8_t* data;
    uint16_t* data16;
    uint8_t crc4_4, crc4_8, crc4_ref;
    uint8_t crc8, crc8_ref;
    uint16_t crc16, crc16_ref;
    uint32_t crc32, not_crc32;

    data = malloc(DATA_LEN);
    data16 = (uint16_t*)data;
    if (!data)
        {
        fprintf(stderr, "Cannot allocate memory\n");
        return 255;
        }

#if RANDOMIZE
    srand((unsigned int)time(NULL));
#endif

    /* Заполнить массив случайными значениями */
    for (i = 0; i < DATA_LEN; i++)
        {
        data[i] = (uint8_t)(rand() & 0xFF);
        }

    /* Тест CRC4 */
    puts("---- CRC4 ITU ----");

    crc4_ref = crc4_4 = crc4_8 = CRC4_START_VAL;
    for (i = 0; i < DATA_LEN; i++)
        {
        crc4_ref = crc4_ref_up4(crc4_ref, data[i] >> 4);
        crc4_ref = crc4_ref_up4(crc4_ref, data[i] & 0x0F);
        crc4_4 = CRC4_Add4(crc4_4, data[i] >> 4);
        crc4_4 = CRC4_Add4(crc4_4, data[i] & 0x0F);
        crc4_8 = CRC4_Add8(crc4_8, data[i]);
        }
    printf("Reference       : 0x%X\n", crc4_ref);
    printf("CRC4_Add4       : 0x%X (%s)\n", crc4_4, OK_STR(crc4_4 == crc4_ref));
    printf("CRC4_Add8       : 0x%X (%s)\n", crc4_8, OK_STR(crc4_8 == crc4_ref));
    crc4_8 = CRC4_Block8(CRC4_START_VAL, data, DATA_LEN);
    printf("CRC4_Block8     : 0x%X (%s)\n", crc4_8, OK_STR(crc4_8 == crc4_ref));

    /* CRC4 блока данных с добавленной CRC должно быть равно 0 */
    crc4_8 = CRC4_Add4(crc4_8, crc4_8);
    printf("CRC4    of { data, crc } = 0x%X (%s)\n", crc4_8, OK_STR(0 == crc4_8));

    /* Тест CRC8 */
    puts("---- Buggy CRC8 ----");

    crc8_ref = eval_crc8(CRC8_START_VAL, data, DATA_LEN);
    printf("Reference       : 0x%02X\n", crc8_ref);

    crc8 = CRC8_START_VAL;
    for (i = 0; i < DATA_LEN; i++)
        {
        crc8 = CRC8_Add8(crc8, data[i]);
        }
    printf("CRC8_Add8       : 0x%02X (%s)\n", crc8, OK_STR(crc8 == crc8_ref));
    crc8 = CRC8_Block8(CRC8_START_VAL, data, DATA_LEN);
    printf("CRC8_Block8     : 0x%02X (%s)\n", crc8, OK_STR(crc8 == crc8_ref));

    /* CRC8 блока данных с добавленной CRC должно быть равно 0 */
    crc8 = CRC8_Add8(crc8, crc8);
    printf("CRC8    of { data, crc } = 0x%02X (%s)\n", crc8, OK_STR(0 == crc8));

    /* Тест CRC8DS */
    puts("---- CRC8 DALLAS ----");

    crc8_ref = eval_revcrc8(CRC8DS_START_VAL, data, DATA_LEN);
    printf("Reference       : 0x%02X\n", crc8_ref);

    crc8 = CRC8DS_START_VAL;
    for (i = 0; i < DATA_LEN; i++)
        {
        crc8 = CRC8DS_Add8(crc8, data[i]);
        }
    printf("CRC8DS_Add8     : 0x%02X (%s)\n", crc8, OK_STR(crc8 == crc8_ref));
    crc8 = CRC8DS_Block8(CRC8DS_START_VAL, data, DATA_LEN);
    printf("CRC8DS_Block8   : 0x%02X (%s)\n", crc8, OK_STR(crc8 == crc8_ref));

    /* CRC8 блока данных с добавленной CRC должно быть равно 0 */
    crc8 = CRC8DS_Add8(crc8, crc8);
    printf("CRC8DS  of { data, crc } = 0x%02X (%s)\n", crc8, OK_STR(0 == crc8));

    /* Тест CRC16-CCITT */
    puts("---- CRC16 CCITT ----");

    crc16_ref = eval_crc16(CRC16_START_VAL, data, DATA_LEN);
    printf("Reference       : 0x%04X\n", crc16_ref);

    crc16 = CRC16_START_VAL;
    for (i = 0; i < DATA_LEN; i++)
        {
        crc16 = CRC16_Add8(crc16, data[i]);
        }
    printf("CRC16_Add8      : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));
    crc16 = CRC16_Block8(CRC16_START_VAL, data, DATA_LEN);
    printf("CRC16_Block8    : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));

    crc16 = CRC16_START_VAL;
    for (i = 0; i < DATA_LEN / 2; i++)
        {
        crc16 = CRC16_Add16(crc16, data16[i]);
        }
    printf("CRC16_Add16     : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));
    crc16 = CRC16_Block16(CRC16_START_VAL, data16, DATA_LEN / 2);
    printf("CRC16_Block16   : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));

    /* CRC16 блока данных с добавленной CRC16 старшим байтом вперед должно быть равно 0 */
    crc16 = CRC16_Add8(CRC16_Add8(crc16, (uint8_t)(crc16 >> 8)), (uint8_t)(crc16 & 0xFF));
    printf("CRC16   of { data, crchi, crclo } = 0x%04X (%s)\n", crc16, OK_STR(0 == crc16));

    /* Тест CRC16-MODBUS */
    puts("---- CRC16 MODBUS ----");

    crc16_ref = eval_modbuscrc(CRC16MB_START_VAL, data, DATA_LEN);
    printf("Reference       : 0x%04X\n", crc16_ref);

    crc16 = CRC16MB_START_VAL;
    for (i = 0; i < DATA_LEN; i++)
        {
        crc16 = CRC16MB_Add8(crc16, data[i]);
        }
    printf("CRC16MB_Add8    : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));
    crc16 = CRC16MB_Block8(CRC16MB_START_VAL, data, DATA_LEN);
    printf("CRC16MB_Block8  : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));

    crc16 = CRC16MB_START_VAL;
    for (i = 0; i < DATA_LEN / 2; i++)
        {
        crc16 = CRC16MB_Add16(crc16, data16[i]);
        }
    printf("CRC16MB_Add16   : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));
    crc16 = CRC16MB_Block16(CRC16MB_START_VAL, data16, DATA_LEN / 2);
    printf("CRC16MB_Block16 : 0x%04X (%s)\n", crc16, OK_STR(crc16 == crc16_ref));

    /* CRC16 блока данных с добавленной CRC16 младшим байтом вперед должно быть равно 0 */
    crc16 = CRC16MB_Add8(CRC16MB_Add8(crc16, (uint8_t)(crc16 & 0xFF)), (uint8_t)(crc16 >> 8));
    printf("CRC16MB of { data, crclo, crchi } = 0x%04X (%s)\n", crc16, OK_STR(0 == crc16));

    /* Тест CRC32-CCITT */
    puts("---- CRC32 CCITT ----");

    crc32 = CRC32_Block8(CRC32_START_VAL, data, DATA_LEN);
    printf("CRC32_Block8    : 0x%08X\n", crc32);
    /* CRC32 блока данных с добавленной ~CRC32 младшим байтом вперед должно быть равно -1 */
    not_crc32 = ~crc32;
    crc32 = CRC32_Block8(crc32, (uint8_t*)&not_crc32, sizeof(not_crc32));
    printf("CRC32 of { data, ~crc32 } = 0x%08X (%s)\n", crc32, OK_STR(0 == ~crc32));

    return 0;
    }
