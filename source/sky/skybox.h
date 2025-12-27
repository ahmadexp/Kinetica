#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <stdio.h>

GLuint loadbmp(char* filename,bool mipmap);

static GLuint g_skytex[6];

static inline bool SKYBOX_Initialize(){
    char *suffixes[] = { (char*)"XN", (char*)"XP", (char*)"YP", (char*)"YN", (char*)"ZN", (char*)"ZP" };
    char filename[256];
    
    for(int i=0; i<6; i++){
        sprintf(filename, "Media/sky/%s.bmp", suffixes[i]);
        g_skytex[i] = loadbmp(filename, true);
        
        glBindTexture(GL_TEXTURE_2D, g_skytex[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    return true;
}

static inline void SKYBOX_DrawSkyBox(void){}

static inline void SKYBOX_Render(){
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    
    float r = 50.0f; // Radius

    // XN (Left)
    glBindTexture(GL_TEXTURE_2D, g_skytex[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, -r, -r); // Bottom Left (looking from inside) - wait, checking orientation
    glTexCoord2f(1, 0); glVertex3f(-r, -r,  r); // Bottom Right
    glTexCoord2f(1, 1); glVertex3f(-r,  r,  r); // Top Right
    glTexCoord2f(0, 1); glVertex3f(-r,  r, -r); // Top Left
    glEnd();

    // XP (Right)
    glBindTexture(GL_TEXTURE_2D, g_skytex[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( r, -r,  r);
    glTexCoord2f(1, 0); glVertex3f( r, -r, -r);
    glTexCoord2f(1, 1); glVertex3f( r,  r, -r);
    glTexCoord2f(0, 1); glVertex3f( r,  r,  r);
    glEnd();

    // YP (Top)
    glBindTexture(GL_TEXTURE_2D, g_skytex[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r,  r, -r); // FL
    glTexCoord2f(1, 0); glVertex3f( r,  r, -r); // FR
    glTexCoord2f(1, 1); glVertex3f( r,  r,  r); // BR
    glTexCoord2f(0, 1); glVertex3f(-r,  r,  r); // BL
    glEnd(); // Orientation might need checking

    // YN (Bottom)
    glBindTexture(GL_TEXTURE_2D, g_skytex[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(-r, -r, -r);
    glTexCoord2f(0, 1); glVertex3f( r, -r, -r);
    glTexCoord2f(0, 0); glVertex3f( r, -r,  r);
    glTexCoord2f(1, 0); glVertex3f(-r, -r,  r);
    glEnd();

    // ZN (Back)
    glBindTexture(GL_TEXTURE_2D, g_skytex[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( r, -r, -r);
    glTexCoord2f(1, 0); glVertex3f(-r, -r, -r);
    glTexCoord2f(1, 1); glVertex3f(-r,  r, -r);
    glTexCoord2f(0, 1); glVertex3f( r,  r, -r);
    glEnd();

    // ZP (Front)
    glBindTexture(GL_TEXTURE_2D, g_skytex[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, -r,  r);
    glTexCoord2f(1, 0); glVertex3f( r, -r,  r);
    glTexCoord2f(1, 1); glVertex3f( r,  r,  r);
    glTexCoord2f(0, 1); glVertex3f(-r,  r,  r);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
}

static inline void SKYBOX_Finalize(){ 
   glDeleteTextures(6, g_skytex);
}

#endif