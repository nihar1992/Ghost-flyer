#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "camera.h"
#include "misc.h"
#include "orbiter.h"
#include "plane.h"
#include "terrain.h"
#include "miscellaneous.h"




void DrawSkyCube(double x1,double y1,double z1,double x2,double y2,double z2, int i)
{
   
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	double colour[6][4];
	//scene1: clear blue
	colour[0][0] = 0;
	colour[1][0] = 1;
	colour[2][0] = 1;
	colour[3][0]=  0;
	colour[4][0] = 0.2;
	colour[5][0]=  0.5;

	
	//scene 2: afternoon
	colour[0][1] = 0;
	colour[1][1] = 0.8;
	colour[2][1] = 0.9;
	colour[3][1] = 0.196078; 
	colour[4][1] = 0.196078;
	colour[5][1] = 0.8;

	//scene 3: sunset
	colour[0][2] =  1;
	colour[1][2] = 0.25;
	colour[2][2] = 0.0;
	colour[3][2] =  0.53; 
	colour[4][2] = 0.12;
	colour[5][2] =0.471;
	
	//scene4: night
	colour[0][3] =  0;
	colour[1][3] = 0.8;
	colour[2][3] = 0.8;
	colour[3][3] = 0.184314; 
	colour[4][3] =  0.184314 ;
	colour[5][3] =0.309804;

	i=i;
	//back
	
	
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x1,y1,z1);
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x2,y1,z1);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x2,y2,z1);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x1,y2,z1);

	//front
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x1,y1,z2);
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x2,y1,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x2,y2,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x1,y2,z2);

	//bottom
	//glColor3ub(0,100,200);
	glColor4f(0,0.8,0.9,0.5);
	glVertex3d(x1,y1,z1);
    glVertex3d(x2,y1,z1);
    glVertex3d(x2,y1,z2);
    glVertex3d(x1,y1,z2);
   
	//top
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x1,y2,z1);
    glVertex3d(x2,y2,z1);
    glVertex3d(x2,y2,z2);
    glVertex3d(x1,y2,z2);

	//left
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x1,y1,z1);
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x1,y1,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x1,y2,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x1,y2,z1);
	
	
	//right
	
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x2,y1,z1);
	glColor3f(colour[0][i],colour[1][i],colour[2][i]);
	glVertex3d(x2,y1,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x2,y2,z2);
	glColor3f(colour[3][i],colour[4][i],colour[5][i]);
	glVertex3d(x2,y2,z1);
	glDisable(GL_BLEND);

	glEnd();

}

void drawplane(const int counter)
{
	if(counter==1)
	{
		glColor3ub(0,255,0);
		//printf("\n colour changed to green");
	}
	else if(counter==2)
	{
		glColor3ub(0,255,255);
		//printf("\n colour changed to some colour");
	}
	else if(counter==3)
	{
		glColor3ub(0,0,255);
		//printf("\n colour changed to blue");
	}
	if(counter==1)
	{
		
		glRasterPos2d(300,100);
		YsGlDrawFontBitmap20x32("THE BAT X");
	}
	if(counter==2)
	{
		
		glRasterPos2d(300,100);
		YsGlDrawFontBitmap20x32("THE FA-HORNET");
	}
	if(counter==3)
	{
		
		glRasterPos2d(300,100);
		YsGlDrawFontBitmap20x32("THE DESTROYER");
	}

}
//
//double DotProduct(double Ax, double Ay, double Az, double Bx, double By, double Bz)
//{
//    return Ax*Bx+Ay*By+Az*Bz;
//}
//
//void crossproduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, double crossprod[])
//{
//    crossprod[0] = (Ay*Bz)-(By*Az);
//    crossprod[1] = -(Ax*Bz)+(Bx*Az);
//    crossprod[2] = (Ax*By)-(Ay*Bx);
//}

void Rotation( double &x, double &y, double &z)
{
	double r = 180/(3.1429*10000);
	double s=cos(r/2);
	double u[3];
		u[0]=sin(r/2)*0.0;
		u[1]=sin(r/2)*1.0;
		u[2]=sin(r/2)*0.0;

		double tempX=x;
		double tempZ=z;
		double tempY=y;

		double cross[3];
		crossproduct(u[0],u[1],u[2],tempX,tempY,tempZ, cross);

		x = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempX+ 2.0 *s*cross[0];
		y = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempY+ 2.0 *s*cross[1];
        z = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempZ+ 2.0 *s*cross[2];		
	
}


