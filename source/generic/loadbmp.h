GLuint loadbmp(char* filename,bool mipmap){
	printf("Loading BMP: %s\n", filename);
	return loadtexture(filename, mipmap);
}
