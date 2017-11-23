/*
#include <easyx.h>
  #include <math.h>
  #include <windows.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <conio.h>
  #include <graphics.h>
 
 int Draw_Oval(int a,int b,int p1,int p2,int color)
 {
     int x,y;
     double d1,d2;
     x = 0; 
     y = b;
     d1 = b*b+a*a*(-b+0.25);
     putpixel(x+p1,y+p2,color);
     while(b*b*(x+1) < a*a*(y-0.5))   //绘制上半部分
     {
         if(d1 < 0)
        {
             d1 += b*b*(2*x+3);
             x++;
         }
         else
         {
             d1 += (b*b*(2*x+3) + a*a*(-2*y+2));
             x++;
             y--;
         }
        putpixel(x+p1,y+p2,color);
         putpixel(x+p1,-y+p2,color);
         putpixel(-x+p1,y+p2,color);
         putpixel(-x+p1,-y+p2,color);
 
     }   
     
     d2 = sqrt(b*(x+0.5)) +sqrt(a*(y-1.0))-sqrt(double(a*b));
     while(y > 0)  //绘制下半部分
     {
         if(d2 < 0)
         {
             d2 += b*b*(2*x+2) + a*a*(-2*y+3);
             x++;
             y--;
         }
         else
         {
             d2 += a*a*(-2*y+3);
             y--;
         }
         putpixel(x+p1,y+p2,color);
         putpixel(x+p1,-y+p2,color);
		  putpixel(-x+p1,y+p2,color);
         putpixel(-x+p1,-y+p2,color);
     } 

     return 0;
 }
 
 
 
 
 int main()
 { 

     int gd=DETECT,gm,a,b,x,y;
     printf("请输入长半轴和短半轴：");
     scanf("%d %d",&a,&b);
     printf("请输入椭圆圆心坐标:");
     scanf("%d %d",&x,&y);
     initgraph(&gd,&gm,"c:\\tc");
     setbkcolor(BLACK);
     Draw_Oval(a,b,x,y,RED);
     getch(); 
     closegraph(); 
     
     return 0;
 }
 */