#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tolower(ch) ((ch)-'A'+'a')
FILE *fin;
typedef struct node{
    char ch[101];
    int cnt;
}Word;
Word words[10001];
int lenth=0;
int read_word(char ch[]){
    char temp;
    int j=0;
    memset(ch,0,101*sizeof(char));
    while(temp=fgetc(fin)){
        if(temp==EOF)return -1;
        if(temp>='a'&&temp<='z')ch[j++]=temp;
        else if(temp>='A'&&temp<='Z')ch[j++]=tolower(temp);
        else break;
    }
    if(j!=0)ch[j]='\0';
    return 1;
}
int cmp(char a[],char b[]){
    int l1=strlen(a);
    int l2=strlen(b);
    int min=l1>l2?l2:l1;
    int flag=strncmp(a,b,min);
    if(flag>0){//a>b
        return 1;
    }
    else if(flag<0)return 0;
    else {
        if(l1==l2)return 1;//a==b
        else if(l1>l2)return 1;
        else return 0;
    }
}
int binarysearch_right(int lenth,char x[])
{
    if(lenth==0)return -1;
    int left=0,right=lenth-1,mid;
    while(left<=right){
        mid=left+((right-left)>>1);
        if(cmp(x,words[mid].ch))//x >= a[mid]  =  ture
            left=mid+1;
        else right=mid-1;
    }
    return right;
}
void insert_word(int lenth, char ch[],int loc){
    if(loc==-1){
        for(int i=lenth-1;i>=0;i--){
            strcpy(words[i+1].ch,words[i].ch);
            words[i+1].cnt=words[i].cnt;
        }
        strcpy(words[0].ch,ch);
        words[0].cnt=1;
    }
    else {
        for(int i=lenth-1;i>=loc+1;i--){
            strcpy(words[i+1].ch,words[i].ch);
            words[i+1].cnt=words[i].cnt;
        }
        strcpy(words[loc+1].ch,ch);
        words[loc+1].cnt=1;
    }
}
void print_words(int lenth){
    for(int i=0;i<lenth;i++){
        printf("%s %d\n",words[i].ch,words[i].cnt);
    }
}
int main()
{
    for(int i=0;i<10001;i++){
        *words[i].ch='\0';
        words[i].cnt=0;
    }
    fin=fopen("article.txt","r");
    if(fin==NULL){
        printf("can not read");
        return 0;
    }
    char temp[101];
    int ffffff=1;
    while(ffffff=read_word(temp)){
        int i=binarysearch_right(lenth,temp);
        if(strcmp(words[i].ch,temp)==0&&strlen(temp)==strlen(words[i].ch))
            words[i].cnt++;
        else {
            insert_word(lenth,temp,i);
            lenth++;
        }
        if(ffffff==-1)break;
        
    }
    print_words(lenth);
    fclose(fin);
    return 0;
}