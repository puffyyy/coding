#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct string{
    char c;
    int line;
}string[210],stack[110];
char bracketline[210];
int top=-1,size=0,line=1;
//当检测的程序括号为'{'时，若其前序尚未匹配的括号为'('时，输出该'('左括号及所在行号
int main(){
    FILE* in;
    in=fopen("example.c","r");
    char ch;
    while((ch=fgetc(in))!=EOF){
        if(ch=='/'){
            char aftch=fgetc(in);
            if(aftch=='/'){
                while(1){
                    char temp=fgetc(in);
                    if(temp=='\n'){
                        line++;
                        break;
                    }
                }
            }
            else if(aftch=='*'){
                char temp,afttemp;
                while(1){
                    afttemp=fgetc(in);
                    if(afttemp=='\n')line++;
                    if(afttemp=='/'&&temp=='*')break;
                    temp=afttemp;
                }
            }
        }
        else if(ch=='\"'){
             while(1){
                    char temp=fgetc(in);
                    if(temp=='\n'){
                        line++;
                    }
                    if(temp=='\"')break;
                }
        }
        else if(ch=='\''){
             while(1){
                    char temp=fgetc(in);
                    if(temp=='\n'){
                        line++;
                    }
                    if(temp=='\'')break;
                }
        }
        else if(ch=='('||ch=='{'){
            string[size].c=ch;
            string[size].line=line;
            size++;
        }
        else if(ch==')'||ch=='}'){
            string[size].c=ch;
            string[size].line=line;
            size++;
        }
        else if(ch=='\n')line++;
    }
    for(int i=0;i<size;i++){
        if(string[i].c=='('||string[i].c=='{'){
            if(string[i].c=='{'&&stack[top].c=='('){
                printf("without maching '%c' at line %d",stack[top].c,stack[top].line);
                return 0;
            }
            stack[++top].c=string[i].c;
            stack[top].line=string[i].line;
        }
        else if(string[i].c==')'||string[i].c=='}'){
            if(stack[top].c+1==string[i].c||stack[top].c+2==string[i].c)
                top--;
            else {
                printf("without maching '%c' at line %d",string[i].c,string[i].line);
                return 0;
            }
        }
    }
    if(top!=-1){
        printf("without maching '%c' at line %d",stack[0].c,stack[0].line);
    }
    else {
        for(int i=0;i<size;i++)
        printf("%c",string[i].c);
    }

    //if(top!=-1)printf("without maching '%c' at line %d",stack[0]);
    return 0;
}