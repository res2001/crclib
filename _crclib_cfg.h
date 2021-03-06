#ifndef CRCLIB_CFG_H_
#define CRCLIB_CFG_H_


#define FAR_KEYWORD

/*===============================================================================================*/
/* Включение/выключение функций для вычисления различных контрольных сумм */
#define CRC7_EN (0)
#define CRC16_EN       1      /* 16-разрядная CRC */
#define CRC16TBL_EN    0      /* 16-разрядная CRC, вычисляемая табличным методом */
#define CRC8_EN        0      /* 8-разрядная CRC */
#define CRCMODBUS_EN   0      /* CRC шины MODBUS */
#define CRC8REVERSE_EN 0      /* 8-раязядная CRC (посчитана в обратном направлении) */
/*===============================================================================================*/

#endif /*#ifndef CRCLIB_CFG_H_*/
