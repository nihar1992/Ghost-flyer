#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "camera.h"
#include "misc.h"
#include "plane.h"
#include "terrain.h"

Terrain::Terrain()
{
  wid = 0;
  hei = 0;
  ter = NULL;
  red = NULL;
  green = NULL;
  blue = NULL;
}

Terrain::~Terrain()
{
    CleanUp();
	CleanUpColour();
}

void Terrain::CleanUp(void)
{
    if(NULL!=ter)
	{
		delete [] ter;
		
	}
	
	wid = 0;
	hei = 0;
	ter = NULL;
	
}

void Terrain::CleanUpColour(void)
{
	 if(NULL!=red)
	{
		delete [] red;
		
	}
	    if(NULL!=green)
	{
		delete [] green;
		
	}
		  if(NULL!=blue)
	{
		delete [] blue;
		
	}

	red = NULL;
	green = NULL;
	blue = NULL;
}


int Terrain::GetWidth(void)const
{
    return wid;
}

int Terrain::GetHeight(void)const
{
    return hei;
}

void Terrain::SetHeightmap(const int &Wid,const int &Hei,const unsigned char bmp[])
{
	CleanUp();
	ter = new double [Wid*Hei];
	int i;
	wid = Wid-1;
	hei = Hei-1;
    for (i=0;i<((Wid-1)*(Hei-1));i++)
	{
		ter[i] = bmp[i*4];
	}
}

void Terrain::SetColormap(const int &Wid,const int &Hei,const unsigned char bmp[])
{
	
	CleanUpColour();
	
	red = new double [Wid*Hei];
	green = new double [Wid*Hei];
	blue = new double [Wid*Hei];

	int i,j;
	for (i=0;i<(Wid*Hei);i++)
	{
		red[i] = bmp[i*4]/255.;
		green[i] = bmp[i*4+1]/255.;
		blue[i] = bmp[i*4+2]/255.;
	}
}

void Terrain::Print(void)const
{
    int x,y;
    for(y=0; y<hei; y++)
    {
        for(x=0; x<wid; x++)
        {
           printf("%d",GetHeight(x,y));
        }
        printf("\n");
    }
}

void Terrain::Draw(int scale, int scaleh)const
{
	glEnable(GL_TEXTURE_2D);
	GLuint grass = 0;
	glGenTextures(1, &grass);
	glBindTexture(GL_TEXTURE_2D, grass);
	int x,y;
	glBegin(GL_TRIANGLE_STRIP);
	
    for(y=0; y<(hei); y++)
    {
        for(x=0; x<(wid); x++)
        {
                //vertex 1:
				glColor3f(red[y*255+x], green[y*255+x], blue[y*255+x]);
				glTexCoord2f(0.0,0.0);
				glVertex3f(x*scale,-ter[x*(wid+1)+y]*scaleh, y*scale);
				
				//vertex 2:
				glColor3f(red[y*255+(x+1)], green[y*255+(x+1)], blue[y*255+(x+1)]);
				glTexCoord2f(1.0,0.0);
				glVertex3f(x*scale+scale,-ter[(x+1)*(wid+1)+y]*scaleh,y*scale);
				

				//vertex 3:
				glColor3f(red[(y+1)*255+x], green[(y+1)*255+x], blue[(y+1)*255+x]);
				glTexCoord2f(0.0,1.0);
				glVertex3f(x*scale,-ter[x*(wid+1)+(y+1)]*scaleh,(y*scale+scale));
			

				//vertex 4:
				glColor3f(red[(y+1)*255+(x+1)], green[(y+1)*255+(x+1)], blue[(y+1)*255+(x+1)]);
				glTexCoord2f(1.0,1.0);
				glVertex3f((x*scale+scale),-ter[(x+1)*(wid+1)+(y+1)]*scaleh,(y*scale+scale));
				}
        
    } 
	glEnd();
	glDeleteTextures(1, &grass);
	glDisable(GL_TEXTURE_2D);
}

char Terrain::GetHeight(const int &x,const int &y)const
{
    if(0<=x && x<wid && 0<=y && y<hei)
    {
        return ter[y*wid+x];
    }
    return 0;
}