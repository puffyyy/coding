#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tolower(c) 	(c>='A'&&c<='Z' ? 'a'-'A'+c:c)
char a[1200];
char old[101],newc[101];
int lo,ln;
FILE *in,*out;

char* check(char *ch,char *find)
{
    int i, j, k;
    for(i =0; *(ch+i) != '\0'; i++)
    {
        for(j=i,k=0;*(ch+k)!='\0'&&tolower(*(ch+j))== tolower(*(find+k));j++,k++);
        if(*(find+k) == '\0')
        return (ch+i);
    }
    return (NULL);
}
void replace()
{
    char*p=a;
    char*q=a;
    while((p=check(p,old))!=NULL){
        
        while(q!=p)fputc(*q++,out);
        for(int i=0;i<ln;i++)fputc(newc[i],out);
        p+=lo;
        q=p;
    }
    while(*q!='\0')fputc(*q++,out);
}
int main()
{
    
    in=fopen("filein.txt","r");
    out=fopen("fileout.txt","w");
    if(in==NULL)printf("can not open filein\n");
    if(out==NULL)printf("can not open fileout\n");
    scanf("%s%s",old,newc);
    lo=strlen(old);
    ln=strlen(newc);
    while(fgets(a,1024,in)!=NULL){
        replace();
    }
    fclose(in);
    fclose(out);

    return 0;
}