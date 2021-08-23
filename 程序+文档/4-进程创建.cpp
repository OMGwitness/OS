#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main() {
    pid_t pid1 = fork();
    if(pid1 == 0){
        printf("B\n");
        return 0;
    }
    else{
        pid_t pid2 = fork();
        if(pid2 == 0){
            printf("C\n");
            return 0;
        }
        printf("A\n");
        return 0;
    }
}