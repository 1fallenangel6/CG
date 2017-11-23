/*
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<iomanip>
#include <iostream>  

using namespace std; 
#define LEFT 0x01 //在裁剪窗口左侧
#define RIGHT 0x02 //在裁剪窗口右侧
#define DOWN 0x04  //在裁剪窗口下侧
#define UP 0x8  //在裁剪窗口上侧
//数据结构
typedef struct{
	int x;
	int y;
	int code;
}position;
//DDA算法画直线
void DDA(int x0,int y0,int x1,int y1,int color){
	int dx,dy,pace,k,yy=-1,debugdx,debugdy;
	float x,y,xIncre,yIncre;
	dx=x1-x0;
	dy=y1-y0;
	x=x0;
	y=y0;
	if(abs(dx)>abs(dy)) 
		pace=abs(dx);
	else
		pace=abs(dy);
	xIncre=(float)dx/(float)pace;
	yIncre=(float)dy/(float)pace;
	if(dy==0){
		for(k=0;k<pace;k++){
			putpixel((int)(x + 0.5), (int)(y + 0.5),color);
			x = x + xIncre;
			y = y + yIncre;
		}
		return;
	}
	yy = (int)(y + 0.5);
	for(k=0;k<pace;k++){
		putpixel((int)(x + 0.5), (int)(y + 0.5),color);
		x = x + xIncre;
		y = y + yIncre;
	}

}


//给点编码
void encodePoint(position window[],position* p){
	p->code = 0;
	if(p->x<window[0].x)//判断是否在窗口左边
		p->code = p->code|LEFT;
	if(p->x>window[2].x)//判断是否在窗口右边
		p->code = p->code|RIGHT;
	if(p->y>window[2].y)//判断是否在窗口下边
		p->code = p->code|DOWN;
	if(p->y<window[0].y)//判断是否在窗口上侧
		p->code = p->code|UP;
}
//求交函数，求P1P2与窗口所在直线的交点
position* intersection(position window[],position* p1,position* p2){
	position *intersec = new position;//定义交点

	if(p2->x!=p1->x){//默认斜率存在
		double k = (double)((p2->y)-(p1->y))/((p2->x)-(p1->x));//P1P2的斜率
		int code = 1;
		while(!(p1->code&code)){//确定P1在窗口的哪一侧，按照从左右下上检测，例如使用0001与P1的编码求&，	
			code = code<<1;
		}
		double x,y;
		switch(code){//根据P1和窗口的相对位置求交代，例如使用0001与P1的编码求&结果0001，在左侧，然后求P1与左侧窗口所在直线的交点
		case 1:{//结果是0001，求左侧窗口所在直线的交点
				 x = window[0].x;
				 y = p1->y+(double)k*(x-p1->x);
				 break;
			   }
		case 2:{//结果是0010，求右侧窗口所在直线的交点
				 x = window[2].x;
				 y = p1->y+(double)k*(x-p1->x);
				 break;
			   }
		case 4:{//结果是0100，求下侧窗口所在直线的交点
				 y = window[2].y;
				 x = p1->x+(double)(y-p1->y)/k;
				 break;
			   }
		case 8:{//结果是1000，求下侧窗口所在直线的交点
				 y = window[0].y;
				 x = p1->x+(double)(y-p1->y)/k;
				 break;
			   }
		}
		intersec->x = (int)(x+0.5);
		intersec->y = (int)(y+0.5);
		return intersec;
	}
}
//使用Cohen-Sutherland算法裁剪线段，用红线显示窗口外的线段，用白线显示窗口内的线段
void cutLine(position window[],position* p1,position* p2){
	encodePoint(window,p1);//给线段的端点编码
	encodePoint(window,p2);//给线段的端点编码
	if((p1->code|p2->code)==0){//线段在窗口内，"简取"之
		DDA(p1->x,p1->y,p2->x,p2->y,WHITE);//画出在窗口内的线段，由蓝线画出
	}else if((p1->code&p2->code)!=0);//线段在窗口外，"简弃"之
	else{
		if(p1->code==0){//确保P1在窗口外部，如果P1在窗口内，则交换P1和P2的坐标值和编码，这里交换指针即可
			position* temp = p2;
			p2 = p1;
			p1 = temp;
		}
		position* intersec = intersection(window,p1,p2);//求P1P2与窗口所在直线的交点
		DDA(p1->x,p1->y,intersec->x,intersec->y,RED);//画出P1和交点之间的线段，这段线段在窗口外部，即是被舍弃的线段，使用红线画出
		cutLine(window,intersec,p2);//将交点作为P1,递归执行
	}
}
//初始化裁剪窗口，裁剪窗口的四个顶点分别是(200,200),(400,200),(400,400),(200,400)
void initmyWindow(position window[]){
	window[0].x = 200; window[0].y = 200;
	window[1].x = 400; window[1].y = 200;
	window[2].x = 400; window[2].y = 400;
	window[3].x = 200; window[3].y = 400;
}
//绘制窗口
void drawmyWindow(position window[]){
	for(int i=0;i<4;i++){
		DDA(window[i].x,window[i].y,window[(i+1)%4].x,window[(i+1)%4].y,WHITE);
	}
}
// 主函数
void main()
{
	position window[4];//定义裁剪窗口
	//定义线段的两个端点
	position* p1 = new position;
	position* p2 = new position;
	initmyWindow(window);//初始化裁剪窗口
	cout<<"裁剪窗口的四个顶点分别是(200,200),(400,200),(400,400),(200,400)"<<endl;
	cout<<"请输入被裁剪的线段的起点和终点"<<endl;
	cout<<"输入线段起点(0-800):";
	cin>>p1->x>>p1->y;
	cout<<"输入线段终点(0-600):";
	cin>>p2->x>>p2->y;
	initgraph(800, 600);

	drawmyWindow(window);//绘制裁剪窗口
	cutLine(window,p1,p2);//裁剪直线
	// 按任意键退出
	getch();
	closegraph();
}
*/

