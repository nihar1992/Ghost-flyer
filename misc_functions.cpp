#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plane.h"
#include "collision.h"
#include "fssimplewindow.h"

double DotProduct(double Ax, double Ay, double Az, double Bx, double By, double Bz)
{
    return Ax*Bx+Ay*By+Az*Bz;
}

void crossproduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, double crossprod[])
{
    crossprod[0] = (Ay*Bz)-(By*Az);
    crossprod[1] = -(Ax*Bz)+(Bx*Az);
    crossprod[2] = (Ax*By)-(Ay*Bx);
}

void CamRotate(double &tempcX,double &tempcY,double &tempcZ,double &ox,double &oy,double &oz,double &oxr,double &oyr,double &ozr, double r, double cam[], int hVSv)
{
	double s=cos(r/2);
	double u[3];
	double tempX1,tempY1,tempZ1;
	double cross[3];

	u[0]=sin(r/2)*0;
	u[1]=sin(r/2)*1;
	u[2]=sin(r/2)*0;

	
	crossproduct(u[0],u[1],u[2],tempcX,tempcY,tempcZ, cross);

	tempX1 = 2.0*DotProduct(u[0],u[1],u[2],tempcX,tempcY,tempcZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempcX+ 2.0 *s*cross[0];
	tempY1 = 2.0*DotProduct(u[0],u[1],u[2],tempcX,tempcY,tempcZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempcY+ 2.0 *s*cross[1];
    tempZ1 = 2.0*DotProduct(u[0],u[1],u[2],tempcX,tempcY,tempcZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempcZ+ 2.0 *s*cross[2];	
	
	if (hVSv==2)
	{
		cam[0]=oxr-tempX1;
		cam[1]=oyr-tempY1;
		cam[2]=ozr-tempZ1;
	}
	else
	{
		cam[0]=ox+tempX1;
		cam[1]=oy+tempY1;
		cam[2]=oz+tempZ1;
	}
}

void RotatePlane(Vec vertices[], int numbOfPnts, double x, double y, double z, double fx, double fy, double fz, double rx, double ry, double rz, double r, int hVSv, double b, double &cambInside)
{
	double s=cos(r/2);
	double u[3];
	double ub[3];
	double cross[3];

	if(hVSv==1 || hVSv==2)
	{
		u[0]=sin(r/2)*0.0;
		u[1]=sin(r/2)*1.0;
		u[2]=sin(r/2)*0.0;

		r=-r;

		ub[0]=sin(r/2)*fx;
		ub[1]=sin(r/2)*fy;
		ub[2]=sin(r/2)*fz;
	}

	else if(hVSv==3)
	{
		u[0]=sin(r/2)*rx;
		u[1]=sin(r/2)*ry;
		u[2]=sin(r/2)*rz;
	}

	else if(hVSv==4)
	{
		ub[0]=sin(r/2)*fx;
		ub[1]=sin(r/2)*fy;
		ub[2]=sin(r/2)*fz;
	}

	for(int i=0;i<numbOfPnts;i++)
	{
		if(r!=0)
		{
			double tempX,tempY,tempZ;
			if(hVSv==1 || hVSv==2)
			{
				tempX=vertices[i].x;
				tempZ=vertices[i].z;
				tempY=vertices[i].y;

				crossproduct(u[0],u[1],u[2],tempX,tempY,tempZ, cross);

				vertices[i].x = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempX+ 2.0 *s*cross[0];
				vertices[i].y = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempY+ 2.0 *s*cross[1];
				vertices[i].z = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempZ+ 2.0 *s*cross[2];	
			    
				if((r<0 && b<0.6)||(r>0 && b>-0.6))
				{
					tempX=vertices[i].x+10*0.0;
					tempZ=vertices[i].z+10*0.0;
					tempY=vertices[i].y+10*1.0;
		
					double tempbX,tempbY,tempbZ;
					crossproduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ, cross);

					tempbX = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[0] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempX+ 2.0 *s*cross[0];
					tempbY = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[1] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempY+ 2.0 *s*cross[1];
					tempbZ = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[2] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempZ+ 2.0 *s*cross[2];	
		
					vertices[i].x=tempbX-10*0.0;
					vertices[i].z=tempbZ-10*0.0;
					vertices[i].y=tempbY-10*1.0;

					cambInside=b;
				}
			}

			else if(hVSv==3)
			{

				tempX=vertices[i].x;
				tempZ=vertices[i].z;
				tempY=vertices[i].y;

				crossproduct(u[0],u[1],u[2],tempX,tempY,tempZ, cross);

				vertices[i].x = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempX+ 2.0 *s*cross[0];
				vertices[i].y = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempY+ 2.0 *s*cross[1];
				vertices[i].z = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempZ+ 2.0 *s*cross[2];	
			}

			else if(hVSv==4)
			{

				tempX=vertices[i].x+10*0.0;
				tempZ=vertices[i].z+10*0.0;
				tempY=vertices[i].y+10*1.0;
		
				double tempbX,tempbY,tempbZ;
				crossproduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ, cross);

				tempbX = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[0] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempX+ 2.0 *s*cross[0];
				tempbY = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[1] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempY+ 2.0 *s*cross[1];
				tempbZ = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[2] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempZ+ 2.0 *s*cross[2];	
		
				vertices[i].x=tempbX-10*0.0;
				vertices[i].z=tempbZ-10*0.0;
				vertices[i].y=tempbY-10*1.0;
			}

		}		
	}
}

void collisionSpheresRotation(Vec spheres[], int numbOfPnts, double rotx, double roty, double rotz, double fx, double fy, double fz, double rx, double ry, double rz, double rot, int hVSv, double b, double &cambInside)
{
	double s=cos(rot/2);
	double u[3];
	double ub[3];
	double cross[3];

	if(hVSv==1 || hVSv==2)
	{
		u[0]=sin(rot/2)*0.0;
		u[1]=sin(rot/2)*1.0;
		u[2]=sin(rot/2)*0.0;

		rot=-rot;

		ub[0]=sin(rot/2)*fx;
		ub[1]=sin(rot/2)*fy;
		ub[2]=sin(rot/2)*fz;
	}

	else if(hVSv==3)
	{
		u[0]=sin(rot/2)*rx;
		u[1]=sin(rot/2)*ry;
		u[2]=sin(rot/2)*rz;
	}

	else if(hVSv==4)
	{
		ub[0]=sin(rot/2)*fx;
		ub[1]=sin(rot/2)*fy;
		ub[2]=sin(rot/2)*fz;
	}

	for(int i=0;i<numbOfPnts;i++)
	{
		if(rot!=0)
		{
			double tempX,tempY,tempZ;
			if(hVSv==1 || hVSv==2)
			{
				tempX=spheres[i].x;
				tempZ=spheres[i].z;
				tempY=spheres[i].y;

				crossproduct(u[0],u[1],u[2],tempX,tempY,tempZ, cross);

				spheres[i].x = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempX+ 2.0 *s*cross[0];
				spheres[i].y = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempY+ 2.0 *s*cross[1];
				spheres[i].z = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempZ+ 2.0 *s*cross[2];	
			    
				if((rot<0 && b<0.6)||(rot>0 && b>-0.6))
				{
					tempX=spheres[i].x+10*0.0;
					tempZ=spheres[i].z+10*0.0;
					tempY=spheres[i].y+10*1.0;
		
					double tempbX,tempbY,tempbZ;
					crossproduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ, cross);

					tempbX = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[0] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempX+ 2.0 *s*cross[0];
					tempbY = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[1] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempY+ 2.0 *s*cross[1];
					tempbZ = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[2] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempZ+ 2.0 *s*cross[2];	
		
					spheres[i].x=tempbX-10*0.0;
					spheres[i].z=tempbZ-10*0.0;
					spheres[i].y=tempbY-10*1.0;

					cambInside=b;
				}
			}

			else if(hVSv==3)
			{

				tempX=spheres[i].x;
				tempZ=spheres[i].z;
				tempY=spheres[i].y;

				crossproduct(u[0],u[1],u[2],tempX,tempY,tempZ, cross);

				spheres[i].x = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[0] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempX+ 2.0 *s*cross[0];
				spheres[i].y = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[1] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempY+ 2.0 *s*cross[1];
				spheres[i].z = 2.0*DotProduct(u[0],u[1],u[2],tempX,tempY,tempZ) * u[2] + (s*s - DotProduct(u[0],u[1],u[2],u[0],u[1],u[2])) * tempZ+ 2.0 *s*cross[2];	
			}

			else if(hVSv==4)
			{

				tempX=spheres[i].x+10*0.0;
				tempZ=spheres[i].z+10*0.0;
				tempY=spheres[i].y+10*1.0;
		
				double tempbX,tempbY,tempbZ;
				crossproduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ, cross);

				tempbX = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[0] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempX+ 2.0 *s*cross[0];
				tempbY = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[1] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempY+ 2.0 *s*cross[1];
				tempbZ = 2.0*DotProduct(ub[0],ub[1],ub[2],tempX,tempY,tempZ) * ub[2] + (s*s - DotProduct(ub[0],ub[1],ub[2],ub[0],ub[1],ub[2])) * tempZ+ 2.0 *s*cross[2];	
		
				spheres[i].x=tempbX-10*0.0;
				spheres[i].z=tempbZ-10*0.0;
				spheres[i].y=tempbY-10*1.0;
			}

		}		
	}
}

