#include<bits/stdc++.h>
using namespace std;
struct PCB{
    string name;  //作业名
    int bits; //作业位数
    vector<pair<int, int> > pageTable;  //页表

    PCB(string name, int bits){
        this->name = name;
        this->bits = bits;
    }
};
vector<PCB> PCBList;  //作业表
int bitMap[8][8];  //位示图
int empty = 64; //空闲块数
int main(){
    memset(bitMap, 0, sizeof(bitMap));
    char flag1;
    cout << "是否有作业装入或释放？(y/n)：";
    cin >> flag1;
    while(flag1 == 'y'){
        cout << "需要装入作业还是释放作业？（装入按1，释放按2）：";
        int flag2;
        cin >> flag2;
        if(flag2 == 1){
            cout << "请输入作业名：";
            string name;
            cin >> name;
            cout << "请输入作业需要的位数：";
            int bits;
            cin >> bits;
            PCB P(name, bits);
            if(bits > empty)
                cout << "作业所需位数超出空闲块数，不能分配！" << endl;
            else{
                int count = 0;
                for(int i = 0; i < 8; i++){  //遍历位示图，分配足够的物理块，建立页表
                    bool flag = false;
                    for(int j = 0; j < 8; j++){
                        if(!bitMap[i][j]){
                            bits--;
                            bitMap[i][j] = 1;
                            P.pageTable.push_back(make_pair(count++, i * 8 + j));
                            if(!bits){
                                flag = true;
                                break;
                            }
                        }
                    }
                    if(flag)
                        break;
                }
                PCBList.push_back(P);
                empty -= P.bits;
                cout << "分配成功！" << endl;
                cout << "分配后的空闲块数为" << empty << endl;
                cout << "作业" << P.name << "的页表如下：" << endl;
                cout << "页号\t块号" << endl;
                for(int i = 0; i < P.pageTable.size(); i++)
                    cout << P.pageTable[i].first << "\t" <<P.pageTable[i].second << endl;
                cout << "分配后的位示图如下：" << endl;
                for(int i = 0; i < 8; i++)
                    cout << "\t" << i;
                cout << endl;
                for(int i = 0; i < 8; i++){
                    cout << i;
                    for(int j = 0; j < 8; j++)
                        cout << "\t" << bitMap[i][j];
                    cout << endl;
                }
            }
        }
        else{
            cout << "请输入作业名：";
            string name;
            cin >> name;
            bool flag = true;
            for(vector<PCB>::iterator it = PCBList.begin(); it != PCBList.end(); it++){  //遍历页表，释放物理块
                if(it->name == name){
                    for(int i = 0; i < it->pageTable.size(); i++)
                        bitMap[it->pageTable[i].second / 8][it->pageTable[i].second % 8] = 0;
                    empty += it->bits;
                    PCBList.erase(it);
                    flag = false;
                    break;
                }
                it++;
            }
            if(flag)
                cout << "作业" << name << "不存在！" << endl;
            else{
                cout << "释放成功！" << endl;
                cout << "释放后的空闲块数为" << empty << endl;
                cout << "分配后的位示图如下：" << endl;
                for(int i = 0; i < 8; i++)
                cout << "\t" << i;
                cout << endl;
                for(int i = 0; i < 8; i++){
                    cout << i;
                    for(int j = 0; j < 8; j++)
                        cout << "\t" << bitMap[i][j];
                    cout << endl;
                }
            }
        }
        cout << endl << "是否有作业装入或释放？(y/n)：";
        cin >> flag1;
    }
    return 0;
}