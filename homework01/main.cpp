#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#define n 0x12345678    //给定一个32位无符号整形数
#define Str(s)  _Str(s)
#define _Str(s)  #s     //嵌套，能正确的指向
//依次取出这个数的最高8位（HHI），次高8位(LHI)，次低8位(HLO)和最低8位(LLO)
#define HHI(n32) ((n32)>>24&0xff)   //右移24位后和oxff相与取出HHI
#define LHI(n32) ((n32)>>16&0xff)   //右移16位后和0xff相与取出LHI
#define HLO(n32) ((n32)>>8&0xff)    //右移8位后和0xff相与取出HLO
#define LLO(n32) ((n32)&0xff)       //直接与oxff相与取出LLO
#define MAX(x,y) ((x)>(y)?(x):(y)) //取最大值
#define MIN(x,y) ((x)<(y)?(x):(y))  //取最小值

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int n_new;
    QList<qint8> values;     //将取出的结果存放在QList<qint8>的对象value中
    qDebug()<<"原始值："<<Str(n)<<"=="<<n;
    values.append(HHI(n));
    values.append(LHI(n));
    values.append(HLO(n));
    values.append(LLO(n));
    qDebug("0x%x==%d 0x%x==%d 0x%x==%d 0x%x==%d",
           values.at(0),values.at(0),values.at(1),values.at(1),
           values.at(2),values.at(2),values.at(3),values.at(3));
    qDebug("最高8位和次高8位最大值：0x%x(%d)", MAX(values.at(0),values.at(1)),MAX(values.at(0),values.at(1))); //求高位中的最大值
    qDebug("次低8位和最低8位最小值：0x%x(%d)", MIN(values.at(3),values.at(2)),MIN(values.at(2),values.at(3))); //求低位中的最小值
    n_new=(values.at(2)<<24)+(values.at(0)<<16)+(values.at(3)<<8)+values.at(1);                            //按要求重新排列
    qDebug("重新组合后数值：0x%x(%d)",n_new,n_new);
    qDebug()<<"排序前："<<values;
       std::sort(values.begin(),values.end(),std::greater<qint8>());    // //使用sort函数降序排序
    qDebug()<<"排序后："<<values;
    return a.exec();
}
