/*================================================================================================*
 * ����������� ����� CRC-4, CRC-8, CRC-16 � CRC-32 � ���������� ��������� ����������
 *================================================================================================*/

#ifndef FAST_CRC_H_
#define FAST_CRC_H_

#include "fast_crc_cfg.h"

/*================================================================================================*/
/* ���������� 4-������� ������ � CRC4 (0x3 �����) */
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

/* ���������� ����� � CRC4 (0x3 �����) */
#define FASTCRC_CRC4_UPDATE8(crc, data)   do {                              \
    register FASTCRC_U8_TYPE d = (data);                                    \
    FASTCRC_CRC4_UPDATE4((crc), d >> 4);                                    \
    FASTCRC_CRC4_UPDATE4((crc), d);                                         \
    } while (0)

/* ���������� ����� � CRC8 (������������ 0x8C �����) */
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

/* ���������� ����� � CRC8-DALLAS (0x8C ������) */
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

/* ���������� ����� � CRC16-CCITT (0x1021 �����) */
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

/* ���������� 16 ��� � CRC16-CCITT (0x1021 �����) */
/* ������� ������������ � �������� �� ��������� � ����� CRC16_Add8() ������� �� ������� */
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

/* ���������� ����� � CRC16-MODBUS (0xA001 ������) */
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

/* ���������� 16 ��� � CRC16-MODBUS (0xA001 ������) */
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
/* ������ �� ������� ��� inline-������� */
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
/* ���������� CRC4-ITU (������� 0x3, ����� �����) */
/*================================================================================================*/

#if FASTCRC_CRC4_ADD4
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC4_ADD4 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC4_Add4           /* ���������� ������ */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U8_TYPE CRC4_Add8           /* ���������� ����� */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U8_TYPE CRC4_Block8         /* ���������� CRC4 ����� ������ */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* ���������� CRC8 (����������� �� ������ �����������, ������� 0x8C �� Dallas, �� ����� �����) */
/* ��� CRC ������, ������ 6 �������� ��� - ������� ������������ */
/*================================================================================================*/

#if FASTCRC_CRC8_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC8_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC8_Add8           /* ���������� ����� */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U8_TYPE CRC8_Block8         /* ���������� CRC8 ����� ������ */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* ���������� CRC8 (DALLAS, 0x8C, ����� ������) */
/*================================================================================================*/

#if FASTCRC_CRC8DS_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC8DS_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U8_TYPE CRC8DS_Add8         /* ���������� ����� */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U8_TYPE CRC8DS_Block8       /* ���������� CRC8DS ����� ������ */
    (
    FASTCRC_U8_TYPE crc,            /* (��)  - ��������� �������� */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* ���������� CRC16 (CCITT, 0x1021, ����� �����) */
/*================================================================================================*/

#if FASTCRC_CRC16_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16_Add8         /* ���������� ����� */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U16_TYPE CRC16_Add16        /* ���������� 16-������� ����� (������� ���� ������) */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    FASTCRC_U16_TYPE data           /* (��)  - ������ */
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
FASTCRC_U16_TYPE CRC16_Block8       /* ���������� CRC16 ����� ������ */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16_BLOCK16
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16_Block16      /* ���������� CRC16 ����� 16-������ ���� */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    const FASTCRC_U16_TYPE* pdata,  /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_words     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* ���������� CRC16MB (MODBUS, 0xA001, ����� ������) */
/*================================================================================================*/

#if FASTCRC_CRC16MB_ADD8
/*------------------------------------------------------------------------------------------------*/
#if FASTCRC_CRC16MB_ADD8 > 1
FASTCRC_INLINE
#endif
FASTCRC_U16_TYPE CRC16MB_Add8       /* ���������� ����� */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    FASTCRC_U8_TYPE data            /* (��)  - ������ */
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
FASTCRC_U16_TYPE CRC16MB_Add16      /* ���������� 16-������� ����� (������� ���� ������) */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    FASTCRC_U16_TYPE data           /* (��)  - ������ */
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
FASTCRC_U16_TYPE CRC16MB_Block8     /* ���������� CRC16MB ����� ������ */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

#if FASTCRC_CRC16MB_BLOCK16
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U16_TYPE CRC16MB_Block16    /* ���������� CRC16MB ����� 16-������ ���� */
    (
    FASTCRC_U16_TYPE crc,           /* (��)  - ��������� �������� */
    const FASTCRC_U16_TYPE* pdata,  /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_words     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif

/*================================================================================================*/
/* ���������� CRC32 (CCITT) */
/*================================================================================================*/

#if FASTCRC_CRC32_BLOCK8
/*------------------------------------------------------------------------------------------------*/
FASTCRC_U32_TYPE CRC32_Block8       /* ���������� CRC32 ����� ������ */
    (
    FASTCRC_U32_TYPE crc,           /* (��)  - ��������� �������� (��� ������ ����� 0) */
    const FASTCRC_U8_TYPE* pdata,   /* (��)  - ������ */
    FASTCRC_SIZE_TYPE num_bytes     /* (��)  - ������ ������ */
    );
/*------------------------------------------------------------------------------------------------*/
#endif
/*================================================================================================*/

#endif /* FAST_CRC_H_ */
