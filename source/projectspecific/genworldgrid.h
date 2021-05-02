const int streetlevel=3;
const int minbuildingheight=3;
const int maxbuildingheight=9;

const int worldgridsizex = 50;
const int worldgridsizey = 15;
const int worldgridsizez = 50;

//street width setting
const int streetwidth  = 2;

#define GRASS_TILE				10
#define SIDEWALK_CORNER_TILE	9
#define SIDEWALK_TILE			8
const int clue_win_array[9][9]={
			{000,00,0,00,00,0,00,00,00},
			{'M',18,4,21,18,4,28,27,25},				//1
			{'D',21,5,31,28,5,31,27,31},				//2
			{'J',28,5,18,21,5,18,28,33},				//3
			{'S',31,4,28,31,4,21,26,28},				//4
			{'V',28,4,18,21,4,18,26,27},				//5
			{'G',31,5,28,31,5,21,29,27},				//6
			{'P',21,4,31,28,4,31,25,25},				//7
			{'A',18,5,21,18,5,28,29,26}};

char worldgrid[worldgridsizex][worldgridsizey][worldgridsizez][2];

//clean up
void genworldgrid_cleanup(){

	//clean the world grid
	for(int x=0; x<worldgridsizex; x++)
		for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				worldgrid[x][y][z][0]=0;
				worldgrid[x][y][z][1]=0;
			}

}

//island streets and sidewalks
void genworldgrid_street(){
	
	//mid point position
	int worldmidposx = worldgridsizex / 2;
	int worldmidposz = worldgridsizez / 2;

	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=GRASS_TILE;

	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=GRASS_TILE;
		
	
	
}

//Foundation of the building
void genworldgrid_sidewalk(){

	

	//sidewalks
	for(int z=house_low_z+1; z<=(house_high_z-1); z++){
		worldgrid[house_low_x][streetlevel][z][0]=8;
		worldgrid[house_low_x][streetlevel][z][1]=0;
		worldgrid[house_high_x][streetlevel][z][0]=8;
		worldgrid[house_high_x][streetlevel][z][1]=2;
	}
	for(int x=house_low_x+1; x<=(house_high_x-1); x++){
		worldgrid[x][streetlevel][house_low_z][0]=8;
		worldgrid[x][streetlevel][house_low_z][1]=3;
		worldgrid[x][streetlevel][house_high_z][0]=8;
		worldgrid[x][streetlevel][house_high_z][1]=1;
	}

	//sidewalk corners
	worldgrid[house_high_z][streetlevel][house_low_z][0]=9;
	worldgrid[house_high_z][streetlevel][house_low_z][1]=3;
	worldgrid[house_low_z][streetlevel][house_low_z][0]=9;
	worldgrid[house_low_z][streetlevel][house_low_z][1]=0;
	worldgrid[house_low_z][streetlevel][house_high_z][0]=9;
	worldgrid[house_low_z][streetlevel][house_high_z][1]=1;
	worldgrid[house_high_z][streetlevel][house_high_z][0]=9;
	worldgrid[house_high_z][streetlevel][house_high_z][1]=2;
}

