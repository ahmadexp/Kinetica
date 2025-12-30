//these variables should always exist
float screenw;
float screenh;
float screena;
int screenbpp;

bool fullscreen;
bool showcursor;

bool antialiasing;
bool mipmapping;
bool usehmd;
float fov;

//set the settings
void loadgenericsettings(){
	usehmd = false;
	//load the settings ini
	loadinifile((char*)"settings.ini");

	//load read the setttings
	screenw=readfloatfromini((char*)"screenw");
	screenh=readfloatfromini((char*)"screenh");
	screenbpp=(int)readfloatfromini((char*)"screenbpp");

	fullscreen=(bool)(readfloatfromini((char*)"fullscreen")!=0);
	showcursor=(bool)(readfloatfromini((char*)"showcursor")!=0);
	antialiasing=(bool)(readfloatfromini((char*)"antialiasing")!=0);
	mipmapping=(bool)(readfloatfromini((char*)"mipmapping")!=0);
	usehmd=(bool)(readfloatfromini((char*)"usehmd")!=0);
	fov=readfloatfromini((char*)"fov");
	if (fov == 0) fov = 60.0f;

	//calculate the screens aspect ratio
	screena = screenw/screenh;

}
