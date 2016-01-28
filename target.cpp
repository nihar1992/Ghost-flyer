#include <stdio.h>
#include<string.h>
#include <math.h>
#include "fssimplewindow.h"
#include<time.h>
#include"target.h"
const double YsPi=3.1415927;

void Target::Calculatedist(double planeX,double planeY,double planeZ)
{
	dist=sqrt(pow((planeX-centeroftip[0]),2)+pow((planeY-centeroftip[1]),2)+pow((planeZ-centeroftip[2]),2));
	//printf("Distance %lf",dist);
	InitializeCannonBall(planeX,planeY,planeZ);
}
void Target:: GetTargetPoints(double tpx, double tpy,double tpz)
{
	x=tpx;
	y=tpy;
	z=tpz;
}
void Target::Checkhitcube()
{
	if(cannonballstate==1)
	{
		if((pos[0]>centeroftip[0]+500 || pos[0]<centeroftip[0]-500) || (pos[1]<centeroftip[1]-500 || pos[1]>centeroftip[1]+500) || (pos[2]<centeroftip[2]-500 || pos[2]>centeroftip[2]+500))
		{
			cannonballstate=0;
		}
	}
}
void Target::InitializeTarget(double cubex[],double cubey[],double cubez[],double artx[],double arty[],double artz[])
{
	
		for(int i=0;i<24;i++)
		{
			cubeX[i]=cubex[i];
			cubeY[i]=cubey[i];
			cubeZ[i]=cubez[i];
		}
		for(int i=0;i<4;i++)
		{
			artX[i]=artx[i];
			artY[i]=arty[i];
			artZ[i]=artz[i];
		}
		Cvel=10;
		dt=0.05;
		theta=YsPi/2;
		phi=YsPi/2;
		cannonballstate=0;
		targetstate=1;
		pos[0]=0;
		pos[1]=0;
		pos[2]=0;
	
}

