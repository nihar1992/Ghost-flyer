class Collision
{
public:  
	double x,y,z,r;
	int collision_state,check_state;

	Collision();
	void setValues(double X,double Y,double Z,double R, int coll_state,int ch_state);
	void drawSphere(int lats, int longs, double cx, double cy, double cz);

	//function to transfer missile/target's cannon ball to collision object

	int collisionCheckerPlaneBasic(Collision object, double camerax,double  cameray,double cameraz,double fx,double fy,double fz,double ux,double uy,double uz);
	int collisionCheckerPlaneAdv(Collision object, double camerax,double  cameray,double cameraz);
	int collisionCheckerGroundPlaneBasic(double fy, double uy,double cameraY);
	int collisionCheckerGroundPlaneAdv(double cameraY);
	int collisionCheckerBasic(Collision object);
};