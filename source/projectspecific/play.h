void play(float gamespeed){

		//decrease view range
		if(keystate[SDL_SCANCODE_1]==2){
			worldtileviewrange-=1;
			if(worldtileviewrange<1)worldtileviewrange=1;
		}
		//increase view range
		if(keystate[SDL_SCANCODE_2]==2){
			worldtileviewrange+=1;
			if(worldtileviewrange>60)worldtileviewrange=60;
		}

		if(keystate[SDL_SCANCODE_V]==2){
			PositionTest();
		}

		//decrease view range
		if(keystate[SDL_SCANCODE_B]==2){
			test-=1;
			if(test<1)test=1;
			loadtiles();
		}
		//increase view range
		if(keystate[SDL_SCANCODE_N]==2){
			test+=1;
			if(test>60)test=60;
			loadtiles();
		}



		//textures on off
		if(keystate[SDL_SCANCODE_3]==2){
			if(usetextures){usetextures=0;}else{usetextures=1;}
		}
		//ghost mode on off
		if(keystate[SDL_SCANCODE_4]==2){
			if(ghostmode==1){ghostmode=0;}else{ghostmode=1;}
		}
		//previous tile
		if(keystate[SDL_SCANCODE_5]==2){
			worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]-=1;
			if(worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]<0)
				worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]+=worldtilecount;
		}
		//next tile
		if(keystate[SDL_SCANCODE_6]==2){
			worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]+=1;
			if(worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]>worldtilecount-1)
				worldgrid[playerxgridpos][playerygridpos][playerzgridpos][0]-=worldtilecount;
		}
		//rotate tile
		if(keystate[SDL_SCANCODE_7]==2){
			worldgrid[playerxgridpos][playerygridpos][playerzgridpos][1]+=1;
			if(worldgrid[playerxgridpos][playerygridpos][playerzgridpos][1]>3)
				worldgrid[playerxgridpos][playerygridpos][playerzgridpos][1]-=4;
		}
		//save everything
		if(keystate[SDL_SCANCODE_8]==2){
//			saveworldgrid();
		//	save();
		}
		//load everything
		if(keystate[SDL_SCANCODE_9]==2){
//			loadworldgrid();
		//	load();
		}


		//Mouse on off
		if(keystate[SDL_SCANCODE_M]==2){
			if(usemouse==1){usemouse=0;}else{usemouse=1;/*cursorx[0]=(int)screenh/2;cursory[0]=(int)screenw/2;*/}
		}

		//Player on off
		if(keystate[SDL_SCANCODE_P]==2){
			if(showplayer==1){showplayer=0;}else{showplayer=1;}
		}

		//Autoexit on off
		if(keystate[SDL_SCANCODE_E]==2){
			if(autoexit==1){autoexit=0;}else{autoexit=1;}
		}

		//Joystick on off
		if(keystate[SDL_SCANCODE_J]==2){
			if(usejoystick==1){usejoystick=0;}else{usejoystick=1;}
		}

		if(usejoystick){	//Joystick control	

	#ifdef _WIN32
			if(joyGetPos(0,&joystick))	usejoystick=0;    //obtain joystick value and check the presence
			else{
				if((32768-(float)joystick.wYpos>1500)||(32768-(float)joystick.wYpos<-1500)){
					playerzposmov-=(32768-(float)joystick.wYpos)*(0.03/32768)*gamespeed*cos(camxang)*cos(-camyang);
					playeryposmov-=(32768-(float)joystick.wYpos)*(0.03/32768)*gamespeed*sin(camxang);
					playerxposmov-=(32768-(float)joystick.wYpos)*(0.03/32768)*gamespeed*cos(camxang)*sin(-camyang);
				}
			}
	#else
			if(joystick == NULL){
				joystick = SDL_JoystickOpen(0);
				if(!joystick) usejoystick = 0;
			}
			if(joystick){
				int sval = -SDL_JoystickGetAxis(joystick, 1); // Y axis, negate to match original direction
				if((sval>1500)||(sval<-1500)){
					playerzposmov -= sval * (0.03/32768.0f) * gamespeed * cos(camxang) * cos(-camyang);
					playeryposmov -= sval * (0.03/32768.0f) * gamespeed * sin(camxang);
					playerxposmov -= sval * (0.03/32768.0f) * gamespeed * cos(camxang) * sin(-camyang);
				}
			}
	#endif
		}
		//GPS Minimap on ff
		if(keystate[SDL_SCANCODE_G]==2){
			if(showminimap==1){showminimap=0;}else{showminimap=1;}
		}

		//user shaders
		if(keystate[SDL_SCANCODE_X]==2)
		{
			if(useshaders)
			{
				useshaders=false; 
				glUseProgram(0);
				glClearColor (1.0f, 0.0f, 0.0f, 0.5f);
			}
			else
			{
				useshaders = true;
			}
		}

		//Quit the game
		if(keystate[SDL_SCANCODE_Q]==2)shutdownprogram=1;


	//update entities
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	for(int e=0; e<entitycount[x][y][z]; e++){
		if(entitylist[x][y][z][e]->type==entitytype_disccartridge){
			entitylist[x][y][z][e]->yang+=entitylist[x][y][z][e]->yangmov*gamespeed;
			if(dist3d(
				entitylist[x][y][z][e]->xpos,
				entitylist[x][y][z][e]->ypos,
				entitylist[x][y][z][e]->zpos,
				playerxpos,playerypos,playerzpos)<3.25f){
					delete entitylist[x][y][z][e];
					if(e<entitycount[x][y][z]-1)for(int b=e;b<entitycount[x][y][z];b++)entitylist[x][y][z][b]=entitylist[x][y][z][b+1];
					entitycount[x][y][z]-=1;
					e--;
					collectablesfound++;
//					save();
			}
		}else if(entitylist[x][y][z][e]->type==entitytype_elevator){
			entitylist[x][y][z][e]->ypos+=entitylist[x][y][z][e]->yposmov*gamespeed;
			if(entitylist[x][y][z][e]->yposmov>0){
				if(x==playerxgridpos && z==playerzgridpos
				&& playerypos>entitylist[x][y][z][e]->ypos){
				if(worldgrid[x][y][z][0]==34 || worldgrid[x][y+1][z][0]==34)
					entitylist[x][y][z][e]->ypos-=entitylist[x][y][z][e]->yposmov*gamespeed;
				}
				if(worldgrid[x][y][z][0]==34
				&& entitylist[x][y][z][e]->ypos>y*worldtilesize){
					entitylist[x][y][z][e]->ypos=y*worldtilesize;
					entitylist[x][y][z][e]->yposmov*=-1;
				}
			}else{
				if(x==playerxgridpos && z==playerzgridpos
				&& playerypos<entitylist[x][y][z][e]->ypos-4.5f){
				if(worldgrid[x][y][z][0]==32 || worldgrid[x][y-1][z][0]==32)
					entitylist[x][y][z][e]->ypos-=entitylist[x][y][z][e]->yposmov*gamespeed;
				}
				if(worldgrid[x][y][z][0]==32
				&& entitylist[x][y][z][e]->ypos<y*worldtilesize){
					entitylist[x][y][z][e]->ypos=y*worldtilesize;
					entitylist[x][y][z][e]->yposmov*=-1;
				}
			}
		}
	}

	//update entity grid position
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	for(int e=0; e<entitycount[x][y][z]; e++){
		int xgridpos=(int)floor(entitylist[x][y][z][e]->xpos/worldtilesize+0.5f);
		int ygridpos=(int)floor(entitylist[x][y][z][e]->ypos/worldtilesize+0.5f);
		int zgridpos=(int)floor(entitylist[x][y][z][e]->zpos/worldtilesize+0.5f);
		if(x!=xgridpos || y!=ygridpos || z!=zgridpos)
		if(entitycount[xgridpos][ygridpos][zgridpos]<maxentities){
			entitylist[xgridpos][ygridpos][zgridpos][(int)entitycount[xgridpos][ygridpos][zgridpos]]=entitylist[x][y][z][e];
			entitycount[xgridpos][ygridpos][zgridpos]+=1;
			removeentityfromlist(x,y,z,e);
		}
	}

	//turn the camera

	//if(!mousestate[SDL_BUTTON_RIGHT])

	//remember where the player started
	float oldx=playerxpos;
	float oldy=playerypos;
	float oldz=playerzpos;

	if(usemouse){

		//if(dashusecursor[0]){ //Danyal took this stuff out because it seems to allow for mouse movement
		mouse_camyang = ((float)cursorx[0]-(screenw/2))*(180*radiansindegree/screenw);
		mouse_camxang = ((screenh/2)-(float)cursory[0])*(180*radiansindegree/screenh);
		//}
		//dont look too far up or down
		if(camxang<0-90*radiansindegree)camxang=0-90*radiansindegree;//looking down
		if(camxang>0+90*radiansindegree)camxang=0+90*radiansindegree;//looking up
		//move based on input
		float movespeed=0;
		float moveangle=0;
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDL_SCANCODE_W]|keystate[SDL_SCANCODE_UP])up=1;
		if(keystate[SDL_SCANCODE_S]|keystate[SDL_SCANCODE_DOWN])down=1;
		//to turn sideways left and right
		if(keystate[SDL_SCANCODE_A]|keystate[SDL_SCANCODE_LEFT])left=1;
		if(keystate[SDL_SCANCODE_D]|keystate[SDL_SCANCODE_RIGHT])right=1;

		if(keystate[SDL_SCANCODE_LEFT])
		camyang-=0.01f*gamespeed;

		if(keystate[SDL_SCANCODE_RIGHT])
		camyang+=0.01f*gamespeed;

		moveangle=atan2((float)right-(float)left,(float)up-(float)down);
		movespeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(movespeed>1)movespeed=1;
		if(movespeed>0.1){
		if(ghostmode)
		movein3dspace(playerxposmov,playeryposmov,playerzposmov,camyang,camxang,movespeed*0.2f*gamespeed);
		else{
			playerxposmov+=movespeed*cos(camyang+moveangle)*0.04f*gamespeed;
			playerzposmov+=movespeed*sin(camyang+moveangle)*0.04f*gamespeed;
			}
		}

		//camxang=nav_camxang+mouse_camxang;
		//camyang=nav_camyang+mouse_camyang;
		//camzang=nav_camzang+mouse_camzang;

	}
	else{

		//Arrow key control
		float movespeed=0;
		float moveangle=0;
		bool up=0,down=0;
		if(keystate[SDL_SCANCODE_UP])up=1;
		if(keystate[SDL_SCANCODE_DOWN])down=1;
		moveangle=atan2(0,(float)up-(float)down);
		movespeed=dist2d(0,(float)up-(float)down,0,0);
		if(movespeed>1)movespeed=1;
		if(movespeed>0.1){
			if(ghostmode)
			movein3dspace(playerxposmov,playeryposmov,playerzposmov,camyang,camxang,movespeed*0.2f*gamespeed);
			else{
				playerxposmov+=movespeed*sin(camyang+moveangle)*0.04f*gamespeed;
				playerzposmov-=movespeed*cos(camyang+moveangle)*0.04f*gamespeed;
			}
		}
		if(keystate[SDL_SCANCODE_LEFT])
		camyang-=0.02f*gamespeed;

		if(keystate[SDL_SCANCODE_RIGHT])
		camyang+=0.02f*gamespeed;		

	}

	//camxang=roll*degreesinradian;
	//	camyang=yaw*degreesinradian;
	//	camzang=pitch*degreesinradian;



	//head up on the ramp
	//if(worldgrid[(int)(playerxpos/10)][(int)(playerypos/10)][(int)(playerzpos/10)][0]==ramp_tile)
	//	camxang=10*radiansindegree;
	//else
	//	camxang=0;

