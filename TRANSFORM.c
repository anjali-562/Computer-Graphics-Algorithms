#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int xa,ya,xb,yb;
int v;
int tx,ty;
int sx,sy;
int xf,yf;
float angle;
int xr,yr;
int shx,shy;
float input[3][10];
float output[3][10];
float transform[3][3];

void multiply(){
for(int i=0;i<3;i++){
for(int j=0;j<v;j++){
 output[i][j]=0;
for(int k=0;k<3;k++){
output[i][j]=output[i][j]+transform[i][k]*input[k][j];
}
}
}
}

void translation(){
printf("\nEnter the value of tx: ");
scanf("%d",&tx);
printf("\nEnter the value of ty: ");
scanf("%d",&ty);
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
 if(i==j){
   transform[i][j]=1;
 }
 else{
 transform[i][j]=0;
 }
}
}
transform[0][2]=tx;
transform[1][2]=ty;

}
void scaling(){
printf("Enter scaling matrix:");
printf("Enter Sx,Sy:");
scanf("%d%d",&sx,&sy);

printf("Enter xf,yf:");
scanf("%d%d",&xf,&yf);

for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
if(i==j){
transform[i][j]=1;
}
else{
transform[i][j]=0;
}
}
}
transform[0][0]=sx;
transform[1][1]=sy;
transform[0][2]=xf*(1-sx);
transform[1][2]=yf*(1-sy);
}

void rotation(){
printf("Enter angle:");
scanf("%f",&angle);

angle = angle * M_PI / 180;

printf("Enter xr,yr:");
scanf("%d%d",&xr,&yr);

for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
if(i==j){
transform[i][j]=1;
}
else{
transform[i][j]=0;
}
}
}
transform[0][0]=cos(angle);
transform[0][1]=-sin(angle);
transform[0][2]=xr*(1-cos(angle))+yr*(sin(angle));

transform[1][0]=sin(angle);
transform[1][1]=cos(angle);
transform[1][2]=yr*(1-cos(angle))-xr*(sin(angle));
}

void shear(){
int ch;
printf("\nEnter your choice:");
printf("\n1.X shear:");
printf("\n2.Y shear:");
scanf("%d",&ch);

if(ch==1){
printf("\nEnter the value of x shear: ");
scanf("%d",&shx);
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
if(i==j){
transform[i][j]=1;
}
else{
transform[i][j]=0;
}
}
}
transform[0][1]=shx;
}
else
{
printf("\nEnter the value of y shear: ");
scanf("%d",&shy);
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
if(i==j){
transform[i][j]=1;
}
else{
transform[i][j]=0;
}
}
}
transform[1][0]=shy;
}

}

void reflection(){
int ch;
printf("\nEnter your choice:");
printf("\n1.X axis:");
printf("\n2.Y axis:");
printf("\n3.perpendicular to the axis:");
printf("\n4.along y=x:");
printf("\n5.along y=-x:");
scanf("%d",&ch);
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
if(i==j){
transform[i][j]=1;
}
else{
transform[i][j]=0;
}
}
}
switch(ch){
case 1:{
transform[1][1]=-1;
break;
}
case 2:{
transform[0][0]=-1;
break;
}
case 3:{
transform[1][1]=-1;
transform[0][0]=-1;
break;
}
case 4:{
transform[0][0]=0;
transform[0][1]=1;
transform[1][0]=1;
transform[1][1]=0;
break;
}
case 5:{
transform[0][0]=0;
transform[0][1]=-1;
transform[1][0]=-1;
transform[1][1]=0;
break;
}
}
}





int Round(float a){
return(int)(a+0.5);
}
void ddaline(int xa,int ya,int xb,int yb){
int dx,dy,steps;
dx=xb-xa;
dy=yb-ya;
if(abs(dx)>abs(dy)){
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
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    ddaline(-320,0,320,0);
    
    ddaline(0,-240,0,240);
    glEnd();

    // Draw original shape in RED
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for(int i=0;i<v;i++){
        ddaline(input[0][i], input[1][i], input[0][(i+1)%v], input[1][(i+1)%v]);
    }
  

    // Draw translated shape in GREEN
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for(int i=0;i<v;i++){
        ddaline(output[0][i], output[1][i], output[0][(i+1)%v], output[1][(i+1)%v]);
    }
    glEnd();

    glFlush();
}



int main(int argc,char**argv)
{
printf("\nEnter the value of vertex: ");
scanf("%d",&v);
for(int i=0;i<v;i++){
printf("\nEnter the value of coordinate x: ");
scanf("%f",&input[0][i]);
printf("\nEnter the value of coordinate y: ");
scanf("%f",&input[1][i]);
input[2][i]=1;
}
printf("Input Matrice:\n");
for(int i=0;i<3;i++){
for(int j=0;j<v;j++){
printf("%f",input[i][j]);
printf("\t");
}
printf("\n");
}

//translation();
//scaling();
//rotation();
//shear();
reflection();
multiply();
printf("Output Matrice:\n");
for(int i=0;i<3;i++){
for(int j=0;j<v;j++){
printf("%f",output[i][j]);
printf("\t");
}
printf("\n");
}


glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);

glutInitWindowSize(640,480);
glutCreateWindow("Translation");
glClearColor(1.0,1.0,1.0,0.0);
glColor3f(0.0,0.0,0.0);
gluOrtho2D(-320,320,-240,240);
glutDisplayFunc(Draw);
glutMainLoop();
return 0;
}
