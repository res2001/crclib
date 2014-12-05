/*================================================================================================*
 * Контрольные суммы CRC-4, CRC-8, CRC-16 и CRC-32 с повышенной скоростью вычислений
 *================================================================================================*/

#ifndef FAST_CRC_H_
#define FAST_CRC_H_

#include "fast_crc_cfg.h"

/*================================================================================================*/
/* Добавление 4-битного ниббла к CRC4 (0x3 влево) */
#if !FASTCRC_CRC4_USE_TABLE
#define FASTCRC_CRC4_UPDATE4(crc, data)   do {                              \
    register FASTCRC_U8_TYPE x = ((crc) ^ (data)) & 0x0F;                   \
    x ^= x >> 3;                                                            \
    (crc) = (x ^ (x << 1)) & 0x0F;                                          \
    } while (0)
#else
#define FASTCRC_CRC4_UPDATE4(crc, data)   do {                              \
    register FASTCRC_U8_TYPE x = ((crc) ^ (data)) & 0x0F;                   \
    (crc) = g_fastcrc_crc4_table[x];                                        \
    } while (0)
#endif

/* Добавление байта к CRC4 (0x3 влево) */
#define FASTCRC_CRC4_UPDATE8(crc, data)   do {                              \
    register FASTCRC_U8_TYPE d = (data);                                    \
    FASTCRC_CRC4_UPDATE4((crc), d >> 4);                                    \
    FASTCRC_CRC4_UPDATE4((crc), d);                                         \
    } while (0)

/* Добавление байта к CRC8 (некорректная 0x8C влево) */
#if !FASTCRC_CRC8_USE_TABLE
#define FASTCRC_CRC8_UPDATE8(crc, data)    do {                             \
    register FASTCRC_U8_TYPE x, p;                                          \
    x = (crc) ^ (data);                                                     \
    (crc) = x >> 4;                                                         \
    x &= 0x0F;                                                              \
    p = x ^ (x >> 2);                                                       \
    p ^= p >> 1;                                                            \
    p &= 1;                                                                 \
    (crc) = (FASTCRC_U8_TYPE)((p ^ (p << 5) ^ (x << 1) ^ (crc)) << 2);      \
    } while (0)
#else
#define FASTCRC_CRC8_UPDATE8(crc, data)    do {                             \
    register FASTCRC_U8_TYPE x = (crc) ^ (data);                            \
    (crc) = g_fastcrc_crc8_table[x];                                        \
    } while (0)
#endif

/* Добавление байта к CRC8-DALLAS (0x8C вправо) */
#if !FASTCRC_CRC8DS_USE_TABLE
#define FASTCRC_CRC8DS_UPDATE8(crc, data)    do {                           \
    register FASTCRC_U8_TYPE x = (crc) ^ (data);                            \
    x ^= (FASTCRC_U8_TYPE)((x << 3) ^ (x << 4) ^ (x << 6));                 \
    (crc) = x ^ (x >> 4) ^ (x >> 5);                                        \
    } while (0)
#else
#define FASTCRC_CRC8DS_UPDATE8(crc, data)    do {                           \
    register FASTCRC_U8_TYPE x = (crc) ^ (data);                            \
    (crc) = g_fastcrc_crc8ds_table[x];                                      \
    } while (0)
#endif

/* Добавление байта к CRC16-CCITT (0x1021 влево) */
#if !FASTCRC_CRC16_USE_TABLE
#define FASTCRC_CRC16_UPDATE8(crc, data)    do {                            \
    register FASTCRC_U16_TYPE x = (((crc) >> 8) ^ (data)) & 0xFF;           \
    x ^= x >> 4;                                                            \
    (crc) = (FASTCRC_U16_TYPE)(((crc) << 8) ^ (x << 12) ^ (x << 5) ^ x);    \
    } while (0)
#else
#define FASTCRC_CRC16_UPDATE8(crc, data)    do {                            \
    register FASTCRC_U8_TYPE idx = (FASTCRC_U8_TYPE)((data) ^ ((crc) >> 8));\
    (crc) = (FASTCRC_U16_TYPE)((crc) << 8) ^ g_fastcrc_crc16_table[idx];    \
    } while (0)
#endif

