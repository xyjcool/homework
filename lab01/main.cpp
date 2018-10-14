#include "mainwindow.h"
#include <QApplication>
#include<stdio.h>
#include <QDebug>
#include<algorithm>
#include<Qvector>
#include<iostream>
using namespace std;

    class students{
    public:
        int number;
        QString name;
        int course1;
        int course2;
    };

    void addStudents(QVector<students> &vec, int number, QString name, int course1, int course2){
        students stu;
        stu.number = number;
        stu.name = name;
        stu.course1 = course1;
        stu.course2 = course2;
        vec.push_back(stu);
    }

    // 按照进行排序 降序
    bool sortByName(const students &s1, const students &s2){
        return s1.name > s2.name;
    }

    // 按照课程1进行排序 降序
    bool sortByCourse1(const students &s1, const students &s2){
        return s1.course1 > s2.course1;
    }

    // 按照课程2进行排序 降序
    bool sortByCourse2(const students &s1, const students &s2){
        return s1.course2 > s2.course2;
    }

    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        QVector<students> vec;
        addStudents(vec, 1403140103, "武松",88, 80);
        addStudents(vec, 1403140101, "林冲",82, 76);
        addStudents(vec, 1403130209, "鲁智深",80, 72);
        addStudents(vec, 1403140102, "宋江",76, 85);

        //迭代器 iterato,输出
        QVector<students>::iterator it;


        qDebug()<< "排序前" << endl;
        for (it = vec.begin(); it != vec.end(); it++)
            {
               qDebug() << it ->number << it->name << it->course1 << it->course2 <<endl;
            }

        sort(vec.begin(), vec.end(), sortByName);
        qDebug() << "按姓名排序后:" << endl;
        for (it = vec.begin(); it != vec.end(); it++){
                   qDebug() << it ->number << it->name << it->course1 << it->course2 <<endl;
        }

        sort(vec.begin(), vec.end(), sortByCourse1);
        qDebug() << "按课程1排序后:" << endl;
        for (it = vec.begin(); it != vec.end(); it++){
                   qDebug() << it ->number << it->name << it->course1 << it->course2 <<endl;
        }

        sort(vec.begin(), vec.end(), sortByCourse2);
        qDebug() << "按课程2排序后:" << endl;
        for (it = vec.begin(); it != vec.end(); it++){
                   qDebug()<< it ->number << it->name << it->course1 << it->course2 <<endl;
        }
        return a.exec();
    }


