#include "adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

void Adc_Init(void) // PA0
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); // 使能ADC1通道时钟

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M	 1.17us的采样周期

    // PA0 作为模拟通道输入引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC1); // 复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  // ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       // 模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 // 模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // 顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);                                 // 根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

    ADC_Cmd(ADC1, ENABLE); // 使能指定的ADC1

    ADC_ResetCalibration(ADC1); // 使能复位校准

    while (ADC_GetResetCalibrationStatus(ADC1))
        ; // 等待复位校准结束

    ADC_StartCalibration(ADC1); // 开启AD校准

    while (ADC_GetCalibrationStatus(ADC1))
        ; // 等待校准结束

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 使能指定的ADC1的软件转换启动功能
}

// 获得ADC值
// ch:通道值 0~3
u16 Get_Adc(u8 ch)
{
    // 设置指定ADC的规则组通道，一个序列，采样时间
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5); // 使用最长采样时间提高精度

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 使能指定的ADC1的软件转换启动功能

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        ; // 等待转换结束

    return ADC_GetConversionValue(ADC1); // 返回最近一次ADC1规则组的转换结果
}

// 获取通道ch的转换值，取times次,然后平均
// ch:通道编号
// times:获取次数
// 返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u8 ch, u8 times)
{
    u32 temp_val = 0;
    u8 t;
    u16 max_val = 0, min_val = 0xFFFF;
    u16 current_val;
    
    // 丢弃前4次采样
    for(t = 0; t < 4; t++) {
        Get_Adc(ch);
        delay_us(50); // 增加采样间隔到50us
    }

    // 正式采样，去除最大最小值
    for (t = 0; t < times; t++)
    {
        current_val = Get_Adc(ch);
        
        // 记录最大最小值
        if(current_val > max_val) max_val = current_val;
        if(current_val < min_val) min_val = current_val;
        
        temp_val += current_val;
        delay_us(50); // 增加采样间隔到50us
    }
    
    // 去除最大最小值后取平均
    if(times > 2) {
        temp_val = (temp_val - max_val - min_val) / (times - 2);
    } else {
        temp_val = temp_val / times;
    }

    return temp_val;
}
