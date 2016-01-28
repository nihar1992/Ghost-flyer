#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fssimplewindow.h"
#include "plane.h"

const double YsPi=3.1415927;

int ParseString(int &nWord,int wordTop[],int wordLength[],char str[],int maxNumWords)
{
    int i,state;
    state=0;
    nWord=0;
    for(i=0; str[i]!=0; i++)
    {
            switch(state)
            {
            case 0:
                if(str[i]!=' ' && str[i]!='\t' && str[i]!=',')
                    {
                        state=1;
                        wordTop[nWord]=i;
                        wordLength[nWord]=1;
                        nWord++;
                    }
                    break;
        case 1:
                    if(str[i]!=' ' && str[i]!='\t' && str[i]!=',')
                    {
                            wordLength[nWord-1]++;
                    }
                    else
                    {
                        state=0;
                    }
                    break;
            }
        }
    return nWord;
}
    
void Plane::Vertices()
{
    char str[256];
    points=0;
    if(fp!=NULL && fgets(str,255,fp)!=NULL)
       {
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

void Plane::Readfile()
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

void Plane::Initialize(char filename[])
{
    fp=fopen(filename,"r");
    (*this).Vertices();
    fclose(fp);
    fp=fopen(filename,"r");
    (*this).Readfile();
	fclose(fp);
}

void copyvertices(Vec vertex[], Vec copy[], int &points, int index)
{
    double centroid[3],sum1=0,sum2=0,sum3=0;
    for(int i=0;i<points;i++)
    {
        sum1=sum1+vertex[i].x;
        sum2=sum2+vertex[i].y;
        sum3=sum3+vertex[i].z;     
    }
    centroid[0]=sum1/points;
    centroid[1]=sum2/points;
    centroid[2]=sum3/points;
    if(index==0)
    {
        for(int i=0;i<points;i++)
        {
            copy[i].x=(vertex[i].x-centroid[0])/5.0;
            copy[i].y=(vertex[i].y-centroid[1])/5.0;
            copy[i].z=(vertex[i].z-centroid[2])/5.0;
        }
    }
    else if(index==1)
    {
        for(int i=0;i<points;i++)
        {
            copy[i].x=(vertex[i].x-centroid[0])/5;
            copy[i].y=(vertex[i].y-centroid[1])/5;
            copy[i].z=(vertex[i].z-centroid[2])/5;
        }
    }
}

void Drawplane(Vec vertex[], Vec &centre, int &points)
{
    int i;
    glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(0,0,0,150);
    for(i=0;i<points;i=i+3)
    {
        glBegin(GL_TRIANGLES);    
        glVertex3d(vertex[i].x+centre.x,vertex[i].y+centre.y,vertex[i].z+centre.z);
        glVertex3d(vertex[i+1].x+centre.x,vertex[i+1].y+centre.y,vertex[i+1].z+centre.z);
        glVertex3d(vertex[i+2].x+centre.x,vertex[i+2].y+centre.y,vertex[i+2].z+centre.z);
        glEnd();
    }
    glDisable(GL_BLEND);
}

void Plane::DrawPlaneMenu()
{
	int i;
	glEnable(GL_BLEND);
   	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0,0,0,100);
	//glColor3ub(0,0,255);
	for(i=0;i<points;i=i+3)
	{
		glBegin(GL_TRIANGLES);	
		glVertex3d(vertex[i].x,vertex[i].y,vertex[i].z);
		glVertex3d(vertex[i+1].x,vertex[i+1].y,vertex[i+1].z);
		glVertex3d(vertex[i+2].x,vertex[i+2].y,vertex[i+2].z);
		glEnd();
	}
	glDisable(GL_BLEND);
}