void Target::DrawTarget()
{
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
		glBegin(GL_QUADS); glColor4ub(128,128,128,200);//right face 
		for(int i=0;i<8;i++) 
		{ 
			glVertex3d(x+cubeX[i],y+cubeY[i],z+cubeZ[i]); 
		} 
		glColor4ub(64,64,64,200); 
		for(int i=8;i<16;i++) 
		{ 
			glVertex3d(x+cubeX[i],y+cubeY[i],z+cubeZ[i]); 
		} 
		glColor4ub(32,32,32,200);
		for(int i=16;i<24;i++) 
		{ 
			glVertex3d(x+cubeX[i],y+cubeY[i],z+cubeZ[i]); 
		} 
	/*for(int i=0;i<8;i++) 
	{ 
		glVertex3d(x+cubeX[i],y+cubeY[i],z+cubeZ[i]); 
	}*/
		double hei=20;
		double x3=artX[0]+hei*cos(theta)*sin(phi);
		double y3=artY[0]+hei*sin(theta)*sin(phi);
		double z3=artZ[0]+hei*cos(phi);
		double x4=artX[1]+hei*cos(theta)*sin(phi);
		double y4=artY[1]+hei*sin(theta)*sin(phi);
		double z4=artZ[1]+hei*cos(phi);
		double x5=artX[2]+hei*cos(theta)*sin(phi);
		double y5=artY[2]+hei*sin(theta)*sin(phi);
		double z5=artZ[2]+hei*cos(phi);
		double x6=artX[3]+hei*cos(theta)*sin(phi);
		double y6=artY[3]+hei*sin(theta)*sin(phi);
		double z6=artZ[3]+hei*cos(phi);
	
		centerofArt[0]=(artX[0]+artX[1])/2+x;
		centerofArt[1]=artY[0]+y;
		centerofArt[2]=(artZ[0]+artZ[2])/2+z;
		//printf("Center of Artilery : %lf %lf %lf",centerofArt[0], centerofArt[1],centerofArt[2]);
		centeroftip[0]=(x3+x4)/2+x;
		centeroftip[1]=y3+y;
		centeroftip[2]=(z3+z5)/2+z;
		rad=2;
		//printf("\ncenteroftip[0]: %lf centeroftip[1]: %lf centeroftip[2]: %lf ",centeroftip[0],centeroftip[1],centeroftip[2]);
		//Front Face
		glColor3ub(128,128,128);
		glVertex3d(artX[0]+x,artY[0]+y,artZ[0]+z);
		glVertex3d(x3+x,y3+y,z3+z);
		glVertex3d(x4+x,y4+y,z4+z);
		glVertex3d(artX[1]+x,artY[1]+y,artZ[1]+z);
		//Back face
		glColor3ub(128,128,128);
		glVertex3d(artX[2]+x,artY[2]+y,artZ[2]+z);
		glVertex3d(x5+x,y5+y,z5+z);
		glVertex3d(x6+x,y6+y,z6+z);
		glVertex3d(artX[3]+x,artY[3]+y,artZ[3]+z);
		//Bottom face
		glColor3ub(64,64,64);
		glVertex3d(artX[0]+x,artY[0]+y,artZ[0]+z);
		glVertex3d(artX[1]+x,artY[1]+y,artZ[1]+z);
		glVertex3d(artX[2]+x,artY[2]+y,artZ[2]+z);
		glVertex3d(artX[3]+x,artY[3]+y,artZ[3]+z);
		//Top face
		glColor3ub(0,0,0);
		glVertex3d(x3+x,y3+y,z3+z);
		glVertex3d(x4+x,y4+y,z4+z);
		glVertex3d(x6+x,y6+y,z6+z);
		glVertex3d(x5+x,y5+y,z5+z);
	
		glColor3ub(64,64,64);
		glVertex3d(artX[0]+x,artY[0]+y,artZ[0]+z);
		glVertex3d(artX[2]+x,artY[2]+y,artZ[2]+z);
		glVertex3d(x5+x,y5+y,z5+z);
		glVertex3d(x3+x,y3+y,z3+z);
	
		glColor3ub(64,64,64);
		glVertex3d(artX[1]+x,artY[1]+y,artZ[1]+z);
		glVertex3d(x4+x,y4+y,z4+z);
		glVertex3d(x6+x,y6+y,z6+z);
		glVertex3d(artX[3]+x,artY[3]+y,artZ[3]+z);
   
		glEnd();
	
	
}
void DrawSphere(double r,double &cx, double &cy, double &cz) 
 { 
	int lats=360;
	int longs=360;
    int i, j;

	for(i = 0; i <= lats; i++) 
	{
		double lat0 = YsPi * (-0.5 + (double) (i - 1) / lats);
		double z0  = sin(lat0);
		double zr0 =  cos(lat0);
    
		double lat1 = YsPi * (-0.5 + (double) i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);
    
		glBegin(GL_QUAD_STRIP);

        for(j = 0; j <= longs; j++) 
		{
			double lng = 2 * YsPi * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
    
			glNormal3f(cx+r*x*zr0, cy+r*y*zr0, cz+r*z0);
            glVertex3f(cx+r*x*zr0, cy+r*y*zr0, cz+r*z0);
            glNormal3f(cx+r*x*zr1, cy+r*y*zr1, cz+r*z1);
			glVertex3f(cx+r*x*zr1, cy+r*y*zr1, cz+ r*z1);
		}
        
		glEnd();
	}
}	
void Target::DrawCannonBall()
{
	if(targetstate==1)
	{
	DrawSphere(rad,pos[0],pos[1],pos[2]);
	}
}

void Target::GetPlaneCoordinates(double planeX,double planeY,double planeZ)
{	
	
	double R;
	R=sqrt(pow(planeX-centerofArt[0],2)+pow(planeY-centerofArt[1],2)+pow(planeZ-centerofArt[2],2));
	phi=acos((planeZ-centerofArt[2])/R);
	//printf("\n%lf",phi*180/YsPi);
	theta=acos((planeX-centerofArt[0])/(R*sin(phi)));
	//printf("\n%lf",theta*180/YsPi);
	//DrawTarget();
	
}
void Target::InitializeCannonBall(double planeX,double planeY,double planeZ)
{
	if(dist<500)
		{
			cannonballstate=1;
			
	memcpy(pos,centeroftip,sizeof(pos));
	
	double vecx=planeX-pos[0];
	double vecy=planeY-pos[1];
	double vecz=planeZ-pos[2];
	vx=vecx/sqrt(pow(vecx,2)+pow(vecy,2)+pow(vecz,2));
	vy=vecy/sqrt(pow(vecx,2)+pow(vecy,2)+pow(vecz,2));
	vz=vecz/sqrt(pow(vecx,2)+pow(vecy,2)+pow(vecz,2));
	pX=planeX;
	pY=planeY;
	pZ=planeZ;
	
	}
}
void Target::MoveCannonBall()
{
	if(targetstate==1)
	{
		pos[0]+=Cvel*vx;
		pos[1]+=Cvel*vy;
		pos[2]+=Cvel*vz;
		//printf("\nVx %lf Vy %lf Vz %lf",pX,pY,pZ);
		//printf("\nPositions : %lf %lf %lf theta: %lf phi : %lf",pos[0],pos[1],pos[2],theta,phi);
		glColor3ub(0,0,255);
		glColor3ub(0,0,0);
		DrawCannonBall();
	}
			
}

 
