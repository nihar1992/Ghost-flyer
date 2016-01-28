#include <math.h>
#include "camera.h"
#include "fssimplewindow.h"

const double YsPi=3.1415927;

CameraObject::CameraObject()
{
    Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=0;
    p=0;
    b=0;

    fov=YsPi/4.0;  // 30 degree
    nearZ=0.1;
    farZ=20000.0;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

void CameraObject::GetUpVector(double &vx,double &vy,double &vz)
{
	const double ux0=0.0;
	const double uy0=1.0;
	const double uz0=0.0;

	const double ux1=cos(b)*ux0-sin(b)*uy0;
	const double uy1=sin(b)*ux0+cos(b)*uy0;
	const double uz1=uz0;

	const double ux2=ux1;
	const double uy2=cos(p)*uy1-sin(p)*uz1;
	const double uz2=sin(p)*uy1+cos(p)*uz1;

    vx=cos(-h)*ux2-sin(-h)*uz2;
    vy=uy2;
    vz=sin(-h)*ux2+cos(-h)*uz2;
}

void CameraObject::GetRightVector(double &vx,double &vy,double &vz)
{
	const double ux0=1.0;
	const double uy0=0.0;
	const double uz0=0.0;

	const double ux1=cos(b)*ux0-sin(b)*uy0;
	const double uy1=sin(b)*ux0+cos(b)*uy0;
	const double uz1=uz0;

	const double ux2=ux1;
	const double uy2=cos(p)*uy1-sin(p)*uz1;
	const double uz2=sin(p)*uy1+cos(p)*uz1;

    vx=cos(-h)*ux2-sin(-h)*uz2;
    vy=uy2;
    vz=sin(-h)*ux2+cos(-h)*uz2;
}

void CameraObject::GetRightHorVector(double &vx,double &vy,double &vz)
{
	const double ux0=1.0;
	const double uy0=0.0;
	const double uz0=0.0;

	const double ux1=cos(0.0)*ux0-sin(0.0)*uy0;
	const double uy1=sin(0.0)*ux0+cos(0.0)*uy0;
	const double uz1=uz0;

	const double ux2=ux1;
	const double uy2=cos(p)*uy1-sin(p)*uz1;
	const double uz2=sin(p)*uy1+cos(p)*uz1;

    vx=cos(-h)*ux2-sin(-h)*uz2;
    vy=uy2;
    vz=sin(-h)*ux2+cos(-h)*uz2;
}
