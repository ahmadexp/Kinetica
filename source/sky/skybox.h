#ifndef __SKYBOX_H__
#define __SKYBOX_H__

//#include "glaux.h"
#include <SDL.h>
#include <iostream>

#ifndef GL_TEXTURE_CUBE_MAP_ARB
#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A
#endif

bool SKYBOX_Initialize(){

	GLenum cube_map_target[6] = {           
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
	};

	SDL_Surface* texture_image[6];

	char sky_tex_name[6][20]={"Media/sky/XN.bmp",
		"Media/sky/XP.bmp",
		"Media/sky/YN.bmp",
		"Media/sky/YP.bmp",
		"Media/sky/ZN.bmp",
		"Media/sky/ZP.bmp"};

	for (int i = 0; i < 6; i++){
		SDL_Surface* temp = SDL_LoadBMP(sky_tex_name[i]);
		if (!temp) {
		    std::cerr << "Failed to load skybox texture: " << sky_tex_name[i] << " Error: " << SDL_GetError() << std::endl;
			texture_image[i] = NULL;
			continue;
		}
		
		texture_image[i] = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGBA32, 0);
		SDL_FreeSurface(temp);

		if (texture_image[i]) {
			// Vertical flip: OpenGL expects bottom-to-top pixel data
			int pitch = texture_image[i]->pitch;
			unsigned char* temp_row = new unsigned char[pitch];
			unsigned char* pixels = (unsigned char*)texture_image[i]->pixels;
			for (int j = 0; j < texture_image[i]->h / 2; ++j) {
				unsigned char* row1 = pixels + j * pitch;
				unsigned char* row2 = pixels + (texture_image[i]->h - 1 - j) * pitch;
				memcpy(temp_row, row1, pitch);
				memcpy(row1, row2, pitch);
				memcpy(row2, temp_row, pitch);
			}
			delete [] temp_row;
		}
	}

	glGenTextures(1, &cube_map_texture_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	for (int i = 0; i < 6; i++) {
		if (texture_image[i]) {
			glTexImage2D(cube_map_target[i], 0, GL_RGBA8, texture_image[i]->w, texture_image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image[i]->pixels);
			SDL_FreeSurface(texture_image[i]);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );

	return true;

}

void SKYBOX_DrawSkyBox(void){
	// Cube size
	float t = 1.5f;

	//use of the cube map texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	//setting the orientation
//	glPushMatrix();
//	glLoadIdentity();
//	glRotatef( camera_pitch, 1.0f, 0.0f, 0.0f );
//	glRotatef( camera_yaw, 0.0f, 1.0f, 0.0f );	
//	glRotatef(camera_roll,0.0f,0.0f,1.0f);

	 // glRotated(90,0,1,0);

	// Rendering the geometry
	glBegin(GL_TRIANGLE_STRIP);			                // X Negative	
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t); 	
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// X Positive
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Negative	
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Positive		
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Negative		
	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Positive	
	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	// Reinitialization of the the mode view matrix
	//glPopMatrix();
}


void SKYBOX_Render(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB); 
	glDisable(GL_LIGHTING);

	glDepthMask(GL_FALSE);

	SKYBOX_DrawSkyBox();  

	glDepthMask(GL_TRUE);

	glDisable(GL_TEXTURE_CUBE_MAP_ARB); 
	glEnable(GL_LIGHTING);
}

void SKYBOX_Finalize(){
	// Suppression de la skybox
	glDeleteTextures( 1, &cube_map_texture_ID );
}


#endif