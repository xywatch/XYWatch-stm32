#ifndef __MPU6050_H
#define __MPU6050_H
// #include "mpuiic.h"
#include "i2c_soft.h"
//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// ALIENTEK战舰STM32开发板V3
// MPU6050 驱动代码
// 正点原子@ALIENTEK
// 技术论坛:www.openedv.com
// 创建日期:2015/1/17
// 版本：V1.0
// 版权所有，盗版必究。
// Copyright(C) 广州市星翼电子科技有限公司 2009-2019
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

// MPU6050 AD0控制脚
// #define MPU_AD0_CTRL			PAout(15)	//控制AD0电平,从而控制MPU地址

// #define MPU_ACCEL_OFFS_REG		0X06	//accel_offs寄存器,可读取版本号,寄存器手册未提到
// #define MPU_PROD_ID_REG			0X0C	//prod id寄存器,在寄存器手册未提到
#define MPU_SELF_TESTX_REG 0X0D   // 自检寄存器X
#define MPU_SELF_TESTY_REG 0X0E   // 自检寄存器Y
#define MPU_SELF_TESTZ_REG 0X0F   // 自检寄存器Z
#define MPU_SELF_TESTA_REG 0X10   // 自检寄存器A
#define MPU_SAMPLE_RATE_REG 0X19  // 采样频率分频器
#define MPU_CFG_REG 0X1A          // 配置寄存器
#define MPU_GYRO_CFG_REG 0X1B     // 陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG 0X1C    // 加速度计配置寄存器
#define MPU_MOTION_DET_REG 0X1F   // 运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG 0X23      // FIFO使能寄存器
#define MPU_I2CMST_CTRL_REG 0X24  // IIC主机控制寄存器
#define MPU_I2CSLV0_ADDR_REG 0X25 // IIC从机0器件地址寄存器
#define MPU_I2CSLV0_REG 0X26      // IIC从机0数据地址寄存器
#define MPU_I2CSLV0_CTRL_REG 0X27 // IIC从机0控制寄存器
#define MPU_I2CSLV1_ADDR_REG 0X28 // IIC从机1器件地址寄存器
#define MPU_I2CSLV1_REG 0X29      // IIC从机1数据地址寄存器
#define MPU_I2CSLV1_CTRL_REG 0X2A // IIC从机1控制寄存器
#define MPU_I2CSLV2_ADDR_REG 0X2B // IIC从机2器件地址寄存器
#define MPU_I2CSLV2_REG 0X2C      // IIC从机2数据地址寄存器
#define MPU_I2CSLV2_CTRL_REG 0X2D // IIC从机2控制寄存器
#define MPU_I2CSLV3_ADDR_REG 0X2E // IIC从机3器件地址寄存器
#define MPU_I2CSLV3_REG 0X2F      // IIC从机3数据地址寄存器
#define MPU_I2CSLV3_CTRL_REG 0X30 // IIC从机3控制寄存器
#define MPU_I2CSLV4_ADDR_REG 0X31 // IIC从机4器件地址寄存器
#define MPU_I2CSLV4_REG 0X32      // IIC从机4数据地址寄存器
#define MPU_I2CSLV4_DO_REG 0X33   // IIC从机4写数据寄存器
#define MPU_I2CSLV4_CTRL_REG 0X34 // IIC从机4控制寄存器
#define MPU_I2CSLV4_DI_REG 0X35   // IIC从机4读数据寄存器

#define MPU_I2CMST_STA_REG 0X36 // IIC主机状态寄存器
#define MPU_INTBP_CFG_REG 0X37  // 中断/旁路设置寄存器 MPU_RA_INT_PIN_CFG MPU6050_RA_INT_PIN_CFG
#define MPU_INT_EN_REG 0X38     // 中断使能寄存器 MPU6050_RA_INT_ENABLE
#define MPU_INT_STA_REG 0X3A    // 中断状态寄存器

#define MPU_ACCEL_XOUTH_REG 0X3B // 加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG 0X3C // 加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG 0X3D // 加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG 0X3E // 加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG 0X3F // 加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG 0X40 // 加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG 0X41 // 温度值高八位寄存器
#define MPU_TEMP_OUTL_REG 0X42 // 温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG 0X43 // 陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG 0X44 // 陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG 0X45 // 陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG 0X46 // 陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG 0X47 // 陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG 0X48 // 陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG 0X63 // IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG 0X64 // IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG 0X65 // IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG 0X66 // IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG 0X67 // IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG 0X68  // 信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG 0X69 // 运动检测控制寄存器
#define MPU_USER_CTRL_REG 0X6A    // 用户控制寄存器
#define MPU_PWR_MGMT1_REG 0X6B    // 电源管理寄存器1
#define MPU_PWR_MGMT2_REG 0X6C    // 电源管理寄存器2
#define MPU_FIFO_CNTH_REG 0X72    // FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG 0X73    // FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG 0X74      // FIFO读写寄存器
#define MPU_DEVICE_ID_REG 0X75    // 器件ID寄存器

#define MPU_INT_STATUS_REG    0x3A

// 中断状态寄存器的位定义：
// Bit 7: Motion Detection Interrupt (0x80)
// Bit 6: Zero Motion Detection Interrupt (0x40)
// Bit 5: Free Fall Detection Interrupt (0x20)
// Bit 4: FIFO Buffer Overflow Interrupt (0x10)
// Bit 3: I2C Master Interrupt (0x08)
// Bit 2: Data Ready Interrupt (0x04)
// Bit 1: Wake on Motion Interrupt (0x02)
// Bit 0: Wake on Motion Detection Interrupt (0x01)

// 这些配置在 
// https://github.com/matthew-t-watson/Quadrocopter/blob/4d4c05e661b657b1649ef301fa238209fa21dac8/MPU6050.h#L49C1-L55C32
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F //运动检测阀值设置寄存器
#define MPU6050_RA_MOT_DUR 0x20 //运动检测时间阀值
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23

// 如果AD0脚(9脚)接地,IIC地址为0X68(不包含最低位).
// 如果接V3.3,则IIC地址为0X69(不包含最低位).
// 注意！！！！！！！！！！！！
// 默认0x68时会与DS3231的0xD0,0XD1冲突故选择AD0上拉至VCC
#define MPU_ADDR 0X69 // INV_MPU.c内的0x68已经均改为0x69

////因为模块AD0默认接GND,所以转为读写地址后,为0XD1和0XD0(如果接VCC,则为0XD3和0XD2)
// #define MPU_READ    0XD1
// #define MPU_WRITE   0XD0

u8 MPU_Init(void);                                  // 初始化MPU6050
u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf); // IIC连续写
u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf);  // IIC连续读
u8 MPU_Write_Byte(u8 reg, u8 data);                 // IIC写一个字节
u8 MPU_Read_Byte(u8 reg);                           // IIC读一个字节

u8 MPU_Set_Gyro_Fsr(u8 fsr);
u8 MPU_Set_Accel_Fsr(u8 fsr);
u8 MPU_Set_LPF(u16 lpf);
u8 MPU_Set_Rate(u16 rate);
u8 MPU_Set_Fifo(u8 sens);

short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx, short *gy, short *gz);
u8 MPU_Get_Accelerometer(short *ax, short *ay, short *az);
u8 MPU_Roll_Detect(float middle);
u8 MPU_Pitch_Detect(void);
u8 MPU_Pitch_Detect2(void);
u8 MPU_Roll_Detect2(float middle);
void MPU_INT_Init(void);
void MPU_GPIO_Config(void);
u8 MPU_movecheck(void);
#endif
