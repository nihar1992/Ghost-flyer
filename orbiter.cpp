#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "camera.h"
#include "misc.h"
#include "orbiter.h"
#include "plane.h"
#include "terrain.h"


OrbitingViewer::OrbitingViewer()
{
    Initialize();
}

void OrbitingViewer::Initialize(void)
{
    h=0;
    p=0;
    dist=400.0;
    focusX=0.0;
    focusY=0.0;
    focusZ=0.0;
}

void OrbitingViewer::SetUpCamera(CameraObject &camera)
{
    camera.h=h;
    camera.p=p;
    camera.b=0.0;

    double vx,vy,vz;
    camera.GetForwardVector(vx,vy,vz);
    camera.x=focusX-vx*dist;////////////////////////in this case you can put camera.x=-vx*dist/////////////////////
    camera.y=focusY-vy*dist;
    camera.z=focusZ-vz*dist;
}