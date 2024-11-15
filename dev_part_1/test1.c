#include<stdio.h>

void fun(int a){
    printf("%d\n",a);
}

int main(){
    void (*fun_ptr)(int) = &fun;
    (*fun_ptr)(10);

    int d = 0;
    for(int i=0;i<3;i++) {
        d+=1;
    }
    return d;
}