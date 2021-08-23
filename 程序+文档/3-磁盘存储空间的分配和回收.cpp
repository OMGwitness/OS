#include<bits/stdc++.h>
using namespace std;
int a[9][4] = {
    {3, 1, 2, 3},
    {3, 4, 5, 6},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 7, 8},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};  //初始的成组链接情况，a[i][0]表示空闲块数，a[i][1-3]表示空闲块号，a[i][1]指向下一个存放组信息的块
int ma[4] = {3, 1, 2, 3};  //专用块，初始为a[0]
int full[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //每个块是否被占用
int now = 0;  //当前ma指向的a的第一维
void show(){  //打印各空闲块组的情况
    if(ma[0] == 0){
        cout << "当前无空闲块！" << endl;
        return;
    }
    cout << "当前空闲块组情况如下：" << endl;
    int id = 1;
    int temp[4];
    memcpy(temp, ma, sizeof(ma));
    cout << "\t空闲块数\t" << "空闲块号\t" << "空闲块号\t" << "空闲块号" << endl;
    while(1){
        if(!temp[0])
            break;
        cout << "第" << id << "组：\t" << temp[0] << "\t\t";
        for(int i = 1; i <= 3; i++)
            if(temp[i])
                cout << temp[i] << "\t\t";
        for(int i = 1; i <= 3 - temp[0]; i++)
            cout << "-\t\t";
        cout << endl;
        if(!temp[1])
            break;
        else{
            id++;
            memcpy(temp, a[temp[1]], sizeof(a[temp[1]]));
        }
    }
}
int main(){
    show();
    cout << "是否需要申请或释放物理块？(y/n)";
    char flag1;
    cin >> flag1;
    while(flag1 == 'y'){
        cout << "需要申请物理块还是释放物理块？（申请输入1，释放输入2）";
        int flag2;
        cin >> flag2;
        if(flag2 == 1){
            if(ma[0] > 1){
                int id1 = 3;
                while (!ma[id1])
                    id1--;
                int id2 = ma[id1];
                cout << "已分配物理块" << id2 << endl;
                ma[id1] = 0;
                a[now][id1] = 0;
                ma[0]--;
                a[now][0]--;
                full[id2] = 1;
                show();
            }
            else if(ma[0] == 1){
                int id1 = 3;
                while (!ma[id1])
                    id1--;
                int id2 = ma[id1];
                cout << "已分配物理块" << id2 << endl;
                a[now][id1] = 0;
                a[now][0]--;
                full[id2] = 1;
                if(!ma[1])
                    for(int i = 0; i < 4; i++)
                        ma[i] = 0;
                else{
                    now = ma[1];
                    memcpy(ma, a[ma[1]], sizeof(a[ma[1]]));
                }
                show();
            }
            else
                cout << "无空闲块，无法分配！" << endl;
        }
        else{
            cout << "请输入需要释放的物理块号：";
            int id;
            cin >> id;
            if(!full[id])
                cout << "该块已为空闲块，无需释放！" << endl;
            else{
                cout << "已释放物理块" << id << endl;
                full[id] = 0;
                if(!ma[0]){
                    ma[0] = 1;
                    ma[1] = id;
                    a[0][0] = 1;
                    a[0][3] = id;
                    now = 0;
                }
                else if(ma[0] < 3){
                    int id1 = 3;
                    while(ma[id1])
                        id1--;
                    ma[id1] = id;
                    ma[0]++;
                    a[now][id1] = id;
                    a[now][0]++;
                }
                else{
                    for(int i = 0; i < 4; i++)
                        a[id][i] = ma[i];
                    ma[0] = 1;
                    ma[1] = id;
                    ma[2] = 0;
                    ma[3] = 0;
                    a[0][0] = 1;
                    a[0][1] = id;
                    a[0][2] = 0;
                    a[0][3] = 0;
                }
                show();
            }
        }
        cout << "是否需要申请或释放物理块？(y/n)";
        cin >> flag1;
    }
    return 0;
}