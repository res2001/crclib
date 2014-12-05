/*================================================================================================*
 * Конфигурация библиотеки FAST_CRC
 *================================================================================================*/

#ifndef FAST_CRC_CFG_H_
#define FAST_CRC_CFG_H_

#include <stddef.h>
#include <stdint.h>

/*================================================================================================*/
/* Типы */
#define FASTCRC_U8_TYPE             uint8_t
#define FASTCRC_U16_TYPE            uint16_t
#define FASTCRC_U32_TYPE            uint32_t
#define FASTCRC_SIZE_TYPE           size_t
/* Префиксы для функций и констант */
#define FASTCRC_INLINE              static inline
#define FASTCRC_CONST_TAB           const

/* Начальные значения CRC */
#define CRC4_START_VAL              0
#define CRC8_START_VAL              0
#define CRC8DS_START_VAL            0
#define CRC16_START_VAL             0
#define CRC16MB_START_VAL           0xFFFFU
#define CRC32_START_VAL             0
/*================================================================================================*/

/*================================================================================================*/
/* Выбор способа расчета контрольных сумм для функций, работающих с байтами */
/* 0 = xor-shift, 1 = по таблице констант */
/* Функции, работающие с 16-битными словами, всегда используют метод xor-shift */
#define FASTCRC_CRC4_USE_TABLE      0
#define FASTCRC_CRC8_USE_TABLE      0
#define FASTCRC_CRC8DS_USE_TABLE    0
#define FASTCRC_CRC16_USE_TABLE     0
#define FASTCRC_CRC16MB_USE_TABLE   0

/* Разрешение компиляции отдельных функций */
/* 0 = не компилировать, 1 = компилировать, 2 = компилировать как inline (если поддерживается) */

#define FASTCRC_CRC4_ADD4           2   /* добавление в CRC4 ниббла             (можно inline) */
#define FASTCRC_CRC4_ADD8           2   /* добавление в CRC4 байта              (можно inline) */
#define FASTCRC_CRC4_BLOCK8         1   /* вычисление CRC4 блока байтов */

#define FASTCRC_CRC8_ADD8           2   /* добавление в CRC8 байта              (можно inline) */
#define FASTCRC_CRC8_BLOCK8         1   /* вычисление CRC8 блока байтов */

#define FASTCRC_CRC8DS_ADD8         2   /* добавление в Dallas CRC8 байта       (можно inline) */
#define FASTCRC_CRC8DS_BLOCK8       1   /* вычисление Dallas CRC8 блока байтов */

#define FASTCRC_CRC16_ADD8          2   /* добавление в CRC16 байта             (можно inline) */
#define FASTCRC_CRC16_ADD16         2   /* добавление в CRC16 16-битного слова  (можно inline) */
#define FASTCRC_CRC16_BLOCK8        1   /* вычисление CRC16 блока байтов */
#define FASTCRC_CRC16_BLOCK16       1   /* вычисление CRC16 блока 16-битных слов */

#define FASTCRC_CRC16MB_ADD8        2   /* добавление в MODBUS CRC16 байта        (можно inline) */
#define FASTCRC_CRC16MB_ADD16       2   /* добавление в MODBUS CRC16 16-бит слова (можно inline) */
#define FASTCRC_CRC16MB_BLOCK8      1   /* вычисление MODBUS CRC16 блока байтов */
#define FASTCRC_CRC16MB_BLOCK16     1   /* вычисление MODBUS CRC16 блока 16-битных слов */

#define FASTCRC_CRC32_BLOCK8        1   /* вычисление CRC32 блока байтов */
/*================================================================================================*/

#endif /* FAST_CRC_CFG_H_ */
