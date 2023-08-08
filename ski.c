/*
 *  Lighting
 *
 *  Demonstrates basic lighting using a cube, sphere and icosahedron.
 *
 *  Key bindings:
 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F8         Change ball increment
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  o          Cycles through objects
 *  +/-        Change field of view of perspective
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int lh = 0;       //disc rotation
int mh = 0;       //chair movement
int gh = 0;
bool flag = true;
int fov=55;       //  Field of view (for perspective)
int obj=1;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=1000;     //  Size of world
double e1 = 0;   //initial eye in x coordinate
double e2 = 1000;   //eye height stays constant
double e3 = 500;   //initial eye in z coordinate
double dist = 200; //amount we move forward by
double c1 = 0;  //eye position in x
double c3 = 250;  //eye position in z
double d1 = 0; //offset between eye and viewpoint in x
double d3 = 0; //offset between eye and viewpoint in z
// Light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   1300;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   2000;  // Elevation of light
float z[65][65];       //  DEM data
float zmin=+1e8;       //  DEM lowest location
float zmax=-1e8;       //  DEM highest location
float zmag=20;          //  DEM magnification
unsigned int texture[10];
typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
#define n 500
vtx is[n];

void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode == 1){
      gluPerspective(fov,asp,dim/16,16*dim);
   }
   else if(mode == 2){
      gluPerspective(fov,asp,dim/16,16*dim);
   }
   // //  Orthogonal transformation
   // else if(mode == 3){
   //    glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
   // }
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

void Lodge(){

}

void Disc(){
   //rotating disc
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glPushMatrix();
   glTranslated(0,0,8.1);
   glRotated(lh,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
   for (int th=0;th<=360;th+=10)
   {
      if(count%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glVertex3d(5.5*Cos(th), 7, 5.5*Sin(th)); glTexCoord2f(X,Y); 
      glVertex3d(5.5*Cos(th), 8, 5.5*Sin(th)); glTexCoord2f(X,Y1); 
      count +=1;
   }
   glEnd();
   glPopMatrix();
   //inner disc
   glPushMatrix();
   glTranslated(0,0,8.1);
   glRotated(lh,0,1,0);
   glBegin(GL_QUAD_STRIP);
   int count1 = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
   for (int th=0;th<=360;th+=10)
   {
      if(count1%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glVertex3d(5*Cos(th), 7, 5*Sin(th)); glTexCoord2f(X,Y); 
      glVertex3d(5*Cos(th), 8, 5*Sin(th)); glTexCoord2f(X,Y1); 
      count1 +=1;
   }
   glEnd();
   glPopMatrix();
   //top of disc
   glPushMatrix();
   glTranslated(0,0,8.1);
   glRotated(lh,0,1,0);
   glBegin(GL_QUAD_STRIP);
   int count2 = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
   for (int th=0;th<=360;th+=10)
   {
      if(count2%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(0, 1, 0);
      glVertex3d(5*Cos(th), 8, 5*Sin(th)); glTexCoord2f(X,Y); 
      glVertex3d(6*Cos(th), 8, 6*Sin(th)); glTexCoord2f(X,Y1); 
      count2 +=1;
   }
   glEnd();
   glPopMatrix();
   //bottom of disc
   glPushMatrix();
   glTranslated(0,0,8.1);
   glRotated(lh,0,1,0);
   glBegin(GL_QUAD_STRIP);
   int count3 = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
   for (int th=0;th<=360;th+=10)
   {
      if(count3%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(0, -1, 0);
      glVertex3d(5*Cos(th), 7, 5*Sin(th)); //glTexCoord2f(X,Y); 
      glVertex3d(6*Cos(th), 7, 6*Sin(th)); // glTexCoord2f(X,Y1); 
      count3 +=1;
   }
   glEnd();
   glPopMatrix();
   //small inner circle axis
   glPushMatrix();
   glTranslated(0,0,8.1);
   glRotated(lh,0,1,0);
   //disc arms
   glBegin(GL_QUADS);
   for (int th=0;th<=360;th+=60)
   {
      //top arms
      glNormal3d(0, 1, 0);
      glTexCoord2f(1,1); glVertex3d(1*Cos(th), 8, 1*Sin(th));  
      glTexCoord2f(0,1); glVertex3d(1*Cos(th+20), 8, 1*Sin(th+20));  
      glTexCoord2f(0,0); glVertex3d(5*Cos(th+20), 8, 5*Sin(th+20)); 
      glTexCoord2f(1,0); glVertex3d(5*Cos(th), 8, 5*Sin(th));  
      //bottom arms
      glNormal3d(0, -1, 0);
      glTexCoord2f(0,1); glVertex3d(1*Cos(th), 7, 1*Sin(th));  
      glTexCoord2f(1,1); glVertex3d(1*Cos(th+20), 7, 1*Sin(th+20));  
      glTexCoord2f(1,0); glVertex3d(5*Cos(th+20), 7, 5*Sin(th+20)); 
      glTexCoord2f(0,0); glVertex3d(5*Cos(th), 7, 5*Sin(th)); 
      //sides
      glNormal3d(Cos(th),0,Sin(th));
      glTexCoord2f(1,0); glVertex3d(1*Cos(th), 7, 1*Sin(th));  
      glTexCoord2f(1,1); glVertex3d(1*Cos(th), 8, 1*Sin(th));  
      glTexCoord2f(0,1); glVertex3d(5*Cos(th), 8, 5*Sin(th)); 
      glTexCoord2f(0,0); glVertex3d(5*Cos(th), 7, 5*Sin(th));  
      //sides 
      glNormal3d(Cos(th),0,Sin(th));
      glTexCoord2f(0,0); glVertex3d(1*Cos(th+20), 7, 1*Sin(th+20));  
      glTexCoord2f(0,1); glVertex3d(1*Cos(th+20), 8, 1*Sin(th+20));  
      glTexCoord2f(1,1); glVertex3d(5*Cos(th+20), 8, 5*Sin(th+20)); 
      glTexCoord2f(1,0); glVertex3d(5*Cos(th+20), 7, 5*Sin(th+20));  
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3d(0,1,0);
   glTexCoord2f(1,1); glVertex3d(0,8,0);
   for(int th=0; th<=360; th+=10){
      if(th%10 == 0){
         glTexCoord2f(0,0); glVertex3d(Sin(th),8,Cos(th));
      }
      else{
         glTexCoord2f(1,0); glVertex3d(Sin(th),8,Cos(th));
      }
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3d(0,-1,0);
   glTexCoord2f(1,1); glVertex3d(0,7,0);
   for(int th=0; th<=360; th+=10){
      if(th%10 == 0){
         glTexCoord2f(0,0); glVertex3d(Sin(th),7,Cos(th));
      }
      else{
         glTexCoord2f(1,0); glVertex3d(Sin(th),7,Cos(th));
      }
   }
   glEnd();
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   int count4 = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
   for (int th=0;th<=360;th+=10)
   {
      if(count4%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glVertex3d(1*Cos(th), 7, 1*Sin(th)); glTexCoord2f(X,Y); 
      glVertex3d(1*Cos(th), 8, 1*Sin(th)); glTexCoord2f(X,Y1); 
      count4 +=1;
   }
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void Post(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glColor3f(1,1,1);
   //post in ground
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1.5*Cos(th), 0, 1.5*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1.5*Cos(th), 20, 1.5*Sin(th));  
      count += 1;
   }
   glEnd();
   //top part
   glBegin(GL_QUADS);
   glNormal3d(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-6,20,1.5);
   glTexCoord2f(0,1); glVertex3d(-6,20,-1.5);
   glTexCoord2f(1,1); glVertex3d(6,20,-1.5);
   glTexCoord2f(1,0); glVertex3d(6,20,1.5);
   //sides
   glNormal3d(-1,0,0);
   glTexCoord2f(1,0); glVertex3d(-6,20,1.5);
   glTexCoord2f(0,0); glVertex3d(-6,20,-1.5);
   glTexCoord2f(1,0); glVertex3d(-6,20.5,-1.5);
   glTexCoord2f(1,1); glVertex3d(-6,20.5,1.5);

   glNormal3d(0,0,-1);
   glTexCoord2f(1,0); glVertex3d(-6,20,-1.5);
   glTexCoord2f(0,0); glVertex3d(6,20,-1.5);
   glTexCoord2f(0,1); glVertex3d(6,20.5,-1.5);
   glTexCoord2f(1,1); glVertex3d(-6,20.5,-1.5);

   glNormal3d(1,0,0);
   glTexCoord2f(0,0); glVertex3d(6,20,1.5);
   glTexCoord2f(1,0); glVertex3d(6,20,-1.5);
   glTexCoord2f(1,1); glVertex3d(6,20.5,-1.5);
   glTexCoord2f(0,1); glVertex3d(6,20.5,1.5);

   glNormal3d(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-6,20,1.5);
   glTexCoord2f(1,0); glVertex3d(6,20,1.5);
   glTexCoord2f(1,1); glVertex3d(6,20.5,1.5);
   glTexCoord2f(0,1); glVertex3d(-6,20.5,1.5);
   //top part
   glNormal3d(0,1,0);
   glTexCoord2f(0,0); glVertex3d(-6,20.5,1.5);
   glTexCoord2f(1,0); glVertex3d(6,20.5,1.5);
   glTexCoord2f(1,1); glVertex3d(6,20.5,-1.5);
   glTexCoord2f(0,1); glVertex3d(-6,20.5,-1.5);
   glEnd();
   //top bars
   glPushMatrix();
   glTranslated(2.5,20.5,0);
   glRotated(-30,0,0,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.375*Cos(th), 0, .375*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(.375*Cos(th), 5, .375*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-2.5,20.5,0);
   glRotated(30,0,0,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.375*Cos(th), 0, .375*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(.375*Cos(th), 5, .375*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();
   //top horizontal bar
   glPushMatrix();
   glTranslated(0,25,0);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(-6.25, .375*Cos(th), .375*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(6.25, .375*Cos(th), .375*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();
   //left rollers
   glPushMatrix();
   glTranslated(-13.5,20,0);
   glRotated(-90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-13.5,20,3);
   glRotated(-90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-13.5,20,-3);
   glRotated(-90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-13.5,20,-6);
   glRotated(-90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   //right rollers
   glPushMatrix();
   glTranslated(13.5,20,0);
   glRotated(90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(13.5,20,3);
   glRotated(90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(13.5,20,-3);
   glRotated(90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();

   glPushMatrix();
   glTranslated(13.5,20,-6);
   glRotated(90,0,0,1);
   glScaled(.25,1,.25);
   Disc();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   //cable
   glPushMatrix();
   glTranslated(6,21.8,0);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), Sin(th), 0);
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), -5); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 6.5);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6,21.8,0);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), Sin(th), 0);
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), -5); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 6.5);  
      count += 1;
   }
   glEnd();
   glPopMatrix();
}

void joint(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glPushMatrix();
   glTranslated(-.6,.4,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), -3, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), -1, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();
   
   glPushMatrix();
   glTranslated(-.3,0,0);
   glRotated(-20,0,0,1);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), -1, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 1, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-.1,.5,0);
   glRotated(-30,0,0,1);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 2, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();
   
   glPushMatrix();
   glTranslated(.8,2,0);
   glRotated(-40,0,0,1);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 2, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.7,3.25,0);
   glRotated(-70,0,0,1);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 3, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();
}

void quad(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glBegin(GL_QUADS);
   //top
glNormal3d(0,1,0);
   glVertex3d(-.5,1.5,0);
   glVertex3d(-.5,1.5,3);
   glVertex3d(37,1.5,3);
   glVertex3d(37,1.5,0);
   //right side
glNormal3d(1,0,0);
   glVertex3d(37,1.5,0);
   glVertex3d(37,1.5,3);
   glVertex3d(37,1,3);
   glVertex3d(37,1,0);
   //front side
glNormal3d(0,0,1);
   glVertex3d(-.5,1,3);
   glVertex3d(-.5,1.5,3);
   glVertex3d(37,1.5,3);
   glVertex3d(37,1,3);
   //left side
glNormal3d(-1,0,0);
   glVertex3d(-.5,1.5,0);
   glVertex3d(-.5,1.5,3);
   glVertex3d(-.5,1,3);
   glVertex3d(-.5,1,0);
   //back side
glNormal3d(0,0,-1);
   glVertex3d(-.5,1,0);
   glVertex3d(-.5,1.5,0);
   glVertex3d(37,1.5,0);
   glVertex3d(37,1,0);
   //bottom
glNormal3d(0,-1,0);
   glVertex3d(-.5,1,0);
   glVertex3d(-.5,1,3);
   glVertex3d(37,1,3);
   glVertex3d(37,1,0);
   glEnd();
}

void skiRun(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[6]);

   glBegin(GL_QUADS);
   glNormal3d(0,1,0);
   glTexCoord2f(1,0); glVertex3d(30,60,-60);
   glTexCoord2f(0,0); glVertex3d(-30,60,-60);
   glTexCoord2f(0,1); glVertex3d(-30,60,-100);
   glTexCoord2f(1,1); glVertex3d(30,60,-100);
   //slope
   glNormal3d(0,Sin(45),Cos(45));
   glTexCoord2f(1,0); glVertex3d(30,0,70);
   glTexCoord2f(0,0); glVertex3d(-30,0,70);
   glTexCoord2f(0,1); glVertex3d(-30,60,-60);
   glTexCoord2f(1,1); glVertex3d(30,60,-60);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glBegin(GL_QUAD_STRIP);

   glEnd();
}

//ski lift loading area
void skiLoad(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   //lift base
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   //top face
   glNormal3f(0,1,0);
   glTexCoord2f(1,0); glVertex3f(1,7,2);
   glTexCoord2f(0,0); glVertex3f(-1,7,2);
   glTexCoord2f(0,1); glVertex3f(-1,7,-1);
   glTexCoord2f(1,1); glVertex3f(1,7,-1);
   //front face
   glNormal3f(0,0,1);
   glTexCoord2f(1,0); glVertex3f(1,0,2);
   glTexCoord2f(0,0); glVertex3f(-1,0,2);
   glTexCoord2f(0,1); glVertex3f(-1,7,2);
   glTexCoord2f(1,1); glVertex3f(1,7,2);
   //back face
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(1,0,-1);
   glTexCoord2f(1,0); glVertex3f(-1,0,-1);
   glTexCoord2f(1,1); glVertex3f(-1,7,-1);
   glTexCoord2f(0,1); glVertex3f(1,7,-1);
   //right face
   glNormal3f(1,0,0);
   glTexCoord2f(0,1); glVertex3f(1,0,2);
   glTexCoord2f(1,0); glVertex3f(1,0,-1);
   glTexCoord2f(1,1); glVertex3f(1,7,-1);
   glTexCoord2f(0,0); glVertex3f(1,7,2);
   //left face
   glNormal3f(-1,0,0);
   glTexCoord2f(1,0); glVertex3f(-1,0,2);
   glTexCoord2f(0,0); glVertex3f(-1,0,-1);
   glTexCoord2f(0,1); glVertex3f(-1,7,-1);
   glTexCoord2f(1,1); glVertex3f(-1,7,2);
   glEnd();
   //wings
   glBegin(GL_TRIANGLES);
   //right face
   glNormal3f(1,0,0);
   glTexCoord2f(1,1); glVertex3f(1,7,2);
   glTexCoord2f(1,0); glVertex3f(1,5,2);
   glTexCoord2f(0,1); glVertex3f(.75,7,8);
   //left face
   glNormal3f(-1,0,0);
   glTexCoord2f(0,1); glVertex3f(-1,7,2);
   glTexCoord2f(0,0); glVertex3f(-1,5,2);
   glTexCoord2f(1,1); glVertex3f(-.75,7,8);
   glEnd();
   //top face
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(1,1); glVertex3f(1,7,2);
   glTexCoord2f(0,1); glVertex3f(-1,7,2);
   glTexCoord2f(0,0); glVertex3f(-.75,7,8);
   glTexCoord2f(1,0); glVertex3f(.75,7,8);
   //bottom face
   // glPushMatrix();
   // glRotated();
   // glNormal3f(0,-1,0);
   // glPopMatrix();
   glTexCoord2f(1,0); glVertex3f(1,5,2);
   glTexCoord2f(0,0); glVertex3f(-1,5,2);
   glTexCoord2f(0,1); glVertex3f(-.75,7,8);
   glTexCoord2f(1,1); glVertex3f(.75,7,8);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   //rotating disc
   Disc();

   //cable
   glPushMatrix();
   glTranslated(-6,7.5,7);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.2,7.5,7.7);
   glRotated(10,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.22,7.5,8.65);
   glRotated(20,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.1,7.5,9.5);
   glRotated(30,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-5.8,7.5,10.4);
   glRotated(40,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-5.34,7.5,11.27);
   glRotated(50,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-4.6,7.5,11.9);
   glRotated(50,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-4,7.5,12.6);
   glRotated(60,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-3.3,7.5,13.2);
   glRotated(70,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-2.5,7.5,13.7);
   glRotated(80,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-1.6,7.5,14.05);
   glRotated(90,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2.4);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,15,0);
   glRotated(180,0,0,1);
   glPushMatrix();
   glTranslated(-6,7.5,7);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.2,7.5,7.7);
   glRotated(10,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.22,7.5,8.65);
   glRotated(20,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6.1,7.5,9.5);
   glRotated(30,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-5.8,7.5,10.4);
   glRotated(40,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-5.34,7.5,11.27);
   glRotated(50,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-4.6,7.5,11.9);
   glRotated(50,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-4,7.5,12.6);
   glRotated(60,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-3.3,7.5,13.2);
   glRotated(70,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-2.5,7.5,13.7);
   glRotated(80,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 1); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 2);  
      count += 1;
   }
   glEnd();
   glPopMatrix();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6,7.5,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 0); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 8);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(6,7.5,8);
   glRotated(180,0,1,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 0); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), 8);  
      count += 1;
   }
   glEnd();
   glPopMatrix();
}

void cable(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(.4*Cos(th), .4*Sin(th), 0); 
      glTexCoord2f(X,Y1); glVertex3d(.4*Cos(th), .4*Sin(th), -11);  
      count += 1;
   }
   glEnd();
}

//ski chair
void chair(){
   // glEnable(GL_TEXTURE_2D);
   // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   // glBindTexture(GL_TEXTURE_2D,texture[2]);

   //top left joint
   joint();

   //top right joint
   glPushMatrix();
   glTranslated(36.2,0,0);
   glRotated(180,0,1,0);
   joint();
   glPopMatrix();

   //top bar
   glPushMatrix();
   glTranslated(.2,4.2,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(4, 1*Cos(th), 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(32, 1*Cos(th), 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //Front bar
   glPushMatrix();
   glTranslated(.2,-19.3,25.3);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(4, 1*Cos(th), 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(32, 1*Cos(th), 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //left side bar
   glPushMatrix();
   glTranslated(-.6,.4,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), -3, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), -15, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //right side bar
   glPushMatrix();
   glTranslated(36.8,.4,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), -3, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), -15, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //left seat bar
   glPushMatrix();
   glTranslated(-.6,-19.43,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 1*Sin(th), 6.8); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 1*Sin(th), 19);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //right seat bar
   glPushMatrix();
   glTranslated(36.8,-19.43,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 1*Sin(th), 6.8); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 1*Sin(th), 19);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //left arm rests
   glPushMatrix();
   glTranslated(-.6,-13,18);
   glRotated(90,0,1,0);
   joint();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-.6,-8.8,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 1*Sin(th), 0); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 1*Sin(th), 14);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(-.6,-15.5,18.6);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), -4, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //right arm rests
   glPushMatrix();
   glTranslated(36.8,-13,18);
   glRotated(90,0,1,0);
   joint();
   glPopMatrix();

   glPushMatrix();
   glTranslated(36.8,-8.8,0);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 1*Sin(th), 0); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 1*Sin(th), 14);  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslated(36.8,-15.5,18.6);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), -4, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //chair hook
   glPushMatrix();
   glTranslated(14.5,8,-4);
   glRotated(90,1,0,0);
   glScaled(.2,3,1);
   quad();
   glPopMatrix();

   //chair hook
   glPushMatrix();
   glTranslated(14.5,7,-.3);
   glRotated(90,0,0,1);
   joint();
   glPopMatrix();

   //hook bar
   glPushMatrix();
   glTranslated(10.3,10.9,-.3);
   glRotated(-15,0,0,1);
   glColor3f(1,1,1);
   glBegin(GL_QUAD_STRIP);
   count = 0;
   X = 1;
   Y = 0;
   Y1 = 1;
      for (int th=0;th<=360;th+=10)
   {
      if(count % 2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(1*Cos(th), 0, 1*Sin(th)); 
      glTexCoord2f(X,Y1); glVertex3d(1*Cos(th), 14, 1*Sin(th));  
      count += 1;
   }
   glEnd();
   glPopMatrix();

   //bottom left joint
   glPushMatrix();
   glTranslated(-.6,-18.8,4.3);
   glRotated(-90,0,1,0);
   glRotated(90,0,0,1);
   joint();
   glPopMatrix();

   //bottom right joint
   glPushMatrix();
   glTranslated(36.8,-18.8,4.3);
   glRotated(-90,0,1,0);
   glRotated(90,0,0,1);
   joint();
   glPopMatrix();

   //bottom left front joint
   glPushMatrix();
   glTranslated(0,-19.4,21.1);
   glRotated(90,1,0,0);
   joint();
   glPopMatrix();

   //bottom right front joint
   glPushMatrix();
   glTranslated(36.2,-19.4,21.1);
   glRotated(180,0,0,1);
   glRotated(90,1,0,0);
   joint();
   glPopMatrix();

   //wooden slats for bottom seat
   glPushMatrix();
   glTranslated(.2,-19.4,22);
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   //top
   glNormal3d(0,1,0);
   glVertex3d(1,1.5,0);
   glVertex3d(1,1.5,3);
   glVertex3d(35.5,1.5,3);
   glVertex3d(35.5,1.5,0);
   //right side
glNormal3d(1,0,0);
   glVertex3d(35.5,1.5,0);
   glVertex3d(35.5,1.5,3);
   glVertex3d(35.5,1,3);
   glVertex3d(35.5,1,0);
   //front side
   glNormal3d(0,0,1);
   glVertex3d(1,1,3);
   glVertex3d(1,1.5,3);
   glVertex3d(35.5,1.5,3);
   glVertex3d(35.5,1,3);
   //left side
glNormal3d(-1,0,0);
   glVertex3d(1,1.5,0);
   glVertex3d(1,1.5,3);
   glVertex3d(1,1,3);
   glVertex3d(1,1,0);
   //back side
glNormal3d(0,0,-1);
   glVertex3d(1,1,0);
   glVertex3d(1,1.5,0);
   glVertex3d(35.5,1.5,0);
   glVertex3d(35.5,1,0);
   //bottom
glNormal3d(0,-1,0);
   glVertex3d(1,1,0);
   glVertex3d(1,1,3);
   glVertex3d(35.5,1,3);
   glVertex3d(35.5,1,0);
   glEnd();
   glColor3f(1,0,0);
   glPopMatrix();

   //wooden slats
   glPushMatrix();
   glTranslated(.2,-19.4,17);
   quad();
   glPopMatrix();

   //wooden slats
   glPushMatrix();
   glTranslated(.2,-19.4,12);
   quad();
   glPopMatrix();

   //wooden slats
   glPushMatrix();
   glTranslated(.2,-19.4,7);
   quad();
   glPopMatrix();

   //wooden slats
   glPushMatrix();
   glTranslated(.2,-19.4,2);
   quad();
   glPopMatrix();

   //wooden slats for top seat
   glPushMatrix();
   glTranslated(.2,-1,0);
   glRotated(90,1,0,0);
   quad();
   glPopMatrix();

   glPushMatrix();
   glTranslated(.2,-6,0);
   glRotated(90,1,0,0);
   quad();
   glPopMatrix();

   glPushMatrix();
   glTranslated(.2,-11,0);
   glRotated(90,1,0,0);
   quad();
   glPopMatrix();

   // glDisable(GL_TEXTURE_2D);
}

void box(){
float white[] = {1,1,1,1};
float black[] = {0,0,0,1};
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
glEnable(GL_TEXTURE_2D);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
glBindTexture(GL_TEXTURE_2D,texture[0]);
glColor3f(1,1,1);
//Sides
glBegin(GL_QUADS);
//back
 glTexCoord2f(0,0); glVertex3f(-1,0,-1);
 glTexCoord2f(0,1); glVertex3f(-1,2,-1);
 glTexCoord2f(.25,1); glVertex3f(1,2,-1);
 glTexCoord2f(.25,0); glVertex3f(1,0,-1);
 //right side
 glTexCoord2f(.25,0); glVertex3f(1,0,-1);
 glTexCoord2f(.25,1); glVertex3f(1,2,-1);
 glTexCoord2f(.5,1); glVertex3f(1,2,1);
 glTexCoord2f(.5,0); glVertex3f(1,0,1);
 //front
 glTexCoord2f(.5,0); glVertex3f(1,0,1);
 glTexCoord2f(.5,1); glVertex3f(1,2,1);
 glTexCoord2f(.75,1); glVertex3f(-1,2,1);
 glTexCoord2f(.75,0); glVertex3f(-1,0,1);
//left side
 glTexCoord2f(1,0); glVertex3f(-1,0,-1);
 glTexCoord2f(1,1); glVertex3f(-1,2,-1);
 glTexCoord2f(.75,1); glVertex3f(-1,2,1);
 glTexCoord2f(.75,0); glVertex3f(-1,0,1);

//  Top 

//  glTexCoord2f(.25,.48); glVertex3f(1,2,-1);
//  glTexCoord2f(.48,.48); glVertex3f(1,2,1);
//  glTexCoord2f(.48,.98); glVertex3f(-1,2,1);
//  glTexCoord2f(.25,.98); glVertex3f(-1,2,-1);
 glEnd();
glDisable(GL_TEXTURE_2D);

glEnable(GL_TEXTURE_2D);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
glBindTexture(GL_TEXTURE_2D,texture[6]);
glBegin(GL_QUADS);
   glColor3ub(255,255,255);
   glNormal3d(0,1,0);
   glTexCoord2f(1,1); glVertex3f(1,0,-1);
   glTexCoord2f(1,0); glVertex3f(1,0,1);
   glTexCoord2f(0,0); glVertex3f(-1,0,1);
   glTexCoord2f(0,1); glVertex3f(-1,0,-1);
glEnd();
glDisable(GL_TEXTURE_2D);
}

void skiier(){

}

void Mountain(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_TRIANGLES);
   for (int th=0;th<=90;th+=5){
      glNormal3d(Cos(th), Sin(th), Sin(th));
      glTexCoord2f(1,1); glVertex3d(0, 1, 0);
      glTexCoord2f(1-(th/90),0); glVertex3d(Cos(th), 0, Sin(th));
      glNormal3d(Cos(th+5), Sin(th+5), Sin(th+5));
      glTexCoord2f(1-(th+5/90),0); glTexCoord2f(0,0); glVertex3d(Cos(th+5), 0, Sin(th+5));
    }
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

//makes tree leaves
void cone(){
    //  tree "leaves"
    //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_TRIANGLES);
   for (int th=0;th<=360;th+=5){
    glNormal3d(Cos(th), Sin(th), Sin(th));
    glTexCoord2f(1,1); glVertex3d(0, 1, 0);
    if(th%10 == 0){
      glTexCoord2f(4,0); glVertex3d(3*Cos(th), -2, 3*Sin(th));
      glNormal3d(Cos(th+5), Sin(th+5), Sin(th+5));
      glTexCoord2f(0,0); glVertex3d(3*Cos(th+5), -2, 3*Sin(th+5));
    }
    else{
      glTexCoord2f(1,0); glVertex3d(Cos(th), 0, Sin(th));
      glNormal3d(Cos(th+5), Sin(th+5), Sin(th+5));
      glTexCoord2f(0,0); glVertex3d(Cos(th+5), 0, Sin(th+5));
    }
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void Tree(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   //trunk
   glBegin(GL_QUAD_STRIP);
   int count = 0;
   int X = 1;
   int Y = 0;
   int Y1 = 1;
   for (int th=0;th<=360;th+=30)
   {
      if(count%2 == 0){
         X = 1;
         Y = 1;
         Y1 = 0;
      }
      else{
         X = 0;
      }
      glNormal3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y); glVertex3d(Cos(th), 0, Sin(th));
      glTexCoord2f(X,Y1); glVertex3d(Cos(th), 15, Sin(th));
      count +=1;
   }
   glEnd();
   //  tree "leaves"
   glPushMatrix();
   glTranslated(0,15,0);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,14,0);
   glScaled(1.2,1.2,1.2);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,13,0);
   glScaled(1.4,1.4,1.4);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,12,0);
   glScaled(1.6,1.6,1.6);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,11,0);
   glScaled(1.8,1.8,1.8);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,10,0);
   glScaled(2,2,2);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,9,0);
   glScaled(2.2,2.2,2.2);
   cone();
   glPopMatrix();
   glPushMatrix();
   glTranslated(0,8,0);
   glScaled(2.4,2.4,2.4);
   cone();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

void snow(){
   //  Offset, scale and rotate
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

   for(int i = -2000; i <2000; i+= 500){
      for(int j =-2000; j < 2000; j+=500){
         glPushMatrix();
         glTranslated(j,4000,i);
         glScaled(10,10,10);
         glColor3f(1,1,1);
         //  Bands of latitude
         glBegin(GL_QUADS);
         //bottom
         glNormal3d(0,-1,0);
         glVertex3d(-.5,0,.5);
         glVertex3d(-.5,0,-.5);
         glVertex3d(.5,0,-.5);
         glVertex3d(.5,0,.5);
         //back side
         glNormal3d(0,0,-1);
         glVertex3d(-.5,0,-.5);
         glVertex3d(-.5,1,-.5);
         glVertex3d(.5,1,-.5);
         glVertex3d(.5,0,-.5);
         //right side
         glNormal3d(1,0,0);
         glVertex3d(.5,0,-.5);
         glVertex3d(.5,1,-.5);
         glVertex3d(.5,1,.5);
         glVertex3d(.5,0,.5);
         //front side
         glNormal3d(0,0,1);
         glVertex3d(-.5,0,.5);
         glVertex3d(-.5,1,.5);
         glVertex3d(.5,1,.5);
         glVertex3d(.5,0,.5);
         //left side
         glNormal3d(-1,0,0);
         glVertex3d(-.5,0,.5);
         glVertex3d(-.5,1,.5);
         glVertex3d(-.5,1,-.5);
         glVertex3d(-.5,0,-.5);
         //top
         glNormal3d(0,1,0);
         glVertex3d(-.5,1,.5);
         glVertex3d(-.5,1,-.5);
         glVertex3d(.5,1,-.5);
         glVertex3d(.5,1,.5);
         glEnd();
         glPopMatrix();
      }
   }
}

void snowy(){
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   
   //snow
   glPushMatrix();
   glTranslated(0,-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-1000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-1500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-2000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-2500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-3000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-3500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,-4000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,4000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,3500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,3000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,2500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,2000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,1500-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,1000-mh,0);
   snow();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,500-mh,0);
   snow();
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode == 1)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = 1000 + 2*dim        *Sin(ph);
      double Ez = 2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,1200,-500 , 0,Cos(ph),0);

      // double Ex = -2*dim*Sin(th)*Cos(ph);
      // double Ey = 2*dim        *Sin(ph);
      // double Ez = 2*dim*Cos(th)*Cos(ph);
      // gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }

   //first person
   else if(mode == 2){
      gluLookAt(e1,e2,e3 , c1,e2,c3 , 0,1,0); //translations for the eyepoint 
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 25);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   //  Draw individual objects
   if (obj==1){
   //snow
   snowy();
   
   //sky box
    glPushMatrix();
    glScaled(2000,2000,2000);
    box();
    glPopMatrix();
   //mountain
    glPushMatrix();
    glTranslated(200,0,-1200);
    glScaled(1200,1200,1200);
    Mountain();
    glPopMatrix();
   //ski run
    glPushMatrix();
    glScaled(20,20,20);
    skiRun();
    glPopMatrix();
   //ski load area at bottom
    glPushMatrix();
    glTranslated(0,0,1700);
    glScaled(20,20,20);
    skiLoad();
    glPopMatrix();
    //first ski posts
    glPushMatrix();
    glTranslated(0,160,1000);
    glScaled(20,20,20);
    Post();
    glPopMatrix();
    //first set cables
    glPushMatrix();
    glTranslated(120,150,1705);
    glRotated(37.5,1,0,0);
    glScaled(20,20,67);
    cable();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-120,150,1705);
    glRotated(37.5,1,0,0);
    glScaled(20,20,67);
    cable();
    glPopMatrix();
   //second ski posts
    glPushMatrix();
    glTranslated(0,470,300);
    glScaled(20,20,20);
    Post();
    glPopMatrix();
    //second set cables
    glPushMatrix();
    glTranslated(120,596,905);
    glRotated(32.75,1,0,0);
    glScaled(20,20,52.25);
    cable();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-120,596,905);
    glRotated(32.75,1,0,0);
    glScaled(20,20,52.25);
    cable();
    glPopMatrix();
    //third ski posts
    glPushMatrix();
    glTranslated(0,783,-413);
    glScaled(20,20,20);
    Post();
    glPopMatrix();
    //third set of cables
    glPushMatrix();
    glTranslated(120,905,200);
    glRotated(32.75,1,0,0);
    glScaled(20,20,53);
    cable();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-120,905,200);
    glRotated(32.75,1,0,0);
    glScaled(20,20,53);
    cable();
    glPopMatrix();
   //ski load area at top
    glPushMatrix();
    glTranslated(0,1200,-1400);
    glRotated(180, 0,1,0);
    glScaled(20,20,20);
    skiLoad();
    glPopMatrix();
    //fourth set of cables
    glPushMatrix();
    glTranslated(120,1215,-500);
    glRotated(8.5,1,0,0);
    glScaled(20,20,84);
    cable();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-120,1215,-500);
    glRotated(8.5,1,0,0);
    glScaled(20,20,84);
    cable();
    glPopMatrix();
    //ski lift chair
    glPushMatrix();
    glTranslated(160,80,1750);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 2
    glPushMatrix();
    glTranslated(160,390,1300);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 3
    glPushMatrix();
    glTranslated(160,550,850);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 4
    glPushMatrix();
    glTranslated(160,800,400);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 5
    glPushMatrix();
    glTranslated(160,1000,-50);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 6
    glPushMatrix();
    glTranslated(160,1130,-500);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 7
    glPushMatrix();
    glTranslated(160,1210,-950);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
    //chair 8
    glPushMatrix();
    glTranslated(160,1280,-1400);
    glScaled(3,3,3);
    glRotated(180,0,1,0);
    chair();
    glPopMatrix();
   //chair 9
    glPushMatrix();
    glTranslated(-160,80,1750);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 10
    glPushMatrix();
    glTranslated(-160,390,1300);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 11
    glPushMatrix();
    glTranslated(-160,550,850);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 12
    glPushMatrix();
    glTranslated(-160,800,400);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 13
    glPushMatrix();
    glTranslated(-160,1000,-50);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 14
    glPushMatrix();
    glTranslated(-160,1130,-500);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 15
    glPushMatrix();
    glTranslated(-160,1210,-950);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
    //chair 16
    glPushMatrix();
    glTranslated(-160,1280,-1400);
    glScaled(3,3,3);
    chair();
    glPopMatrix();
   }
   else if (obj==2){
    glPushMatrix();
    glScaled(30,30,30);
    skiLoad();
    glPopMatrix();
   }
   else if (obj==3){
    glPushMatrix();
    glScaled(30,30,30);
    Tree();
    glPopMatrix();
   }
   else if(obj==4){
    glPushMatrix();
    glScaled(10,10,10);
    chair();
    glPopMatrix();
   }
   else if(obj==5){
      glPushMatrix();
      glScaled(20,20,20);
      Post();
      glPopMatrix();
   }
   else if(obj == 6){
      glPushMatrix();
      glScaled(200,200,200);
      Mountain();
      glPopMatrix();
   }

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      const double len=500;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpective":"First Person nav",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   lh = fmod(60*t,360.0);
   mh = fmod(600*t,2000.0);
   gh = fmod(600*t,450.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P'){
      mode = mode+1;
      mode = mode%2;
   }
   else if (ch == 'w' || ch == 'W'){
      e1 += dist*d1; //move forward calculations for x eye point
      e3 += dist*d3; //move forward calculations for z eye point
      c1 = e1+d1; //update eye position
      c3 = e3+d3; //update eye position
   }
   else if (ch == 's' || ch == 'S'){
      e1 -= dist*d1; //move backwards calculations for x eyepoint
      e3 -= dist*d3; //move backwards calculations for z eyepoint
      c1 = e1+d1;
      c3 = e3+d3;
   }
   else if (ch == 'a' || ch == 'A'){
      th -= 5;//turn left
      d1 = Cos(th);
      d3 = Sin(th);
      c1 = e1+d1;
      c3 = e3+d3;
   }
   else if (ch == 'd' || ch == 'D'){
      th += 5;//turn right
      d1 = Cos(th);
      d3 = Sin(th);
      c1 = e1+d1;
      c3 = e3+d3;
   }
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 10;
   else if (ch==']')
      ylight += 10;
   //  Ambient level
   else if (ch=='1' && ambient>0)
      ambient -= 5;
   else if (ch=='!' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='2' && diffuse>0)
      diffuse -= 5;
   else if (ch=='@' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='3' && specular>0)
      specular -= 5;
   else if (ch=='#' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Switch scene/object
   else if (ch == 'o')
      obj = (obj+1)%10;
   else if (ch == 'O')
      obj = (obj-1)%10;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project();
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project();
}

/*
 *  Random numbers from min to max to the power p
 */
static float frand(float min,float max,float p)
{
   return pow(rand()/(float)RAND_MAX,p)*(max-min)+min;
}

/*
 * Initialize icosasphere locations
 */
void Init()
{
   for (int i=0;i<n;i++)
   {
      float th = frand(0,360,1);
      float ph = frand(-90,+90,1);
      float r  = frand(0.1,0.7,3);
      is[i].x = r*Sin(th)*Cos(ph);
      is[i].y = r*Cos(th)*Cos(ph);
      is[i].z = r*Sin(ph) + 1.0;
   }
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize
   Init();
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400,400);
   glutCreateWindow("Dylan Smith HW6");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   texture[0] = LoadTexBMP("sky.bmp");
   texture[1] = LoadTexBMP("concrete.bmp");
   texture[2] = LoadTexBMP("gray.bmp");
   texture[3] = LoadTexBMP("bark.bmp");
   texture[4] = LoadTexBMP("evergreen.bmp");
   texture[5] = LoadTexBMP("mountain.bmp");
   texture[6] = LoadTexBMP("snow.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
