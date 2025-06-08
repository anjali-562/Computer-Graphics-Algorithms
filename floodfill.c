#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

int input[2][10];
int x,y,xa,ya,xb,yb,v;
float fcol[3];
float backcol[3];

void FloodFill(int x,int y,float fcol[3],float backcol[3])
{
    float current[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
    
    if((current[0]==backcol[0] && current[1]==backcol[1] && current[2]==backcol[2]) && (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2]))
    {
        glColor3f(fcol[0],fcol[1],fcol[2]);
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();
        
        FloodFill(x,y+1,fcol,backcol);
        FloodFill(x,y-1,fcol,backcol);
        FloodFill(x+1,y,fcol,backcol);
        FloodFill(x-1,y,fcol,backcol);
        
    }
}

int ROUND(float a)
{
    return (int) (a+0.5);
}
void DDA(int xa,int ya, int xb,int yb)
{
    int dx,dy,steps;
    dx=xb-xa;
    dy=yb-ya;
    
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    
    float xinc,yinc;
    xinc=(float)dx/steps;
    yinc=(float)dy/steps;
    
    glVertex2d(xa,ya);
    float x=xa,y=ya;
    
    for(int i=0;i<steps;i++)
    {
        x=x+xinc;
        y=y+yinc;
        glVertex2d(ROUND(x),ROUND(y));
    }
    
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(fcol[0],fcol[1],fcol[2]);
     DDA(xa,ya,xa,yb); // Top edge
     DDA(xa,yb,xb,yb); // Right edge
     DDA(xb,yb,xb,ya); // Bottom edge
     DDA(xb,ya,xa,ya); // Left edge
     glEnd();
    glFlush();
   
    FloodFill((xa + xb)/2, (ya + yb)/2, fcol, backcol);
    

}

int main(int argc,char **argv)
{   
printf("\nEnter xa,ya");
scanf("%d%d",&xa,&ya);
printf("\nEnter xb,yb");
scanf("%d%d",&xb,&yb);
    for(int i=0;i<3;i++)
    {
        printf("\nBackground Color[%d]: ",i);
        scanf("%e",&backcol[i]);
    }
    
    for(int i=0;i<3;i++)
    {
        printf("\nFill Color[%d]: ",i);
        scanf("%e",&fcol[i]);
    }
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Flood Fill");
    glClearColor(backcol[0],backcol[1],backcol[2],0);
    glColor3f(0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMainLoop();
}

