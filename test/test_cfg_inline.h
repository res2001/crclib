/*================================================================================================*
 * ������������ ���������� FAST_CRC
 *================================================================================================*/

#ifndef FAST_CRC_CFG_H_
#define FAST_CRC_CFG_H_

#include <stddef.h>
#include <stdint.h>

/*================================================================================================*/
/* ���� */
#define FASTCRC_U8_TYPE             uint8_t
#define FASTCRC_U16_TYPE            uint16_t
#define FASTCRC_U32_TYPE            uint32_t
#define FASTCRC_SIZE_TYPE           size_t
/* �������� ��� ������� � �������� */
#define FASTCRC_INLINE              static inline
#define FASTCRC_CONST_TAB           const

/* ��������� �������� CRC */
#define CRC4_START_VAL              0
#define CRC8_START_VAL              0
#define CRC8DS_START_VAL            0
#define CRC16_START_VAL             0
#define CRC16MB_START_VAL           0xFFFFU
#define CRC32_START_VAL             0
/*================================================================================================*/

/*================================================================================================*/
/* ����� ������� ������� ����������� ���� ��� �������, ���������� � ������� */
/* 0 = xor-shift, 1 = �� ������� �������� */
/* �������, ���������� � 16-������� �������, ������ ���������� ����� xor-shift */
#define FASTCRC_CRC4_USE_TABLE      0
#define FASTCRC_CRC8_USE_TABLE      0
#define FASTCRC_CRC8DS_USE_TABLE    0
#define FASTCRC_CRC16_USE_TABLE     0
#define FASTCRC_CRC16MB_USE_TABLE   0

/* ���������� ���������� ��������� ������� */
/* 0 = �� �������������, 1 = �������������, 2 = ������������� ��� inline (���� ��������������) */

#define FASTCRC_CRC4_ADD4           2   /* ���������� � CRC4 ������             (����� inline) */
#define FASTCRC_CRC4_ADD8           2   /* ���������� � CRC4 �����              (����� inline) */
#define FASTCRC_CRC4_BLOCK8         1   /* ���������� CRC4 ����� ������ */

#define FASTCRC_CRC8_ADD8           2   /* ���������� � CRC8 �����              (����� inline) */
#define FASTCRC_CRC8_BLOCK8         1   /* ���������� CRC8 ����� ������ */

#define FASTCRC_CRC8DS_ADD8         2   /* ���������� � Dallas CRC8 �����       (����� inline) */
#define FASTCRC_CRC8DS_BLOCK8       1   /* ���������� Dallas CRC8 ����� ������ */

#define FASTCRC_CRC16_ADD8          2   /* ���������� � CRC16 �����             (����� inline) */
#define FASTCRC_CRC16_ADD16         2   /* ���������� � CRC16 16-������� �����  (����� inline) */
#define FASTCRC_CRC16_BLOCK8        1   /* ���������� CRC16 ����� ������ */
#define FASTCRC_CRC16_BLOCK16       1   /* ���������� CRC16 ����� 16-������ ���� */

#define FASTCRC_CRC16MB_ADD8        2   /* ���������� � MODBUS CRC16 �����        (����� inline) */
#define FASTCRC_CRC16MB_ADD16       2   /* ���������� � MODBUS CRC16 16-��� ����� (����� inline) */
#define FASTCRC_CRC16MB_BLOCK8      1   /* ���������� MODBUS CRC16 ����� ������ */
#define FASTCRC_CRC16MB_BLOCK16     1   /* ���������� MODBUS CRC16 ����� 16-������ ���� */

#define FASTCRC_CRC32_BLOCK8        1   /* ���������� CRC32 ����� ������ */
/*================================================================================================*/

#endif /* FAST_CRC_CFG_H_ */
