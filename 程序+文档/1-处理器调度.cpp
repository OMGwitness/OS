#include<bits/stdc++.h>
using namespace std;
struct PCB{
    string name;  //进程名
    struct PCB *next;  //指向下一个PCB的指针
    int requestTime;  //要求运行时间
    int runTime;  //已运行时间
    char condition;  //状态

    PCB(string name){
        this->name = name;
        this->next = NULL;
        this->runTime = 0;
        this->condition = 'R';
    }
};
int main(){
    PCB P1("P1");
    PCB P2("P2");
    PCB P3("P3");
    PCB P4("P4");
    PCB P5("P5");
    P1.next = &P2;
    P2.next = &P3;
    P3.next = &P4;
    P4.next = &P5;
    P5.next = &P1;
    cout << "请输入进程P1的要求运行时间：";
    cin >> P1.requestTime;
    cout << "请输入进程P2的要求运行时间：";
    cin >> P2.requestTime;
    cout << "请输入进程P3的要求运行时间：";
    cin >> P3.requestTime;
    cout << "请输入进程P4的要求运行时间：";
    cin >> P4.requestTime;
    cout << "请输入进程P5的要求运行时间：";
    cin >> P5.requestTime;
    PCB *former = &P5, *now = &P1;
    int time = 0;
    while(1){
        now->runTime++;
        cout << "在时间段" << time << "-" << ++time << "内" << endl;
        cout << "进程" << now->name << "在运行" << endl;
        if(now->requestTime <= now->runTime){  //当前进程执行完毕
            if(now->next == now){  //当前进程的下一个进程还是当前进程，说明全部执行完毕
                cout << "运行后所有进程执行完毕" <<endl;
                break;
            }
            now->condition = 'E';
            former->next = now->next;
        }
        else
            former = former->next;
        now = now->next;
        PCB *temp = now;
        cout << "运行后就绪队列情况为";
        cout << temp->name;
        while(temp->next != now){ //temp从now开始遍历循环队列
            temp = temp->next;
            cout << " -> " << temp->name;
        }
        cout << endl << endl;
    }
    return 0;
}