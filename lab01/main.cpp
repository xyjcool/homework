#include "mainwindow.h"
#include <QApplication>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    void addStudents(vector<students> &vec, int age, string name){
        students stu;
        stu.age = age;
        stu.name = name;
        vec.push_back(stu);

    }

    // 按照年龄进行排序 升序
    bool sortByAge(const students &s1, const students &s2){
        return s1.age < s2.age;
    }


    // 先按照年龄进行排序 年纪一样 按照姓名排序
    bool sortByAll(const students &s1, const students &s2){
        if(s1.age < s2.age) return true;
        else if(s1.age > s2.age) return false;
        else return s1.name < s2.name;
    }
    int main(){
        vector<students> vec;
        addStudents(vec, 20, "zhangming");
        addStudents(vec, 20, "xiaoming");
        addStudents(vec, 20, "xiaoming2");
        addStudents(vec, 23, "xiaohong");
        addStudents(vec, 22, "xiaofei");
        addStudents(vec, 27, "xiaogang");
        cout << "排序前:" << endl;
        for(vector<students>::iterator iter = vec.begin(); iter != vec.end(); ++iter){
            cout << (*iter).age << " " << (*iter).name << endl;
        }
        sort(vec.begin(), vec.end(), sortByAll);
        cout << "排序后:" << endl;
        for(vector<students>::iterator iter = vec.begin(); iter != vec.end(); ++iter){
            cout << (*iter).age << " " << (*iter).name << endl;
        }
    }

    return a.exec();
}