//	camxang=playeryposmov*100*radiansindegree;

	//end of head up on the ramp

	//else
		//camxang=0;

	//gravity and jumping
	if(ghostmode==0){
		if(playergrounded){
			playerjumping=0;
			playeryposmov-=0.01f*gamespeed;
			/* //Danyal commented this to remove jumping from keyboard mode
			if(keystate[SDLK_SPACE]){
				playeryposmov=0.65f;
				playerjumping=1;
			}
			
		}else if(playerjumping){
			playeryposmov-=(0.03f-playeryposmov*0.08f)*gamespeed;
			
			if(keystate[SDLK_SPACE] && playeryposmov>0.1)
				playerjumping=1;
			else
				playerjumping=0;
			*/
		}else{
			playeryposmov-=0.035f*gamespeed;
		}
	}

	//movement takes effect
	playerxpos+=playerxposmov*gamespeed;
	playerypos+=playeryposmov*gamespeed;
	playerzpos+=playerzposmov*gamespeed;


	//bump into the world
	if(ghostmode==0){
		playerypos+=playerheight;
		int lowx=highint(playerxgridpos-2,0);
		int lowy=highint(playerygridpos-2,0);
		int lowz=highint(playerzgridpos-2,0);
		int highx=lowint(playerxgridpos+2+1,worldgridsizex);
		int highy=lowint(playerygridpos+2+1,worldgridsizey);
		int highz=lowint(playerzgridpos+2+1,worldgridsizez);
		for(int x=lowx; x<highx; x++)
		for(int y=lowy; y<highy; y++)
		for(int z=lowz; z<highz; z++){
			if(worldgrid[x][y][z][0]!=0)
				spherebumpmesh(playerxpos,playerypos,playerzpos,
				playerwidth,//playerwidth/playerheight,
				x*worldtilesize,y*worldtilesize,z*worldtilesize,0,
				worldtilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],
				1,0);
			for(int a=0; a<entitycount[x][y][z]; a++){
				if(entitytypesolid[entitylist[x][y][z][a]->type]==1){
					spherebumpmesh(playerxpos,playerypos,playerzpos,
					playerwidth,//playerwidth/playerheight,
					entitylist[x][y][z][a]->xpos,
					entitylist[x][y][z][a]->ypos,
					entitylist[x][y][z][a]->zpos,
					entitylist[x][y][z][a]->yang,
					entitycollisionmesh[entitylist[x][y][z][a]->type],1,0);
				}
			}
		}
		for(int x=lowx; x<highx; x++)
			for(int y=lowy; y<highy; y++)
				for(int z=lowz; z<highz; z++)
					if(worldgrid[x][y][z][0]){
						if(worldgrid[x][y][z][0]!=0)
							spherebumpmesh(playerxpos,playerypos,playerzpos,
							playerwidth,//playerwidth/playerheight,
							x*worldtilesize,y*worldtilesize,z*worldtilesize,0,
							worldtilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],
							0,1);
						for(int a=0; a<entitycount[x][y][z]; a++){
							if(entitytypesolid[entitylist[x][y][z][a]->type]==1){
								spherebumpmesh(playerxpos,playerypos,playerzpos,
								playerwidth,//playerwidth/playerheight,
								entitylist[x][y][z][a]->xpos,
								entitylist[x][y][z][a]->ypos,
								entitylist[x][y][z][a]->zpos,
								entitylist[x][y][z][a]->yang,
								entitycollisionmesh[entitylist[x][y][z][a]->type],0,1);
							}
						}
					}
		playerypos-=playerheight;
		if(playerypos>(float)(oldy+playeryposmov*gamespeed)+0.001){
			playergrounded=1;
		}else{
			playergrounded=0;
		}
	}
	//adjust momentum
	playerxposmov=(playerxpos-oldx)/gamespeed;
	playeryposmov=(playerypos-oldy)/gamespeed;
	playerzposmov=(playerzpos-oldz)/gamespeed;

	//Audio Effects ***************************
	ALfloat source0Vel[]={ 50*playerxposmov, 50*playeryposmov, 50*playerzposmov};
	alSourcefv(source[0],AL_VELOCITY,source0Vel);
	alListener3f(AL_POSITION, 245-playerxpos,26-playerypos,245-playerzpos);
	float directionvect[6];
	directionvect[0] = (float) sin((90*radiansindegree)-camyang);
	directionvect[1] = 0;
	directionvect[2] = (float) cos((90*radiansindegree)-camyang);
	directionvect[3] = 0;
	directionvect[4] = 1;
	directionvect[5] = 0;
	alListenerfv(AL_ORIENTATION, directionvect);
