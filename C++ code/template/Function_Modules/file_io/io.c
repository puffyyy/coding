#include<stdio.h>//standard input output header

int main()
{
    FILE *in,*out;                //filename.type should exist with .exe in the same directory
    in=fopen("file_in_name.type","r");//r->read
    out=fopen("file_out_name.type","w");//w->write
    char c;
    char s[10];
    int n=10;
    c=fgetc(in);//从文件（file_in_name.type）中读入一个字符,返回1或EOF
    fputc(c,out);//输出一个字符到文件（file_out_name.type）中
    fgets(s,n,in);//从 文件in上读入一行（最多读入n-1个字符），放入s字符数组中。返回s或NULL。
    fputs(s,out); //把字符串s（不一定含\n）写入文件out中。返回非负数或EOF
    fscanf(in, "%d", &n); //从文件in中读入一个整数
    fprintf( out, "%d\n", n); //输出一个整数到文件out中

}
