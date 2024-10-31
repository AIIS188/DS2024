#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include "D:\DS24\DS24\exp1\Vertor.h"





int main(){
    //（1）
    Vector<Complex> A(10000);
    for(int i;i<10000;i++){
        
        int j=rand()%100*rand()%100,k=rand()%100*rand()%100;
        A[i].reset(j,k);  
    }
    A.setsize(10000);
    
    Complex B(10,10);
    //插入
    A.insert(3,B);
    A.insert(4,B);
    A.insert(5,B);
    //无序去重
    A.deduplicate();
    A.msort();
    //置乱
    // A.unsort();
    // A.traverse(allprint1);
    // cout<<"\n"<<A.find(B)<<"\n";
    //删除
    // A.remove(0);
    // A.traverse(allprint1);
    //无序去重
    // A.deduplicate();
    // 有序去重
    // A.uniquify();
    
    // A.traverse(allprint1);
    //（2）
    Vector<Complex> C(A),D(A);//逆序，乱序向量生成
    C.resort();
    D.unsort();
//时间对象声明
    clock_t start_time,end_time;
    double total_time;
//顺序排序时间
    Vector<Complex> A1(A),A2(A);
    start_time=clock();
    A1.sort();//冒泡排序
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"冒泡顺序排序所用时间："<<total_time<<"\n";

    start_time=clock();
    A2.msort();
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"归并顺序排序所用时间："<<total_time<<"\n";
//乱序排序时间
    Vector<Complex> D1(D),D2(D);
    start_time=clock();
    D1.sort();
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"冒泡乱序排序所用时间："<<total_time<<"\n";

    start_time=clock();
    D2.msort();
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"归并乱序排序所用时间："<<total_time<<"\n";
//逆序排序时间
    Vector<Complex> C1(C),C2(C);
    start_time=clock();
    C1.sort();
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"冒泡逆序排序时间：" <<total_time<<"\n";

    start_time=clock();
    C2.msort();
    end_time=clock();
    total_time= double(end_time - start_time) / CLOCKS_PER_SEC;
    cout<<"归并逆序排序时间："<<total_time<<"\n";
//(3)返回子向量输出验证
    Vector<Complex> search_A;
    search_A=A.findmodel(100,120);
    search_A.traverse(allprint1);
};