//	gluLookAt(245-playerxpos, 26-playerypos, 245-playerzpos,(245-playerxpos + sin(camyang)), 26-playerypos,(245-playerzpos - cos(camyang)),0.0, 1.0, 0.0);
//	ALfloat source0Pos[]={ (245-playerxpos)/10+(cos(camyang)), 26-playerypos, (245-playerzpos)/10+(sin(camyang))};	// Behind and to the left of the listener
//	alSourcefv(source[0],AL_POSITION,source0Pos);

	//end of Audio effect *************************

	//lose momentum
	
	if(ghostmode){
		playerxposmov-=playerxposmov*0.1f*gamespeed;
		playeryposmov-=playeryposmov*0.1f*gamespeed;
		playerzposmov-=playerzposmov*0.1f*gamespeed;
	}else{
		if(wheelchairmode){
			playerxposmov-=playerxposmov*0.15f*gamespeed;
			playeryposmov-=playeryposmov*0.004f*gamespeed;
			playerzposmov-=playerzposmov*0.15f*gamespeed;
		}else{
			playerxposmov-=playerxposmov*0.10f*gamespeed;
			playeryposmov-=playeryposmov*0.04f*gamespeed;
			playerzposmov-=playerzposmov*0.10f*gamespeed;
		}
	}
	
	//update the players grid position
	playerxgridpos=(int)((playerxpos+worldtilesize*0.5)/worldtilesize);
	playerygridpos=(int)((playerypos+worldtilesize*0.5)/worldtilesize);
	playerzgridpos=(int)((playerzpos+worldtilesize*0.5)/worldtilesize);

	//position camera
	camxpos=playerxpos;
	camypos=playerypos+playerheadheight;
	camzpos=playerzpos;
	//***Door Control***//
