#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fssimplewindow.h"
#include <math.h>
#include "plane.h"
#include "missile.h"

void Missile::Vertices()
{
	char str[256];
	if(fp!=NULL && fgets(str,255,fp)!=NULL)
   	{
		points=0;
		while(fgets(str,255,fp)!=NULL)
		{
			int nWord,wordTop[16],wordLength[16];
			ParseString(nWord,wordTop,wordLength,str,16);
			if(strcmp(str+wordTop[0],"vertex")==1)
			{
				points=points+1;
			}
		}
	}
	else
	{
	return;
	}
}	

void Missile::Readfile()
{
	int nRead;
	char str[256];
	if(fp!=NULL && fgets(str,255,fp)!=NULL)
   	{
		vertex=new Vec[points];
        	if(vertex!=NULL)
        	{
			nRead=0;
        	    	while(fgets(str,255,fp)!=NULL && nRead<points)
        	    	{
        	    	    	int nWord,wordTop[16],wordLength[16];
        	        	ParseString(nWord,wordTop,wordLength,str,16);
        	        	if(strcmp(str+wordTop[0],"vertex")==1)
        	        	{
        	            		vertex[nRead].x=atof(str+wordTop[1]);
        	            		vertex[nRead].y=atof(str+wordTop[2]);
		            		vertex[nRead].z=-atof(str+wordTop[3]);
        	            		nRead++;
        	 		}
        	    	}
		}  	
	}
}

void Missile::Initialize()
{
	char *filename;
	filename="atom.stl";
	fp=fopen(filename,"r");
	(*this).Vertices();
	fclose(fp);
	fp=fopen(filename,"r");
	(*this).Readfile();
	fclose(fp);
	copy=new Vec[points];
	state=0;
	Vec centroid;
	centroid.x=0;
	centroid.y=0;
	centroid.z=0;
	for(int i=0;i<points;i++)
	{
		centroid.x=centroid.x+vertex[i].x/points;
		centroid.y=centroid.y+vertex[i].y/points;
		centroid.z=centroid.z+vertex[i].z/points;
	}
	for(int i=0;i<points;i++)
	{
		vertex[i].x=(vertex[i].x-centroid.x)/30;
		vertex[i].y=(vertex[i].y-centroid.y)/30;
		vertex[i].z=(vertex[i].z-centroid.z)/30;
	}
	centre.x=0;
	centre.y=0;
	centre.z=0;

	double mismin,mismax;
	mismin=mismax=vertex[0].z;
	for(int i=1;i<points;i++)
	{
		if(mismax<vertex[i].z)
		{
			mismax=vertex[i].z;	
		}
		if(mismin>vertex[i].z)
		{
			mismin=vertex[i].z;
		}
	}
	dia=mismax-mismin;
}
	
void Missile::Reset(Vec origin)
{
	centre.x=origin.x;
	centre.y=origin.y;
	centre.z=origin.z;
	for(int i=0;i<points;i++)
	{
		copy[i].x=vertex[i].x+origin.x;
		copy[i].y=vertex[i].y+origin.y;
		copy[i].z=vertex[i].z+origin.z;
	}
}

void Missile::Drawmissile()
{
	int i;
	glEnable(GL_BLEND);
   	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255,0,0,150);
	for(i=0;i<points;i=i+3)
	{
		glBegin(GL_TRIANGLES);	
		glVertex3d(copy[i].x,copy[i].y,copy[i].z);
		glVertex3d(copy[i+1].x,copy[i+1].y,copy[i+1].z);
		glVertex3d(copy[i+2].x,copy[i+2].y,copy[i+2].z);
		glEnd();
	}
	glDisable(GL_BLEND);
}

void Missile::Move(double fx, double fy, double fz)
{
	centre.x=centre.x+fx*20;
	centre.y=centre.y+fy*20;
	centre.z=centre.z+fz*20;
	for(int i=0;i<points;i++)
	{
		copy[i].x=copy[i].x+fx*20;
		copy[i].y=copy[i].y+fy*20;
		copy[i].z=copy[i].z+fz*20;
	}
}

void Missile::Checkhitcube()
{
	if(state==1)
	{
		if((centre.x<0 || centre.x>2600) || (centre.z<0 || centre.z>2600) || (centre.y<-500 || centre.y>900))
		{
			state=0;
		}
	}
}
