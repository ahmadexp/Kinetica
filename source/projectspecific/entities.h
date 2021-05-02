const int entitytypecount			= 3;
const int entitytype_disccartridge	= 0;
const int entitytype_elevator		= 1;
const int entitytype_trashcan		= 2;
const int entitytype_door           = 1;
const bool entitytypesolid[] = {0,1,1,};
GLuint entitytexture[entitytypecount];
class entity{
	public:
		int type;
		float xpos,ypos,zpos;
		float xang,yang,zang;
		float xangmov,yangmov,zangmov;
		float xposmov,yposmov,zposmov;
		entity();
		~entity();
};
entity::entity(){
	type=0;
	xpos=0,ypos=0,zpos=0;
	xang=0 ,yang=0,zang=0;
	xposmov=0,yposmov=0,zposmov=0;
	xangmov=0,yangmov=0,zangmov=0;
}
entity::~entity(){
}
const int maxdoors=20;
entity door[maxdoors];
int entity_init(){
	for(int i=0;i<maxdoors;i++){
		door[i].type=0;
		door[i].xang=0;
		door[i].yang=0;
		door[i].zang=0;
    }
	return 0;
}
const int maxentities = 2;
entity *entitylist[worldgridsizex][worldgridsizey][worldgridsizez][maxentities];
char entitycount[worldgridsizex][worldgridsizey][worldgridsizez];

void removeentityfromlist(int x,int y,int z,int a){
	if(a<entitycount[x][y][z]-1)
		for(int b=a;b<entitycount[x][y][z];b++)
			entitylist[x][y][z][b]=entitylist[x][y][z][b+1];
	entitycount[x][y][z]-=1;
}
InterleavedVertex* entityinterleavedvertex[entitytypecount];
//const int entitytypecount			= 3;
float *entityvertexarray[entitytypecount];
float *entitytexturearray[entitytypecount];
float *entitynormalarray[entitytypecount];
int entityvertexcount[entitytypecount];
collisionmesh *entitycollisionmesh[entitytypecount];

void loadentities(){

	//generic reusable char array for filenames
	char filename[256];

	//setup each of the entities
	for(int a=1; a<entitytypecount; a++){
		//get the file name
		sprintf_s(filename,"%s%i%s","Media/entities/",a,".obj");
		//load the file
		loadobj((char*)filename,entityvertexarray[a],entitytexturearray[a],entitynormalarray[a],entityvertexcount[a],1.0);
		//rig the texture coordinates
		/*for(int b=0; b<entityvertexcount[a]/3; b++){
			entitytexturearray[a][b*3*2+0]=0;
			entitytexturearray[a][b*3*2+1]=1;
			entitytexturearray[a][b*3*2+2]=1;
			entitytexturearray[a][b*3*2+3]=1;
			entitytexturearray[a][b*3*2+4]=0;
			entitytexturearray[a][b*3*2+5]=0;
		}*/
		//rig the normals
		for(int b=0; b<entityvertexcount[a]/3; b++){
			CVector3 g_vTriangle[3];
			g_vTriangle[0]=CVector3(entityvertexarray[a][b*9+0],entityvertexarray[a][b*9+1],entityvertexarray[a][b*9+2]);
			g_vTriangle[1]=CVector3(entityvertexarray[a][b*9+3],entityvertexarray[a][b*9+4],entityvertexarray[a][b*9+5]);
			g_vTriangle[2]=CVector3(entityvertexarray[a][b*9+6],entityvertexarray[a][b*9+7],entityvertexarray[a][b*9+8]);
			CVector3 vNormal = Normal(g_vTriangle);
			entitynormalarray[a][b*9+0]=-vNormal.x;//vert1
			entitynormalarray[a][b*9+1]=-vNormal.y;
			entitynormalarray[a][b*9+2]=-vNormal.z;
			entitynormalarray[a][b*9+3]=-vNormal.x;//vert2
			entitynormalarray[a][b*9+4]=-vNormal.y;
			entitynormalarray[a][b*9+5]=-vNormal.z;
			entitynormalarray[a][b*9+6]=-vNormal.x;//vert3
			entitynormalarray[a][b*9+7]=-vNormal.y;
			entitynormalarray[a][b*9+8]=-vNormal.z;
		}
		entityinterleavedvertex[a] = new InterleavedVertex[entityvertexcount[a]];
		for(int b=0; b<entityvertexcount[a]; b++){
			entityinterleavedvertex[a][b].px=entityvertexarray[a][b*3+0];
			entityinterleavedvertex[a][b].py=entityvertexarray[a][b*3+1];
			entityinterleavedvertex[a][b].pz=entityvertexarray[a][b*3+2];
			entityinterleavedvertex[a][b].nx=entitynormalarray[a][b*3+0];
			entityinterleavedvertex[a][b].ny=entitynormalarray[a][b*3+1];
			entityinterleavedvertex[a][b].nz=entitynormalarray[a][b*3+2];
			entityinterleavedvertex[a][b].tx=entitytexturearray[a][b*2+0];
			entityinterleavedvertex[a][b].ty=entitytexturearray[a][b*2+1];
		}
		//create the collision meshes
	
		entitycollisionmesh[a] = new collisionmesh(entityvertexcount[a],entityvertexarray[a]);
        sprintf_s(filename,"%s%i%s","Media/entities/",a,".bmp");
		entitytexture[a]=loadbmp((char*)filename,mipmapping);
	}

}