/* Добавление 16 бит к CRC16-CCITT (0x1021 влево) */
/* Наличие преимущества в скорости по сравнению с двумя CRC16_Add8() зависит от системы */
#define FASTCRC_CRC16_UPDATE16(crc, data)   do {                            \
    register FASTCRC_U16_TYPE t, y, z, q;                                   \
    t = (data);                                                             \
    y = (((crc) >> 8) ^ t) & 0xFF;                                          \
    z = ((crc) ^ (t >> 8)) & 0xFF;                                          \
    t = y ^ z;                                                              \
    q = (FASTCRC_U16_TYPE)((y ^ (y << 1)) << 12);                           \
    t ^= t >> 4;                                                            \
    t ^= y >> 3;                                                            \
    q ^= q >> 4;                                                            \
    z ^= z >> 4;                                                            \
    (crc) = (FASTCRC_U16_TYPE)(t ^ (t << 5) ^ (y << 4) ^ (z << 12) ^ q);    \
    } while (0)

/* Добавление байта к CRC16-MODBUS (0xA001 вправо) */
#if !FASTCRC_CRC16MB_USE_TABLE
#define FASTCRC_CRC16MB_UPDATE8(crc, data)  do {                            \
    register FASTCRC_U16_TYPE c, p;                                         \
    c = ((crc) ^ (data)) & 0xFF;                                            \
    p = c ^ (c >> 4);                                                       \
    p ^= p >> 2;                                                            \
    p ^= p >> 1;                                                            \
    p &= 1;                                                                 \
    c |= (FASTCRC_U16_TYPE)(p << 8);                                        \
    (crc) = (FASTCRC_U16_TYPE)(((crc) >> 8) ^ (c << 6) ^ (c << 7) ^ p);     \
    } while (0)
#else
#define FASTCRC_CRC16MB_UPDATE8(crc, data)  do {                            \
    register FASTCRC_U8_TYPE idx = (FASTCRC_U8_TYPE)((crc) ^ (data));       \
    (crc) = ((crc) >> 8) ^ g_fastcrc_crc16mb_table[idx];                    \
    } while (0)
#endif

/* Добавление 16 бит к CRC16-MODBUS (0xA001 вправо) */
#define FASTCRC_CRC16MB_UPDATE16(crc, data) do {                            \
    register FASTCRC_U16_TYPE c, p, d;                                      \
    c = (crc) ^ (data);                                                     \
    p = c ^ (c >> 8);                                                       \
    p ^= p >> 4;                                                            \
    p ^= p >> 2;                                                            \
    p ^= p >> 1;                                                            \
    p &= 1;                                                                 \
    d = (FASTCRC_U16_TYPE)(c << 14);                                        \
    c = (FASTCRC_U16_TYPE)((c >> 2) | (p << 14));                           \
    (crc) = (FASTCRC_U16_TYPE)(c ^ (c << 1) ^ d ^ (d >> 2) ^ p);            \
    } while (0)
/*================================================================================================*/

/*================================================================================================*/
/* Ссылки на таблицы для inline-функций */
#if ((FASTCRC_CRC4_ADD4 > 1) || (FASTCRC_CRC4_ADD8 > 1)) && FASTCRC_CRC4_USE_TABLE
extern FASTCRC_CONST_TAB FASTCRC_U8_TYPE g_fastcrc_crc4_table[16];
#endif
#if (FASTCRC_CRC8_ADD8 > 1) && FASTCRC_CRC8_USE_TABLE
extern FASTCRC_CONST_TAB FASTCRC_U8_TYPE g_fastcrc_crc8_table[256];
#endif
#if (FASTCRC_CRC8DS_ADD8 > 1) && FASTCRC_CRC8DS_USE_TABLE
extern FASTCRC_CONST_TAB FASTCRC_U8_TYPE g_fastcrc_crc8ds_table[256];
#endif
#if (FASTCRC_CRC16_ADD8 > 1) && FASTCRC_CRC16_USE_TABLE
extern FASTCRC_CONST_TAB FASTCRC_U16_TYPE g_fastcrc_crc16_table[256];
#endif
#if (FASTCRC_CRC16MB_ADD8 > 1) && FASTCRC_CRC16MB_USE_TABLE
extern FASTCRC_CONST_TAB FASTCRC_U16_TYPE g_fastcrc_crc16mb_table[256];
#endif
/*================================================================================================*/

