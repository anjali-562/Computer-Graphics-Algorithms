#include<stdio.h>
#include<GL/glut.h>

int xa,ya,xb,yb;
int x,y;
float bcol[3],fcol[3];

void boundaryfill(int x, int y, float bcol[3], float fcol[3])
{
  float current[3];
  glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, current);
  
  for(int i = 0; i < 3; i++)
  {
   printf("\n%f", current[i]);
  } 
  if((bcol[0] != current[0] || bcol[1] != current[1] || bcol[2] != current[2])  && (fcol[0] != current[0] || fcol[1] != current[1] || fcol[2] != current[2]))
  {
    glColor3f(fcol[0],fcol[1],fcol[2]);
    glBegin(GL_POINTS);
    glVertex2d(x,y);
    glEnd();
    glFlush();
    
    boundaryfill(x+1,y,bcol,fcol);
    boundaryfill(x-1,y,bcol,fcol);
    boundaryfill(x,y+1,bcol,fcol);
    boundaryfill(x,y-1,bcol,fcol);
  }
 } 




int Round(float a){
return(int)(a+0.5);
}
void ddaline(int xa,int ya,int xb,int yb){
int dx,dy,steps;
dx=xb-xa;
dy=yb-ya;

if (abs(dx)>abs(dy)){
steps=abs(dx);
}
else{
steps=abs(dy);
}
float xinc,yinc;
xinc=(float)dx/steps;
yinc=(float)dy/steps;

float x=xa,y=ya;
glVertex2d(xa,ya);
for(int i=0;i<steps;i++){
x=x+xinc;
y=y+yinc;
glVertex2d(Round(x),Round(y));
}
}

void draw(){
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POINTS);
ddaline(200,200,100,300);

glEnd();
glFlush();

}

int main(int argc,char**argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(640,480);
glutCreateWindow("DDALINE");
glClearColor(1,1,1,0);
glColor3f(0,0,0);
gluOrtho2D(0,640,0,480);
glutDisplayFunc(draw);
glutMainLoop();

return 0;
}