//***Door 2 start***//
	if((playerxpos>=170.75)&&(playerxpos<=175.75)){
	if(door_ang<100)
		door_ang=door_ang+100;
	    door[2].yang=door_ang;
   }
	if((playerxpos>=175.75)&&(playerxpos<=180.75)){
	if(door[2].yang==0)
	    door_ang=100;
     }
   if((playerxpos<170.75)||(playerxpos>180.75))
	door[2].yang=0;
//***Door 2 End***/
//***Door 0 End***//
  if((playerxpos>=308.5)&&(playerxpos<=313.5)){
	if(door_ang<100)
		door_ang=door_ang+100;
	door[0].yang=door_ang;
   }
   if((playerxpos>=313.5)&&(playerzpos<=318.5)){
	if(door[0].yang==0)
	    door_ang=100;
     }
  if((playerzpos<308.5)||(playerzpos>318.5))
	door[0].yang=0;                                 
  //***Door 0 End***/
  //***Door 1 Start***//
  if((playerzpos>=173.75)&&(playerzpos<=178.75)){   
	if(door_ang<100)
		door_ang=door_ang+100;
	    door[1].yang=door_ang;
     }
   if((playerzpos>=168.75)&&(playerzpos<=173.75)){
	if(door[1].yang==0)
	    door_ang=100;
     }
  if((playerzpos<168.75)||(playerzpos>178.775))
	door[1].yang=0;                                 
  //***Door 1 End***/
  //***Door 3 Start***//
 if((playerzpos>=306.75)&&(playerzpos<=311.75)){
	if(door_ang<100)
		door_ang=door_ang+100;
	    door[3].yang=door_ang;
   }
   if((playerzpos>=311.75)&&(playerzpos<=316.75)){
	if(door[3].yang==0)
	    door[3].yang=100;
     }
  if((playerzpos<306.75)||(playerzpos>316.75))
	door[3].yang=0;                                 
  //***Door 3 End***/
  //***Door 4 and 12 Start***//
  if((playerxpos>=207.3)&&(playerxpos<=211.3)){
	if((playerzpos>=192)&&(playerzpos<=197)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	  if (playerypos<35)
	door[4].yang=door_ang;
	 else
    door[12].yang=door_ang;
   }
	if((playerzpos<=192)&&(playerzpos>=187)){
	if (playerypos<35)
    if(door[4].yang==0)
	  door[4].yang=100;
	else
    if(door[12].yang==0)
	  door[12].yang=100; 
	}
	if((playerzpos<187)||(playerzpos>197))
	if (playerypos<35)
	door[4].yang=0;
	 else
    door[12].yang=0;
}
  //***Door 4 and 12 End***/
  //***Door 5 and 13 Start***//
  if((playerxpos>=278.3)&&(playerxpos<=283.3)){
	if((playerzpos>=192)&&(playerzpos<=197)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[5].yang=door_ang;
	 else
    door[13].yang=door_ang;
   }
	if((playerzpos<=192)&&(playerzpos>=187)){
	if (playerypos<35)
    if(door[5].yang==0)
	  door[5].yang=100;
	else
    if(door[13].yang==0)
	  door[13].yang=100; 
	}
	if((playerzpos<187)||(playerzpos>197))
    if (playerypos<35)
	door[5].yang=0;
	 else
    door[13].yang=0;

  }
