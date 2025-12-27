//http://www.codeproject.com/KB/cpp/endianness.aspx
#include <cstdint>

uint32_t EndianFlipUnsignedLong(uint32_t nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

int32_t EndianFlipLong(int32_t nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

unsigned short EndianFlipUnsignedShort(unsigned short nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

short EndianFlipShort(short nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

GLuint loadbmp(char* filename,bool mipmap){

	unsigned short Type;          // signature - 'BM'
	uint32_t  Size;          // file size in bytes
	unsigned short Reserved1;     // 0
	unsigned short Reserved2;     // 0
	uint32_t  OffBits;       // offset to bitmap
	uint32_t  StructSize;    // size of this struct (40)
	uint32_t  Width;         // bmap width in pixels
	uint32_t  Height;        // bmap height in pixels
	unsigned short Planes;        // num planes - always 1
	unsigned short BitCount;      // bits per pixel
	uint32_t  Compression;   // compression flag
	uint32_t  SizeImage;     // image size in bytes
	int32_t           XPelsPerMeter; // horz resolution
	int32_t           YPelsPerMeter; // vert resolution
	uint32_t  ClrUsed;       // 0 -> color table size
	uint32_t  ClrImportant;  // important color count

	unsigned char	*pPixels = NULL;

	FILE	*fp = NULL;

	fp = fopen(filename,"r");

	if(fp==NULL)    //ahmad
		return NULL;     //ahmad

	fread(&Type,sizeof(unsigned short),1,fp);
	fread(&Size,sizeof(uint32_t),1,fp);
	fread(&Reserved1,sizeof(unsigned short),1,fp);
	fread(&Reserved2,sizeof(unsigned short),1,fp);
	fread(&OffBits,sizeof(uint32_t),1,fp);
	fread(&StructSize,sizeof(uint32_t),1,fp);
	fread(&Width,sizeof(uint32_t),1,fp);
	fread(&Height,sizeof(uint32_t),1,fp);
	fread(&Planes,sizeof(unsigned short),1,fp);
	fread(&BitCount,sizeof(unsigned short),1,fp);
	fread(&Compression,sizeof(uint32_t),1,fp);
	fread(&SizeImage,sizeof(uint32_t),1,fp);
	fread(&XPelsPerMeter,sizeof(int32_t),1,fp);
	fread(&YPelsPerMeter,sizeof(int32_t),1,fp);
	fread(&ClrUsed,sizeof(uint32_t),1,fp);
	fread(&ClrImportant,sizeof(uint32_t),1,fp);

	pPixels = new unsigned char[Width * Height * BitCount];
	fread(pPixels, BitCount, Width * Height, fp);
	fclose(fp);

	GLuint texName;
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		if(BitCount==16)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB16,Width,Height,
			GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
		if(BitCount==24)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,Width,Height,
			GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
		if(BitCount==32)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,Width,Height,
			GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		if(BitCount==16)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);	
		if(BitCount==24)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
		if(BitCount==32)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,
			0,GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}

	delete pPixels;

	return texName;

}
