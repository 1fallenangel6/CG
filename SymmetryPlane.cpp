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

// ���ݽṹ
typedef struct{
	int x;
	int y;
}position;

//���ź���������������������ԭ��Ϊ�ο��㣬�Ŵ����Сmulti��
void amplify(position Plane[],float multi){
	for(int i = 0;i<12;i++){
		Plane[i].x = Plane[i].x*multi;//������Ŵ����Сmulti��
		Plane[i].y = Plane[i].y*multi;//������Ŵ����Сmulti��
	}
}
//���Ʒɻ����ɻ��ܹ�12�����㣬����ָ���ɻ�����ɫ
void drawPlane(position Plane[],int Color){
	for(int i = 0;i<12;i++){
		DDA(Plane[i].x,Plane[i].y,Plane[(i+1)%12].x,Plane[(i+1)%12].y,Color);
	}
}
//��ʼ���ɻ��Ķ���
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


//ˮƽ�Գ�
void horizonSymmestry(position Plane[],int y){
	for(int i = 0;i<12;i++){
		Plane[i].y = 2*y - Plane[i].y;
	}
	//����ˮƽ�Գ���
	setlinestyle(PS_DASH,1);
	setlinecolor(WHITE);
	line(0,y,800,y);
}
//��ֱ�Գ�
void verticalSymmestry(position Plane[],int x){
	for(int i = 0;i<12;i++){
		Plane[i].x = 2*x - Plane[i].x;
	}
	//������ֱ�Գ���
	setlinestyle(PS_DASH,1);
	setlinecolor(WHITE);
	line(x,0,x,600);
}

// ������
void main()
{
	position Plane[11];
	
	//�ԳƱ任����
	int hv,x,y;
	cout<<"�ԳƱ任����ѡ������ˮƽ�Գ����ֱ�Գ��ᣬˮƽ�Գ��� 0 ����ֱ�Գ��� 1"<<endl;
	cin>>hv;
	if(hv==0){
		cout<<"������ˮƽ�Գ��� y = ";
		cin>>y;
	}else{
		cout<<"�����봹ֱ�Գ��� x = ";
		cin>>x;	
	}

	initgraph(800,600);
	// ���Ի���

	initPlane(Plane);//��ʼ���ɻ��Ķ���
	drawPlane(Plane,GREEN);//���Ƴ�ʼ���ķɻ�
	
	if(hv==0)
		horizonSymmestry(Plane,y);
	else
		verticalSymmestry(Plane,x);
	
	drawPlane(Plane,RED);//���ƶԳƱ任��ķɻ�
	// ��������˳�
	getch();
	closegraph();
}
*/