double bigRadiusProviderPlane(int numbOfPoints,Vec vertex[])
{
	double max=0.0;
	double dist;
	for(int i=0;i<numbOfPoints;i++)
	{
		dist=((vertex[i].x*vertex[i].x)+(vertex[i].y*vertex[i].y)+(vertex[i].z*vertex[i].z));
		if(max<dist)
			max=dist;
	}
	return sqrt(max);
}

void planeBodyCalc(int numbOfPoints,Vec vertex[],double bodyTipPositiveZ[],double bodyTipNegativeZ[],double &maxRadiusBody)
{
	double max=0.0;
	double min=0.0;
	double dist;
	for(int i=0;i<numbOfPoints;i++)
	{
		dist=vertex[i].z;
		if(dist>0.0 && max<dist)
		{
			max=dist;
			 bodyTipPositiveZ[2]=vertex[i].z;
			 bodyTipPositiveZ[0]=vertex[i].x;
			 bodyTipPositiveZ[1]=vertex[i].y;
		}
		if(dist<0.0 && min>dist)
		{
			min=dist;
			 bodyTipNegativeZ[2]=vertex[i].z;
			 bodyTipNegativeZ[0]=vertex[i].x;
			 bodyTipNegativeZ[1]=vertex[i].y;
		}

	}

	//below calc used to calc max radius along body
	double maxX=-100.0;
	double minX=100.0;
	double maxY=-100.0;
	double minY=100.0;
	for(int i=0;i<numbOfPoints;i++)
	{
		if(vertex[i].z<-6.0 && vertex[i].z> bodyTipNegativeZ[2])//change -6.0 to a variable???
		{
			if(minX>vertex[i].x)
			{
				minX=vertex[i].x;
			}
			if(maxX<vertex[i].x)
			{
				maxX=vertex[i].x;
			}
			if(minY>vertex[i].y)
			{
				minY=vertex[i].y;
			}
			if(maxY<vertex[i].y)
			{
				maxY=vertex[i].y;
			}
		}
	}
	if((maxX-minX)>(maxY-minY))
		maxRadiusBody=(maxX-minX)*0.75;//0.75 and 0.5 as the axis is along z axis
	else
		maxRadiusBody=(maxY-minY)*0.75;
}

