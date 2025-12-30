//super ultra mega generic includes

//#define NO_SDL_GLEXT
bool useshaders = true;

#ifdef _WIN32
#include <GL/glew.h>
#include <GL/glut.h>
#else
#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#endif

const float PI=3.14159265f;
const float degreesinradian=360/(2*PI); 
const float radiansindegree=(2*PI)/360;

using namespace OVR;

float                camxpos=0,camypos=0,camzpos=0;
float                camxang=0,camyang=90*radiansindegree,camzang=0;
int vp;
bool shutdownprogram = 0;
Ptr<HMDDevice>      pHMD;
Quatf               Rot;
float               LastSensorYaw;
Vector3f            EyePos;
float               EyeYaw;
float               EyePitch;       
float               EyeRoll;   
float               tyaw,yaw, pitch, roll,Start_yaw=0;
static OVR::SensorDevice* pSensor;
static OVR::SensorFusion fusion;
static OVR::DeviceManager* pManager;
static OVR::Quatf q;


enum Eye {
        Left, Right
    };

bool shading_enabled = false;

#ifdef _WIN32
#define uglGetProcAddress(x) wglGetProcAddress(x)
#else
// On Mac/Linux, standard GL functions are usually linked directly or loaded differently (e.g. glX). 
// For now, define as NULL or proper loader if needed.
#define uglGetProcAddress(x) NULL 
#endif

#ifdef _WIN32
#include <windows.h>
#endif
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>

extern SDL_Window* window;
extern SDL_GLContext gl_context;

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include <malloc.h>
#else
#include <stdlib.h>
// Compatibility macros for MSVC secure functions
#define sprintf_s(buf, fmt, ...) sprintf(buf, fmt, ##__VA_ARGS__)
#define strcpy_s(dst, src) strcpy(dst, src)
#define strcat_s(dst, src) strcat(dst, src)
#endif

//to read the joystick playing wave clips 
#ifdef _WIN32
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")
#endif

#include <stdio.h>

GLuint cube_map_texture_ID;

#include "skybox.h"
//SKYBOX * skybox; 

//super generic
#include "genericmath.h"
#include "readinifiles.h"
#include "genericsettings.h"
#include "dirlist.h"
//#include "skybox.h"
#include "initvideo.h"
#include "input.h"
#include "bresenham.h"
#include "3dfunctions.h"
//3DMath.h is already included from within spherebumpmesh.h
//#include "3DMath.h"
#include "spherebumpmesh.h"
//specific to OpenGL
#include "opengl/loadtexture.h"

#include "loadobj.h"
#include "lodepng.h"
#include "loadbmp.h"
#include "loadms3d.h"

//include sound with OpenAL
#include "AL/sound.h"

//specific to SDL surfaces

#include "sdldraw/loadanddrawsurfaces.h"
#include "sdldraw/getputpixel.h"
#include "sdldraw/drawcircle.h"
#include "sdldraw/drawline.h"
#include "sdldraw/drawpolygon.h"
#include "sdldraw/drawhexagon.h"
#include "sdldraw/filtersurface.h"
#include "sdldraw/rotoscale.h"
#include "sdldraw/savesurface.h"

//the dashboard and related functions
#include "dashboard/dashsetup.h"
#include "dashboard/dashloop.h"



void genericsetup(){
	//seed the random number generator
	srand((int)time(NULL));

	//setup the screen or window
	initvideo();

	//init_sound();

	SKYBOX_Initialize();

	//setup for the controller input

	setupinput();
}