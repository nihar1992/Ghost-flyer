class CameraObject
{
public:
    double x,y,z;
    double h,p,b;
    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);

    void GetForwardVector(double &vx,double &vy,double &vz);
    void GetUpVector(double &vx,double &vy,double &vz);
    void GetRightVector(double &vx,double &vy,double &vz);
	void GetRightHorVector(double &vx,double &vy,double &vz);
};