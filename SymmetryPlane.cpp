/*
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<iomanip>
#include <iostream> 
#include <math.h>

#define pi 3.1415926

using namespace std;  
  
float xs = 0.0;  
float ys = 0.0;  
float xe = 0.0;  
float ye = 0.0;
int bkColor;

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

// 数据结构
typedef struct{
	int x;
	int y;
}position;

//缩放函数，将所有坐标以坐标原点为参考点，放大或缩小multi倍
void amplify(position Plane[],float multi){
	for(int i = 0;i<12;i++){
		Plane[i].x = Plane[i].x*multi;//横坐标放大或缩小multi倍
		Plane[i].y = Plane[i].y*multi;//纵坐标放大或缩小multi倍
	}
}
//绘制飞机，飞机总共12个顶点，可以指定飞机的颜色
void drawPlane(position Plane[],int Color){
	for(int i = 0;i<12;i++){
		DDA(Plane[i].x,Plane[i].y,Plane[(i+1)%12].x,Plane[(i+1)%12].y,Color);
	}
}
//初始化飞机的顶点
void initPlane(position Plane[]){
	Plane[0].x = 110;  Plane[0].y = 350;
	Plane[1].x = 250; Plane[1].y = 300;
	Plane[2].x = 350; Plane[2].y = 120;
	Plane[3].x = 320; Plane[3].y = 300;
	Plane[4].x = 550; Plane[4].y = 330;
	Plane[5].x = 600; Plane[5].y = 260;
	Plane[6].x = 580; Plane[6].y = 350;
	Plane[7].x = 600; Plane[7].y = 440;
	Plane[8].x = 550; Plane[8].y = 380;
	Plane[9].x = 320; Plane[9].y = 400;
	Plane[10].x = 350; Plane[10].y = 580;
	Plane[11].x = 250; Plane[11].y = 400;
}


//水平对称
void horizonSymmestry(position Plane[],int y){
	for(int i = 0;i<12;i++){
		Plane[i].y = 2*y - Plane[i].y;
	}
	//画出水平对称轴
	setlinestyle(PS_DASH,1);
	setlinecolor(WHITE);
	line(0,y,800,y);
}
//垂直对称
void verticalSymmestry(position Plane[],int x){
	for(int i = 0;i<12;i++){
		Plane[i].x = 2*x - Plane[i].x;
	}
	//画出垂直对称轴
	setlinestyle(PS_DASH,1);
	setlinecolor(WHITE);
	line(x,0,x,600);
}

// 主函数
void main()
{
	position Plane[11];
	
	//对称变换输入
	int hv,x,y;
	cout<<"对称变换，请选择输入水平对称轴或垂直对称轴，水平对称轴 0 ，垂直对称轴 1"<<endl;
	cin>>hv;
	if(hv==0){
		cout<<"请输入水平对称轴 y = ";
		cin>>y;
	}else{
		cout<<"请输入垂直对称轴 x = ";
		cin>>x;	
	}

	initgraph(800,600);
	// 测试画线

	initPlane(Plane);//初始化飞机的顶点
	drawPlane(Plane,GREEN);//绘制初始化的飞机
	
	if(hv==0)
		horizonSymmestry(Plane,y);
	else
		verticalSymmestry(Plane,x);
	
	drawPlane(Plane,RED);//绘制对称变换后的飞机
	// 按任意键退出
	getch();
	closegraph();
}
*/