//***Door 5 and 13 End***/
//***Door 7 and 15 Start***//
  if((playerzpos>=278)&&(playerzpos<=282)){
  if((playerxpos>=194.25)&&(playerxpos<=199.25)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[7].yang=door_ang;
	 else
    door[15].yang=door_ang;
   }
  if((playerxpos<=194.25)&&(playerxpos>=189.25)){
	if (playerypos<35)
    if(door[7].yang==0)
	  door[7].yang=100;
	else
    if(door[15].yang==0)
	  door[15].yang=100; 
	}
	if((playerxpos<189.25)||(playerxpos>199.25))
    if (playerypos<35)
	door[7].yang=0;
	 else
    door[15].yang=0;

  }
//***Door 7 and 15 End***/
//***Door 6 and 14 start***//
if((playerzpos>=208)&&(playerzpos<=212)){
	if((playerxpos>=194.25)&&(playerxpos<=199.25)){
		if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[6].yang=door_ang;
	 else
    door[14].yang=door_ang;
	}
	if((playerxpos<=194.25)&&(playerxpos>=189.25)){
	if (playerypos<35)
    if(door[6].yang==0)
	  door[14].yang=100;
	else
    if(door[14].yang==0)
	  door[14].yang=100; 
	}
	if((playerxpos<189.25)||(playerxpos>199.25))
	if (playerypos<35)
	door[6].yang=0;
	 else
    door[14].yang=0;
}
//***Door 6 and 14 End***/
//***Door 8 and 16 start***//
if((playerxpos>=207.3)&&(playerxpos<=211.3)){
	if((playerzpos>=288.75)&&(playerzpos<=293.75)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[8].yang=door_ang;
	 else
    door[16].yang=door_ang;
   }
  if((playerzpos>=293.75)&&(playerzpos<=298.75)){
	if (playerypos<35)
    if(door[8].yang==0)
	  door[8].yang=100;
	else
    if(door[16].yang==0)
	  door[16].yang=100; 
	}
	if((playerzpos<289.75)||(playerzpos>298.75))
	  if (playerypos<35)
	door[8].yang=0;
	 else
    door[16].yang=0;

 }
