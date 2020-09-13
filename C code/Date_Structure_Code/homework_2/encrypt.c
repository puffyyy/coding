#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fin,*fout;
int flag[27],lenth;
char key[51];
char a[1025];
void simplekey()
{
    for(int i=0;key[i]!='\0';){
        if(flag[key[i]-'a']==0){
            flag[key[i]-'a']=1;
            i++;
        }
        else strcpy(key+i,key+1+i);
    }
}
void Init()
{
    int i,j=0,l=strlen(key);
    
    for(i=25;i>=0;i--){
        if(flag[i]==1)continue;
        else key[l+j++]='a'+i;
    }
    key[l+j]='\0';
}
void print()
{
    for(int i=0;key[i]!='\0';i++){
        putchar(key[i]);
        putchar(' ');
    }
}
int main()
{
    
    fin=fopen("encrypt.txt","r");
    fout=fopen("output.txt","w");
    scanf("%s",key);
    lenth=strlen(key);
    simplekey();
    Init();
    print();
    while(fgets(a,1024,fin)!=NULL){
        for(int i=0;a[i]!='\n';i++){
            if(a[i]<='z'&&a[i]>='a')fputc(key[a[i]-'a'],fout);
            else fputc(a[i],fout);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}