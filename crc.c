/*
 * ���������� ����������� ����.
 */

#include "crc.h"


/*===============================================================================================*/
#if defined(LES_CRC)
/*-----------------------------------------------------------------------------------------------*/
unsigned short eval_crc16(unsigned short crc, const unsigned char *msg, unsigned msg_len)
{
	/* ���������� 16-���������� ������������ ����������� ���� (��� - CRC)
	*  crc     - �������� �������� ���, 0 ��� ������ ������
	*  msg     - ��������� ����� ���������
	*  msg_len - ����� ������ � �����
	*  ���������� 16-��������� ���
	*/
	
	const unsigned short crc_poly = 0x1021;			/* ����������� ��������� */
	unsigned char        j;
	
	
	while (msg_len-- > 0)
	{
		crc ^= (unsigned short)*msg++ << 8;
		
		for (j = 8; j > 0; j--)				/* �������� ������� ���� */
		{
			if (crc & 0x8000)
			{
				crc = crc << 1 ^ crc_poly;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	
	return crc & 0xffff;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
unsigned char eval_crc8(unsigned char crc, const unsigned char *msg, unsigned msg_len)
{
	/*
	 * ������ 8-������ ����������� �����.
	 * ��������
	 *   ����������� 8-������ ����������� ���������� ���.
	 * ���������
	 *   crc     - ��������� �������� ����������� ����� (��� ������ ������ ������ ���� ����� 0);
	 *   msg     - ��������� �� ������ ������, �� ������� ����������� ����������� �����;
	 *   msg_len - ����� ��������������� �������.
	 * ������������ ��������
	 *   ���������� �������� 8-������ ����������� �����.
	 */

	const unsigned char crc8_poly = 0x8c;		/* ����������� ������� ��� 8-������ CRC */
	unsigned char       j;


	while (msg_len-- > 0)
	{
		crc ^= *msg++;
		for (j = 8; j > 0; j--)
		{
			if (crc & 0x80)	crc = (crc << 1) ^ crc8_poly;
			else            crc <<= 1;
		}
	}
	
	return crc & 0xff;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
unsigned char eval_revcrc8(unsigned char crc, const unsigned char *msg, unsigned msg_len)
{
	/*
	 * ������ 8-������ ����������� �����.
	 * ��������
	 *   ����������� 8-������ ����������� ���������� ���.
	 * ���������
	 *   crc     - ��������� �������� ����������� ����� (��� ������ ������ ������ ���� ����� 0);
	 *   msg     - ��������� �� ������ ������, �� ������� ����������� ����������� �����;
	 *   msg_len - ����� ��������������� �������.
	 * ������������ ��������
	 *   ���������� �������� 8-������ ����������� �����.
	 */

	const unsigned char revcrc8_poly = 0x8c;		/* ����������� ������� ��� 8-������ CRC */
	unsigned char       j;


	while (msg_len-- > 0)
	{
		crc ^= *msg++;
		for (j = 8; j > 0; j--)
		{
			if (crc & 0x01)	crc = (crc >> 1) ^ revcrc8_poly;
			else            crc >>= 1;
		}
	}
	
	return crc & 0xff;
}
/*-----------------------------------------------------------------------------------------------*/

#endif						/*#if defined(LES_CRC)*/
/*===============================================================================================*/