#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "fssimplewindow.h"
#include "plane.h"
#include "camera.h"
#include "collision.h"
#include "miscellaneous.h"
#include "misc.h"
#include "terrain.h"
#include "target.h"
#include "orbiter.h"
#include "missile.h"
#include "yspng.h"
#include "ysglfontdata.h"

//#include "Leap.h"
//
//using namespace Leap;
//bool controlOn=false;
//Frame centerFrame;
//Frame lastFrame;
//const int FINGER_LIMIT = 3;
//Controller controller;


const double YsPi=3.1415927;

void DrawCircle(int cx,int cy,int rad,int fill)
{
    const double YS_PI=3.1415927;

    if(0!=fill)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    int i;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }

    glEnd();
}

int game_menu1()
{
	PlaySound(TEXT("menu11.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
	int state_counter=0;
	YsRawPngDecoder png[1];
		png[0].Decode("planemenu1.png");
		GLuint texId[1];

		// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

		glGenTextures(1,&texId[0]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D,texId[0]);  // Making the texture identifier current (or bring it to the deck)

		// glPixelStorei(GL_UNPACK_ALIGNMENT,1);  Do I need it?
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexImage2D
			(GL_TEXTURE_2D,
			 0,
			 4,
			 png[0].wid,
			 png[0].hei,
			 0,
			 GL_RGBA,
			 GL_UNSIGNED_BYTE,
			 png[0].rgba);
		
		
	int	lastKey=FSKEY_NULL;
    while(lastKey==FSKEY_NULL)
    {
///////////////////////////////////////////Leap Motion menu 1/////////////////////////////////////////////////

			//Frame thisFrame = controller.frame();
		 // double handHeight = thisFrame.hands()[0].palmPosition().y;
			//double pos= thisFrame.hands()[0].palmPosition().x;
			//double radiusChange = thisFrame.hands()[0].sphereRadius()-lastFrame.hands()[0].sphereRadius();

			//if (thisFrame.fingers().count() > FINGER_LIMIT)
			//{
			//		// Set center frame when the hand opens
			//		if (!controlOn)
			//		{
			//			centerFrame = thisFrame;
			//			controlOn = true;
			//		}

			//		controlOn = true;
   //         
			//}
			//else
			//{
			//	controlOn = false;
			//}	

	

			//if(pos>100)
			//{
			//	state_counter = 1;
			//	break;
			//}

////////////////////////////////////////////////////////////leap motion end////////////////////////////////////////////
			FsPollDevice();
			lastKey=FsInkey();
			if(lastKey==FSKEY_ENTER)
			{
				state_counter =1;
				break;
			}

			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glColor4d(1.0,1.0,1.0,1.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,texId[0]);
			glBegin(GL_QUADS);

			glTexCoord2d(0.0,0.0);
			glVertex2i(0,0);

			glTexCoord2d(1.0,0.0);
			glVertex2i(800,0);

			glTexCoord2d(1.0,1.0);
			glVertex2i(800,600);

			glTexCoord2d(0.0,1.0);
			glVertex2i(0,600);

			glEnd();
			FsSwapBuffers();
			/*lastFrame = thisFrame;*/
			FsSleep(25);

			
	}
	if(state_counter==1)
	{		
		return 1;
	}
	else{return 0;}
	
}



///////////////////////////////////
int game_menu2()
{
	
	Plane plane,plane1,plane2;
	//char filename;

	CameraObject camera;
	OrbitingViewer orbit;

    camera.z=200.0;
	camera.x=0;
	camera.y=0;
/////////////////////////////////////////////////////////plane initialization/////////////////////////////////////////
	//plane.fp=fopen("1.stl","r");
	////plane.points=plane.Vertices();
	//printf("\n %d",plane.points);
	//fclose(plane.fp);
	//plane.fp=fopen("1.stl","r");
	//plane.Readfile();
	//fclose(plane.fp
	plane.Initialize("airplane.stl");
	double centroid[3],sum1=0,sum2=0,sum3=0;
	for(int i=0;i<plane.points;i++)
	{
		sum1=sum1+plane.vertex[i].x;
		sum2=sum2+plane.vertex[i].y;
		sum3=sum3+plane.vertex[i].z;	 
	}
	centroid[0]=sum1/plane.points;
	centroid[1]=sum2/plane.points;
	centroid[2]=sum3/plane.points;
	for(int i=0;i<plane.points;i++)
	{
		plane.vertex[i].x=(plane.vertex[i].x-centroid[0])/6;
		plane.vertex[i].y=(plane.vertex[i].y-centroid[1])/6;
		plane.vertex[i].z=(plane.vertex[i].z-centroid[2])/6;
	}
//////////////////////////////////////////////////////plane1 initialization///////////////////////////////////////////////
	//plane1.fp=fopen("2.stl","r");
	////plane1.points=plane1.Vertices();
	//printf("\n %d",plane1.points);
	//fclose(plane1.fp);
	//plane1.fp=fopen("2.stl","r");
	//plane1.Readfile();
	//fclose(plane1.fp);
	plane1.Initialize("2.stl");
	sum1=0;sum2=0;sum3=0;
	for(int i=0;i<plane1.points;i++)
	{
		sum1=sum1+plane1.vertex[i].x;
		sum2=sum2+plane1.vertex[i].y;
		sum3=sum3+plane1.vertex[i].z;	 
	}
	centroid[0]=sum1/plane1.points;
	centroid[1]=sum2/plane1.points;
	centroid[2]=sum3/plane1.points;
	for(int i=0;i<plane1.points;i++)
	{
		plane1.vertex[i].x=(plane1.vertex[i].x-centroid[0])/1.4;
		plane1.vertex[i].y=(plane1.vertex[i].y-centroid[1])/1.4;
		plane1.vertex[i].z=(plane1.vertex[i].z-centroid[2])/1.4;
	}
//////////////////////////////////////////////////////plane2 initialization//////////////////////////////////////////////
	//plane2.fp=fopen("3.stl","r");
	////plane2.points=plane2.Vertices();
	//printf("\n %d",plane2.points);
	//fclose(plane2.fp);
	//plane2.fp=fopen("3.stl","r");
	//plane2.Readfile();
	//fclose(plane2.fp);
	plane2.Initialize("3.stl");
	sum1=0;sum2=0;sum3=0;
	for(int i=0;i<plane2.points;i++)
	{
		sum1=sum1+plane2.vertex[i].x;
		sum2=sum2+plane2.vertex[i].y;
		sum3=sum3+plane2.vertex[i].z;	 
	}
	centroid[0]=sum1/plane2.points;
	centroid[1]=sum2/plane2.points;
	centroid[2]=sum3/plane2.points;
	for(int i=0;i<plane2.points;i++)
	{
		plane2.vertex[i].x=(plane2.vertex[i].x-centroid[0])/5;
		plane2.vertex[i].y=(plane2.vertex[i].y-centroid[1])/5;
		plane2.vertex[i].z=(plane2.vertex[i].z-centroid[2])/5;
	}
//////////////////////////////////////////////
	YsRawPngDecoder png[2];
	png[0].Decode("menu2image.png");
	GLuint texId[2];

	// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

	glGenTextures(1,&texId[0]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D,texId[0]);  // Making the texture identifier current (or bring it to the deck)

		// glPixelStorei(GL_UNPACK_ALIGNMENT,1);  Do I need it?
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexImage2D
			(GL_TEXTURE_2D,
			 0,
			 4,
			 png[0].wid,
			 png[0].hei,
			 0,
			 GL_RGBA,
			 GL_UNSIGNED_BYTE,
			 png[0].rgba);
			png[1].Decode("menu3image.png");
			glGenTextures(1,&texId[1]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D,texId[1]);  // Making the texture identifier current (or bring it to the deck)

		// glPixelStorei(GL_UNPACK_ALIGNMENT,1);  Do I need it?
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexImage2D
			(GL_TEXTURE_2D,
			 0,
			 4,
			 png[1].wid,
			 png[1].hei,
			 0,
			 GL_RGBA,
			 GL_UNSIGNED_BYTE,
			 png[1].rgba);
//////////////////////////////////////////////////////
	int	key=FSKEY_NULL;
	int state_counter=0;
	int counter_plane=1;


	while(key==FSKEY_NULL || key==FSKEY_RIGHT || key==FSKEY_LEFT)
	{

/////////////////////////////////////////////Leap Motion Menu 2//////////////////////////////////////////////
					 //Get the next frame
					//Frame thisFrame = controller.frame();
					//double handHeight = thisFrame.hands()[0].palmPosition().y;
					//double pos= thisFrame.hands()[0].palmPosition().x;
					//double pos1= thisFrame.hands()[0].direction().pitch();

					//if (thisFrame.fingers().count() > FINGER_LIMIT)
					//{
					//		// Set center frame when the hand opens
					//		if (!controlOn)
					//		{
					//			centerFrame = thisFrame;
					//			controlOn = true;
					//		}

					//		controlOn = true;
     //       
					//}
					//else
					//{
					//	controlOn = false;
					//}	

	

					//if(pos>100)
					//{
					//	counter_plane=3;}

					//else if(pos<-100)
					//{
					//	counter_plane=1;}
					//else if(pos>-100 && pos<100)
					//{
					//	counter_plane=2;}
/////////////////////////////////////////////Leap Motion Menu 2 end//////////////////////////////////////////////	
		
		//glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		int	key=FSKEY_NULL;
		int wid,hei;/////
        FsGetWindowSize(wid,hei);////
		FsPollDevice();
		key=FsInkey();

		if(key==FSKEY_RIGHT && counter_plane<3)
		{
			counter_plane=counter_plane + 1;
			
		}
		if(key==FSKEY_LEFT && counter_plane>1)
		{
			counter_plane=counter_plane - 1;
			
		}
		if(key==FSKEY_ESC)
		{
			state_counter=1;
			break;
		}
		if(key==FSKEY_ENTER /*|| pos1>1.0*/)
		{
			PlaySound(TEXT("1.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
			state_counter=2;
			time_t start = time(0);
			int timer=0,b=0;
			while(timer==0)
			{
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
				glColor4d(1.0,1.0,1.0,1.0);

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,texId[1]);
				glBegin(GL_QUADS);

				glTexCoord2d(0.0,0.0);
				glVertex2i(0,0);

				glTexCoord2d(1.0,0.0);
				glVertex2i(800,0);

				glTexCoord2d(1.0,1.0);
				glVertex2i(800,600);

				glTexCoord2d(0.0,1.0);
				glVertex2i(0,600);

				glEnd();
				glDisable(GL_TEXTURE_2D);
				glColor3i(0,0,0);
				glBegin(GL_QUADS);
				glVertex2i(150,450);
				glVertex2i(150,550);
				glVertex2i(650,550);
				glVertex2i(650,450);
				glEnd();
				time_t end=time(0);
				b=end-start;
				
				glColor3f(0.89,0.47,0.2);
				glBegin(GL_POLYGON);
				glVertex2i(150,450);
				glVertex2i(150,550);
				glVertex2i(150+(b*100),550);
				glVertex2i(150+(b*100),450);
				glEnd();
				if(b>5){timer=1;}
				if(b==2){PlaySound(TEXT("jarvis.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);}
				FsSwapBuffers();
				FsSleep(15);

			}

			break;
		}
		
			if(counter_plane==1)
			{
				for(int i=0;i<plane.points;i++)
				{
					Rotation(plane.vertex[i].x,plane.vertex[i].y,plane.vertex[i].z);
				}
			}
			if(counter_plane==2)
			{
				for(int i=0;i<plane1.points;i++)
				{
					Rotation(plane1.vertex[i].x,plane1.vertex[i].y,plane1.vertex[i].z);
				}
			}
			if(counter_plane==3)
			{
				for(int i=0;i<plane2.points;i++)
				{
					Rotation(plane2.vertex[i].x,plane2.vertex[i].y,plane2.vertex[i].z);
				}
			}
		
////////////////////////////
		///////////////////////////////////////

		//orbit.p-=YsPi/180.0;

		orbit.SetUpCamera(camera);
    	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glViewport(0,0,wid,hei);

        // Set up 3D drawing
        camera.SetUpCameraProjection();
        camera.SetUpCameraTransformation();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);

        // 3D drawing from here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glColor4d(1.0,1.0,1.0,1.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texId[0]);
		glBegin(GL_QUADS);

		glTexCoord3d(0.0,0.0,0.0);
		glVertex3i(-400,300,-320);

		glTexCoord3d(1.0,0.0,0.0);
		glVertex3i(400,300,-320);

		glTexCoord3d(1.0,1.0,1.0);
		glVertex3i(400,-300,-320);

		glTexCoord3d(0.0,1.0,0.0);
		glVertex3i(-400,-300,-320);

		glEnd();
		glDisable(GL_TEXTURE_2D);

		/////////////////////////////////////////////////////////////////////////////////////////////////
        
		glEnable(GL_BLEND);
   	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(25,25,25,165);
	//glColor3ub(0,0,255);
	glBegin(GL_TRIANGLES);
	
		
	if(counter_plane==1)
	{
			for(int i=0;i<plane.points;i=i+3)
			{
				glVertex3d(plane.vertex[i].x,plane.vertex[i].y,plane.vertex[i].z);
				glVertex3d(plane.vertex[i+1].x,plane.vertex[i+1].y,plane.vertex[i+1].z);
				glVertex3d(plane.vertex[i+2].x,plane.vertex[i+2].y,plane.vertex[i+2].z);
			}
	}
	if(counter_plane==2)
	{
			for(int i=0;i<plane1.points;i=i+3)
			{
				glVertex3d(plane1.vertex[i].x,plane1.vertex[i].y,plane1.vertex[i].z);
				glVertex3d(plane1.vertex[i+1].x,plane1.vertex[i+1].y,plane1.vertex[i+1].z);
				glVertex3d(plane1.vertex[i+2].x,plane1.vertex[i+2].y,plane1.vertex[i+2].z);
			}
	}
	if(counter_plane==3)
	{
			for(int i=0;i<plane2.points;i=i+3)
			{
				glVertex3d(plane2.vertex[i].x,plane2.vertex[i].y,plane2.vertex[i].z);
				glVertex3d(plane2.vertex[i+1].x,plane2.vertex[i+1].y,plane2.vertex[i+1].z);
				glVertex3d(plane2.vertex[i+2].x,plane2.vertex[i+2].y,plane2.vertex[i+2].z);
			}
	}
		
	glEnd();
	glDisable(GL_BLEND);
		
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

		
		
		glColor3ub(0,0,0);
		/*glRasterPos2d(10,250);
		YsGlDrawFontBitmap16x24("<-- Previous");
		glRasterPos2d(650,250);
		YsGlDrawFontBitmap16x24("Next -->");
		glRasterPos2d(230,450);
		YsGlDrawFontBitmap16x24("Press Enter to continue");*/
		drawplane(counter_plane);

			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*lastFrame = thisFrame;	*/
		FsSwapBuffers();
		
        FsSleep(25);


	}	
	if(state_counter==1)
	{
		return 0;
	}
	if(state_counter==2)
	{
		return 2;
	}
	else{return 1;}
	
}
void game_over(int targetdead)
{
		if(targetdead==5){
			PlaySound(TEXT("win.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);}
		if(targetdead!=5){
			PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);}
		int state_counter=0;
		YsRawPngDecoder png[1];
		if(targetdead==5){
			png[0].Decode("win.png");}
		if(targetdead!=5){
			png[0].Decode("gameover.png");}
		GLuint texId[1];

		// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

		glGenTextures(1,&texId[0]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D,texId[0]);  // Making the texture identifier current (or bring it to the deck)

		// glPixelStorei(GL_UNPACK_ALIGNMENT,1);  Do I need it?
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexImage2D
			(GL_TEXTURE_2D,
			 0,
			 4,
			 png[0].wid,
			 png[0].hei,
			 0,
			 GL_RGBA,
			 GL_UNSIGNED_BYTE,
			 png[0].rgba);
		
		
	int	lastKey=FSKEY_NULL;
    while(lastKey==FSKEY_NULL)
    {
		 glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			FsPollDevice();
			lastKey=FsInkey();
			if(lastKey==FSKEY_ESC)
			{
				break;
			}

			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glColor4d(1.0,1.0,1.0,1.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,texId[0]);
			glBegin(GL_QUADS);

			glTexCoord2d(0.0,0.0);
			glVertex2i(0,0);

			glTexCoord2d(1.0,0.0);
			glVertex2i(800,0);

			glTexCoord2d(1.0,1.0);
			glVertex2i(800,600);

			glTexCoord2d(0.0,1.0);
			glVertex2i(0,600);

			glEnd();
			FsSwapBuffers();
			
			FsSleep(25);
			
	}
	
}


int main()
{
	int targetdead=0;
	int terminate=0;
	int terminateGame=0;
	int terminateover=0;
	int timer_game_over = 0;
	Vec origin;
	//Below variables used for target
	double cubex[24]={+25,+25,+25, +25, -25, -25, -25, -25, -25, +25, +25, -25, -25, +25, +25, -25, -25, +25, +25, -25, -25, +25, +25, -25};
	double cubey[24]={-25, +25, +25, -25, -25, +25, +25, -25, +25, +25, +25, +25, -25, -25, -25, -25, -25, -25, +25, +25, -25, -25, +25, +25};
	double cubez[24]={-25,-25,+25,+25,-25, -25, +25, +25, -25, -25, +25, +25, -25, -25, +25, +25, +25, +25, +25, +25, -25, -25, -25, -25};
	double artx[4]={5,-5,5,-5};
	double arty[4]={25,25,25,25};
	double artz[4]={5,5,-5,-5};
	Target target[5];
	Collision targetColl[5];
	Collision cannonBallCol[5];
	for(int i=0;i<5;i++)
	{
		target[i].InitializeTarget(cubex,cubey,cubez,artx,arty,artz);
		cannonBallCol[i].setValues(target[i].pos[0],target[i].pos[1],target[i].pos[2],2,1,1);
	}

	target[0].GetTargetPoints(2600-1650,-50,1920);
	target[1].GetTargetPoints(2600-860,-10,1970);
	target[2].GetTargetPoints(2600-680,-110,1470);
	target[3].GetTargetPoints(2600-2330,-220,760);
	target[4].GetTargetPoints(2600-530,-10,300);

	targetColl[0].setValues(2600-1650,-50,1920,40,1,1);
	targetColl[1].setValues(2600-860,-10,1970,40,1,1);
	targetColl[2].setValues(2600-680,-110,1470,40,1,1);
	targetColl[3].setValues(2600-2330,-220,760,40,1,1);
	targetColl[4].setValues(2600-530,-10,300,40,1,1);

	//Below variables used for airplane
	Vec *vertex;
	Plane airplane;

	char *filename;
	filename="Talon.stl";
	airplane.Initialize(filename);

	int numberOfPoints;
	numberOfPoints= airplane.points;
	vertex= new Vec [numberOfPoints];
	copyvertices(airplane.vertex, vertex, airplane.points,0);

	//Below variables used for missile
	const int nMissile=5;
	Collision planeMissile[nMissile];
	Missile missile[nMissile];
	double mx,my,mz;
	for(int i=0;i<nMissile;i++)
	{
		missile[i].Initialize();
		planeMissile[i].setValues(missile[i].centre.x,missile[i].centre.y,missile[i].centre.z,missile[i].dia*0.25,1,1);
	}
	
	
	//Below variables used for terrain
	Terrain terrain;
	YsRawPngDecoder png;
	YsRawPngDecoder png1;
	if(YSOK==png.Decode("terrain-bmp_png.png"))
	{
		png.Flip();
	}
	if(YSOK==png1.Decode("Ground_Grass.png"))
	{
		png.Flip();
	}
	terrain.SetColormap(png1.wid, png1.hei,png1.rgba );
    terrain.SetHeightmap(png.wid, png.hei,png.rgba );

	Collision terrainCol[26];
	terrainCol[0].setValues(1910,-270,370,250, 1,1);
	terrainCol[1].setValues(2600-2620,-410,2190,200, 1,1);
	terrainCol[2].setValues(2600-2390,-340,1470,250, 1,1);
	terrainCol[3].setValues(2600-2290,-620,1150,400, 1,1);
	terrainCol[4].setValues(2600-2350,-550,640,400, 1,1);
	terrainCol[5].setValues(2600-2320,-620,330,610, 1,1);
	terrainCol[6].setValues(2600-1790,-430,330,240, 1,1);
	terrainCol[7].setValues(2600-1710,-580,2100,410, 1,1);
	terrainCol[8].setValues(992,-230,1030,200, 1,1);
	terrainCol[9].setValues(2600-1600,-380,1620,140, 1,1);
	terrainCol[10].setValues(2600-1590,-470,1330,290, 1,1);
	terrainCol[11].setValues(2600-1440,-720,1060,520, 1,1);
	terrainCol[12].setValues(2600-940,-670,490,400, 1,1);
	terrainCol[13].setValues(2600-480,-670,350,470, 1,1);
	terrainCol[14].setValues(2600-80,-530,250,500, 1,1);
	terrainCol[15].setValues(2600+70,-530,1030,180, 1,1);
	terrainCol[16].setValues(2600+70,-530,1600,280, 1,1);
	terrainCol[17].setValues(2600-840,-610,1250,210, 1,1);
	terrainCol[18].setValues(2600-720,-400,1430,60, 1,1);
	terrainCol[19].setValues(2600-820,-360,1980,330, 1,1);
	terrainCol[20].setValues(2600-1310,-410,1910,80, 1,1);
	terrainCol[21].setValues(992,-141,984,100, 1,1);
	terrainCol[22].setValues(2600-570,-510,2530,280, 1,1);
	terrainCol[23].setValues(2600+20,-370,2190,210, 1,1);
	terrainCol[24].setValues(2600-440,-480,1860,410, 1,1);
	terrainCol[25].setValues(2600-680,-440,1750,350, 1,1);

	//Below variables used for camera
	double r=0;
	double cambInside=0.0;
	int hVSv=0;

	double fx,fy,fz;
	double rx,ry,rz;
	double ux,uy,uz;
	double tempcX,tempcY,tempcZ,ox,oy,oz,oxr,oyr,ozr;
    CameraObject camera;

	camera.z=1280;
	camera.y=100;
	camera.x=1280;

	camera.GetForwardVector(fx,fy,fz);
	camera.GetUpVector(ux,uy,uz);
	camera.GetRightVector(rx,ry,rz);

	//below variables used for banking moving left/right
	int bankingState=0;
	tempcX=10*rx;
	tempcZ=10*rz;
	tempcY=10*ry;
	ox=camera.x-tempcX;
	oy=camera.y-tempcY;
	oz=camera.z-tempcZ;
	oxr=camera.x+tempcX;
	oyr=camera.y+tempcY;
	ozr=camera.z+tempcZ;

	//Below variables used for collision spheres of airplane
	Collision *planeSpheres;
	Collision bigPlaneSpheres;
	Vec *spheres;

	double rBig=bigRadiusProviderPlane(numberOfPoints, vertex);
	double  bodyTipPositiveZ[3];
	double  bodyTipNegativeZ[3];
	double wingTipPostiveX[3];
	double wingTipNegativeX[3];
	double tailTipPositiveY[3];
	double maxRadiusBody=0.0;
	int totalNumberOfSpheresPlane=0;
	int numberOfSpheresBodyPlane=0;
	int numberOfSpheresWingPlane=0;
	int numberOfSpheresTailPlane=0;

	planeBodyCalc(numberOfPoints,vertex, bodyTipPositiveZ,  bodyTipNegativeZ,maxRadiusBody);
	planeWingCalc(numberOfPoints,vertex,wingTipPostiveX,wingTipNegativeX);
	planeTailCalc(numberOfPoints,vertex,tailTipPositiveY);


	numberOfSpheresTailPlane=numberOfSpheresProvider(tailTipPositiveY[1], 0.0, 3.0);
	numberOfSpheresWingPlane=numberOfSpheresProvider(wingTipPostiveX[0], wingTipNegativeX[0], 3.0);
	numberOfSpheresBodyPlane=numberOfSpheresProvider(bodyTipPositiveZ[2], bodyTipNegativeZ[2], maxRadiusBody);

	totalNumberOfSpheresPlane=numberOfSpheresTailPlane+numberOfSpheresWingPlane+numberOfSpheresBodyPlane;

	planeSpheres= new Collision[totalNumberOfSpheresPlane];
	spheres= new Vec[totalNumberOfSpheresPlane];

	bigPlaneSpheres.setValues(0,0,0,rBig,1,1);

	int j=0;
	while(j<totalNumberOfSpheresPlane)
	{
		for(int i= bodyTipPositiveZ[2]-maxRadiusBody;i> bodyTipNegativeZ[2]+maxRadiusBody;i=i-maxRadiusBody)
		{
			planeSpheres[j].setValues(75.0*fx-10*ux,75.0*fy-10*uy,75.0*fz-10*uz+i,maxRadiusBody,1,1);
			j++;
		}
		for(int i=wingTipPostiveX[0]-3;i>wingTipNegativeX[0]+3;i=i-3)//radius=3
		{
			planeSpheres[j].setValues(75.0*fx-10*ux+i,75.0*fy-10*uy+wingTipPostiveX[1],75.0*fz-10*uz+wingTipPostiveX[2],3.0,1,1);
			j++;
		}
		for(int i=tailTipPositiveY[1]-3;i>0+3;i=i-3)//radius=3
		{
			planeSpheres[j].setValues(75.0*fx-10*ux+tailTipPositiveY[0],75.0*fy-10*uy+i,75.0*fz-10*uz+tailTipPositiveY[2],3.0,1,1);
			j++;
		}
	}

	for(int i=0;i<numberOfPoints;i++)
	{
		vertex[i].x=75.0*fx-10*ux+vertex[i].x;
		vertex[i].y=75.0*fy-10*uy+vertex[i].y;
		vertex[i].z=75.0*fz-10*uz+vertex[i].z;
	}
	 int game_counter = 0;
	FsOpenWindow(16,16,800,600,1);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	while(game_counter!=2)
	{
		if(game_counter==0)
		{
			game_counter = game_menu1();
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			
		}
		else if(game_counter==1)
		{
			
			game_counter = game_menu2();
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		}

	}
		
	

	 while(0==terminate)
	 {

///////////////////////////////////////////Leap Motion Plane Control////////////////////////////////////////////////

		// Frame thisFrame = controller.frame();
		//
		//double handHeight = thisFrame.hands()[0].palmPosition().y;
		//double pos= thisFrame.hands()[0].direction().yaw();
		//double pos1= thisFrame.hands()[0].direction().pitch();
	

		//if (thisFrame.fingers().count() > FINGER_LIMIT)
		//{
		//		// Set center frame when the hand opens
		//		if (!controlOn)
		//		{
		//			centerFrame = thisFrame;
		//			controlOn = true;
		//		}

		//		controlOn = true;
  //          
		//}
		//else
		//{
		//	controlOn = false;
		//}

////////////////////////////////////////////////////Leap Motion main end/////////////////////////////////////////////

        FsPollDevice();

		int wid,hei;
        FsGetWindowSize(wid,hei);

		int key=FsInkey();
		switch(key)
        {
			case FSKEY_SPACE:
				for(int i=0;i<nMissile;i++)
				{
	    			if(missile[i].state==0)
					{
						origin.x=camera.x+50.0*fx-10*ux;
						origin.y=camera.y+50.0*fy-10*uy;
						origin.z=camera.z+50.0*fz-10*uz;
					
						camera.GetForwardVector(mx,my,mz);
						PlaySound(TEXT("missile.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
						missile[i].Reset(origin);


						planeMissile[i].check_state=1;
						planeMissile[i].collision_state=1;

						missile[i].state=1;	
						break;
					}
				}
				break;
			case FSKEY_ESC:
				terminate=1;
				break;
		}

		if(0!=FsGetKeyState(FSKEY_LEFT) /*|| (FsGetKeyState(FSKEY_N) && pos<-0.1)*/)///////////////leap  part
        {
			double cam[3];
            camera.h+=YsPi/180.0;
			if(camera.b<0.6)
				camera.b+=YsPi/180.0;
			r=YsPi/180.0;
			hVSv=1;
			CamRotate(tempcX,tempcY,tempcZ,ox,oy,oz,oxr,oyr,ozr,YsPi/180.0, cam, hVSv);
			camera.x=cam[0];
            camera.y=cam[1];
            camera.z=cam[2];
			bankingState=1;

        }

		else if(0!=FsGetKeyState(FSKEY_RIGHT) /*|| (FsGetKeyState(FSKEY_N) && pos>0.2) */)
        {
			double cam[3];
			camera.h-=YsPi/180.0;
			if(camera.b>-0.6)
				camera.b-=YsPi/180.0;
			r=-YsPi/180.0;
			hVSv=2;
			CamRotate(tempcX,tempcY,tempcZ,ox,oy,oz,oxr,oyr,ozr,-YsPi/180.0, cam, hVSv);
			camera.x=cam[0];
            camera.y=cam[1];
            camera.z=cam[2];
			bankingState=1;
        }

		else if(0!=FsGetKeyState(FSKEY_UP) /*|| (FsGetKeyState(FSKEY_N) && pos1>0.1)*/)
        {
			oxr=camera.x+tempcX;
			oyr=camera.y+tempcY;
			ozr=camera.z+tempcZ;

			ox=camera.x-tempcX;
			oy=camera.y-tempcY;
			oz=camera.z-tempcZ;

			if(camera.p<1.5)
			{
				camera.p+=YsPi/180.0;
				r=YsPi/180.0;
				hVSv=3;
			}
        }

		else if(0!=FsGetKeyState(FSKEY_DOWN)/*|| (FsGetKeyState(FSKEY_N) && pos1<-0.1)*/)
        {
			oxr=camera.x+tempcX;
			oyr=camera.y+tempcY;
			ozr=camera.z+tempcZ;

			ox=camera.x-tempcX;
			oy=camera.y-tempcY;
			oz=camera.z-tempcZ;

			if(camera.p>-1.5)
			{
				camera.p-=YsPi/180.0;
				r=-YsPi/180.0;
				hVSv=3;
			}
        }

		/*else if(0!=FsGetKeyState(FSKEY_F))
        {
		double vx,vy,vz;
        camera.GetForwardVector(vx,vy,vz);
        camera.x+=vx*10.0;
        camera.y+=vy*10.0;
        camera.z+=vz*10.0;
		}

		else if(0!=FsGetKeyState(FSKEY_B))
        {
		double vx,vy,vz;
        camera.GetForwardVector(vx,vy,vz);
        camera.x-=vx*10.0;
        camera.y-=vy*10.0;
        camera.z-=vz*10.0;
		}*/

		//auto forward motion
		double vx,vy,vz;
		if((camera.x+75.0*fx-10*ux)>2400 || (camera.x+75.0*fx-10*ux)<100 || (camera.y+75.0*fy-10*uy)>800 || (camera.z+75.0*fz-10*uz)>2400 || (camera.z+75.0*fz-10*uz)<100)
		{
		}
		else
		{
		camera.GetForwardVector(vx,vy,vz);
		if(camera.p<0)
		{
			camera.x+=vx*0.3*(8.0-5*camera.p);
			camera.y+=vy*0.3*(8.0-5*camera.p);
			camera.z+=vz*0.3*(8.0-5*camera.p);
		}
		else
		{
			camera.x+=vx*0.3*8.0;
			camera.y+=vy*0.3*8.0;
			camera.z+=vz*0.3*8.0;
		}
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glViewport(0,0,wid,hei);

		camera.SetUpCameraProjection();
        camera.SetUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);   // Enable smooth shading
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);

		for(int i=0;i<5;i++)
		{

			if(target[i].cannonballstate==0)
			{
				target[i].GetPlaneCoordinates(camera.x+75.0*fx-10*ux,camera.y+75.0*fy-10*uy,camera.z+75.0*fz-10*uz);
				target[i].Calculatedist(camera.x+75.0*fx-10*ux,camera.y+75.0*fy-10*uy,camera.z+75.0*fz-10*uz);
			    
			}
			else if(target[i].cannonballstate==1)
			{
				target[i].MoveCannonBall();
				cannonBallCol[i].x=target[i].pos[0];
				cannonBallCol[i].y=target[i].pos[1];
				cannonBallCol[i].z=target[i].pos[2];
				
			}
			
			if(target[i].targetstate==1)
			{
				target[i].Checkhitcube();
				target[i].DrawTarget();
				targetColl[i].drawSphere(50,50,0,0,0);
			}
			//////////////////////You Win Screen Target Counter///////////////////
			
		}
		


		//MISSILE MOTION
		for(int i=0;i<nMissile;i++)
		{
			missile[i].Checkhitcube();
			if(missile[i].state==1)
			{
			
				missile[i].Move(mx,my,mz);
				missile[i].Drawmissile();
				planeMissile[i].x=missile[i].centre.x;
				planeMissile[i].y=missile[i].centre.y;
				planeMissile[i].z=missile[i].centre.z;
			}
		}



		//TERRAIN DRAWING
		terrain.Draw(10,5);
		DrawSkyCube(0,-500,0,2600,900,2600,3);

		tempcX=10*rx;
		tempcZ=10*rz;
		tempcY=10*ry;

		for(int i=0;i<totalNumberOfSpheresPlane;i++)
		{
			spheres[i].x=planeSpheres[i].x;
			spheres[i].y=planeSpheres[i].y;
			spheres[i].z=planeSpheres[i].z;
		}
		
		if(0==FsGetKeyState(FSKEY_LEFT)&& 0==FsGetKeyState(FSKEY_RIGHT) && 0==FsGetKeyState(FSKEY_UP) && 0==FsGetKeyState(FSKEY_DOWN) /*&& 0==FsGetKeyState(FSKEY_N)*/ )
		{
			oxr=camera.x+tempcX;
			oyr=camera.y+tempcY;
			ozr=camera.z+tempcZ;

			ox=camera.x-tempcX;
			oy=camera.y-tempcY;
			oz=camera.z-tempcZ;

			if(bankingState==1)
			{
				hVSv=4;
				r=cambInside*0.1;
				RotatePlane(vertex, numberOfPoints, camera.x,camera.y, camera.z, fx,fy,fz, rx,ry,rz,r,hVSv,camera.b,cambInside);
				collisionSpheresRotation(spheres, totalNumberOfSpheresPlane, camera.x,camera.y, camera.z, fx,fy,fz, rx,ry,rz,r,hVSv,camera.b,cambInside);
				cambInside=cambInside-r;
				camera.b=cambInside;
				if(cambInside==0.0)
				{
					bankingState=0;
				}
			}
		}

		camera.GetForwardVector(fx,fy,fz);
		camera.GetRightHorVector(rx,ry,rz);
		ux=uz=0.0;uy=1.0;

		if(hVSv!=4 && hVSv!=0)
		{
			RotatePlane(vertex, numberOfPoints, camera.x,camera.y, camera.z, fx,fy,fz, rx,ry,rz,r,hVSv,camera.b,cambInside);
			collisionSpheresRotation(spheres, totalNumberOfSpheresPlane, camera.x,camera.y, camera.z, fx,fy,fz, rx,ry,rz,r,hVSv,camera.b,cambInside);
			
		}

		for(int i=0;i<totalNumberOfSpheresPlane;i++)
		{
			planeSpheres[i].x=spheres[i].x;
			planeSpheres[i].y=spheres[i].y;
			planeSpheres[i].z=spheres[i].z;
		}

		r=0;
		hVSv=0;
		
		origin.x=camera.x;
		origin.y=camera.y;
		origin.z=camera.z;
		Drawplane(vertex,origin,airplane.points);


		//COLLISION CHECKING------------->

		//PLANE WITH GROUND
		if(bigPlaneSpheres.collisionCheckerGroundPlaneBasic(fy,uy,camera.y)==0)
		{
			for(int j=0;j<totalNumberOfSpheresPlane;j++)
			{
				if(planeSpheres[j].collisionCheckerGroundPlaneAdv(camera.y)==1)
				{
					PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
					terminate=1;
				}
			}
		}

		//PLANE WITH HILLS
		for(int i=0;i<26;i++)
		{
			if(bigPlaneSpheres.collisionCheckerPlaneBasic(terrainCol[i],camera.x, camera.y,camera.z,fx,fy,fz,ux,uy,uz)==1)
			{
				for(int j=0;j<totalNumberOfSpheresPlane;j++)
				{
					if(planeSpheres[j].collisionCheckerPlaneAdv(terrainCol[i],camera.x,camera.y,camera.z)==1)
					{
						PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
						terminate=1;
					}
				}
			}
			
		}

		//PLANE WITH TARGETS
		for(int i=0;i<5;i++)
		{
			if(bigPlaneSpheres.collisionCheckerPlaneBasic(targetColl[i],camera.x, camera.y,camera.z,fx,fy,fz,ux,uy,uz)==1)
			{
				for(int j=0;j<totalNumberOfSpheresPlane;j++)
				{
					if(planeSpheres[j].collisionCheckerPlaneAdv(targetColl[i],camera.x,camera.y,camera.z)==1)
					{
						PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
						terminate=1;
					}
				}
			}
			
		}

		//MISSILE COLLISIONS COMPLETE
		for(int i=0;i<nMissile;i++)
		{
			if(missile[i].state==1)
			{
				for(int j=0;j<5;j++)
				{
					if(planeMissile[i].collisionCheckerBasic(targetColl[j])==1)
					{
						PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
						missile[i].state=0;
						target[j].targetstate=0;
						cannonBallCol[j].x=-10000;
						cannonBallCol[j].r=0;
						targetdead=targetdead+1;
						
					}
				}

				for(int j=0;j<26;j++)
				{
					if(planeMissile[i].collisionCheckerBasic(terrainCol[j])==1)
					{
						missile[i].state=0;
					}
				}

			}

		}

		//CANNONBALL COLLISIONS COMPLETE
		for(int i=0;i<5;i++)
		{
			if(target[i].cannonballstate==1)
			{
				if(bigPlaneSpheres.collisionCheckerPlaneBasic(cannonBallCol[i],camera.x, camera.y,camera.z,fx,fy,fz,ux,uy,uz)==1)
				{
					for(int j=0;j<totalNumberOfSpheresPlane;j++)
					{
						if(planeSpheres[j].collisionCheckerPlaneAdv(cannonBallCol[i],camera.x,camera.y,camera.z)==1)
						{
							PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
							terminate=1;
						}
					}
				}

				for(int j=0;j<26;j++)
				{
					if(cannonBallCol[i].collisionCheckerBasic(terrainCol[j])==1)
					{
						target[i].cannonballstate=0;
						PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC|SND_ALIAS | SND_APPLICATION);
					}
				}

			}

		}

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);
		if(terminate==0)
		{
			glColor3f(0.0,0.0,0.0);
			glBegin(GL_QUADS);
			glVertex2i(10,490);
			glVertex2i(110,490);
			glVertex2i(110,590);
			glVertex2i(10,590);

			glEnd();

			glColor3f(1.0,0.0,0.0);
			if(target[0].targetstate==1)
			DrawCircle((2600/26-1650/26)+10,(1920/26)+490,2,1);
			if(target[2].targetstate==1)
			DrawCircle((2600/26-680/26)+10,(1470/26)+490,2,1);
			if(target[3].targetstate==1)
			DrawCircle(2600/26-2330/26+10,760/26+490,2,1);
			if(target[4].targetstate==1)
			DrawCircle(2600/26-530/26+10,300/26+490,2,1);
			if(target[1].targetstate==1)
			DrawCircle(2600/26-860/26+10,1970/26+490,2,1);
		
			glColor3f(1.0,1.0,1.0);
			DrawCircle((camera.x+75.0*fx-10*ux)/26+10,(camera.z+75.0*fz-10*uz)/26+490,2,1);
			glBegin(GL_LINES);
			glVertex2d((camera.x+75.0*fx-10*ux)/26+10,(camera.z+75.0*fz-10*uz)/26+490);
			glVertex2d((camera.x+75.0*fx-10*ux)/26+10+fx*10,(camera.z+75.0*fz-10*uz)/26+490+fz*10);

			glEnd();
		}
		if(targetdead==5)
		{
			terminate=1;
		}
        FsSwapBuffers();
		/*lastFrame = thisFrame;*/
        FsSleep(10);
	
    }

	FsSleep(2000);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	game_over(targetdead);
	FsSleep(2000);
	
    return 0;
}