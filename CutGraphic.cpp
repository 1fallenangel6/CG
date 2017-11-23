
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
		setlinestyle(PS_SOLID,1);
		setlinecolor(WHITE);
		line(p1->x,p1->y,p2->x,p2->y);
	}else if((p1->code&p2->code)!=0);//�߶��ڴ����⣬"����"֮
	else{
		if(p1->code==0){//ȷ��P1�ڴ����ⲿ�����P1�ڴ����ڣ��򽻻�P1��P2������ֵ�ͱ��룬���ｻ��ָ�뼴��
			position* temp = p2;
			p2 = p1;
			p1 = temp;
		}
		position* intersec = intersection(window,p1,p2);//��P1P2�봰������ֱ�ߵĽ���
		setlinestyle(PS_DASH,1);
		setlinecolor(RED);
		line(p1->x,p1->y,intersec->x,intersec->y);//����P1�ͽ���֮����߶Σ�����߶��ڴ����ⲿ�����Ǳ��������߶Σ�ʹ�ú��߻���
		cutLine(window,intersec,p2);//��������ΪP1,�ݹ�ִ��
	}
}

//���ƴ���
void drawmyWindow(position window[]){

	setlinestyle(PS_SOLID,1);
	setlinecolor(WHITE);
	for(int i=0;i<4;i++){
		line(window[i].x,window[i].y,window[(i+1)%4].x,window[(i+1)%4].y);
	}
}
// ������
void main()
{
	position window[4];//����ü�����
	int pointnum;
	//�����߶ε������˵�
	position* p1 = new position;
	position* p2 = new position;
	cout<<"������ü����ڵ��ĸ����������,����˳ʱ������Ͻǵĵ�һ�����㿪ʼ����"<<endl;
	for(int i=0;i<4;i++){
		cout<<"�����봰�ڵĵ�"<<i+1<<"���������( x 0-800, y 0-600):";
		cin>>window[i].x>>window[i].y;
	}
	cout<<"�����뱻�ü��Ķ���εĶ��������";
	cin>>pointnum;
	position *polygons = new position[pointnum];
	for(int i=0;i<pointnum;i++){
		cout<<"�������"<<i+1<<"���������( x 0-800, y 0-600):";
		cin>>polygons[i].x>>polygons[i].y;
	}

	initgraph(800, 600);
	drawmyWindow(window);//���Ʋü�����
	for(int i=0;i<pointnum;i++){
		cutLine(window,&(polygons[i]),&(polygons[(i+1)%pointnum]));//�ü�ֱ��
	}
	
	// ��������˳�
	getch();
	closegraph();
}


