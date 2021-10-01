#ifndef __LED_DEF_H
#define __LED_DEF_H


#define LED_BRIGHTNESS_DEFAULT    0x04 /** 数码管亮度, 0x00 - 0x07 **/
#define LED_GRID_NBR        5 /** 数码管位数，实际使用位数 **/
#define LED_GRID_NBR_MAX    6 /** 数码管最大位数支持，驱动芯片决定 **/

#define DEF_LED_NONE 0x00
#define DEF_LED_0    0x3F /** 0 **/
#define DEF_LED_1    0x06
#define DEF_LED_2    0x5B
#define DEF_LED_3    0x4F
#define DEF_LED_4    0x66
#define DEF_LED_5    0x6D
#define DEF_LED_6    0x7D
#define DEF_LED_7    0x07
#define DEF_LED_8    0x7F
#define DEF_LED_9    0x6F
#define DEF_LED_A    0x77
#define DEF_LED_B    0x7C
#define DEF_LED_C    0x39
#define DEF_LED_D    0x5E
#define DEF_LED_E    0x79
#define DEF_LED_F    0x71 /** F **/
#define DEF_LED_P    0x73 /** P **/
#define DEF_LED_R    0x50 /** r **/
#define DEF_LED_O    0x5C /** o **/
#define DEF_LED_T    0x78 /** t **/
#define DEF_LED_L    0x38 /** L **/
#define DEF_LED_N    0x40 /** - **/
#define DEF_LED_DP   0x80 /** . **/

extern const unsigned char seg_code_tbl[];

#endif
