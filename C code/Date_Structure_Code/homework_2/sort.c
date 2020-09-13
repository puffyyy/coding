#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct address_list{
    char name[21];
    char num[12];
}contact[201];
int n;
int check(int i)
{
    int ans=1;
    for(int j=1;j+i<n;j++){
        if(strcmp(contact[i+j].name,contact[i+j-1].name)==0)ans++;
        else break;
    }
    return ans;
}
int cmp(struct address_list a, struct address_list b)
{
    int l1,l2;
    l1=strlen(a.name);
    l2=strlen(b.name);
    int min=l1<l2?l1:l2;
    return strncmp(a.name,b.name,min);
}
void insert_sort(struct address_list* a)
{
    struct address_list current;
    for(int i=0;i<n-1;i++)
    {
        strcpy(current.name,a[i+1].name);
        strcpy(current.num,a[i+1].num);
        int preindex=i;  
        while (preindex>=0&&cmp(current,a[preindex])<0)
        {
            strcpy(a[preindex+1].name,a[preindex].name);
            strcpy(a[preindex+1].num,a[preindex].num);
            preindex--;
        }
        strcpy(a[preindex+1].name,current.name);
        strcpy(a[preindex+1].num,current.num);
    }
    return;
}
int main()
{
    
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s%s",contact[i].name,contact[i].num);
    }
    insert_sort(contact);
    
    for(int i=0;i<n;i++){
        int wide=check(i);
        if(wide==1)printf("%s %s\n",contact[i].name,contact[i].num);
        else {
            int count=1;
            printf("%s %s\n",contact[i].name,contact[i].num);
            for(int j=1;j<wide;j++)
            for(int k=0;k<j;){
                if(strcmp(contact[i+j].num,contact[i+k].num)==0){
                    memcpy(&contact[i+k],&contact[i+k+1],(n)*sizeof(struct address_list));
                    wide--;
                    n--;
                    if(j>=wide)break;
                }
                else {
                    if(k==j-1)printf("%s_%d %s\n",contact[i+j].name,count++,contact[i+j].num);
                    k++;
                }
            }
            i+=wide-1;
        }
    }


    
    return 0;
}