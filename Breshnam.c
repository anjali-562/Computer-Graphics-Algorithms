#include<stdio.h>
#include<GL/glut.h>
int xa,ya,xb,yb;







void bresline(int xa,int ya,int xb,int yb){
int c,r,f;
int dx;
int d;
int dy;
dx=xb-xa;
dy=yb-ya;
if(abs(dx)>abs(dy)){
d=2*abs(dy)-abs(dx);
//GentleSlope
if(dx>0){
c=xa;
r=ya;
f=xb;
}
else{
c=xb;
r=yb;
f=xa;
}
while(f>c){
if(d<0){
c=c+1;
d=d+2*abs(dy);
glVertex2d(c,r);
}
else{
c=c+1;
if((dx>0&&dy>0)||(dx<0&&dy<0)){
//positive
r=r+1;
}
else{
//negative
r=r-1;
}
d=d+2*abs(dy)-2*abs(dx);
glVertex2d(c,r);
}
}
}
else{
d=2*abs(dx)-abs(dy);
if(dy>0){
c=xa;
r=ya;
f=yb;
}
else{
c=xb;
r=yb;
f=ya;
}
while(f>r){

if(d<0){
r=r+1;
d=d+2*abs(dx);
glVertex2d(c,r);
}
else{
r=r+1;
if((dx>0&&dy>0)||(dx<0&&dy<0)){
//positive
c=c+1;
}
else{
//negative
c=c-1;
}
d=d+2*abs(dx)-2*abs(dy);
glVertex2d(c,r);
}
}
}
}








void Draw()
{

glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POINTS);
bresline(80,60,90,100);
glEnd();
glFlush();

}

int main(int argc,char**argv)
{
printf("\nEnter the first point: ");
scanf("%d%d",&xa,&ya);
printf("\nEnter the second point: ");
scanf("%d%d",&xb,&yb);
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(0, 0);
glutInitWindowSize(640, 480);
glutCreateWindow("BreshnamLine");
glClearColor(1.0, 1.0, 1.0, 0);
glColor3f(0.0, 0.0, 0.0);
gluOrtho2D(0, 640, 0, 480);
glutDisplayFunc(Draw);
glutMainLoop();

return 0;
}
