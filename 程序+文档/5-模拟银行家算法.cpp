#include<bits/stdc++.h>
using namespace std;
int m, n;  //进程数和资源种类的数目
int Max[10][10], Allocation[10][10], Need[10][10];  //最大需求矩阵，已分配矩阵，需求矩阵
int Available[10]; //剩余矩阵
bool safe(){
    bool done[10];
    int temp[10];
    memset(done, false, sizeof(done));
    memcpy(temp, Available, sizeof(Available));
    bool flag1 = true;
    while(flag1){
        flag1 = false;
        for(int i = 0; i < m; i++){
            if(!done[i]){
                bool flag2 = true;
                for(int j = 0; j < n; j++){
                    if(temp[j] < Need[i][j]){
                        flag2 = false;
                        break;
                    }
                }
                if(flag2){
                    done[i] = true;
                    flag1 = true;
                    for(int j = 0; j < n; j++)
                        temp[j] += Allocation[i][j];
                    break;
                }
            }
        }
    }
    for(int i = 0; i < m; i++)
        if(!done[i])
            return false;
    return true;
}
void show(){
    cout << "系统当前的资源分配情况如下：" << endl;
	cout << "Process ";
    for(int i = 0; i < 2 * n - 1; i++)
        cout << " ";
    cout << "Max";
    for(int i = 0; i < 2 * n - 2; i++)
        cout << " ";
    cout << "     ";
    for(int i = 0; i < 2 * n - 5; i++)
        cout << " ";
    cout << "Allocation";
    for(int i = 0; i < 2 * n - 5; i++)
        cout << " ";
    cout << "     ";
    for(int i = 0; i < 2 * n - 2; i++)
        cout << " ";
    cout << "Need";
    for(int i = 0; i < 2 * n - 2; i++)
        cout << " ";
    cout << "     ";
    for(int i = 0; i < 2 * n - 4; i++)
        cout << " ";
    cout << "Available";
    for(int i = 0; i < 2 * n - 5; i++)
        cout << " ";
    cout << endl << "       ";
    for(int i = 0; i < 4; i++){
		for(int j = 0; j < n; j++)
			cout << setw(4) << (char)('A' + j);
        cout << "     ";
	}
	cout << endl << "       ";
    for(int i = 0; i < 3; i++){
		for(int j = 0; j < n; j++)
			cout << "    ";
        cout << "     ";
	}
    for(int i = 0; i < n; i++)
        cout << setw(4) << Available[i];
    cout << endl;
    for(int i = 0; i < m; i++){
        cout << "   " << i << "   ";
        for(int j = 0; j < n; j++)
            cout << setw(4) << Max[i][j];
        cout << "     ";
        for(int j = 0; j < n; j++)
            cout << setw(4) << Allocation[i][j];
        cout << "     ";
        for(int j = 0; j < n; j++)
            cout << setw(4) << Need[i][j];
        cout << endl;
    }
}
int main(){
    cout << "请输入进程数：";
    cin >> m;
    cout << "请输入资源种类的数目：";
    cin >> n;
    cout << "请输入一个 " << m << " * " << n << " 的最大需求矩阵：" << endl;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> Max[i][j];
    cout << "请输入一个 " << m << " * " << n << " 的分配矩阵：" << endl;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> Allocation[i][j];
    bool flag1 = true;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if(Need[i][j] < 0){
                cout << "输入非法！第" << i << "号进程的第" << (char)('A' + j) << "号资源的分配量超过最大需求！" << endl;
                flag1 = false;
            }
        }
        if(!flag1)
            break;
    }
    if(flag1){
        cout << "请输入一个 1 * " << n << " 的剩余矩阵：" << endl;
        for(int i = 0; i < n; i++)
            cin >> Available[i];
        show();
        if(safe()){
            cout << "当前为安全状态！" << endl;
            cout << "是否有进程请求资源？(y/n)";
            char flag2;
            cin >> flag2;
            while(flag2 == 'y'){
                int p;
                int r[10];
                cout << "请输入请求资源的进程号：";
                cin >> p;
                cout << "请输入一个 1 * " << n << " 的请求矩阵：" << endl;
                for(int i = 0; i < n; i++)
                    cin >> r[i];
                bool flag3 = true;
                for(int i = 0; i < n; i++){
                    if(Need[p][i] < r[i]){
                        cout << "输入非法！第" << (char)('A' + i) << "号资源的请求量超过需求量！无法分配！" << endl;
                        flag3 = false;
                    }
                    if(Available[i] < r[i]){
                        cout << "第" << (char)('A' + i) << "号资源的请求量超过剩余量！无法分配！" << endl;
                        flag3 = false;
                    }
                }
                if(flag3){
                    for(int i = 0; i < n; i++){
                        Allocation[p][i] += r[i];
                        Need[p][i] -= r[i];
                        Available[i] -= r[i];
                    }
                    if(safe())
                        cout << "分配后仍处于安全状态，分配成功！" << endl;
                    else{
                        cout << "若分配会处于不安全状态，无法分配！" << endl;
                        for(int i = 0; i < n; i++){
                            Allocation[p][i] -= r[i];
                            Need[p][i] += r[i];
                            Available[i] += r[i];
                        }
                    }
                }
                show();
                cout << endl << "是否有进程请求资源？(y/n)";
                cin >> flag2;
            }
        }
        else
            cout << "当前为不安全状态！" << endl;
    }
    return 0;
}