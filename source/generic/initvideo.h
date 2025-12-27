SDL_Window* window = NULL;
SDL_GLContext gl_context;

float background_color[4]={0.5, 0.66, 0.85, 1};      // bakgournd sky color 0.5
float fog_color[4]={0.4, 0.56, 0.75, 0.1};			  // fog color	

void initopengl(){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);						//Initialize SDL
    
    //Set Pixel Format
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    if(antialiasing){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Assuming 4x MSAA
	}

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

    int width = (int)screenw;
    int height = (int)screenh;

    // Handle vrmode split if necessary, or just create full window.
    // Original code halved width for vrmode SetVideoMode, which is weird for window setup but maybe logic resides elsewhere.
    // Keeping logic: if vrmode, width is screenw/2?
    // Wait, original: screen = SDL_SetVideoMode((int)screenw/2...
    // Only if screenw was 0 initially then it set it.
    // But later: if(fullscreen==0) if(vrmode) screen = SDL_SetVideoMode((int)screenw/2...
    
    // Let's rely on standard resolution if not 0.
    if(screenw == 0 || screenh == 0) {
        screenw = 1024; // Default?
        screenh = 768;
    }
    
    // Adjust for vrmode logic as per original
    int create_w = (int)screenw;
    if(vrmode && !fullscreen) create_w = (int)screenw/2; 
    
    window = SDL_CreateWindow("TheKineticaEngin", 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              create_w, (int)screenh, 
                              flags);

    if (!window) { SDL_Quit(); exit(3); }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) { SDL_Quit(); exit(3); }
    
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // VSync

	SDL_GL_SwapWindow(window);	

    // Update global screen size variables from actual window size
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    screenw = (float)w;
    screenh = (float)h;
    screena = screenw/screenh;

    //Size OpenGL to Video Surface
	if(vp==1){
        if (vrmode)
            glViewport((int)screenw/2, 0, (int)screenw/2, (int)screenh);
        else 
            glViewport(0, 0, (int)screenw, (int)screenh);
	}
	else{
        if (vrmode)
            glViewport(0, 0, (int)screenw/2, (int)screenh);
        else 
            glViewport(0, 0, (int)screenw, (int)screenh);
    } 

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0,screena,1.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
	
    //OpenGL Render Settings
	glClearColor(background_color[0],background_color[1],background_color[2],background_color[3]);							//background color  
    glClearDepth(1000.0);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.0f);


    // Apply antialiasing GL settings if enabled 
	if(antialiasing){
		glEnable(GL_MULTISAMPLE);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	}

}

void initvideo(){

	//the setup
	initopengl();
	
	//get correct info about the screen (already done in initopengl)
	
    screenbpp = 32; // Assuming 32-bit color for now

	//show or hide the cursor
	SDL_ShowCursor(showcursor);

}
