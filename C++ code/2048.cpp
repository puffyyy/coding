#include<cstdio>
#include<iostream>
#include<windows.h>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<conio.h>
using namespace std;

int a[5][5],MN,ss,st,score,step,personalbest;
bool pd[5][5],self;

void gotoxy(int x,int y)
{
	COORD pos;
	pos.X=(short int)(x*2);
	pos.Y=(short int)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(short unsigned int)a);
}

void clear(int x,int y)
{
	color(0);
	int wherex=x*5+1;
	int wherey=y*5+1;
	for(int i=wherex;i<=wherex+4;i++){
		gotoxy(wherey,i);
		for(int j=wherey;j<=wherey+4;j++)
		{
			printf("  ");
		}
	}
}

void pp(int x,int y,int w)
{
	int wherex = x * 5 + 1;
	int wherey = y * 5 + 1;
	int num = 0;
	int c[7];
	int gg = w;
	int much = -1;
	while(gg)
	{
		gg/=2;
		much++;
	}
	much*=17;
	if(much>255)much=256;		// Much变量用于设置方块颜色 
	while(w){
		c[++num] = w % 10;			// num变量记录了w位数 
		w /= 10;					// c[]记录了各位上的数字 
	}
	for(int i = wherex; i <= wherex + 4; i++)
	{
		gotoxy(wherey, i);		// 转换光标 
		for(int j = wherey;j <= wherey + 4; j++)
		{
			color(much);		// 设置颜色 
			if(i == wherex + 2 && j == wherey + 1){		// 打印数字 
				color(15);
				if(num == 1){
					printf("  %d   ",c[1]);					
				}
				if(num==2){
					printf("  %d%d  ",c[2],c[1]);
				}
				if(num==3){
					printf(" %d%d%d  ",c[3],c[2],c[1]);
				}
				if(num==4){
					printf(" %d%d%d%d ",c[4],c[3],c[2],c[1]);
				}
				color(much);								//  中间行打印数字 
				printf("■");
				break;
			}
			else if(i!=wherex && i!=wherex+4 && j!=wherey && j!=wherey+4)
			{			// 判断是否是边框上的坐标 
				color(0);
				printf("  ");
			}
			else{
				printf("■");
			}
		}
	}
}

void clearall()
{
	for(int i=0;i<=50;i++)
	{
		gotoxy(0,i);
		for(int j=0;j<=100;j++)
		{
			printf("  ");
		}
	}
}

void init()
{
	clearall();
	gotoxy(0,0);
	color(15);
	printf("Choose the difficulty you wanna play:\n");
	printf("1:(easy,3*3)\n");
	printf("2:(medium,4*4)\n");
	printf("3:(hard,5*5)\n");
	char c=(char)getch();
	while(c!='1' && c!='2' && c!='3'){
		c=(char)getch();
	}
	clearall();
	ss=c-'1'+3;
	MN=ss*5+1;
	for(int i=0;i<=5;i++)
	{
		gotoxy(0,i);
		for(int j=0;j<=50;j++)
		{
			color(0);
			printf("  ");
		}
	}
	for(int i=0;i<=MN;i++)
	{
		color(8);
		gotoxy(0,i);
		printf("■");
		gotoxy(i,0);
		printf("■");
		gotoxy(MN,i);
		printf("■");
		gotoxy(i,MN);
		printf("■");
	}
}

void initb()
{
	gotoxy(0,0);
	color(15);
	printf("Choose the difficulty you wanna watch:\n");
	printf("1:(easy,3*3)\n");
	printf("2:(medium,4*4)\n");
	printf("3:(hard,5*5)\n");
	char c=(char)getch();
	while(c!='1' && c!='2' && c!='3'){
		c=(char)getch();
	}
	ss=c-'1'+3;
	MN=ss*5+1;
	for(int i=0;i<=5;i++)
	{
		gotoxy(0,i);
		for(int j=0;j<=50;j++)
		{
			color(0);
			printf("  ");
		}
	}
	for(int i=0;i<=MN;i++)
	{
		color(8);
		gotoxy(0,i);
		printf("■");
		gotoxy(i,0);
		printf("■");
		gotoxy(MN,i);
		printf("■");
		gotoxy(i,MN);
		printf("■");
	}
}

void getrand()
{
	int much=0;
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		if(!a[i][j])much++;
	}
	much=(rand()%much)+1;
	int x,y;
	for(int i=0;i<ss;i++){
		for(int j=0;j<ss;j++)
		{
			if(!a[i][j])much--;
			if(!much){
				x=i;
				y=j;
				break;
			}
		}
		if(!much)break;
	}
	int w=rand()%2;
	w++;
	w*=2;
	a[x][y]=w;
}