//buildings
void genworldgrid_building(){

	
	//wall
	for (int y=0;y<1;y++)
	{
		for(int z=house_low_z+2; z<=(house_high_z-2); z++){
			worldgrid[house_low_x+1][streetlevel+y][z][0]=72;
			worldgrid[house_low_x+1][streetlevel+y][z][1]=0;
			worldgrid[house_high_x-1][streetlevel+y][z][0]=72;
			worldgrid[house_high_x-1][streetlevel+y][z][1]=2;
		}
		for(int x=house_low_x+2; x<=(house_high_x-2); x++){
			worldgrid[x][streetlevel+y][house_low_z+1][0]=72;
			worldgrid[x][streetlevel+y][house_low_z+1][1]=3;
			worldgrid[x][streetlevel+y][house_high_z-1][0]=72;
			worldgrid[x][streetlevel+y][house_high_z-1][1]=1;
		}

		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][0]=71;
		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][1]=2;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][0]=71;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][1]=3;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][0]=71;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][1]=0;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][0]=71;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][1]=1;
	}

	//building windows
	//wall 1
	worldgrid[house_low_x+4][streetlevel][house_low_z+1][0]=window_tile;
	worldgrid[house_low_x+4][streetlevel][house_low_z+1][1]=3;
	worldgrid[house_low_x+7][streetlevel][house_low_z+1][0]=window_tile;
	worldgrid[house_low_x+7][streetlevel][house_low_z+1][1]=3;
	worldgrid[house_low_x+11][streetlevel][house_low_z+1][0]=window_tile;
	worldgrid[house_low_x+11][streetlevel][house_low_z+1][1]=3;
	//wall 2
	worldgrid[house_low_x+1][streetlevel][house_high_z-4][0]=window_tile;
	worldgrid[house_low_x+1][streetlevel][house_high_z-4][1]=0;
	worldgrid[house_low_x+1][streetlevel][house_high_z-7][0]=window_tile;
	worldgrid[house_low_x+1][streetlevel][house_high_z-7][1]=0;
	worldgrid[house_low_x+1][streetlevel][house_high_z-11][0]=window_tile;
	worldgrid[house_low_x+1][streetlevel][house_high_z-11][1]=0;
	//wall 3
	worldgrid[house_low_x+4][streetlevel][house_high_z-1][0]=window_tile;
	worldgrid[house_low_x+4][streetlevel][house_high_z-1][1]=1;
	worldgrid[house_low_x+8][streetlevel][house_high_z-1][0]=window_tile;
	worldgrid[house_low_x+8][streetlevel][house_high_z-1][1]=1;
	worldgrid[house_low_x+11][streetlevel][house_high_z-1][0]=window_tile;
	worldgrid[house_low_x+11][streetlevel][house_high_z-1][1]=1;
	//wall 4
	worldgrid[house_high_x-1][streetlevel][house_high_z-4][0]=window_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-4][1]=2;
	worldgrid[house_high_x-1][streetlevel][house_high_z-8][0]=window_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-8][1]=2;
	worldgrid[house_high_x-1][streetlevel][house_high_z-11][0]=window_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-11][1]=2;


	expectdist=0;    //reset the expected distance value

	

	//building door
	worldgrid[house_low_x+8][streetlevel][house_low_z+1][0]=door_tile;
	worldgrid[house_low_x+7][streetlevel][house_high_z-1][0]=door_tile;
	int entrydoorz=house_high_z-3-(rand()%(house_high_z-house_low_z-6));
	worldgrid[house_low_x+1][streetlevel][house_low_z+7][0]=door_tile;
	worldgrid[house_high_x-1][streetlevel][house_low_z+8][0]=door_tile;

	//calculated the expected distance
	//to the entrance door
	expectdist += sqrt(((float)((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))*((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))) 
					+(((worldgridsizex/2)-(entrydoorz))*((worldgridsizex/2)-(entrydoorz))));
	//to the stairs
	expectdist += sqrt((((23.6)-(house_low_x+1))*((23.6)-(house_low_x+1)))
					+(((23.3)-(entrydoorz))*((23.3)-(entrydoorz))));
	

	//floor base
	for(int y=0;y<=2;y++)
		for(int z=house_low_z+2; z<=(house_high_z-2); z++)
			for(int x=house_low_x+2; x<=(house_high_x-2); x++)
				worldgrid[x][streetlevel+y][z][0]=hardwood_tile;//stairtype

	switch(stairtype){
	case 1:

//stairs at 180 degrees
	
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	break;
	
	case 2:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	//isolators

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	case 3:

	//ramps at 180 degrees
    worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
/*worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;*/
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	
	break;
	
	case 4:
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	
	/*case 5:
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=double_stairs_tile;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=double_stairs_tile;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][1]=0;
		
		break;		
	case 6:
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=double_ramp_tile;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=double_ramp_tile;
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][1]=0;
		break;*/		
	}
	
	/*switch(stairtype){
	case 1:

	//stairs at 180 degrees
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	break;
	case 2:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	//isolators

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	case 3:

	//stairs at 180 degrees
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;

	break;
	
	case 4:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	}*/
	//roof
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+3][house_low_z+((house_high_z-house_low_z)/2)][0]=roof_tile;

	

	if(allocentric)
	{   
		worldgrid[23][3][30][0]=timhortonswall_tile;  ////////////////////////////
		worldgrid[26][4][30][0]=atmmachinewall_tile; 
	//	worldgrid[1+house_low_x+(2)*(house_high_x-house_low_x)/4][streetlevel+1][house_high_z-1][0]=timhortonswall_tile;
		//worldgrid[house_high_x-2][streetlevel+2][house_high_z-1][0]=atmmachinewall_tile;
	}
	//added by saloni
