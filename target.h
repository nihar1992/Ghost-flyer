class Target
{
	public:
		double cubeX[24],cubeY[24],cubeZ[24];
		double artX[4],artY[4],artZ[4];
		double vx,vy,vz,theta,phi,rad,dt,Cvel;
		double centeroftip[3],centerofArt[3],pos[3];
		double x,y,z;
		double dist;
		double pX,pY,pZ;
		int cannonballstate,targetstate;
		double planeX,planeY,planeZ;
		//Target(double cubex[],double cubey[],double cubez[],double artx[],double arty[],double artz[]);
		void InitializeTarget(double cubex[],double cubey[],double cubez[],double artx[],double arty[],double artz[]);
		void DrawTarget();
		void InitializeCannonBall(double planeX,double planeY,double planeZ);
		void Calculatedist(double planeX,double planeY,double planeZ);
		void DrawCannonBall();
		void MoveCannonBall();
		void GetTargetPoints(double tpx, double tpy,double tpz);
		void GetPlaneCoordinates(double tx, double ty, double tz);
		void Checkhitcube();
		
};