bool moveup()
{	// 移动有两种操作： 第一种是合并，第二种累积元素 
	memset(pd,false,sizeof(pd));			// pd用于记录各自是否被合并过 
	bool pdd=false;
	for(int i=1;i<ss;i++)					// 因为是向上移动所以从第二层开始遍历 
	for(int j=0;j<ss;j++)			
	if(a[i][j])
	{
		int wherex=i;
		while(wherex && a[wherex-1][j]==0){
			wherex--;						// 获取没有元素的最远的位置 
		}
		a[wherex][j] = a[i][j];				// 赋值 
		if(wherex != i){
			a[i][j] = 0;					// 原来的位置置零 
			pdd = true;
		}
		if(wherex && a[wherex-1][j] == a[wherex][j] && (!pd[wherex-1][j]))
		{
			pd[wherex-1][j]=true;
			a[wherex-1][j]*=2;
			score+=a[wherex-1][j];
			a[wherex][j]=0;
			pdd=true;
		}			// 判断是否符合合并的条件 
	}
	return pdd;
}


bool moveleft()
{
	memset(pd,false,sizeof(pd));
	bool pdd=false;
	for(int i=0;i<ss;i++)
	for(int j=1;j<ss;j++)
	if(a[i][j])
	{
		int wherey=j;
		while(wherey && a[i][wherey-1]==0){
			wherey--;
		}
		a[i][wherey]=a[i][j];
		if(wherey!=j){
			a[i][j]=0;
			pdd=true;
		}
		if(wherey && a[i][wherey-1]==a[i][wherey] && (!pd[i][wherey-1]))
		{
			pd[i][wherey-1]=true;
			a[i][wherey-1]*=2;
			score+=a[i][wherey-1];
			a[i][wherey]=0;
			pdd=true;
		}
	}
	return pdd;
}

bool movedown()
{
	memset(pd,false,sizeof(pd));
	bool pdd=false;
	for(int i=ss-2;i>=0;i--)
	for(int j=0;j<ss;j++)
	if(a[i][j])
	{
		int wherex=i;
		while(wherex!=ss-1 && a[wherex+1][j]==0){
			wherex++;
		}
		a[wherex][j]=a[i][j];
		if(wherex!=i){
			a[i][j]=0;
			pdd=true;
		}
		if(wherex<ss-1 && a[wherex+1][j]==a[wherex][j] && (!pd[wherex+1][j]))
		{
			pd[wherex+1][j]=true;
			a[wherex+1][j]*=2;
			score+=a[wherex+1][j];
			a[wherex][j]=0;
			pdd=true;
		}
	}
	return pdd;
}


bool moveright()
{
	memset(pd,false,sizeof(pd));
	bool pdd=false;
	for(int i=0;i<ss;i++)
	for(int j=ss-2;j>=0;j--)
	if(a[i][j])
	{
		int wherey=j;
		while(wherey<ss-1 && a[i][wherey+1]==0){
			wherey++;
		}
		a[i][wherey]=a[i][j];
		if(wherey!=j){
			a[i][j]=0;
			pdd=true;
		}
		if(wherey<ss-1 && a[i][wherey+1]==a[i][wherey] && (!pd[i][wherey+1]))
		{
			pd[i][wherey+1]=true;
			a[i][wherey+1]*=2;
			score+=a[i][wherey+1];
			a[i][wherey]=0;
			pdd=true;
		}
	}
	return pdd;
}

bool check()
{
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	if(a[i][j])
	{
		if(i!=ss-1 && a[i][j]==a[i+1][j])return true;
		if(j!=ss-1 && a[i][j]==a[i][j+1])return true;
	}else return true;
	return false;
} 	//用来检查是否还可以进行移动，如果不能返回false 

void printscreen()
{
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	if(a[i][j]){
		pp(i,j,a[i][j]);
	}
	color(15);
	gotoxy(MN/2-1,MN+1);
	printf("Step:%d",step);
	gotoxy(MN/2-2,MN+2);
	printf(" Score:%d",score);
	if(self){
		if(score>personalbest)personalbest=score;
		gotoxy(MN/2-3,MN+3);
		printf("Personalbest:%d",personalbest);
	}
}

void gameover()
{
	Sleep(1000);
	color(15);
	for(int i=1;i<MN;i++)
	for(int j=1;j<MN;j++){
		gotoxy(i,j);
		printf("  ");
		Sleep(5);
	}				// 清屏 
	color(15);
	gotoxy(MN/2,MN/2);
	printf("GG");
	gotoxy(MN/3-1,MN/2+1);
	printf("press 'r' to restart");
	gotoxy(MN/3-1,MN/2+2);
	printf("press 'q' to quit");			// 打印提示信息 
	char c=(char)getch();
	while(c!='r' && c!='q')
	{
		c=(char)getch();
	}										// 接受指令 
	if(c=='r')
	{
		for(int i=0;i<=MN;i++)
		for(int j=0;j<=MN;j++)
		{
			gotoxy(i,j);
			printf("  ");
		}									// 清屏	
	}else if(c=='q'){
		exit(0);
	}
}

bool checkwin()
{
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		if(a[i][j]==2048){
			return true;
		}
	}
	return false;
}

