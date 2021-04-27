#include<stdio.h>
#include<stdlib.h>
int chess[19][19];


int main()
{
    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    scanf("%d",&chess[i][j]);
    for(int i=0;i<19;i++)//行
    for(int j=0;j<19;j++)//列
    {
        if(chess[i][j]==0)continue;
        int com=chess[i][j],flag1=0,flag2=0,flag3=0,flag4=0;
    
        for(int k=1;k<4;k++){//右
            if(j+k<19){
                if(com!=chess[i][j+k]){flag1=0;break;}
                else flag1=1;
            }
        }
        if(flag1==1){
            if(j+4<19){
                if(chess[i][j+4]!=0)flag1=0;
            }
            else flag1=0;
        }
        for(int k=1;k<4;k++){//下
            if(i+k<19){
                if(com!=chess[i+k][j]){flag2=0;break;}
                flag2=1;
            }
        }
        if(flag2==1){
            if(i+4<19){
                if(chess[i+4][j]!=0)flag2=0;
            }
            else flag2=0;
        }
        for(int k=1;k<4;k++){//左下
            if(i+k<19&&j-k>=0){
                if(com!=chess[i+k][j-k]){flag3=0;break;}
                else flag3=1;
            }
        }
        if(flag3==1){
            if(i+4<19&&j-4>=0){
                if(chess[i+4][j-4]!=0)flag3=0;
            }
            else flag3=0;
        }
        for(int k=1;k<4;k++){//右下
            if(i+k<19&&j+k<19){
                if(com!=chess[i+k][j+k]){flag4=0;break;}
                else flag4=1;
            }
        }
        if(flag4==1){
            if(i+4<19&&j+4<19){
                if(chess[i+4][j+4]!=0)flag4=0;
            }
            else flag4=0;
        }
        if(flag1||flag2||flag3||flag4){
            printf("%d:%d,%d",com,i+1,j+1);
            return 0;
        }
    }
    printf("No");
    return 0;
}