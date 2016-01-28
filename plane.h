#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int ParseString(int &nWord,int wordTop[],int wordLength[],char str[],int maxNumWords);

class Vec
{
public:  
    double x,y,z;
};

class Plane
{
public:
    FILE *fp;
    int points;
    Vec *vertex;
    void Vertices();
    void Readfile();    
    void Initialize(char filename[]);
	void DrawPlaneMenu();
};

void copyvertices(Vec vertex[], Vec copy[], int &points, int index);
void Drawplane(Vec vertex[], Vec &centre, int &points);