for(int y=streetlevel+1;y<=streetlevel+2;y++){
	   worldgrid[house_low_x+7][y][house_low_z+2][0]=interior_wallcorner_tile_l;///done
		worldgrid[house_low_x+7][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+8][y][house_low_z+2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+8][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+2][y][house_high_z-7][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+2][y][house_high_z-7][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-8][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+2][y][house_high_z-8][1]=1;
		worldgrid[house_low_x+7][y][house_high_z-2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+7][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+8][y][house_high_z-2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+8][y][house_high_z-2][1]=2;
		worldgrid[house_high_x-2][y][house_high_z-8][0]=interior_wallcorner_tile_l;
		worldgrid[house_high_x-2][y][house_high_z-8][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-7][0]=interior_wallcorner_tile_l;
		worldgrid[house_high_x-2][y][house_high_z-7][1]=3;
		//interior_wallcorner_tile is important for saloni it block the middle rums
		//walls
		//1 outside don't want it 
		worldgrid[house_low_x+1][y][house_low_z+1][0]=wallcorner_tile;
		worldgrid[house_low_x+1][y][house_low_z+1][1]=3;
		worldgrid[house_low_x+2][y][house_low_z+1][0]=wall_tile;
		worldgrid[house_low_x+2][y][house_low_z+1][1]=3;
		worldgrid[house_low_x+3][y][house_low_z+1][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+3][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+4][y][house_low_z+1][0]=window_tile;
		worldgrid[house_low_x+4][y][house_low_z+1][1]=3;
		worldgrid[house_low_x+5][y][house_low_z+1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+5][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+6][y][house_low_z+1][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+6][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+7][y][house_low_z+1][0]=double_window_tile;
		worldgrid[house_low_x+7][y][house_low_z+1][1]=1;
		worldgrid[house_low_x+9][y][house_low_z+1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+9][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+10][y][house_low_z+1][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+10][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+11][y][house_low_z+1][0]=window_tile;
		worldgrid[house_low_x+11][y][house_low_z+1][1]=3;
		worldgrid[house_low_x+12][y][house_low_z+1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+12][y][house_low_z+1][1]=2;
		worldgrid[house_low_x+13][y][house_low_z+1][0]=wall_tile;
		worldgrid[house_low_x+13][y][house_low_z+1][1]=3;
		//1 inside
		worldgrid[house_low_x+1][y][house_low_z+2][0]=wall_tile;
		worldgrid[house_low_x+1][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+2][y][house_low_z+2][0]=block_tile;
		worldgrid[house_low_x+2][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+3][y][house_low_z+2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+3][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+4][y][house_low_z+2][0]=door_tile;
		worldgrid[house_low_x+4][y][house_low_z+2][1]=1;
		worldgrid[house_low_x+5][y][house_low_z+2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+5][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+6][y][house_low_z+2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+6][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+9][y][house_low_z+2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+9][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+10][y][house_low_z+2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+10][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+11][y][house_low_z+2][0]=door_tile;
		worldgrid[house_low_x+11][y][house_low_z+2][1]=1;
		worldgrid[house_low_x+12][y][house_low_z+2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+12][y][house_low_z+2][1]=0;
//		interior_wallcorner_tile is important for saloni it changes internal things
		//2 outside
		worldgrid[house_low_x+1][y][house_high_z-1][0]=wallcorner_tile;
		worldgrid[house_low_x+1][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+1][y][house_high_z-2][0]=wall_tile;
		worldgrid[house_low_x+1][y][house_high_z-2][1]=0;
		worldgrid[house_low_x+1][y][house_high_z-3][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+1][y][house_high_z-3][1]=3;
		worldgrid[house_low_x+1][y][house_high_z-4][0]=window_tile;
		worldgrid[house_low_x+1][y][house_high_z-4][1]=0;
		worldgrid[house_low_x+1][y][house_high_z-5][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+1][y][house_high_z-5][1]=3;
		worldgrid[house_low_x+1][y][house_high_z-6][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+1][y][house_high_z-6][1]=3;
	    worldgrid[house_low_x+1][y][house_high_z-7][0]=double_window_tile;
		worldgrid[house_low_x+1][y][house_high_z-7][1]=2;
		worldgrid[house_low_x+1][y][house_high_z-9][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+1][y][house_high_z-9][1]=3;
		worldgrid[house_low_x+1][y][house_high_z-10][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+1][y][house_high_z-10][1]=3;
		worldgrid[house_low_x+1][y][house_high_z-11][0]=window_tile;
		worldgrid[house_low_x+1][y][house_high_z-11][1]=0;
		worldgrid[house_low_x+1][y][house_high_z-12][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+1][y][house_high_z-12][1]=3;
		//2 inside front side
		worldgrid[house_low_x+2][y][house_high_z-3][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+2][y][house_high_z-3][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-4][0]=door_tile;
		worldgrid[house_low_x+2][y][house_high_z-4][1]=2;
		worldgrid[house_low_x+2][y][house_high_z-5][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+2][y][house_high_z-5][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-6][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+2][y][house_high_z-6][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-9][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+2][y][house_high_z-9][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-10][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+2][y][house_high_z-10][1]=1;
		worldgrid[house_low_x+2][y][house_high_z-11][0]=door_tile;
		worldgrid[house_low_x+2][y][house_high_z-11][1]=2;
		worldgrid[house_low_x+2][y][house_high_z-12][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+2][y][house_high_z-12][1]=1;
				
		
	//	3 outside
	    worldgrid[house_low_x+1][y][house_high_z-1][0]=wallcorner_tile;
		worldgrid[house_low_x+1][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+2][y][house_high_z-1][0]=wall_tile;
		worldgrid[house_low_x+2][y][house_high_z-1][1]=1;
		worldgrid[house_low_x+3][y][house_high_z-1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+3][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+4][y][house_high_z-1][0]=window_tile;
		worldgrid[house_low_x+4][y][house_high_z-1][1]=1;
		worldgrid[house_low_x+5][y][house_high_z-1][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+5][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+6][y][house_high_z-1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+6][y][house_high_z-1][1]=0;
	    worldgrid[house_low_x+8][y][house_high_z-1][0]=double_window_tile;
		worldgrid[house_low_x+8][y][house_high_z-1][1]=3;
		worldgrid[house_low_x+9][y][house_high_z-1][0]=inout_wallcorner_tile_l;
		worldgrid[house_low_x+9][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+10][y][house_high_z-1][0]=inout_wallcorner_tile_r;
		worldgrid[house_low_x+10][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+11][y][house_high_z-1][0]=window_tile;
		worldgrid[house_low_x+11][y][house_high_z-1][1]=1;
		worldgrid[house_low_x+12][y][house_high_z-1][0]=inout_wallcorner_tile_l;
	    worldgrid[house_low_x+12][y][house_high_z-1][1]=0;
		worldgrid[house_low_x+13][y][house_high_z-1][0]=wall_tile;
		worldgrid[house_low_x+13][y][house_high_z-1][1]=1;
		//3 inside
		worldgrid[house_low_x+1][y][house_high_z-2][0]=wall_tile;
		worldgrid[house_low_x+1][y][house_high_z-2][1]=0;
		worldgrid[house_low_x+2][y][house_high_z-2][0]=block_tile;
		worldgrid[house_low_x+2][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+3][y][house_high_z-2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+3][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+4][y][house_high_z-2][0]=door_tile;
		worldgrid[house_low_x+4][y][house_high_z-2][1]=3;
		worldgrid[house_low_x+5][y][house_high_z-2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+5][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+6][y][house_high_z-2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+6][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+9][y][house_high_z-2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+9][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+10][y][house_high_z-2][0]=interior_wallcorner_tile_r;
		worldgrid[house_low_x+10][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+11][y][house_high_z-2][0]=door_tile;
		worldgrid[house_low_x+11][y][house_high_z-2][1]=3;
		worldgrid[house_low_x+12][y][house_high_z-2][0]=interior_wallcorner_tile_l;
		worldgrid[house_low_x+12][y][house_high_z-2][1]=2;
		
		//4 outside
		worldgrid[house_high_x-1][y][house_high_z-1][0]=wallcorner_tile;
		worldgrid[house_high_x-1][y][house_high_z-1][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-2][0]=wall_tile;
		worldgrid[house_high_x-1][y][house_high_z-2][1]=2;
		worldgrid[house_high_x-1][y][house_high_z-3][0]=inout_wallcorner_tile_r;
		worldgrid[house_high_x-1][y][house_high_z-3][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-4][0]=window_tile;
		worldgrid[house_high_x-1][y][house_high_z-4][1]=2;
		worldgrid[house_high_x-1][y][house_high_z-5][0]=inout_wallcorner_tile_l;
		worldgrid[house_high_x-1][y][house_high_z-5][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-6][0]=inout_wallcorner_tile_r;
		worldgrid[house_high_x-1][y][house_high_z-6][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-8][0]=double_window_tile;
		worldgrid[house_high_x-1][y][house_high_z-8][1]=0;
		worldgrid[house_high_x-1][y][house_high_z-9][0]=inout_wallcorner_tile_l;
		worldgrid[house_high_x-1][y][house_high_z-9][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-10][0]=inout_wallcorner_tile_r;
		worldgrid[house_high_x-1][y][house_high_z-10][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-11][0]=window_tile;
		worldgrid[house_high_x-1][y][house_high_z-11][1]=2;
		worldgrid[house_high_x-1][y][house_high_z-12][0]=inout_wallcorner_tile_l;
		worldgrid[house_high_x-1][y][house_high_z-12][1]=1;
		worldgrid[house_high_x-1][y][house_high_z-14][0]=wallcorner_tile;
		worldgrid[house_high_x-1][y][house_high_z-14][1]=2;
		worldgrid[house_high_x-1][y][house_high_z-13][0]=wall_tile;
		worldgrid[house_high_x-1][y][house_high_z-13][1]=2;
		//4 inside
		worldgrid[house_high_x-2][y][house_high_z-1][0]=wall_tile;
		worldgrid[house_high_x-2][y][house_high_z-1][1]=1;
		worldgrid[house_high_x-2][y][house_high_z-2][0]=block_tile;
		worldgrid[house_high_x-2][y][house_high_z-2][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-3][0]=interior_wallcorner_tile_r;
		worldgrid[house_high_x-2][y][house_high_z-3][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-4][0]=door_tile;
		worldgrid[house_high_x-2][y][house_high_z-4][1]=0;
		worldgrid[house_high_x-2][y][house_high_z-5][0]=interior_wallcorner_tile_l;
		worldgrid[house_high_x-2][y][house_high_z-5][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-6][0]=interior_wallcorner_tile_r;
		worldgrid[house_high_x-2][y][house_high_z-6][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-9][0]=interior_wallcorner_tile_l;
		worldgrid[house_high_x-2][y][house_high_z-9][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-10][0]=interior_wallcorner_tile_r;
		worldgrid[house_high_x-2][y][house_high_z-10][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-11][0]=door_tile;
		worldgrid[house_high_x-2][y][house_high_z-11][1]=0;
		worldgrid[house_high_x-2][y][house_high_z-12][0]=interior_wallcorner_tile_l;
		worldgrid[house_high_x-2][y][house_high_z-12][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-14][0]=wall_tile;
		worldgrid[house_high_x-2][y][house_high_z-14][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-13][0]=block_tile;
		worldgrid[house_high_x-2][y][house_high_z-13][1]=1;
	}

	if(allocentric){
		//G
		a_win_pos[0]=clue_win_array[4][1];
		a_win_pos[1]=clue_win_array[4][2];
		a_win_pos[2]=clue_win_array[4][3];
		//G

		//D
		b_win_pos[0]=clue_win_array[2][4];
		b_win_pos[1]=clue_win_array[2][5];
		b_win_pos[2]=clue_win_array[2][6];
		//D

		//P
		c_win_pos[0]=clue_win_array[7][1];
		c_win_pos[1]=clue_win_array[7][2];
		c_win_pos[2]=clue_win_array[7][3];
		//P
		
	/*	//5
		a_win_pos[0]=house_low_x+(2)*(house_high_x-house_low_x)/4;
		a_win_pos[1]=streetlevel+1;
		a_win_pos[2]=house_low_z+1;
		//5

		//2
		b_win_pos[0]=house_low_x+((3)*(house_high_x-house_low_x)/4);
		b_win_pos[1]=streetlevel+2;
		b_win_pos[2]=house_high_z-1;
		//2

		//6
		c_win_pos[0]=house_high_x-1;
		c_win_pos[1]=streetlevel+2;
		c_win_pos[2]=house_low_z+(2)*(house_high_z-house_low_z)/4;
		//6
*/
		if(kidmode){
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;
		}
		else
		{
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;
		}
		switch(targetwin+1){
			case 1:
				//climb the stairs
				expectdist = clue_win_array[6][7];                                            
				//for the clue chart resembles letter W
				win_clue=clue_win_array[6][0];
			break;
			case 2:
				//climb the stairs
				expectdist = clue_win_array[2][8];
				//for the clue chart resembles letter F
				win_clue=clue_win_array[2][0]+2;
			break;
			case 3:
				//climb the stairs
				expectdist = clue_win_array[7][7];
				//for the clue chart resembles letter H
				win_clue=clue_win_array[7][0];
			break;
		/*switch(((trial-1)%3)+1){
			case 1:
				//climb the stairs
				expectdist += 6;
				//for the clue chart resembles letter W
				win_clue=87;
			break;
			case 2:
				//climb the stairs
				expectdist += 12;
				//for the clue chart resembles letter F
				win_clue=70;
			break;
			case 3:
				//climb the stairs
				expectdist += 13;
				//for the clue chart resembles letter H
				win_clue=72;
			break;*/
		}	
	}
	else{
		
		switch(trial){
			case 1:

				//climb the stairs
				//1
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[1][1];
					a_win_pos[1]=clue_win_array[1][2];
					a_win_pos[2]=clue_win_array[1][3];
					win_clue=clue_win_array[1][0];
					expectdist = clue_win_array[1][7];
				}
				else{
					a_win_pos[0]=clue_win_array[1][4];
					a_win_pos[1]=clue_win_array[1][5];
					a_win_pos[2]=clue_win_array[1][6];
					win_clue=clue_win_array[1][0]+2;
					expectdist = clue_win_array[1][8];
				}
				//1

				//to the target window
				//4
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[4][1];
					b_win_pos[1]=clue_win_array[4][2];
					b_win_pos[2]=clue_win_array[4][3];
				}
				else{
					b_win_pos[0]=clue_win_array[4][4];
					b_win_pos[1]=clue_win_array[4][5];
					b_win_pos[2]=clue_win_array[4][6];
				}
				//4

				//3
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[3][1];
					c_win_pos[1]=clue_win_array[3][2];
					c_win_pos[2]=clue_win_array[3][3];
				}
				else{
					c_win_pos[0]=clue_win_array[3][4];
					c_win_pos[1]=clue_win_array[3][5];
					c_win_pos[2]=clue_win_array[3][6];
				}
				//3

			break;
			case 2:
				//climb the stairs
				//2
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[2][1];
					a_win_pos[1]=clue_win_array[2][2];
					a_win_pos[2]=clue_win_array[2][3];
					win_clue=clue_win_array[2][0];
					expectdist = clue_win_array[2][7];
				}
				else{
					a_win_pos[0]=clue_win_array[2][4];
					a_win_pos[1]=clue_win_array[2][5];
					a_win_pos[2]=clue_win_array[2][6];
					win_clue=clue_win_array[2][0]+2;
					expectdist = clue_win_array[2][8];
				}
				//2

				//to the target window
				//7
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[7][1];
					b_win_pos[1]=clue_win_array[7][2];
					b_win_pos[2]=clue_win_array[7][3];
				}
				else{
					b_win_pos[0]=clue_win_array[7][4];
					b_win_pos[1]=clue_win_array[7][5];
					b_win_pos[2]=clue_win_array[7][6];
				}
				//7

				//8
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[8][1];
					c_win_pos[1]=clue_win_array[8][2];
					c_win_pos[2]=clue_win_array[8][3];
				}
				else{
					c_win_pos[0]=clue_win_array[8][4];
					c_win_pos[1]=clue_win_array[8][5];
					c_win_pos[2]=clue_win_array[8][6];
				}
				//8
			break;
			case 3:
				//climb the stairs
				//3
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[3][1];
					a_win_pos[1]=clue_win_array[3][2];
					a_win_pos[2]=clue_win_array[3][3];
					win_clue=clue_win_array[3][0];
					expectdist = clue_win_array[3][7];
				}
				else{
					a_win_pos[0]=clue_win_array[3][4];
					a_win_pos[1]=clue_win_array[3][5];
					a_win_pos[2]=clue_win_array[3][6];
					win_clue=clue_win_array[3][0]+2;
					expectdist = clue_win_array[3][8];
				}
				//3

				//to the target window
				//6
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[6][1];
					b_win_pos[1]=clue_win_array[6][2];
					b_win_pos[2]=clue_win_array[6][3];
				}
				else{
					b_win_pos[0]=clue_win_array[6][4];
					b_win_pos[1]=clue_win_array[6][5];
					b_win_pos[2]=clue_win_array[6][6];
				}
				//6
			
				//5
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[5][1];
					c_win_pos[1]=clue_win_array[5][2];
					c_win_pos[2]=clue_win_array[5][3];
				}
				else{
					c_win_pos[0]=clue_win_array[5][4];
					c_win_pos[1]=clue_win_array[5][5];
					c_win_pos[2]=clue_win_array[5][6];
				}
				//5

			break;
			case 4:
				//climb the stairs
				//4
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[4][1];
					a_win_pos[1]=clue_win_array[4][2];
					a_win_pos[2]=clue_win_array[4][3];
					win_clue=clue_win_array[4][0];
					expectdist = clue_win_array[4][7];
				}
				else{
					a_win_pos[0]=clue_win_array[4][4];
					a_win_pos[1]=clue_win_array[4][5];
					a_win_pos[2]=clue_win_array[4][6];
					win_clue=clue_win_array[4][0]+2;
					expectdist = clue_win_array[4][8];
				}
				//4

				//to the target window
				//3
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[3][1];
					b_win_pos[1]=clue_win_array[3][2];
					b_win_pos[2]=clue_win_array[3][3];
				}
				else{
					b_win_pos[0]=clue_win_array[3][4];
					b_win_pos[1]=clue_win_array[3][5];
					b_win_pos[2]=clue_win_array[3][6];
				}
				//3

				//6
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[6][1];
					c_win_pos[1]=clue_win_array[6][2];
					c_win_pos[2]=clue_win_array[6][3];
				}
				else{
					c_win_pos[0]=clue_win_array[6][4];
					c_win_pos[1]=clue_win_array[6][5];
					c_win_pos[2]=clue_win_array[6][6];
				}
				//6

			break;
			case 5:
				//climb the stairs
				//5
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[5][1];
					a_win_pos[1]=clue_win_array[5][2];
					a_win_pos[2]=clue_win_array[5][3];
					win_clue=clue_win_array[5][0];
					expectdist = clue_win_array[5][7];
				}
				else{
					a_win_pos[0]=clue_win_array[5][4];
					a_win_pos[1]=clue_win_array[5][5];
					a_win_pos[2]=clue_win_array[5][6];
					win_clue=clue_win_array[5][0]+2;
					expectdist = clue_win_array[5][8];
				}
				//5

				//to the target window
				//1
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[1][1];
					b_win_pos[1]=clue_win_array[1][2];
					b_win_pos[2]=clue_win_array[1][3];
				}
				else{
					b_win_pos[0]=clue_win_array[1][4];
					b_win_pos[1]=clue_win_array[1][5];
					b_win_pos[2]=clue_win_array[1][6];
				}
				//1

				//4
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[4][1];
					c_win_pos[1]=clue_win_array[4][2];
					c_win_pos[2]=clue_win_array[4][3];
				}
				else{
					c_win_pos[0]=clue_win_array[4][4];
					c_win_pos[1]=clue_win_array[4][5];
					c_win_pos[2]=clue_win_array[4][6];
				}
				//4

			break;
			case 6:
				//climb the stairs
				//6
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[6][1];
					a_win_pos[1]=clue_win_array[6][2];
					a_win_pos[2]=clue_win_array[6][3];
					win_clue=clue_win_array[6][0];
					expectdist = clue_win_array[6][7];
				}
				else{
					a_win_pos[0]=clue_win_array[6][4];
					a_win_pos[1]=clue_win_array[6][5];
					a_win_pos[2]=clue_win_array[6][6];
					win_clue=clue_win_array[6][0]+2;
					expectdist = clue_win_array[6][8];
				}
				//6

				//to the target window
				//8
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[8][1];
					b_win_pos[1]=clue_win_array[8][2];
					b_win_pos[2]=clue_win_array[8][3];
				}
				else{
					b_win_pos[0]=clue_win_array[8][4];
					b_win_pos[1]=clue_win_array[8][5];
					b_win_pos[2]=clue_win_array[8][6];
				}
				//8

				//2
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[2][1];
					c_win_pos[1]=clue_win_array[2][2];
					c_win_pos[2]=clue_win_array[2][3];
				}
				else{
					c_win_pos[0]=clue_win_array[2][4];
					c_win_pos[1]=clue_win_array[2][5];
					c_win_pos[2]=clue_win_array[2][6];
				}
				//2

			break;
			case 7:
				//climb the stairs
				//7
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[7][1];
					a_win_pos[1]=clue_win_array[7][2];
					a_win_pos[2]=clue_win_array[7][3];
					win_clue=clue_win_array[7][0];
					expectdist = clue_win_array[7][7];
				}
				else{
					a_win_pos[0]=clue_win_array[7][4];
					a_win_pos[1]=clue_win_array[7][5];
					a_win_pos[2]=clue_win_array[7][6];
					win_clue=clue_win_array[7][0]+2;
					expectdist = clue_win_array[7][8];
				}
				//7

				//to the target window
				//5
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[5][1];
					b_win_pos[1]=clue_win_array[5][2];
					b_win_pos[2]=clue_win_array[5][3];
				}
				else{
					b_win_pos[0]=clue_win_array[5][4];
					b_win_pos[1]=clue_win_array[5][5];
					b_win_pos[2]=clue_win_array[5][6];
				}
				//5

				//3
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[3][1];
					c_win_pos[1]=clue_win_array[3][2];
					c_win_pos[2]=clue_win_array[3][3];
				}
				else{
					c_win_pos[0]=clue_win_array[3][4];
					c_win_pos[1]=clue_win_array[3][5];
					c_win_pos[2]=clue_win_array[3][6];
				}
				//3

			break;
			case 8:
				//climb the stairs
				//8
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[8][1];
					a_win_pos[1]=clue_win_array[8][2];
					a_win_pos[2]=clue_win_array[8][3];
					win_clue=clue_win_array[8][0];
					expectdist = clue_win_array[8][7];
				}
				else{
					a_win_pos[0]=clue_win_array[8][4];
					a_win_pos[1]=clue_win_array[8][5];
					a_win_pos[2]=clue_win_array[8][6];
					win_clue=clue_win_array[8][0]+2;
					expectdist = clue_win_array[8][8];
				}
				//8

				//to the target window
				//2
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[2][1];
					b_win_pos[1]=clue_win_array[2][2];
					b_win_pos[2]=clue_win_array[2][3];
				}
				else{
					b_win_pos[0]=clue_win_array[2][4];
					b_win_pos[1]=clue_win_array[2][5];
					b_win_pos[2]=clue_win_array[2][6];
				}
				//2

				//6
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[6][1];
					c_win_pos[1]=clue_win_array[6][2];
					c_win_pos[2]=clue_win_array[6][3];
				}
				else{
					c_win_pos[0]=clue_win_array[6][4];
					c_win_pos[1]=clue_win_array[6][5];
					c_win_pos[2]=clue_win_array[6][6];
				}
				//6

			break;
		//objective windows
	/*	switch(2){//trial
			case 1:

				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=76+rand_sel;
				//1
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//1

				//to the target window
				expectdist += 1 + sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//4
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 2:
				//climb the stairs
				expectdist += (2.6*2);

				rand_sel=((int)rand()%3)+1;
				win_clue=67+rand_sel;
				//2
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_high_z-1;
				//2

				//to the target window
				expectdist += 3 + sqrt(((22.3-a_win_pos[0])*(22.3-a_win_pos[0]))+((25.5-a_win_pos[2])*(25.5-a_win_pos[2])));

				//7
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_high_z-1;
				//7

				//8
				c_win_pos[0]=house_low_x+1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8
			break;
			case 3:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=77-rand_sel;
				//3
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+1;
				//3

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//6
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6
			
				//5
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+1;
				//5

			break;
			case 4:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=86-rand_sel;
				//4
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//4

				//to the target window
				expectdist += 2.5 + sqrt(((26.5-a_win_pos[0])*(26.5-a_win_pos[0]))+((25.7-a_win_pos[2])*(25.7-a_win_pos[2])));

				//3
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+1;
				//3

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;
			case 5:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=89-rand_sel;
				//5
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+1;
				//5

				//to the target window
				expectdist += 3.8 + sqrt(((22.1-a_win_pos[0])*(22.1-a_win_pos[0]))+((23.4-a_win_pos[2])*(23.4-a_win_pos[2])));

				//1
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//1

				//4
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

			break;
			case 6:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=74-rand_sel;
				//6
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//6

				//to the target window
				expectdist += 2.5 + sqrt(((26.3-a_win_pos[0])*(26.3-a_win_pos[0]))+((23-a_win_pos[2])*(23-a_win_pos[2])));

				//8
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8

				//2
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_high_z-1;
				//2

			break;
			case 7:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=79+rand_sel;
				//7
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_high_z-1;
				//7

				//to the target window
				expectdist += sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//5
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+1;
				//5

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 8:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=64+rand_sel;
				//8
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//8

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//2
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_high_z-1;
				//2

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;*/
		}

		if(kidmode){
			switch(targetwin)
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile;  
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break; 

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=puppywall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=kittenwall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=cowwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=kittenwall_tile;  
						break;
			}
		}
		else
		{
			switch(targetwin)   //targetwin
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=X_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=circle_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=triangle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=circle_window_tile;  
						break;
			}
		}
	}
}

