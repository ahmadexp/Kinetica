//controller input variables
int cursorx[4];
int cursory[4];
int cursorxmov[4];
int cursorymov[4];
bool centercursor=0;

const int keycount=SDL_NUM_SCANCODES;
int keystate[keycount];
const int buttoncount=20;
int buttonstate[keycount];
const int mousecount=10;
int mousestate[mousecount];

// Initialize input device
void setupinput(){

}

void updateinput(){
	if (pSensor)
	{        
		Quatf    hmdOrient = fusion.GetOrientation();
		float    yaw = 0.0f;

		hmdOrient.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

		EyeYaw += (yaw - LastSensorYaw);
		LastSensorYaw = yaw;    
		roll=roll;
		//EyeYaw=EyeYaw;
		//pitch=pitch;

		camxang = -pitch; 
		camyang = -yaw-Start_yaw; 
		camzang = -roll;
	}


	
   
    //*** Adjust 0.5,0.5 according to how you render
   

	SDL_Event event;

    for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;
    for(int a=0;a<buttoncount;a++)if(buttonstate[a]==2)buttonstate[a]=1;
    for(int a=0;a<mousecount;a++)if(mousestate[a]==2)mousestate[a]=1;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                shutdownprogram = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode < keycount && event.key.keysym.scancode >= 0)
		            keystate[event.key.keysym.scancode]=2;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.scancode < keycount && event.key.keysym.scancode >= 0)
		            keystate[event.key.keysym.scancode]=0;
                break;
            case SDL_JOYBUTTONDOWN:
                if (event.jbutton.button < buttoncount)
		            buttonstate[event.jbutton.button]=2;
                break;
            case SDL_JOYBUTTONUP:
                if (event.jbutton.button < buttoncount)
		            buttonstate[event.jbutton.button]=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button < mousecount)
		            mousestate[event.button.button]=2;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button < mousecount)
    		        mousestate[event.button.button]=0;
                break;
        }
    }
	
	// Normalize distinct press states (2 -> 1) similar to original logic
    // Original logic: for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;
    // But original logic did this BEFORE peeping events?
    // "for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;"
    // This turns a "just pressed" frame (2) into "held" (1) for the next frame.
    // If we do this here, we need to do it at start of frame or end?
    // Original:
    // 1. Normalize (2->1)
    // 2. Peep (set 2, or 0)
    // So if I set 2 in the loop, it remains 2 for this frame. Next frame it becomes 1.
    // So I should perform normalization at the start of updateinput.
    
    // BUT, updateinput is called inside the loop.
    // Let's preserve the normalization loop at the top.
    
	if(centercursor){
		//SDL_WM_GrabInput(SDL_GRAB_ON); // SDL_SetRelativeMouseMode(SDL_TRUE) is better in SDL2, but Warp is requested.
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		//SDL_GetRelativeMouseState(&cursorxmov[0],&cursorymov[0]);
        // SDL 1.2 used screen->w/2.
		SDL_WarpMouseInWindow(window, (int)screenw/2, (int)screenh/2);
		cursorxmov[0]=cursorx[0]-((int)screenw/2);
		cursorymov[0]=cursory[0]-((int)screenh/2);
	}else{
		int oldx=cursorx[0];
		int oldy=cursory[0];
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		cursorxmov[0]=cursorx[0]-oldx;
		cursorymov[0]=cursory[0]-oldy;
	}
}

