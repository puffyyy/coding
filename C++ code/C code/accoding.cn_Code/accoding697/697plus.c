#include<stdio.h>//24ms
#include<stdlib.h>
struct people{
    float boy;
    float girl;
    int pos;
}line[10010];
int boypos[10010],girlpos[10010],a[10010],b[10010];
int cmp(const void* a,const void *b)
{
    struct people *c=(struct people*)a;
    struct people *d=(struct people*)b;
    return (c->boy > d->boy)?1:-1;//升序排列
}
int cmp1(const void* a,const void *b)
{
    struct people *c=(struct people*)a;
    struct people *d=(struct people*)b;
    return (c->girl > d->girl)?1:-1;//升序排列
}
int main ()
{
    int n;
    while(~scanf("%d",&n))
    {
        int i;
        for(i=0;i<n;i++){
            scanf("%f%f",&line[i].boy,&line[i].girl);
            line[i].pos=i;
        }
        qsort(line,n,sizeof(line[0]),cmp);
        for(i=0;i<n;i++){
            boypos[line[i].pos]=i;
            a[i]=line[i].pos;
        }
        
        qsort(line,n,sizeof(line[0]),cmp1);
        for(i=0;i<n;i++){
            girlpos[line[i].pos]=i;
            b[i]=line[i].pos;
        }
        

        for(i=0;i<n;i++)
        printf("%d ",girlpos[a[i]]+1);
        putchar ('\n');
        for(i=0;i<n;i++)
        printf("%d ",boypos[b[i]]+1);
         putchar ('\n');
    }
    return 0;
}