void gamestart()
{
	init();
	step=0;
	score=0;
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		a[i][j]=0;
	}
	getrand();
	printscreen();
	bool alreadywin=true;
	while(1)
	{
		bool mm=false;
		if(!check())
		{
			gameover();
			return;
		}
		char c=(char)getch();
		if(c=='w')
		{
			mm=moveup();
		}
		if(c=='a')
		{
			mm=moveleft();
		}
		if(c=='s')
		{
			mm=movedown();
		}
		if(c=='d')
		{
			mm=moveright();
		}
		if(!mm)continue;
		if(checkwin() && alreadywin)
		{
			for(int i=0;i<ss;i++)
			for(int j=0;j<ss;j++)clear(i,j);
			gotoxy(2,MN/2);
			color(15);
			printf("You Win!Press any key to continue!");
			getch();
			alreadywin=false;
		}
		getrand();
		for(int i=0;i<ss;i++)
		for(int j=0;j<ss;j++)clear(i,j);
		step++;
		printscreen();
	}
}

void Corner()
{
	initb();
	step=0;
	score=0;
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		a[i][j]=0;
	}
	getrand();
	printscreen();
	while(1)
	{
		bool mm=false;
		if(!check())
		{
			gameover();
			return;
		}
		mm=moveup();
		if(!mm)
		{
			mm=moveleft();
		}
		if(!mm)
		{
			mm=movedown();
		}
		if(!mm)
		{
			mm=moveright();
		}
		if(!mm)continue;
		getrand();
		for(int i=0;i<ss;i++)
		for(int j=0;j<ss;j++)clear(i,j);
		step++;
		printscreen();
		Sleep(st);
	}
}

void Swing()
{
	initb();
	step=0;
	score=0;
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		a[i][j]=0;
	}
	getrand();
	printscreen();
	int cur=1;
	while(1)
	{
		bool mm=false;
		if(!check())
		{
			gameover();
			return;
		}
		if(cur){
			mm=moveup();
			if(!mm)
			{
				mm=movedown();
			}
		}else{
			mm=moveleft();
			if(!mm)
			{
				mm=moveright();
			}
		}
		if(!mm)cur^=1;
		if(!mm)continue;
		getrand();
		for(int i=0;i<ss;i++)
		for(int j=0;j<ss;j++)clear(i,j);
		step++;
		printscreen();
		Sleep(st);
	}
}

void Swirl()
{
	initb();
	step=0;
	score=0;
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		a[i][j]=0;
	}
	getrand();
	printscreen();
	int num=0;
	while(1)
	{
		num++;
		bool mm=false;
		if(!check())
		{
			gameover();
			return;
		}
		if(num%4==0){
			mm=moveup();
		}else if(num%4==1){
			mm=moveright();
		}else if(num%4==2){
			mm=movedown();
		}else mm=moveleft();
		if(!mm)continue;
		getrand();
		for(int i=0;i<ss;i++)
		for(int j=0;j<ss;j++)clear(i,j);
		step++;
		printscreen();
		Sleep(st);
	}
}

void Random()
{
	score=0;
	step=0;
	initb();
	for(int i=0;i<ss;i++)
	for(int j=0;j<ss;j++)
	{
		a[i][j]=0;
	}
	getrand();
	printscreen();
	while(1)
	{
		int num=rand()%4;
		bool mm=false;
		if(!check())
		{
			gameover();
			return;
		}
		if(num==0){
			mm=moveup();
		}else if(num==1){
			mm=moveright();
		}else if(num==2){
			mm=movedown();
		}else mm=moveleft();
		if(!mm)continue;
		getrand();
		for(int i=0;i<ss;i++)
		for(int j=0;j<ss;j++)if(a[i][j]==0)clear(i,j);
		step++;
		printscreen();
		Sleep(st);
	}
}

void AIplay()
{
	clearall();
	gotoxy(0,0);
	printf("please write the time that you want to sleep between every step:");
	scanf("%d",&st);
	clearall();
	gotoxy(0,0);
	printf("There are 4 kinds of way to play automatically:\n");
	printf("1:Corner\n");
	printf("2:Swing\n");
	printf("3:Swril\n");
	printf("4:Random\n");
	char c=(char)getch();
	while(c!='1' && c!='2' && c!='3' && c!='4')
	{
		c=(char)getch();
	}
	clearall();
	if(c=='1'){
		Corner();
	}else
	if(c=='2'){
		Swing();
	}else
	if(c=='3'){
		Swirl();
	}else
	if(c=='4'){
		Random();
	}
}

int main()
{
	srand((int)time(NULL));
	color(15);
	clearall();
	personalbest=0;
	while(1)
	{
		clearall();
		score=0;
		gotoxy(0,0);
		printf("press '1' to watch the computer play the game automatically.\n");
		printf("press '2' to play yourself!");
		char c=(char)getch();
		while(c!='1' && c!='2')
		{
			c=(char)getch();
		}
		if(c=='1'){
			self=false;
			AIplay();
		}else{
			self=true;
			gamestart();
		}
	}
}
