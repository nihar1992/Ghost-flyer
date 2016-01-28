double DotProduct(double Ax, double Ay, double Az, double Bx, double By, double Bz);
void crossproduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, double crossprod[]);

void CamRotate(double &tempcX,double &tempcY,double &tempcZ,double &ox,double &oy,double &oz,double &oxr,double &oyr,double &ozr, double r, double cam[], int hVSv);
void RotatePlane(Vec vertices[], int numbOfPnts, double x, double y, double z, double fx, double fy, double fz, double rx, double ry, double rz, double r, int hVSv, double b,double &cambInside);
void collisionSpheresRotation(Vec spheres[], int numbOfPnts, double rotx, double roty, double rotz, double fx, double fy, double fz, double rx, double ry, double rz, double rot, int hVSv, double b, double &cambInside);

double bigRadiusProviderPlane(int numbOfPoints,Vec vertex[]);
void planeBodyCalc(int numbOfPoints,Vec vertex[],double bodyTipPositiveZ[],double bodyTipNegativeZ[],double &maxRadiusBody);
void planeWingCalc(int numbOfPoints,Vec vertex[],double wingTipPostiveX[],double wingTipNegativeX[]);
void planeTailCalc(int numbOfPoints,Vec vertex[],double tailTipPositiveY[]);
int numberOfSpheresProvider(double endPoint1, double endPoint2, double radius);