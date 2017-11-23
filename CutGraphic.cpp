
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
		setlinestyle(PS_SOLID,1);
		setlinecolor(WHITE);
		line(p1->x,p1->y,p2->x,p2->y);
	}else if((p1->code&p2->code)!=0);//线段在窗口外，"简弃"之
	else{
		if(p1->code==0){//确保P1在窗口外部，如果P1在窗口内，则交换P1和P2的坐标值和编码，这里交换指针即可
			position* temp = p2;
			p2 = p1;
			p1 = temp;
		}
		position* intersec = intersection(window,p1,p2);//求P1P2与窗口所在直线的交点
		setlinestyle(PS_DASH,1);
		setlinecolor(RED);
		line(p1->x,p1->y,intersec->x,intersec->y);//画出P1和交点之间的线段，这段线段在窗口外部，即是被舍弃的线段，使用红线画出
		cutLine(window,intersec,p2);//将交点作为P1,递归执行
	}
}

//绘制窗口
void drawmyWindow(position window[]){

	setlinestyle(PS_SOLID,1);
	setlinecolor(WHITE);
	for(int i=0;i<4;i++){
		line(window[i].x,window[i].y,window[(i+1)%4].x,window[(i+1)%4].y);
	}
}
// 主函数
void main()
{
	position window[4];//定义裁剪窗口
	int pointnum;
	//定义线段的两个端点
	position* p1 = new position;
	position* p2 = new position;
	cout<<"请输入裁剪窗口的四个顶点的坐标,按照顺时针从左上角的第一个顶点开始输入"<<endl;
	for(int i=0;i<4;i++){
		cout<<"请输入窗口的第"<<i+1<<"个点的坐标( x 0-800, y 0-600):";
		cin>>window[i].x>>window[i].y;
	}
	cout<<"请输入被裁剪的多边形的顶点个数：";
	cin>>pointnum;
	position *polygons = new position[pointnum];
	for(int i=0;i<pointnum;i++){
		cout<<"请输入第"<<i+1<<"个点的坐标( x 0-800, y 0-600):";
		cin>>polygons[i].x>>polygons[i].y;
	}

	initgraph(800, 600);
	drawmyWindow(window);//绘制裁剪窗口
	for(int i=0;i<pointnum;i++){
		cutLine(window,&(polygons[i]),&(polygons[(i+1)%pointnum]));//裁剪直线
	}
	
	// 按任意键退出
	getch();
	closegraph();
}


