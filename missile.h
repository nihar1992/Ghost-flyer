class Missile
{
public:
	FILE *fp;
	Vec *vertex;
	Vec *copy;
	Vec centre;
	void Vertices();
	int state;
	int points;
	double dia;
	void Readfile();	
	void Initialize();
	void Reset(Vec origin);
	void Drawmissile();
	void Move(double fx, double fy, double fz);
	void Checkhitcube();
};
