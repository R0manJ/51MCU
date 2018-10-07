//这个是DS18B20温度传感器的学习过程代码。
#include<reg51.h>

#define uint unsigned int;
#define uchar unsigned char;

sbit DQ = P3^7;

//延时1ms ， 为什么？
void Delay1ms(uint i)
{
    uint x;
    for(;y>0;y--)
    {
        for(x=110;x>0;x--);
    }
}
int initDS18B20()
{
    uchar i;
    DQ = 0;
    i = 70;
    while(i--); // 延时642us？
    DQ = 1；
    while(DQ)
    {
        Delay1ms(1);
        i++;
        if(i>5)
        {
            return 0;
            //等待时间超过5ms ， 初始化失败。
        }
        return 1;
    }
}

//写入一个字节
void DS18B20WriteByte(uchar date)
{
    uint i , j;
    for( j=0;j<8;j++)
    {
        DQ = 0;
        i++;
        DQ = date & 0x01;
        i = 6;
        while(i --); //延时68us ，持续时间最少60us
        DQ = 1；
        date >> 1;
    }
}

//读取一个字节
uchar DS18B20ReadByte()
{
    uchar byte , bit;
    uint i , j;
    for(j=8;j>0;j--)
    {
        DQ = 0;
        i++;
        DQ = 1;
        i++;
        i++;//自加操作是为了延时6us；
        bit = DQ;
        byte = (byte >> 1)|(bite << 7);
        i = 4;
        while(i--);
    }
}

//发送转换温度的指令请求。
void DS18B20ChangeTempCom()
{
    initDS18B20();
    Delay1ms(1);
    DS18B20WriteByte(0xcc);
    DS18B20WriteByte(0x44);
    Delay1ms(100);
}

//发送读取温度的指令请求
void DS18B20ReadTempCom()
{
    initDS18B20;
    Delay1ms(1);
    DS18B20WriteByte(0xcc);
    DS18B20WriteByte(0xbe);
}

//读取温度
int DS18B20ReadTemp()
{
    int temp = 0;
    uchar tmh,tml;
    DS18B20ChangeTempCom();
    DS18B20ReadTempCom();
    tml = DS18B20ReadByte();
    tmh = DS18B20ReadByte();
    temp = tmh;
    temp <<= 8;
    temp |= tml;
    return temp;
}

void showTemp(int data)
{
    float tp;
    //获取date是源码，如果是负数的话，获取的为补码，所以可以直接判断值。
    if(date < 0)
    {
        date -= 1;
        date = ~date;
        tp = date;
        //乘与 2的 -4 次方，数值的权重运算问题。
        date = tp * 0.0625 * 100 + 0.5;
    }
    else
    {
        tp = date ; 
        date = tp * 0.0625 * 100 + 0.5;
    }
}

// 需要编写 串口通讯逻辑 ， 用于检查 DS18B20 的使用情况。
void main()
{
    while(1)
    {
        showTemp(DS18B20ReadTemp);
        //test git
    }
}