/*================================================================================================*/
/* Вычисление CRC4-ITU (полином 0x3, сдвиг влево) */
/*================================================================================================*/

#if FASTCRC_CRC4_ADD4
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC4_ADD4 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC4_Add4           /* Добавление ниббла */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC4_ADD4 > 1
    {
    FASTCRC_CRC4_UPDATE4(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC4_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC4_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC4_Add8           /* Добавление байта */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC4_ADD8 > 1
    {
    FASTCRC_CRC4_UPDATE8(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC4_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U8_TYPE CRC4_Block8         /* Вычисление CRC4 блока байтов */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* Вычисление CRC8 (совместимая со старой библиотекой, полином 0x8C от Dallas, но сдвиг влево) */
/* Эта CRC плохая, только 6 значащих бит - полином неподходящий */
/*================================================================================================*/

#if FASTCRC_CRC8_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC8_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC8_Add8           /* Добавление байта */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC8_ADD8 > 1
    {
    FASTCRC_CRC8_UPDATE8(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC8_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U8_TYPE CRC8_Block8         /* Вычисление CRC8 блока байтов */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* Вычисление CRC8 (DALLAS, 0x8C, сдвиг вправо) */
/*================================================================================================*/

#if FASTCRC_CRC8DS_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC8DS_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC8DS_Add8         /* Добавление байта */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC8DS_ADD8 > 1
    {
    FASTCRC_CRC8DS_UPDATE8(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC8DS_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U8_TYPE CRC8DS_Block8       /* Вычисление CRC8DS блока байтов */
    (
    FASTCRC_U8_TYPE crc,            /* (вх)  - начальное значение */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* Вычисление CRC16 (CCITT, 0x1021, сдвиг влево) */
/*================================================================================================*/

#if FASTCRC_CRC16_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16_Add8         /* Добавление байта */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC16_ADD8 > 1
    {
    FASTCRC_CRC16_UPDATE8(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16_ADD16
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16_ADD16 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16_Add16        /* Добавление 16-битного слова (младший байт первым) */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    FASTCRC_U16_TYPE data           /* (вх)  - данные */
    )
#if FASTCRC_CRC16_ADD16 > 1
    {
    FASTCRC_CRC16_UPDATE16(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16_Block8       /* Вычисление CRC16 блока байтов */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16_BLOCK16
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16_Block16      /* Вычисление CRC16 блока 16-битных слов */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    const FASTCRC_U16_TYPE* pdata,  /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_words     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* Вычисление CRC16MB (MODBUS, 0xA001, сдвиг вправо) */
/*================================================================================================*/

#if FASTCRC_CRC16MB_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16MB_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16MB_Add8       /* Добавление байта */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    FASTCRC_U8_TYPE data            /* (вх)  - данные */
    )
#if FASTCRC_CRC16MB_ADD8 > 1
    {
    FASTCRC_CRC16MB_UPDATE8(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16MB_ADD16
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16MB_ADD16 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16MB_Add16      /* Добавление 16-битного слова (младший байт первым) */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    FASTCRC_U16_TYPE data           /* (вх)  - данные */
    )
#if FASTCRC_CRC16MB_ADD16 > 1
    {
    FASTCRC_CRC16MB_UPDATE16(crc, data);
    return crc;
    }
#else
    ;
#endif
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16MB_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16MB_Block8     /* Вычисление CRC16MB блока байтов */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16MB_BLOCK16
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16MB_Block16    /* Вычисление CRC16MB блока 16-битных слов */
    (
    FASTCRC_U16_TYPE crc,           /* (вх)  - начальное значение */
    const FASTCRC_U16_TYPE* pdata,  /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_words     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* Вычисление CRC32 (CCITT) */
/*================================================================================================*/

#if FASTCRC_CRC32_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U32_TYPE CRC32_Block8       /* Вычисление CRC32 блока байтов */
    (
    FASTCRC_U32_TYPE crc,           /* (вх)  - начальное значение (при первом блоке 0) */
    const FASTCRC_U8_TYPE* pdata,   /* (вх)  - данные */
    FASTCRC_SIZE_TYPE num_bytes     /* (вх)  - размер данных */
    );
/*------------------------------------------------------------------------------------------------*/
#endif
/*================================================================================================*/

#endif /* FAST_CRC_H_ */
