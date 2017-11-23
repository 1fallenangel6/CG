/*
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<iomanip>
#include <iostream>  

using namespace std; 
#define LEFT 0x01 //�ڲü��������
#define RIGHT 0x02 //�ڲü������Ҳ�
#define DOWN 0x04  //�ڲü������²�
#define UP 0x8  //�ڲü������ϲ�
//���ݽṹ
typedef struct{
	int x;
	int y;
	int code;
}position;
//DDA�㷨��ֱ��
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


//�������
void encodePoint(position window[],position* p){
	p->code = 0;
	if(p->x<window[0].x)//�ж��Ƿ��ڴ������
		p->code = p->code|LEFT;
	if(p->x>window[2].x)//�ж��Ƿ��ڴ����ұ�
		p->code = p->code|RIGHT;
	if(p->y>window[2].y)//�ж��Ƿ��ڴ����±�
		p->code = p->code|DOWN;
	if(p->y<window[0].y)//�ж��Ƿ��ڴ����ϲ�
		p->code = p->code|UP;
}
//�󽻺�������P1P2�봰������ֱ�ߵĽ���
position* intersection(position window[],position* p1,position* p2){
	position *intersec = new position;//���彻��

	if(p2->x!=p1->x){//Ĭ��б�ʴ���
		double k = (double)((p2->y)-(p1->y))/((p2->x)-(p1->x));//P1P2��б��
		int code = 1;
		while(!(p1->code&code)){//ȷ��P1�ڴ��ڵ���һ�࣬���մ��������ϼ�⣬����ʹ��0001��P1�ı�����&��	
			code = code<<1;
		}
		double x,y;
		switch(code){//����P1�ʹ��ڵ����λ���󽻴�������ʹ��0001��P1�ı�����&���0001������࣬Ȼ����P1����ര������ֱ�ߵĽ���
		case 1:{//�����0001������ര������ֱ�ߵĽ���
				 x = window[0].x;
				 y = p1->y+(double)k*(x-p1->x);
				 break;
			   }
		case 2:{//�����0010�����Ҳര������ֱ�ߵĽ���
				 x = window[2].x;
				 y = p1->y+(double)k*(x-p1->x);
				 break;
			   }
		case 4:{//�����0100�����²ര������ֱ�ߵĽ���
				 y = window[2].y;
				 x = p1->x+(double)(y-p1->y)/k;
				 break;
			   }
		case 8:{//�����1000�����²ര������ֱ�ߵĽ���
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
//ʹ��Cohen-Sutherland�㷨�ü��߶Σ��ú�����ʾ��������߶Σ��ð�����ʾ�����ڵ��߶�
void cutLine(position window[],position* p1,position* p2){
	encodePoint(window,p1);//���߶εĶ˵����
	encodePoint(window,p2);//���߶εĶ˵����
	if((p1->code|p2->code)==0){//�߶��ڴ����ڣ�"��ȡ"֮
		DDA(p1->x,p1->y,p2->x,p2->y,WHITE);//�����ڴ����ڵ��߶Σ������߻���
	}else if((p1->code&p2->code)!=0);//�߶��ڴ����⣬"����"֮
	else{
		if(p1->code==0){//ȷ��P1�ڴ����ⲿ�����P1�ڴ����ڣ��򽻻�P1��P2������ֵ�ͱ��룬���ｻ��ָ�뼴��
			position* temp = p2;
			p2 = p1;
			p1 = temp;
		}
		position* intersec = intersection(window,p1,p2);//��P1P2�봰������ֱ�ߵĽ���
		DDA(p1->x,p1->y,intersec->x,intersec->y,RED);//����P1�ͽ���֮����߶Σ�����߶��ڴ����ⲿ�����Ǳ��������߶Σ�ʹ�ú��߻���
		cutLine(window,intersec,p2);//��������ΪP1,�ݹ�ִ��
	}
}
//��ʼ���ü����ڣ��ü����ڵ��ĸ�����ֱ���(200,200),(400,200),(400,400),(200,400)
void initmyWindow(position window[]){
	window[0].x = 200; window[0].y = 200;
	window[1].x = 400; window[1].y = 200;
	window[2].x = 400; window[2].y = 400;
	window[3].x = 200; window[3].y = 400;
}
//���ƴ���
void drawmyWindow(position window[]){
	for(int i=0;i<4;i++){
		DDA(window[i].x,window[i].y,window[(i+1)%4].x,window[(i+1)%4].y,WHITE);
	}
}
// ������
void main()
{
	position window[4];//����ü�����
	//�����߶ε������˵�
	position* p1 = new position;
	position* p2 = new position;
	initmyWindow(window);//��ʼ���ü�����
	cout<<"�ü����ڵ��ĸ�����ֱ���(200,200),(400,200),(400,400),(200,400)"<<endl;
	cout<<"�����뱻�ü����߶ε������յ�"<<endl;
	cout<<"�����߶����(0-800):";
	cin>>p1->x>>p1->y;
	cout<<"�����߶��յ�(0-600):";
	cin>>p2->x>>p2->y;
	initgraph(800, 600);

	drawmyWindow(window);//���Ʋü�����
	cutLine(window,p1,p2);//�ü�ֱ��
	// ��������˳�
	getch();
	closegraph();
}
*/

