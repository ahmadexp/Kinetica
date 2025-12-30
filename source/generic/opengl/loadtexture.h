GLuint maketexturefromsurface(SDL_Surface *surface,bool mipmap, bool flip = false){

	GLuint texture;
	GLenum texture_format;
	GLint  nOfColors;
	
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	if (!formattedSurface) return 0;
	
	// Vertical flip: OpenGL expects bottom-to-top pixel data
	if (flip) {
		int pitch = formattedSurface->pitch;
		unsigned char* temp_row = new unsigned char[pitch];
		unsigned char* pixels = (unsigned char*)formattedSurface->pixels;
		for (int i = 0; i < formattedSurface->h / 2; ++i) {
			unsigned char* row1 = pixels + i * pitch;
			unsigned char* row2 = pixels + (formattedSurface->h - 1 - i) * pitch;
			memcpy(temp_row, row1, pitch);
			memcpy(row1, row2, pitch);
			memcpy(row2, temp_row, pitch);
		}
		delete [] temp_row;
	}

	nOfColors = formattedSurface->format->BytesPerPixel;
	if (nOfColors == 4) {
		if (formattedSurface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else {
		texture_format = GL_RGB;
	}
	GLint internal_format = (nOfColors == 4) ? GL_RGBA8 : GL_RGB8;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, internal_format, formattedSurface->w, formattedSurface->h,
			texture_format,GL_UNSIGNED_BYTE,formattedSurface->pixels);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0, internal_format, formattedSurface->w, formattedSurface->h,0,
			texture_format,GL_UNSIGNED_BYTE,formattedSurface->pixels);
	}
	SDL_FreeSurface(formattedSurface);
	
	return texture;

}

GLuint loadtexture(char* filename,bool mipmap, bool flip = true){
	
	GLuint texture = 0;
	SDL_Surface *surface = NULL;
	GLenum texture_format;
	GLint  nOfColors;
	
	SDL_Surface* temp = IMG_Load(filename);
	
	if(temp){ 
		SDL_SetSurfaceBlendMode(temp, SDL_BLENDMODE_NONE);
		surface = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGBA32, 0);
		SDL_FreeSurface(temp);
	}
	
	if(surface){
		// Vertical flip: OpenGL expects bottom-to-top pixel data
		if (flip) {
			int pitch = surface->pitch;
			unsigned char* temp_row = new unsigned char[pitch];
			unsigned char* pixels = (unsigned char*)surface->pixels;
			for (int i = 0; i < surface->h / 2; ++i) {
				unsigned char* row1 = pixels + i * pitch;
				unsigned char* row2 = pixels + (surface->h - 1 - i) * pitch;
				memcpy(temp_row, row1, pitch);
				memcpy(row1, row2, pitch);
				memcpy(row2, temp_row, pitch);
			}
			delete [] temp_row;
		}

		nOfColors = surface->format->BytesPerPixel;

		if (nOfColors == 4) {
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else {
			texture_format = GL_RGB;
		}
		
		GLint internal_format = (nOfColors == 4) ? GL_RGBA8 : GL_RGB8;
		
		glGenTextures( 1, &texture );
		glBindTexture( GL_TEXTURE_2D, texture );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		
		if(mipmap){
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, internal_format, surface->w, surface->h,
				texture_format, GL_UNSIGNED_BYTE, surface->pixels);
		}else{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D,0, internal_format, surface->w, surface->h, 0,
				texture_format, GL_UNSIGNED_BYTE, surface->pixels);
		}
	} else {
		printf("Error: surface is NULL, failed to load or convert %s\n", filename);
	}
	
	if(surface)SDL_FreeSurface( surface);

	return texture;

}
