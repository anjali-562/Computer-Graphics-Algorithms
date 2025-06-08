#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int xc,yc,r;

void bcircle(int xc,int yc,int r)
{
 int x,y,d;
 x=0,y=r,d=3-2*r;
 
 do{
        glVertex2d(xc + x, yc + y);
        glVertex2d(xc - x, yc + y);
        glVertex2d(xc + x, yc - y);
        glVertex2d(xc - x, yc - y);
        glVertex2d(xc + y, yc + x);
        glVertex2d(xc - y, yc + x);
        glVertex2d(xc + y, yc - x);
        glVertex2d(xc - y, yc - x);
    
    if(d<0)
    {
     x=x+1;
     d=d+4*x+6;
    }
    else
    {
     x=x+1;
     y=y-1;
     d=d+4*x-4*y+10;
    }
 }
 while(y>=x);
}

void draw()
{
 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_POINTS);
 bcircle(xc,yc,r);
 glEnd();
 glFlush();
}

int main(int argc,char**argv)
{
printf("\nEnter the r: ");
scanf("%d",&r);
printf("\nEnter the coordinate: ");
scanf("%d%d",&xc,&yc);

 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowPosition(0,0);
 glutInitWindowSize(640,480);
 glutCreateWindow("BresCircle");
 glClearColor(1.0,1.0,1.0,0.0);
 glColor3f(0.0,0.0,0.0);
 gluOrtho2D(0,640,0,480);
 glutDisplayFunc(draw);
 glutMainLoop();
 return 0;
}
