#include <stdio.h>
#include <math.h>


class Terrain
{
protected:
  double *ter;
  double *red, *green, *blue;
  int wid, hei;

 public:
    Terrain();
    ~Terrain();
    void CleanUp(void);
	void CleanUpColour(void);
	int GetWidth(void)const;
    int GetHeight(void)const;
    void SetHeightmap(const int &Wid,const int &Hei,const unsigned char height[]);
	void SetColormap(const int &Width,const int &Height,const unsigned char bmp[]);
    void Print(void)const;
    void Draw(int s1, int s2)const;
    char GetHeight(const int &x,const int &y)const;
};
