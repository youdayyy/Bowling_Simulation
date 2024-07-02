#define GL_SILENCE_DEPRECATION
#include <cstring>
#include<iostream>
#include<stack>
#include<math.h>
#include <cmath>
#include<GL/glut.h> 
#include <unistd.h>
#include <vector>
using namespace std;
#define SPACEBAR 32
#define ESC 27
float posX = 0.0, posY = 0.0, posZ = 0.0;
int num = 0;
int roundNo = 1;
int flag[10]={0};
int otflag=0;
vector<string> finalScore;
struct Point{
int x;
int y;
}pins[10];
void assignvalues(){
pins[0].x = 35;
pins[0].y = 90;
pins[1].x = 45;
pins[1].y = 90;
pins[2].x = 55;
pins[2].y = 90;
pins[3].x = 65;
pins[3].y = 90;
pins[4].x = 40;
pins[4].y = 83;
pins[5].x = 50;
pins[5].y = 83;
pins[6].x = 60;
pins[6].y = 83;
pins[7].x = 45;
pins[7].y = 76;
pins[8].x = 55;
pins[8].y = 76;
pins[9].x = 50;
pins[9].y = 69;
}
void output()
{
glColor3f(1.0, 1.0, 1.0);
glRasterPos2f(2, 90);
int i;
string s1 = "INSTRUCTIONS";
string s2 = "1.Left and Right Arrow to move the ball";
string s3 = "2.Spacebar to launch the ball";
string s4 = "3.ESC to display score";
for (i = 0; i <s1.length(); i++) {
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, int(s1[i]));
}
glRasterPos2f(2, 87);
for (i = 0; i <s2.length(); i++) {
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, int(s2[i]));
}
glRasterPos2f(2, 84);
for (i = 0; i <s3.length(); i++) {
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, int(s3[i]));
}
glRasterPos2f(2, 81);
for (i = 0; i <s4.length(); i++) {
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, int(s4[i]));
}
s3 = "SCORES";
glColor3f(1.0, 1.0, 1.0);
glRasterPos2f(72, 90);
for (i = 0; i <s3.length(); i++) {
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, int(s3[i]));
}
s2="\n";
int posy = 87;
for (i = 0; i <finalScore.size();i++) {
glRasterPos2i(72, posy);
for(int j=0;j<finalScore[i].length();j++)
{
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,
int(finalScore[i][j]));
}
posy = posy - 2;
}
}
void outputscore(){
string s1 = "Round-";
string s2="\n";
s1.append(to_string(roundNo));
roundNo++;
s1.append(" Score-");
s1.append(to_string(num));
s1.append(s2);
num=0;
finalScore.push_back(s1);
}
void drawPath()
{
glLineWidth(10);
glBegin(GL_LINES);
glVertex3d(30.0, 0.0, 0.0);
glVertex3d(30.0, 100.0, 0.0);
glVertex3d(70.0, 0.0, 0.0);
glVertex3d(70.0, 100.0, 0.0);
glEnd();
}
void drawCircle(int x, int y,float r)
{
float theta;
glBegin(GL_POLYGON);
for (int k = 0; k < 360; k++)
{
theta = k * (3.1416 / 180);
glVertex2f(x + r * cos(theta), y + r * sin(theta));
}
glEnd();
}
void display(void) {
glClear(GL_COLOR_BUFFER_BIT);
//Border
glColor3f(0.2, 0.0, 0.4);
drawPath();
//Alley
glColor3f(0.2,0.2, 0.2);
glRectf(30.0, 0.0, 70.0, 100.0);
// Launching Line
glColor3f(1.0, 1.0, 1.0); // White
glBegin(GL_LINES);
glVertex2f(30.0, 27.0); // Start of the line
glVertex2f(70.0, 27.0); // End of the line
glEnd();
//Bowling Pins
for(int i =0;i<10;i++)
{
if(flag[i]==0){
glColor3f(0.0, 0.0, 0.0);
drawCircle(pins[i].x,pins[i].y,2.6);
glColor3f(0.0, 1.0, 1.0);
drawCircle(pins[i].x,pins[i].y,2);
}
}
//Bowling Ball
glPushMatrix();
glTranslatef(posX, posY, posZ);
glColor3f(1.0, 1.0, 0.0);
drawCircle(50,20, 5.5);
glPopMatrix();
output();
if(otflag==1){
outputscore();
otflag=0;
}
glutSwapBuffers();
}
void fallpin(){
float xfinal1 = 50 + posX;
for(int i=0;i<10;i++)
{
if(pins[i].x>=xfinal1 && pins[i].x<=xfinal1+6)
{
flag[i]=1;
}
else if(pins[i].x>=xfinal1-6 && pins[i].x<=xfinal1)
{
flag[i]=1;
}
}
}
float ball_unit = 1.0f;
void moveball()
{
if(posY<93){
posY+=ball_unit;
}
else{
glutIdleFunc(NULL);
return;
}
if(posY>53)
{
fallpin();
}
glutPostRedisplay();
}
void reassign()
{
for(int i=0;i<10;i++){
if(flag[i]==1)
{
num++;
}
flag[i]=0;
}
}
float move_unit = 0.5f;
void keyboardown(int key, int x, int y) {
switch (key) {
case GLUT_KEY_RIGHT:
posX += move_unit;
if(posX>=14)
{
posX-=move_unit;
}
break;
case GLUT_KEY_LEFT:
posX -= move_unit;
if(posX<=-14)
{
posX+=move_unit;
}
break;
case ESC:
posX=0;
posY=0;
otflag = 1;
glutIdleFunc(NULL);
reassign();
break;
case SPACEBAR:
glutIdleFunc(moveball);
break;
default:
break;
}
glutPostRedisplay();
}
void myinit() {
glClearColor(0.2, 0.0, 0.2, 1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}
int main(int argc, char** argv) {
assignvalues();
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(800, 800);
glutInitWindowPosition(0, 0);
glutCreateWindow("Bowling Simulation");
glutDisplayFunc(display);
glutSpecialFunc(keyboardown);
myinit();
glutMainLoop();
return 0;
}