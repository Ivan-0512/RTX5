
#include "spi_led.h"
#include "utility.h"

//片选拉高，器件不选通
#define LED_CS_HIGH()    gpio_bit_set(GPIOB, GPIO_PIN_12);
//片选拉低，器件选通
#define LED_CS_LOW()     gpio_bit_reset(GPIOB, GPIO_PIN_12);

const uint8_t seg_code_tbl[] =
{
	0x3F, /** 0 **/
	0x06,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x6F,
	0x77,
	0x7C,
	0x39,
	0x5E,
	0x79,
	0x71, /** F **/
};

static void TM1620_Delay_us( unsigned short timeus );
static void displayCalValCh(uint8_t num);

static void _rcu_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_SPI1);
}

static void _gpio_config(void)
{
    /* SPI1 GPIO configuration: SCK/PB13, MISO/PB14, MOSI/PB15 */
    gpio_af_set(GPIOB, GPIO_AF_0, GPIO_PIN_13 |GPIO_PIN_15);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 |GPIO_PIN_15);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 |GPIO_PIN_15);
	
	/* SPI1 CS*/
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_bit_set(GPIOB, GPIO_PIN_12);
}

static void _spi_config(void)
{
    spi_parameter_struct spi_init_struct;

    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(SPI1);
    spi_struct_para_init(&spi_init_struct);
    
    /* SPI0 parameter configuration */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_64;
    spi_init_struct.endian               = SPI_ENDIAN_LSB;
    spi_init(SPI1, &spi_init_struct);
    
    /* configure SPI1 byte access to FIFO */
    spi_fifo_access_size_config(SPI1, SPI_BYTE_ACCESS);
}

uint8_t LED_WriteByte(uint8_t Data)
{
	while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE));
	spi_i2s_data_transmit(SPI1, Data);
	return 0;
}

static void TM1620_Delay_us( unsigned short timeus )
{
	unsigned char ix;
	while(timeus--){
		for(ix=0; ix<150; ix++)
		{
			__NOP();
		}
	}
}

void spiLedInit(SegLed *seg_led)
{
	uMemSet((void *)seg_led->buf, 0x00, LED_GRID_NBR_MAX);
	seg_led->hidden = 0;
	
    _rcu_config();
    _gpio_config();
    _spi_config();
    spi_enable(SPI1);
}

void
ledRefresh(SegLed *seg_led)
{
	uint8_t ix;
	uint8_t ctr;
	
	if(seg_led->hidden) {
		ctr = 0x80;
	} else {
		//1.设置显示模式
		LED_CS_LOW();
		TM1620_Delay_us(5);
		LED_WriteByte(0x02);//6位8段
		TM1620_Delay_us(5);
		LED_CS_HIGH();
		TM1620_Delay_us(5);
		
		//2.设置数据命令
		LED_CS_LOW();
		TM1620_Delay_us(5);
		LED_WriteByte(0x40);//采用地址自动加1
		TM1620_Delay_us(5);
		LED_CS_HIGH();
		TM1620_Delay_us(5);
		
		//3.设置显示地址及显示数据
		LED_CS_LOW();
		TM1620_Delay_us(5);
		LED_WriteByte(0xC0);//设置起始地址（0xC0）显示地址范围为0xC0-0xCB共12个BYTE
		for(ix=0; ix<=LED_GRID_NBR_MAX; ix++) {
			LED_WriteByte(seg_led->buf[ix]);//GR1 连续写入最多12个数据
			LED_WriteByte(0x00);
		}
		TM1620_Delay_us(5);
		LED_CS_HIGH();
		TM1620_Delay_us(5);
		
		ctr = 0x88 | LED_BRIGHTNESS_DEFAULT;
	}
	//4.显示控制命令
	LED_CS_LOW();
	TM1620_Delay_us(5);
	LED_WriteByte(ctr);//设置脉冲宽度11/16,BIT0-BIT2控制显示亮度,BIT3位显示开关控制
	TM1620_Delay_us(5);
	LED_CS_HIGH();
	TM1620_Delay_us(5);
}