//***Door 8 and 16 End***/
//***Door 9 and 17 start***//
if((playerxpos>=278)&&(playerxpos<=282)){
	if((playerzpos>=288.75)&&(playerzpos<=293.75)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[9].yang=door_ang;
	 else
    door[17].yang=door_ang;
   }
	if((playerzpos>=293.75)&&(playerzpos<=298.75)){
	if (playerypos<35)
    if(door[9].yang==0)
	  door[9].yang=100;
	else
    if(door[17].yang==0)
	  door[17].yang=100; 
	}
	if((playerzpos<289.75)||(playerzpos>298.75))
    if (playerypos<35)
	door[9].yang=0;
	 else
    door[17].yang=0;
}
//***Door 9 and 17 End***/
//***Door 10 and 18 start***//
if((playerzpos>=277)&&(playerzpos<=280)){
	if((playerxpos>=290.75)&&(playerxpos<=295.75)){
	if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[10].yang=door_ang;
	 else
    door[18].yang=door_ang;
   }
	if((playerxpos<=300.75)&&(playerxpos>=295.75)){
	if (playerypos<35)
    if(door[10].yang==0)
	  door[10].yang=100;
	else
    if(door[18].yang==0)
	  door[18].yang=100; 
	}
	if((playerxpos<290.75)||(playerxpos>300.75))
	if (playerypos<35)
	door[10].yang=0;
	 else
    door[18].yang=0;

}
//***Door 10 and 18 End***/
//***Door 11 and 19 start***//
if((playerzpos>=206)&&(playerzpos<=210)){
if((playerxpos>=290.75)&&(playerxpos<=295.75)){
	  if(door_ang<100)
		door_ang=door_ang+100;
	if (playerypos<35)
	door[11].yang=door_ang;
	 else
    door[19].yang=door_ang;
   }
	if((playerxpos<=300.75)&&(playerxpos>=295.75)){
	if (playerypos<35)
    if(door[11].yang==0)
	  door[11].yang=100;
	else
    if(door[19].yang==0)
	  door[19].yang=100; 
	}
	if((playerxpos<290.75)||(playerxpos>300.75))
    if (playerypos<35)
	door[11].yang=0;
	 else
    door[19].yang=0;

}
//***Door 11 and 19 End***//
//***Door Control End***//

}
