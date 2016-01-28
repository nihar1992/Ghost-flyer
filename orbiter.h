#include <stdio.h>
#include <math.h>


class OrbitingViewer
{
public:
    double h,p;
    double dist;
    double focusX,focusY,focusZ;

    OrbitingViewer();
    void Initialize(void);
    void SetUpCamera(CameraObject &camera);
};
