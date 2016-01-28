#include <math.h>
#include "fssimplewindow.h"
#include "collision.h"
#include "plane.h"

const double YsPi=3.1415927;

Collision::Collision()
{
	x=0.0;
	y=0.0;
	z=0.0;
	r=0.0;
	collision_state=0;
	check_state=0;
}

void Collision::setValues(double X,double Y,double Z,double R, int coll_state,int ch_state)
{
	x=X;
	y=Y;
	z=Z;
	r=R;
	collision_state=coll_state;
	check_state=ch_state;
}

//Sphere drawing for debugging purpose
void Collision::drawSphere(int lats, int longs, double camX, double camY, double camZ) 
{
	double cx=camX+x;
	double cy=camY+y;
	double cz=camZ+z;
	double rad=r;
       int i, j;
       for(i = 0; i <= lats; i++) 
	   {
           double lat0 = YsPi * (-0.5 + (double) (i - 1) / lats);
           double z0  = rad*sin(lat0);
           double zr0 =  rad*cos(lat0);
    
           double lat1 = YsPi * (-0.5 + (double) i / lats);
           double z1 = rad*sin(lat1);
           double zr1 = rad*cos(lat1);
		   glEnable(GL_BLEND);
		   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
           glColor4ub(255,0,0,100);
           glBegin(GL_QUAD_STRIP);
           for(j = 0; j <= longs; j++) 
		   {
               double lng = 2 * YsPi * (double) (j - 1) / longs;
               double x = cos(lng);
               double y = sin(lng);
    
               glNormal3f((float)cx+x * zr0, (float)cy+y * zr0, (float)cz+z0);
               glVertex3f((float)cx+x * zr0, (float)cy+y * zr0, (float)cz+z0);
               glNormal3f((float)cx+x * zr1, (float)cy+y * zr1, (float)cz+z1);
               glVertex3f((float)cx+x * zr1, (float)cy+y * zr1, (float)cz+z1);
           }
           glEnd();
		   glDisable(GL_BLEND);
       }
 }

int Collision::collisionCheckerGroundPlaneBasic(double fy, double uy, double cameraY)
{
	if((cameraY+75.0*fy-10*uy)+500<r)//-500 is the water 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Collision::collisionCheckerGroundPlaneAdv(double cameraY)
{
	if((cameraY+y)+500<r)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Collision::collisionCheckerPlaneBasic(Collision object, double camerax,double  cameray,double cameraz,double fx,double fy,double fz,double ux,double uy,double uz)
{
	double d= sqrt(pow((x+camerax+75.0*fx-10*ux)-object.x,2)+pow((y+cameray+75.0*fy-10*uy)-object.y,2)+pow((z+cameraz+75.0*fz-10*uz)-object.z,2));
	if(d<r+object.r)
		return 1;
	else
		return 0;
}

int Collision::collisionCheckerPlaneAdv(Collision object, double camerax,double  cameray,double cameraz)
{
	double d= sqrt(pow((x+camerax)-object.x,2)+pow((y+cameray)-object.y,2)+pow((z+cameraz)-object.z,2));
	if(d<r+object.r)
		return 1;
	else
		return 0;
}

int Collision::collisionCheckerBasic(Collision object)
{
	double d= sqrt(pow((x)-object.x,2)+pow((y)-object.y,2)+pow((z)-object.z,2));
	if(d<r+object.r)
		return 1;
	else
		return 0;
}