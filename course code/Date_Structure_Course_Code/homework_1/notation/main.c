#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char a[100],b[100];
int Find_dot(char a[])
{
    int i;
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]=='.')break;
    }
    //if(a[i]=='\0') i=-1;
    return i;
}
int Check_zero(char b[])
{
    int i;
    for(i=0;b[i]!='\0';i++)
    {
        if(b[i]!='0')break;
    }
    return i;
}
int main()
{
    int point,len;
    scanf("%s",&a);
    point=Find_dot(a);  //�ָ�
    /*if(point==-1)
    {
        printf("%s",a);
        return 0;
    }*/
    a[point]='\0';      //a�ַ�������
    strcpy(b,a+point+1);

    len=strlen(a);

    if(len==1){
        if(a[0]=='0'){  //��С��
                int count_zero,power;
                count_zero=Check_zero(b);
                if((strlen(b)-count_zero)!=1){
                    printf("%c.",*(b+count_zero));
                    printf("%s",b+count_zero+1);
                    power=count_zero+1;
                    printf("e-%d",power);
                }
                else {
                    printf("%s",b+count_zero);
                    power=count_zero+1;
                    printf("e-%d",power);

                }
        }
        else {          //һλ����
            printf("%s.%se0",a,b);
        }
    }
    else {
        int power=len-1;
        putchar(a[0]);
        printf(".%s%se%d",a+1,b,power);
    }

    return 0;
}
//  

