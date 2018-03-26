#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void delay(void)
{
	u32 i;
	for(i = 0;i < 5000000;i++)
	{}
}

void uart_init(u32 bound);

void uart_send_str(u8 *ch);

int main(int argc, char *argv[])
{
	SystemInit();
	uart_init(115200);//初始化串口

	GPIO_InitTypeDef GPIO_InitStructure;
	// GPIOC Periph clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	// Configure PC12 to mode: slow rise-time, pushpull output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // GPIO No. 12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // slow rise time
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // push-pull output
	GPIO_Init(GPIOE, &GPIO_InitStructure); // GPIOC init
	
	while(1)
	{
		uart_send_str((u8 *)"hello world!\r\n");
		GPIOE->BRR = 1 << 12;  // LED STAT off
		delay();delay();delay();
		GPIOE->BSRR = 1 << 12; //LED STAT on
		delay();
	}
}

void uart_send_str(u8 *ch)
{
	do
	{
		USART_SendData(UART4, *ch);
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC) != SET);
	}while(*ch++ != '\0');
}

void uart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能GPIOC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能UART4时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	//速度 50MHz
	
	
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	//USART 初始化设置 
	USART_InitStructure.USART_BaudRate = bound;						//一般设置为 9600/115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为 8 位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
	
	USART_Init(UART4, &USART_InitStructure); //初始化串口
	USART_Cmd(UART4, ENABLE); //使能串口
}


