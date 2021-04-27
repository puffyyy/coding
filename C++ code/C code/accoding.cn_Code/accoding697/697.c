#include<stdio.h>
#include<stdlib.h>
struct people{
    float stature;
    int no;
}girl[10010],boy[10010];
int cmp(const void* a,const void *b)
{
    struct people *c=(struct people*)a;
    struct people *d=(struct people*)b;
    return (c->stature > d->stature)?1:-1;//升序排列
}
int main ()
{
    int n;
    while(~scanf("%d",&n))
    {
        int i,j;
        for(i=0;i<n;i++){
            scanf("%f %f",&boy[i].stature,&girl[i].stature);
            boy[i].no=i;
            girl[i].no=i;
        }
        qsort(boy,n,sizeof(boy[0]),cmp);//按身高排名
        qsort(girl,n,sizeof(girl[0]),cmp);
    
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(boy[i].no==girl[j].no)printf("%d ",j+1);
        putchar('\n');
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(girl[i].no==boy[j].no)printf("%d ",j+1);
        putchar('\n');
    }
    return 0;
}