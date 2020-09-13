#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char pre='\0',now='\0',mid='\0';
int checktype(char ch)
{
    switch(ch)
    {
        case 'A'...'Z': return 1;
        break;
        case 'a'...'z': return 2;
        break;
        case '0'...'9': return 3;
        break;
        default : return -1;
    }
}
int check(char a,char c)//为真时不展开
{
    if(a>=c)return 1;
    else if(checktype(a)!=checktype(c)||checktype(a)==-1)return 1;
    else return 0;
}
void expand(char a,char c)
{
    if(check(a,c)){
        putchar('-');
    }
    else {
            int i;
            for(i=1;i<(c-a);i++)//i=0&i=c-a在主函数输出过了
            putchar(a+i);       //mid->pre->i=0
    }                           //now->mid->i=c-a
}
int main()
{
    int fl=0;
    fl=scanf("%c",&mid);
    do{
        fl=scanf("%c",&now);
        if(mid=='-'){
            expand(pre,now);
        }
        else putchar(mid);

        pre=mid;    //缓冲字符
        mid=now;
        if(now=='\n'||now=='\r'||fl==EOF)break;
    }while(1);

    return 0;
}
