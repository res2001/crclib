/*================================================================================================*
 * ������������ ���������� FAST_CRC
 *================================================================================================*/

#ifndef FAST_CRC_CFG_H_
#define FAST_CRC_CFG_H_

#include <stdint.h>

/*================================================================================================*/
/* ���� */
#define FASTCRC_U8_TYPE             uint8_t
#define FASTCRC_U16_TYPE            uint16_t
#define FASTCRC_U32_TYPE            uint32_t
#define FASTCRC_SIZE_TYPE           size_t

/* ��������� �������� CRC */
#define CRC16_START_VAL             0
#define CRC32_START_VAL             0
/*================================================================================================*/

/*================================================================================================*/
/* ���������� ���������� ��������� ������� */
#define FASTCRC_CRC16_ADD8          1   /* ���������� � CRC16 ����� */
#define FASTCRC_CRC16_ADD16         1   /* ���������� � CRC16 16-������� ����� */
#define FASTCRC_CRC16_BLOCK8        1   /* ���������� CRC16 ����� ������ */
#define FASTCRC_CRC16_BLOCK16       1   /* ���������� CRC16 ����� 16-������ ���� */
#define FASTCRC_CRC32_BLOCK8        1   /* ���������� CRC32 ����� ������ */
/*================================================================================================*/

#endif /* FAST_CRC_CFG_H_ */
