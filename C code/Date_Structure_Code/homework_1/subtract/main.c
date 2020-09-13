#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char a[81],b[81];
void Dleadingzero(char ch[])//删除前导零
{
    int i;
    for(i=0;ch[i]!='\0';i++)
    {
        if(ch[i]=='0')continue;
        else break;
    }
    strcpy(ch,ch+i);
}
int chcmp(char a[],char b[])//比较a，b的大小
{
    int lena=strlen(a);
    int lenb=strlen(b);
    if(lena>lenb)return 1;//strcmp读取到任意一个'\0'即结束判断
    else if(lena<lenb)return -1;//所以需要先判断长度
    else return strcmp(a,b);

}
void invert (char str [] )//翻转str //ps:抄的作业题填空4
{
    int i,j,k;
    for(i=0,j=strlen(str)-1;i<j;i++,j--)
    {
        k=str[i];
        str[i]=str[j];
        str[j]=k;
    }
}
void putans(char a[])
{
    int i;
    for(i=strlen(a)-1;i>=0;i--)
    {
        if(a[i]!='0')break;
    }

    for(;i>=0;i--)
        putchar(a[i]);
}
void subtract_long(char a[],char b[])//计算a-b
{
    invert(a);
    invert(b);
    int i;
    int lena=strlen(a);
    int lenb=strlen(b);
    int len=(lena<lenb)?lena:lenb;//最短
    for(i=0;i<len;i++)
    {
        a[i]+='0'-b[i];
        if(a[i]<'0'){
            a[i+1]--;
            a[i]+=10;
        }
    }
    for(i=0;i<lena;i++)
    {
        if(a[i]<'0'){
            a[i+1]--;
            a[i]+=10;
        }
    }
    putans(a);
}

int main()
{
    int flag;
    scanf("%s%s",&a,&b);
    Dleadingzero(a);
    Dleadingzero(b);
    flag=chcmp(a,b);
    //printf("%s\n%s\n******\n%d\n",a,b,flag);
    if(flag==0)putchar('0');
    else if(flag>0)subtract_long(a,b);
    else {
            putchar('-');
            subtract_long(b,a);
    }
    return 0;
}
