#ifndef CRC_H_
#define CRC_H_

#if defined(LES_CRC)
/*===============================================================================================*/
extern unsigned short eval_crc16   (unsigned short crc, const unsigned char *msg,
                                    unsigned msg_len);
extern unsigned char  eval_crc8    (unsigned char crc, const unsigned char *msg, unsigned msg_len);
extern unsigned char  eval_revcrc8 (unsigned char crc, const unsigned char *msg, unsigned msg_len);
/*===============================================================================================*/
#endif

#endif