void planeWingCalc(int numbOfPoints,Vec vertex[],double wingTipPostiveX[],double wingTipNegativeX[])
{
	double max=0.0;
	double dist;
	for(int i=0;i<numbOfPoints;i++)
	{
		dist=vertex[i].x;
		if(dist>0.0 && max<dist)
		{
			max=dist;
			wingTipPostiveX[2]=vertex[i].z;
			wingTipPostiveX[0]=vertex[i].x;
			wingTipPostiveX[1]=vertex[i].y;
		}

	}
	wingTipNegativeX[2]=wingTipPostiveX[2];
	wingTipNegativeX[0]=-wingTipPostiveX[0];
	wingTipNegativeX[1]=wingTipPostiveX[1];
}

void planeTailCalc(int numbOfPoints,Vec vertex[],double tailTipPositiveY[])
{
	double max=0.0;
	double dist;
	for(int i=0;i<numbOfPoints;i++)
	{
		dist=vertex[i].y;
		if(dist>0.0 && max<dist)
		{
			max=dist;
			tailTipPositiveY[2]=vertex[i].z;
			tailTipPositiveY[0]=vertex[i].x;
			tailTipPositiveY[1]=vertex[i].y;
		}
	}
}

//calculates number of spheres given end points and radius
//distance between centres of two spheres is=radius
int numberOfSpheresProvider(double endPoint1, double endPoint2, double radius)
{
	double dist=abs(endPoint2-endPoint1);
	int numberOfSpheres=(int)(dist/radius)-1;
	return numberOfSpheres;
}
