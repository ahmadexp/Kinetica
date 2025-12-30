SDL_Surface *screen; // Kept for compatibility if used, but might be invalid for GL
SDL_Window* window = NULL;
SDL_GLContext gl_context;

float background_color[4]={0.5, 0.66, 0.85, 1};      // bakgournd sky color 0.5
float fog_color[4]={0.4, 0.56, 0.75, 0.1};			  // fog color	

void initopengl(){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    
    //enable anti aliasing
	if(antialiasing){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	}

    //Set Pixel Format
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Uint32 flags = SDL_WINDOW_OPENGL;
    if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    
    if(screenw==0 || screenh==0) { screenw=800; screenh=600; } // Default if 0

    window = SDL_CreateWindow("TheKineticaEngin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)screenw, (int)screenh, flags);
    if(!window) { SDL_Quit(); exit(3); }
    
    gl_context = SDL_GL_CreateContext(window);
	if(!gl_context){
		printf("ERROR: SDL_GL_CreateContext failed: %s\n", SDL_GetError());
		exit(3);
	}
	if(SDL_GL_MakeCurrent(window, gl_context) < 0){
		printf("ERROR: SDL_GL_MakeCurrent failed: %s\n", SDL_GetError());
	}
    
    const char *version = (const char *)glGetString(GL_VERSION);
    const char *renderer = (const char *)glGetString(GL_RENDERER);
    printf("OpenGL Version: %s\n", version ? version : "NULL");
    printf("OpenGL Renderer: %s\n", renderer ? renderer : "NULL");
    
    // Update globals
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    screenw = (float)w;
    screenh = (float)h;
    screena = screenw/screenh;
    
    //screen = SDL_GetWindowSurface(window); // Might work or return NULL.
	screen = NULL;
    //if(screen) screenbpp = screen->format->BitsPerPixel;
	screenbpp = 32;
    // else default to 32?
    
	if(antialiasing){
		glEnable(GL_MULTISAMPLE);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
    }

	SDL_GL_SwapWindow(window);

    //Size OpenGL to Video Surface
	if(vp==1){
        glViewport((int)screenw/2, 0, (int)screenw/2, (int)screenh);
	}
	else{
        glViewport(0, 0, (int)screenw/2, (int)screenh); // Original logic preserved
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

}

void initvideo(){

	//the setup
	initopengl();
	
	//show or hide the cursor
	SDL_ShowCursor(showcursor);

}
