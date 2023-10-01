#include<stdio.h>
#include<string.h>

void MyFun(char *name)
{
        char MyBuf[20];
        strcpy(MyBuf, name);
        printf("You have entered: %s\n", MyBuf);
}
int main(int argc, char *argv[])
{
        printf("The size of the argument is: %d\n", sizeof(argv[1]));
        MyFun(argv[1]);
        return 0;
}