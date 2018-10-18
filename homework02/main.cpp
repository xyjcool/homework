#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>

namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

//使用结构体存放成绩信息的数据类型
typedef struct{
    QStringList stu;
} studData;


// 运算符重载函数，可以直接输出studData结构
QDebug operator << (QDebug d, const studData &data) {
    for(int i=0;i<data.stu.size();i++)
            d.noquote().nospace()<<QString(data.stu.at(i))<<"\t" ;
    return d;
}

// 比较类，用于std::sort第三个参数
class myCmp {
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};

//重载函数，用qlist把整体排序规则定好
bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    result=(d1.stu.at(currentColumn)>d2.stu.at(currentColumn));
    return result;

}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();

private:
    QString tempFile;
    QList<studData> data;
    studData header ;          //数据表头

};

void ScoreSorter::readFile(){

    QFile file(tempFile);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败。\n"<<endl;

    }

    //把表头和数据的读入分开，存入不同的位置，方便后期排序（解决了表头不需要排序的问题）
    QString header1(file.readLine());
        header.stu = header1.split(" ", QString::SkipEmptyParts);//去除末尾的\n
        if((header.stu).last() == "\n") header.stu.removeLast();
        studData  Lastdata;
        while(!file.atEnd())
        {
            QByteArray line=file.readLine();
            QString str(line);
            Lastdata.stu = str.split(" ", QString::SkipEmptyParts);//去末尾'\n' 如果是空 qlist()  则摒弃,否则添加到 data
            if((Lastdata.stu).last() == "\n")
                Lastdata.stu.removeLast();
            if(Lastdata.stu.size()==0)
                continue;
            data.append(Lastdata);
    }
        file.close();
    }


void ScoreSorter::doSort(){

    for(int i=0;i<header.stu.size();i++)
        {
            myCmp cmp(i);
            std::sort(data.begin(),data.end(),cmp);
            qDebug()<<"排序后输出，当前排序第"<<i+1<<"列";
            //单独输出表头
            qDebug()<<"\t"<<(header);
            //输出数据
            for(int i=0;i<data.size();i++)
                qDebug()<<data.at(i);
            qDebug()<<"-----------------------------------------------------------------------\n";
        }
}


// 构造函数定义-分配资源给文件名
ScoreSorter::ScoreSorter(QString dataFile){

    tempFile=dataFile;
}

 // 自定义qDebug,使其输出文本文件
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   QFile file("sort_data.txt");
   file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text );
   QTextStream out(&file);
   out << msg  << endl;
   out.setCodec("UTF-8");
   file.flush();
   file.close();

   QTextStream ts (stdout);
   ts << msg << endl;
   file.flush();
   file.close();
}

int main()
{
    qInstallMessageHandler(myMessageOutput);
    QString datafile = "D:/Dev/homework/All-homework/homework/homework02/data.txt";

    // 如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
