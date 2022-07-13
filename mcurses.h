#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <clocale>
#include <csignal>
#include <cmath>
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include <ctime>
#include <limits>
#include <random>
#include "termios.h"
using namespace std;
#pragma once
#ifndef MCURSES_H
#define MCURSES_H
#define INPUTBUFFER 255
#define DEFAULTBG ' '
#define COLOR1PART string("\033["+ to_string(int(
#define COLOR2PART ))+"m")
#define INPUTBUFFER 255
namespace mcurses{
class mcurses_kernel {
public:
const char FBLACK = 30;//0
const char FRED = 31;//1
const char FGREEN = 32;//2
const char FYELLOW = 33;//3
const char FBLUE = 34;//4
const char FMAGENTA = 35;//5
const char FCYAN = 36;//6
const char FGRAY = 37;//7
const char FLRED = 38;//8
const char FWHITE = 39;//9
const char FLGREEN = 92;//10
const char FLYELLOW = 93;//11
const char FLBLUE = 94;//12
const char FLMAGENTA = 95;//13
const char FLCYAN = 96;//14
const char FLGRAY = 97;//15
const char FLWHITE = 39;//15
const char BBLACK = 40;//0
const char BRED = 41;//1
const char BGREEN = 42;//2
const char BYELLOW = 43;//3
const char BBLUE = 44;//4
const char BMAGENTA = 45;//5
const char BCYAN = 46;//6
const char BWHITE = 47;//7
const char BGRAY = 100;//8
const char BLGRAY = 100;//9
const char BLRED = 101;//10
const char BLGREEN = 102;//11
const char BLYELLOW = 103;//12
const char BLBLUE = 104;//13
const char BLMAGENTA = 105;//14
const char BLCYAN = 106;//15
const char BLWHITE = 107;//16
const char* DEFAULT = "\033[0m";
mcurses_kernel(){
x = 1;
y = 1;
aspect = 1;
background = DEFAULTBG;
for(int i = 0; i < INPUTBUFFER; i++) CFI.push_front('\0');
}
mcurses_kernel(float x, float y, float aspect) {
y++;
this->x = y;
this->y = x;
this->aspect = aspect;
this->x *= aspect;
background = DEFAULTBG;
for(int i = 0; i < INPUTBUFFER; i++) CFI.push_front('\0');
clear();
}
mcurses_kernel(float x, float y, float aspect, char background) : mcurses_kernel(x, y, aspect)
{this->background = background;}
static char getch() {
char buf = 0;
struct termios old = {0};
fflush(stdout);
if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
old.c_lflag &= ~ICANON;
old.c_lflag &= ~ECHO;
old.c_cc[VMIN]  = 1;
old.c_cc[VTIME] = 0;
if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
if (read(0, &buf, 1) < 0) perror("read()");
old.c_lflag |= ICANON;
old.c_lflag |= ECHO;
if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
return buf;
}
string getColor(const string color, const bool fg){
if(fg){
if (color == "BLACK") return COLOR1PART FBLACK COLOR2PART;
if (color == "RED") return COLOR1PART FRED COLOR2PART;
if (color == "GREEN") return COLOR1PART FGREEN COLOR2PART;
if (color == "YELLOW") return COLOR1PART FYELLOW COLOR2PART;
if (color == "BLUE") return COLOR1PART FBLUE COLOR2PART;
if (color == "CYAN") return COLOR1PART FCYAN COLOR2PART;
if (color == "MAGENTA") return COLOR1PART FMAGENTA COLOR2PART;
if (color == "WHITE") return COLOR1PART FWHITE COLOR2PART;
if (color == "GRAY") return COLOR1PART FGRAY COLOR2PART;
if (color == "LRED") return COLOR1PART FLRED COLOR2PART;
if (color == "LGREEN") return COLOR1PART FLGREEN COLOR2PART;
if (color == "LYELLOW") return COLOR1PART FLYELLOW COLOR2PART;
if (color == "LBLUE") return COLOR1PART FLBLUE COLOR2PART;
if (color == "LCYAN") return COLOR1PART FLCYAN COLOR2PART;
if (color == "LMAGENTA") return COLOR1PART FLMAGENTA COLOR2PART;
if (color == "LGRAY") return COLOR1PART FLGRAY COLOR2PART;
if (color == "LWHITE") return COLOR1PART FLWHITE COLOR2PART;
}
else{
if (color == "BLACK") return COLOR1PART BBLACK COLOR2PART;
if (color == "RED") return COLOR1PART BRED COLOR2PART;
if (color == "GREEN") return COLOR1PART BGREEN COLOR2PART;
if (color == "YELLOW") return COLOR1PART BYELLOW COLOR2PART;
if (color == "BLUE") return COLOR1PART BBLUE COLOR2PART;
if (color == "CYAN") return COLOR1PART BCYAN COLOR2PART;
if (color == "MAGENTA") return COLOR1PART BMAGENTA COLOR2PART;
if (color == "WHITE") return COLOR1PART BWHITE COLOR2PART;
if (color == "GRAY") return COLOR1PART BGRAY COLOR2PART;
if (color == "LRED") return COLOR1PART BLRED COLOR2PART;
if (color == "LGREEN") return COLOR1PART BLGREEN COLOR2PART;
if (color == "LYELLOW") return COLOR1PART BLYELLOW COLOR2PART;
if (color == "LBLUE") return COLOR1PART BLBLUE COLOR2PART;
if (color == "LCYAN") return COLOR1PART BLCYAN COLOR2PART;
if (color == "LMAGENTA") return COLOR1PART BLMAGENTA COLOR2PART;
if (color == "LWHITE") return COLOR1PART BLWHITE COLOR2PART;
if (color == "LGRAY") return COLOR1PART BLGRAY COLOR2PART;
}
if (color == "NONE") return "";
return DEFAULT;
}
string getColorName(const int id){
switch(id){
case 0:return "BLACK";
case 1:return "WHITE";
case 2:return "CYAN";
case 3:return "RED";
case 4:return "GREEN";
case 5:return "GRAY";
case 6:return "YELLOW";
case 7:return "MAGENTA";
case 8:return "LMAGENTA";
case 9:return "LGREEN";
case 10:return "LGRAY";
case 11:return "LYELLOW";
case 12:return "LRED";
case 13:return "LCYAN";
case 14:return "BLUE";
case 15:return "LBLUE";
case 16:return "LWHITE";
default:return "NONE";
}
}
mcurses_kernel setLocale(const int category, const char* locale) {setlocale(category, locale);return *this;}
void exitProgram(const int result, const char* message){
setCursor(0,y);
cout << "Exit message: " << message << endl;
exit(result);
}
mcurses_kernel setCursor(const float x, const float y){
cout << "\033[" + to_string(int(y+1)) + ";" + to_string(int(x)) + "f";
cursorX = x;
cursorY = y;
return *this;
}
mcurses_kernel moveCursorX(const float x){
if(x > 0) cout << "\033[" + to_string(int(x)) << "C";
else if(x < 0) cout << "\033[" + to_string(int(x)) << "D";
cursorX += x;
return *this;
}
mcurses_kernel moveCursorY(const float y){
if(y > 0) cout << "\033[" + to_string(int(y+1)) << "A";
else if(y < 0) cout << "\033[" + to_string(int(y+1)) << "B";
cursorY += (y+1);
return *this;
}
mcurses_kernel clear(){
cout << "\033[2J";
setCursor(0,0);
return *this;
}
mcurses_kernel drawPoint(float x, float y, string bgColor) {
return drawPoint(x,y,bgColor,bgColor,background);
}
mcurses_kernel drawPoint(float x, float y, string bgColor, char background) {
return drawPoint(x,y,bgColor,bgColor,background);
}
mcurses_kernel drawPoint(float x, float y, const string color, const string bgColor) {
return drawPoint(x,y,color,bgColor,background);
}
mcurses_kernel drawPoint(float x,float y,string color,string bgColor,const char background) {
x *= aspect;
color = getColor(color, true);
bgColor = getColor(bgColor, false);
string pixel = color;
pixel += bgColor;
if (color == "NONE") pixel = " ";
else {
pixel += char(background);
pixel += DEFAULT;
}
if(background != '\n')
setCursor(x+this->aspect,y);
for (int i = 0; i < this->aspect &&
x <= this->x &&
y <= this->y; i++) {
cout << pixel;
}
return *this;
}
mcurses_kernel print(string text, float x, float y, string color, string bgColor) {
string toOut =
getColor(color, true)+
getColor(bgColor, false)+
text+
DEFAULT;
setCursor((x+1)*aspect, y);
cout << toOut;
return *this;
}

float getX(){return x;}
float getY(){return y;}
float getAspect(){return aspect;}
float getCursorX(){return cursorX;}
float getCursorY(){return cursorY;}
char getBackground(){return background;}
string getBackgroundColor(){return backgroundColor;}
mcurses_kernel setX(const float x){this->x=x;return *this;}
mcurses_kernel setY(const float y){this->y=y;return *this;}
mcurses_kernel setAspect(const float aspect){this->aspect=aspect;return *this;}
mcurses_kernel setBackground(const char background){this->background=background;return *this;}
mcurses_kernel setBackgroundColor(const string backgroundColor){this->backgroundColor=backgroundColor;return *this;}

public:
float x, y, aspect, cursorX, cursorY;
char background;
string backgroundColor;
list <char> CFI; //Chars From Input
};
class mcurses_module : public mcurses_kernel{
public:
mcurses_module(float x, float y, float aspect) : mcurses_kernel(x, y, aspect){}
mcurses_module(float x, float y, float aspect, char background) : mcurses_kernel(x, y, aspect, background){}
};
class mcurses_simple_figures : public mcurses_module{
public:
mcurses_kernel* screen;
mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen) : mcurses_module(x,y,aspect){
this->screen = screen;
this->aspect = aspect;
this->x = x;
this->y = y;
}
mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen,const char background) : mcurses_simple_figures(x,y,aspect,screen)
{screen->setBackground(background);}

mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string bgColor) {
for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
screen->drawPoint((float)i, (float)k, bgColor);
return *this;
}
mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const char background) {
for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
screen->drawPoint((float)i, (float)k, color, background);
return *this;
}
mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const string bgColor) {
for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
screen->drawPoint((float)i, (float)k, color, bgColor);
return *this;
}
mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const string bgColor,const char background) {
for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
screen->drawPoint((float)i, (float)k, color, bgColor,background);
return *this;
}
mcurses_simple_figures drawLine(float x,float y,float size,bool vertical,const string color) {
if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color);
else for(int k = x; k < size+x; k++) drawPoint(k,y,color);
return *this;
}
mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color,const char background) {
if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,background);
else for(int k = x; k < size+x; k++) drawPoint(k,y,color,background);
return *this;
}
mcurses_simple_figures drawLine(float x,float y,float size,bool vertical,const string color,const string bgColor) {
if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor);
else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor);
return *this;
}
mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color,const string bgColor,const char background) {
if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor,background);
else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor,background);
return *this;
}
mcurses_simple_figures drawBorder(const float x,float y,const float width,const float height,float size,const string color) {
if(size!=0){
while(size >= width || size >= height)size-=1;
drawLine(x, y, width, false, color);//x-up
drawLine(x, y, height, true, color);//y-left
drawLine(x, y + height, width, false, color);//x-down
drawLine(x + width-1, y, height + 1, true, color);//y-right
if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
return *this;
}
return *this;
}
mcurses_simple_figures drawBorder(const float x,const float y,const float width,const float height,float size,const string color,const char background) {
if(size!=0){
while(size >= width || size >= height)size-=1;
drawLine(x, y, width, false, color, background);
drawLine(x, y, height, true, color, background);
drawLine(x, y + height, width, false, color, background);
drawLine(x + width-1, y, height + 1, true, color, background);
if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color,background);
}
return *this;
}
mcurses_simple_figures drawBorder(const float x,float y,const float width,const float height,float size,const string color,const string bgColor) {
if(size!=0){
while(size >= width || size >= height)size-=1;
drawLine(x, y, width, false, color, bgColor);//x-up
drawLine(x, y, height, true, color, bgColor);//y-left
drawLine(x, y + height, width, false, color, bgColor);//x-down
drawLine(x + width-1, y, height + 1, true, color, bgColor);//y-right
if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor);
return *this;
}
return *this;
}
mcurses_simple_figures drawBorder(const float x,const float y,const float width,const float height,float size,const string color,const string bgColor,const char background) {
if(size!=0){
while(size >= width || size >= height)size-=1;
drawLine(x, y, width, false, color, bgColor, background);
drawLine(x, y, height, true, color, bgColor, background);
drawLine(x, y + height, width, false, color, bgColor, background);
drawLine(x + width-1, y, height + 1, true, color, bgColor, background);
if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor,background);
}
return *this;
}
mcurses_simple_figures drawBackground(const string color) {
for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
for (int i = 0; i < int(screen->getY()); i++)
screen->drawPoint((float)i, (float)k, color, color);
screen->setBackgroundColor(color);
return *this;
}
mcurses_simple_figures drawBackground(const string color, const char backgroundd) {
for (int i = 0; i < int(screen->getY()); i++)
for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
screen->drawPoint((float)k, (float)i, color, color, backgroundd);
screen->setBackgroundColor(color);
return *this;
}
};
class mcurses_colored_figures : public mcurses_module{
public:
mcurses_kernel* screen;

//mcurses_simple_figures() : mcurses_module(){}
mcurses_colored_figures(float x,float y,float aspect,mcurses_kernel*screen) : mcurses_module(x, y, aspect){this->screen=screen;}
mcurses_colored_figures(float x,float y,float aspect,mcurses_kernel*screen,char background) : mcurses_colored_figures(x, y, aspect,screen){this->screen=screen;}

mcurses_colored_figures drawPointStripesH(float x,float y,const string firstColor,const string secondColor){
if(int(x)%2==0) screen->drawPoint((float)y, (float)x, firstColor, secondColor);
else screen->drawPoint((float)y, (float)x, secondColor, firstColor);
return *this;
}
mcurses_colored_figures drawPointStripesV(float x,float y,const string firstColor,const string secondColor) const{
if(int(y)%2==0) screen->drawPoint((float)y, (float)x, firstColor, secondColor);
else screen->drawPoint((float)y, (float)x, secondColor, firstColor);
return *this;
}
mcurses_colored_figures drawPointCross(float x,float y,const string firstColor,const string secondColor,bool type){
if (int(y) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, secondColor);
else screen->drawPoint((float) y, (float) x, secondColor, firstColor);
if (int(x) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawPointRandom(float x, float y){
screen->drawPoint((float) x, (float) y, randomColorName(), randomColorName());
return *this;
}
mcurses_colored_figures drawPointStripesH(float x,float y,const string firstColor,const string secondColor,char background) const{
if(int(x)%2==0) screen->drawPoint((float)y, (float)x, secondColor, firstColor, background);
else screen->drawPoint((float)y, (float)x, firstColor, secondColor, background);
return *this;
}
mcurses_colored_figures drawPointStripesV(float x,float y,const string firstColor,const string secondColor,char background) const{
if(int(y)%2==0) screen->drawPoint((float)y, (float)x, firstColor, firstColor);
else screen->drawPoint((float)y, (float)x, secondColor, secondColor);
return *this;
}
mcurses_colored_figures drawPointCross(float x,float y,const string firstColor,const string secondColor,bool type,char background){
if (int(y) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, firstColor);
else screen->drawPoint((float) y, (float) x, secondColor, secondColor);
if (int(x) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, firstColor);
return *this;
}
mcurses_colored_figures drawPointRandom(float x,float y,char background){
screen->drawPoint((float) x, (float) y, randomColorName(), randomColorName());
return *this;
}

mcurses_colored_figures drawRectangleStripesH(float x,float y,float width,float height,const string firstColor,const string secondColor) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointStripesH(k,i,firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawRectangleStripesHRandom(float x,float y,float width,float height) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleStripesH(x, y, width, height, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawRectangleStripesV(float x,float y,float width,float height,const string firstColor,const string secondColor) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointStripesV(k,i,firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawRectangleStripesVRandom(float x,float y,float width,float height) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleStripesV(x,y,width,height,firstColor,secondColor);
return *this;
}
mcurses_colored_figures drawRectangleCross(float x,float y,float width,float height,const string firstColor,const string secondColor,bool type) {
for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
if (k >= (int)x && k <= (int)x + (int)height)
for (int i = 0; i < int(screen->getY()); i++)
if (i >= (int)y && i <= (int)y + (int)width)
drawPointCross(k, i, firstColor, secondColor, type);
return *this;
}
mcurses_colored_figures drawRectangleCrossRandom(float x,float y,float width,float height,bool type) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleCross(x,y,width,height,firstColor,secondColor,type);
return *this;
}
mcurses_colored_figures drawRectangleRandom(float x, float y, float width, float height) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointRandom(i,k);
return *this;
}
mcurses_colored_figures drawRectangleStripesH(float x,float y,float width,float height,const string firstColor,const string secondColor,char background) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointStripesH(k,i,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawRectangleStripesHRandom(float x,float y,float width,float height,char background) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleStripesH(x,y,width,height,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawRectangleStripesV(float x,float y,float width,float height,const string firstColor,const string secondColor,char background) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointStripesV(k,i,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawRectangleStripesVRandom(float x,float y,float width,float height,char background) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleStripesV(x,y,width,height,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawRectangleCross(float x,float y,float width,float height,const string firstColor,const string secondColor,bool type,char background) {
for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
if (k >= (int)x && k <= (int)x + (int)height)
for (int i = 0; i < int(screen->getY()); i++)
if (i >= (int)y && i <= (int)y + (int)width)
drawPointCross(k, i, firstColor, secondColor, type, background);
return *this;
}
mcurses_colored_figures drawRectangleCrossRandom(float x,float y,float width,float height,const bool type,char background) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawRectangleCross(x,y,width,height,firstColor,secondColor,type,background);
return *this;
}
mcurses_colored_figures drawRectangleRandom(float x,float y,float width,float height,char background) {
for (int i = 0; i < int(y + width); i++)
if (i >= (int)y && i <= (int)y + (int)width)
for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
if (k >= (int)x && k <= (int)x + (int)height)
drawPointRandom(k,i,background);
return *this;
}

mcurses_colored_figures drawLineStripesH(float x,float y,float size,bool vertical,const string firstColor,const string secondColor) {
if (!vertical) for(int i = y; i < size+y; i++) drawPointStripesH(x, (float)i, firstColor, secondColor);
else for(int k = x; k < size+x; k++) drawPointStripesH((float)k, y, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawLineStripesHRandom(float x,float y,float size,bool vertical) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawLineStripesH(x,y,size,vertical,firstColor,secondColor);
return *this;
}
mcurses_colored_figures drawLineStripesV(float x,float y,float size,bool vertical,const string firstColor,const string secondColor) const {
if (!vertical) for(int i = y; i < size+y; i++) drawPointStripesV(x,(float)i,firstColor,secondColor);
else for(int k = x; k < size+x; k++) drawPointStripesV((float)k,y,firstColor,secondColor);
return *this;
}
mcurses_colored_figures drawLineStripesVRandom(float x,float y,float size,bool vertical) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawLineStripesV(x,y,size,vertical,firstColor,secondColor);
return *this;
}
mcurses_colored_figures drawLineRandom(float x,float y,float size,bool vertical) {
if (vertical) for(int i = y; i < size+y; i++) drawPointRandom(x,i);
else for(int k = x; k < size+x; k++) drawPointRandom(k,y);
return *this;
}
mcurses_colored_figures drawLineStripesH(float x,float y,float size,bool vertical,const string firstColor,const string secondColor,char background) const {
if (!vertical) for(int i = y; i < size+y; i++) drawPointStripesH(x,i,firstColor,secondColor,background);
else for(int k = x; k < size+x; k++) drawPointStripesH(k,y,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawLineStripesHRandom(float x,float y,float size,bool vertical,char background) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawLineStripesH(x,y,size,vertical,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawLineStripesV(float x, float y, float size, bool vertical,const string firstColor, const string secondColor, char background) const {
if (!vertical) for(int i = y; i < size+y; i++) drawPointStripesV(x,i,firstColor,secondColor,background);
else for(int k = x; k < size+x; k++) drawPointStripesV(k,y,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawLineStripesVRandom(float x, float y, float size, bool vertical, char background) {
const string firstColor = randomColorName(), secondColor = randomColorName();
drawLineStripesV(x,y,size,vertical,firstColor,secondColor,background);
return *this;
}
mcurses_colored_figures drawLineRandom(float x, float y, float size, bool vertical, char background) {
if (vertical) for(int i = y; i < size+y; i++) drawPointRandom(x,i,background);
else for(int k = x; k < size+x; k++) drawPointRandom(k,y,background);
return *this;
}

mcurses_colored_figures drawBorderStripesH(float x,float y,float width,float height,float size,const string firstColor,const string secondColor) {
while(size >= width || size >= height)size-=1;
drawLineStripesH(x, y, width, false, firstColor, secondColor);//x-up
drawLineStripesH(x, y, width, true, firstColor, secondColor);//y-left
drawLineStripesH(x, y + height, width, false, firstColor, secondColor);//x-down
drawLineStripesH(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBorderStripesHRandom(float x,float y,float width,float height,float size) {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBorderStripesH(x,y,width,height,size, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBorderStripesV(float x,float y,float width,float height,float size,const string firstColor,const string secondColor) {
while(size >= width || size >= height)size-=1;
drawLineStripesV(x, y, width, false, firstColor, secondColor);//x-up
drawLineStripesV(x, y, width, true, firstColor, secondColor);//y-left
drawLineStripesV(x, y + height, width, false, firstColor, secondColor);//x-down
drawLineStripesV(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBorderStripesVRandom(float x,float y,float width,float height,float size) {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBorderStripesV(x,y,width,height,size, firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBorderRandom(float x,float y,float width,float height,float size) {
while(size >= width || size >= height)size--;
drawLineRandom(x, y, width, false);//y-up
drawLineRandom(x, y, height, true);//x-left
drawLineRandom(x, y + height-1, width, false);//y-down
drawLineRandom(x + width-1, y, height-1, true);//x-right
if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1);
return *this;
}
mcurses_colored_figures drawBorderStripesH(float x,float y,float width,float height,float size,const string firstColor,const string secondColor,char background) {
while(size >= width || size >= height)size-=1;
drawLineStripesH(x, y, width, false, firstColor, secondColor, background);
drawLineStripesH(x, y, height, true, firstColor, secondColor, background);
drawLineStripesH(x, y + height-1, width, false, firstColor, secondColor, background);
drawLineStripesH(x + width-1, y, height + 1, true,  firstColor, secondColor, background);
if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
return *this;
}
mcurses_colored_figures drawBorderStripesHRandom(float x,float y,float width,float height,float size,char background) {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBorderStripesH(x,y,width,height,size, firstColor, secondColor, background);
return *this;
}
mcurses_colored_figures drawBorderStripesV(float x,float y,float width,float height,float size,const string firstColor,const string secondColor,char background) {
while(size >= width || size >= height)size-=1;
drawLineStripesV(x, y, width, false, firstColor, secondColor, background);
drawLineStripesV(x, y, width, true, firstColor, secondColor, background);
drawLineStripesV(x, y + height, width, false, firstColor, secondColor, background);
drawLineStripesV(x + width, y, width + 1, true, firstColor, secondColor, background);
if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
return *this;
}
mcurses_colored_figures drawBorderStripesVRandom(float x,float y,float width,float height,float size,char background) {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBorderStripesV(x,y,width,height,size, firstColor, secondColor, background);
return *this;
}
mcurses_colored_figures drawBorderRandom(float x,float y,float width,float height,float size,char background) {
while(size >= width || size >= height)size-=1;
drawLineRandom(x, y, width, false, background);//y-up
drawLineRandom(x, y, height, true, background);//x-left
drawLineRandom(x, y + height, width, false, background);//y-down
drawLineRandom(x + width, y, height, true, background);//x-right
if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1,background);
return *this;
}

mcurses_colored_figures drawBackgroundStripesH(const string firstColor,const string secondColor){
float screenX = screen->getX();
float screenY = screen->getY();
float screenAspect = screen->getAspect();
for (int k = 0; k < int(screenX/screenAspect); k++)
for (int i = 0; i < int(screenY); i++)
if(k%2==0) screen->drawPoint((float)i, (float)k, firstColor, firstColor);
else screen->drawPoint((float)i, (float)k, secondColor, secondColor);
return *this;
}
mcurses_colored_figures drawBackgroundStripesHRandom(){
string firstColor = randomColorName(), secondColor = randomColorName();
drawBackgroundStripesH(firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBackgroundStripesV(const string firstColor,const string secondColor) {
for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
for (int i = 0; i < int(screen->getY()); i++)
if (i % 2 == 0) screen->drawPoint((float) i, (float) k, firstColor, firstColor);
else screen->drawPoint((float) i, (float) k, secondColor, secondColor);
return *this;
}
mcurses_colored_figures drawBackgroundStripesVRandom() {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBackgroundStripesV(firstColor, secondColor);
return *this;
}
mcurses_colored_figures drawBackgroundCross(const string firstColor,const string secondColor,bool type) {
for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
for (int i = 0; i < int(screen->getY()); i++)
drawPointCross(k, i, firstColor, secondColor, type);
return *this;
}
mcurses_colored_figures drawBackgroundCrossRandom(bool type) {
string firstColor = randomColorName(), secondColor = randomColorName();
drawBackgroundCross(firstColor, secondColor, type);
return *this;
}
mcurses_colored_figures drawBackgroundRandom(){
for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
for (int i = 0; i < int(screen->getY()); i++)
screen->drawPoint((float) i, (float) k, randomColorName(), randomColorName());
return *this;
}

int randomINT(int min,int max){

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> dist6(min,max);
int num = dist6(rng);
return num;
}
string randomColorName(){
return getColorName(randomINT(0,16));
}
};
class Imcurses_widget{
public:
virtual void render() =0;
virtual void show() =0;
virtual void hide() =0;

int isHided = 1;
float x, y;
};
class progress_bar : public Imcurses_widget{
public:
mcurses_simple_figures *msf;
progress_bar(const float x, const float y, const float aspect,
const float width, const float height,
const float borderSize, mcurses_simple_figures &msf){
this->x=x;
this->y=y;
this->msf = &msf;
this->width=width;
this->height=height;
this->borderSize=borderSize;
}
progress_bar(const float x, const float y, const float aspect,
mcurses_simple_figures &msf, const char background)
: progress_bar(x, y, aspect, width, height, borderSize, msf) {
msf.screen->setBackground(background);
}
void show() override{ isHided = 0;}
void hide() override{ isHided = 2;}
void render() override{
if(isHided == 0){
float PX = 100 / maxValue * value / width;
msf->drawBorder(x, y, width + (borderSize*2), height + borderSize, borderSize,
backgroundForegroundColor,backgroundBackgroundColor,
background)
.drawRectangle(x + borderSize, y + borderSize, width, height,
unfilledForegroundColor, unfilledBackgroundColor,
unfilledBackground)
.drawRectangle(x + borderSize, y + borderSize, float(PX), height,
filledForegroundColor, filledBackgroundColor,
filledBackground);
}else if(isHided == 2){
msf->drawRectangle(x, y, width + (borderSize*2), height + borderSize, backgroundForegroundColor, backgroundBackgroundColor);
}
}

private:
char isHided = 1;
float width = 1,
height = 1,
borderSize = 1;
int value = 0,
maxValue = 1,
step = 1;
char background = '-',
filledBackground = '#',
unfilledBackground = '.';
string backgroundBackgroundColor = "WHITE",
backgroundForegroundColor = "BLACK",
filledBackgroundColor = "GREEN",
filledForegroundColor = "WHITE",
unfilledBackgroundColor = "GRAY",
unfilledForegroundColor = "WHITE";

public:
progress_bar PBsetValue(const float value) {
this->value = value;
render();
return *this;
}
progress_bar PBsetMaxValue(const float maxValue) {
this->maxValue = maxValue;
render();
return *this;
}
progress_bar PBsetStep(const float step) {
this->step = step;
render();
return *this;
}
progress_bar PBsetBackground(const char background) {
this->background = background;
render();
return *this;
}
progress_bar PBsetFilledBackground(const char filledBackground) {
this->filledBackground = filledBackground;
render();
return *this;
}
progress_bar PBsetUnfilledBackground(const char unfilledBackground) {
this->unfilledBackground = unfilledBackground;
render();
return *this;
}
progress_bar
PBsetBackgroundBackgroundColor(const string backgroundBackgroundColor) {
this->backgroundBackgroundColor = backgroundBackgroundColor;
render();
return *this;
}
progress_bar
PBsetBackgroundForegroundColor(const string backgroundForegroundColor) {
this->backgroundForegroundColor = backgroundForegroundColor;
render();
return *this;
}
progress_bar
PBsetFilledBackgroundColor(const string filledBackgroundColor) {
this->filledBackgroundColor = filledBackgroundColor;
render();
return *this;
}
progress_bar
PBsetFilledForegroundColor(const string filledForegroundColor) {
this->filledForegroundColor = filledForegroundColor;
render();
return *this;
}
progress_bar
PBsetUnfilledBackgroundColor(const string unfilledBackgroundColor) {
this->unfilledBackgroundColor = unfilledBackgroundColor;
render();
return *this;
}
progress_bar
PBsetUnfilledForegroundColor(const string unfilledForegroundColor) {
this->unfilledForegroundColor = unfilledForegroundColor;
render();
return *this;
}
progress_bar PBsetX(const float x) {
this->x = x;
return *this;
}
progress_bar PBsetY(const float y) {
this->y = y;
return *this;
}
progress_bar PBsetWidth(const float width) {
this->width = width;
return *this;
}
progress_bar PBsetHeight(const float height) {
this->height = height;
return *this;
}
progress_bar PBsetBorderSize(const float borderSize) {
this->borderSize = borderSize;
return *this;
}
float PBgetX() { return x; }
float PBgetY() { return y; }
float PBgetWidth() { return width; }
float PBgetHeight() { return height; }
float PBgetBorderSize() { return borderSize; }
float PBgetValue() { return value; }
float PBgetMaxValue() { return maxValue; }
float PBgetStep() { return step; }
char PBgetBackground() { return background; }
char PBgetFilledBackground() { return filledBackground; }
char PBgetUnfilledBackground() { return unfilledBackground; }
string PBgetBackgroundBackgroundColor() { return backgroundBackgroundColor; }
string PBgetBackgroundForegroundColor() { return backgroundForegroundColor; }
string PBgetFilledBackgroundColor() { return filledBackgroundColor; }
string PBgetFilledForegroundColor() { return filledForegroundColor; }
string PBgetUnfilledBackgroundColor() { return unfilledBackgroundColor; }
string PBgetUnfilledForegroundColor() { return unfilledForegroundColor; }
};
class container : public Imcurses_widget{
public:
mcurses_simple_figures *msf;
void render() override{
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->render();
}
}
void show() override{
isHided = 0;
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->show();
}
}
void hide() override{
isHided = 2;
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->hide();
}
}
container(mcurses_simple_figures &msf){
this->msf = &msf;
}
container(const float x, const float y, const float aspect,
mcurses_simple_figures &msf, const char background)
: container(msf) {
msf.screen->setBackground(background);
}

container add(Imcurses_widget* widget){
mwvector.push_back(widget);
return *this;
}

vector<Imcurses_widget*> getAll(){
return mwvector;
}
container moveX(float x){
this->x += x;
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->x += x;
}
return *this;
}
container moveY(float y){
this->y += y;
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->y += y;
getAll()[i]->render();
}
return *this;
}
private:
vector<Imcurses_widget*> mwvector;
};
class window : public container{
public:
static enum shadows{UP_LEFT=0,UP,UP_RIGHT,RIGHT,DOWN_RIGHT,DOWN,DOWN_LEFT,LEFT} shadowTypes;

mcurses_simple_figures *msf;
window(mcurses_simple_figures &msf, float x, float y, float width, float height, string backgroundColor, int shadow, int shadowType)
: window(msf,x,y,width,height,backgroundColor,shadow,shadowType,"BLACK"){}
window(mcurses_simple_figures &msf, float x, float y, float width, float height, string backgroundColor, int shadow, int shadowType, string shadowColor) : container(msf){
this->x=x;
this->y=y;
this->shadow = shadow;
this->backgroundColor = backgroundColor;
this->shadowColor = shadowColor;
this->width = width;
this->height = height;
this->shadowType=shadowType;
this->msf=&msf;
}

void render() override{
if(shadow != 0){
switch(shadowType){
case UP_LEFT:
msf->drawBorder(x-shadow,y-shadow,width,height-1,shadow,shadowColor);
break;
case UP:
msf->drawBorder(x,y-shadow,width,height-1,shadow,shadowColor);
break;
case UP_RIGHT:
msf->drawBorder(x+1,y-shadow,width+shadow-1,height-1,shadow,shadowColor);
break;
case DOWN_LEFT:
msf->drawBorder(x-shadow,y+shadow,width,height-1,shadow,shadowColor);
break;
case DOWN:
msf->drawBorder(x,y+shadow,width,height-1,shadow,shadowColor);
break;
case DOWN_RIGHT:
msf->drawBorder(x+shadow,y+shadow,width,height-1,shadow,shadowColor);
break;
case LEFT:
msf->drawBorder(x-shadow,y,width,height-1,shadow,shadowColor);
break;
case RIGHT:
msf->drawBorder(x+shadow,y,width,height-1,shadow,shadowColor);
break;
}
}
msf->drawRectangle(x,y,width,height,backgroundColor);
for(int i = 0; i < getAll().size(); i++){
getAll()[i]->render();
}
}
void show() override{
isHided = 0;
}
void hide() override{
isHided = 2;
}
private:
int shadow = 1,
shadowType;
float width, height;
string backgroundColor = "WHITE",
shadowColor = "BLACK";
};
class label : public Imcurses_widget{
public:
mcurses_simple_figures* msf;
label(mcurses_simple_figures &msf,float x, float y,string text){
this->x = x;
this->y = y;
this->msf = &msf;
this->text = text;
}
void render() override{
msf->print(text,x,y,"RED","WHITE");
}
void show() override{
isHided = 0;
render();
}
void hide() override{
isHided = 2;
}
private:
string text = "";
public:
float getX(){return x;}
float getY(){return y;}
string getText(){return text;}
label setX(float x){
this->x = x;
return *this;
}
label setY(float y){
this->x = x;
return *this;
}
label setText(string text){
this->text = text;
return *this;
}
};
}
#endif
