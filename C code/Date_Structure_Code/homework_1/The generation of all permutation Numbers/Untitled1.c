/*
#include<stdio.h>

#include<string.h>

int n,count;//n��ʾ�������е����ݵĸ�����count��ʾ��ͬ���еĸ���
void fun(char a[],int flag[],int i,char ans[])
{
    int j,k;
    if(i==n)
    {
    for(k=0;k<n;k++) printf("%c",ans[k]);
        printf("\n");
        count++;
        return ;
    }
    else
    {
        for(j=0;j<n;j++)
        {
            if(flag[j]==0)
            {
                ans[i]=a[j];

                flag[j]=1;
                fun(a,flag,i+1,ans);
                flag[j]=0;
            }
        }
    }
}

int main()
{
    int i;
    int flag[20];
    char a[20],ans[20];
    scanf("%s",a);
    //scanf("%d",&n);
    n=strlen(a);
    for(i=0;i<n;i++)
    {
        flag[i]=0;
        //a[i]=i+1;
    }
    count=0;
    fun(a,flag,0,ans);//�ӵ�0�ſ�ʼ����������ȷ��ÿһ��λ�õ���ֵ
    //printf("total:%d\n",count);
    return 0;
}*/
