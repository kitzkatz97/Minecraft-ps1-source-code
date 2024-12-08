// Some of The code in this project comes from a combination of things from
// Wituz's Playstation Development series on youtube
// and Lameguy64's TMD model viewer example.
//
// Edits by Rubixcube6 aka MBDesigns
// Website: https://www.masonbarrydesigns.com/

//Include all the features you want for your project here
//Each of these files contains a set of functions you can
//use in your projects.
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DDDR 0.0174533


#include "Constants.c"
#include "Controller.c"
#include "ReadCD.c"
#include "Audio.c"
#include "2D.c"
#include "3D.c"
#include <libmath.h>

//Declare any function you make here
void Initialize();
void Start();
void Update();
void Render();
void Controls();


int voxeldata[4][24] = {
 {
 1,0,0,0,1,
 1,0,0,0,0,
 1,0,0,0,0,
 1,0,0,0,0,
 1,1,1,1,1
 },{
 1,0,0,0,1,
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 1,0,0,0,1
 },{
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 1,0,0,0,0
 },{
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 1,0,0,0,0
 },{
 2,0,0,0,2,
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 1,0,0,0,2
 }

};


int worldchunk[99][999];
int perlin[999];


int chunk[9][99] = {
 {//y1

 2,2,2,2,2,0,0,0,0,0,
 2,2,2,2,2,2,0,0,0,0,
 2,2,2,2,2,2,0,0,0,0,
 2,2,2,2,2,2,2,0,0,0,
 2,2,2,2,2,2,2,2,2,0,
 2,2,2,2,2,2,2,2,2,2,
 2,2,2,2,2,2,2,2,2,2,
 2,2,0,2,2,2,2,2,2,2,
 2,2,2,2,2,8,8,2,2,2,
 2,2,2,2,8,8,8,8,2,2,
 
 },{//y2   14

 1,0,0,0,0,2,2,2,2,2,
 0,0,0,0,0,0,2,2,2,2,
 0,0,0,0,0,0,2,2,2,2,
 0,0,0,0,0,0,0,2,2,2,
 0,0,0,0,0,0,0,0,0,2,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,13,0,0,
 0,0,5,0,0,0,0,0,0,0,
 0,0,0,0,0,0,10,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y3

 0,0,0,0,0,0,0,0,0,1,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,5,0,0,0,0,0,0,0,
 0,0,0,0,0,0,14,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y4

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,5,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 
 },{//y5

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,5,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 6,6,6,6,6,0,0,0,0,0,
 
 },{//y6

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,6,6,0,0,0,0,0,0,
 0,6,5,6,0,0,0,0,0,0,
 0,6,6,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y7

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,6,0,0,0,0,0,0,0,
 0,6,6,6,0,0,0,0,0,0,
 0,0,6,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y8

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y9

 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 },{//y10

 0,0,0,0,0,0,0,0,0,10,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 
 }

};

int mapX = 10;
int mapY = 10;
int mapS = 1;

//////////////////////////////////////
////    Game variables go here    ////
//////////////////////////////////////

//How fast the car drives
int movementSpeed = 7;
int momentum = 0;
int fallspeed = 0;
int fallvelocity =0;
int playerXpos;
int playerYpos;
int playerZpos;

//how fast the car turns
int rotationSpeed = 30;
//int vfi;
//int vfj;
int vfy;
int vfx;
int vfz;
int vfblocktype;
int vfi=0;
int vfj=0;
int vfxo;
int vfzo;


int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
float px,py,pdx,pdy,pa;
float aTan;
float nTan;
float disH,hx,hy;
float disV,vx,vy;
float lineH;
float lineO;
float ca;

//Store all your CD Files Here
//the number is how many files
//you eventually want to load.
u_long* cdData[15];
Sprite* sprites[1];
Line line;
Box box;
// Every TMD model you load needs a struct
//as showd below


struct {
	VECTOR position;
	SVECTOR rotation;
} voxel;
struct {
	VECTOR position;
	SVECTOR rotation;
} Camrot;

typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
} TESTSPRITE;
//The main function is the first
//thing that runs in your game
int main() {

    //all the functions here are described below

	Initialize();
	Start();

	//This is the main loop of your
	//game that will run every frame
	while(1) {
		Update();
		
		Render();
	}

	return 0;
}

//This function runs once right when the game launches
void Initialize() {
 //SetFogFar( 63000, 32 );
 //SetFogNear( , 5 );
    //get the CD system started so you can read files
	ReadCDInit();

	//do all the necessary steps for getting
	//the screen ready to display things
	initializeScreen();

	//get the controller system ready for
	//reading input from the controller
	initializePad();

    //Start reading the CD
	cd_open();

	//read a specific file by name and
	//store it in the cdData variable.
	//(make sure to edit mkpsxiso/cuesheet.xml and
    //add it there or it won't be included on the CD)
    //The number is the slot you want to store the file into.
	
	
	
	cd_read_file("ATLAS.TIM", &cdData[0]);
    cd_read_file("COBBLE.TMD", &cdData[1]);
	cd_read_file("GRASS.TMD", &cdData[2]);
	cd_read_file("DIRT.TMD", &cdData[3]);
	cd_read_file("STONE.TMD", &cdData[4]);
	cd_read_file("LOG.TMD", &cdData[5]);
	cd_read_file("LEAVES.TMD", &cdData[6]);
	cd_read_file("GRAVEL.TMD", &cdData[7]);
	cd_read_file("SAND.TMD", &cdData[8]);
	cd_read_file("MOSCOB.TMD", &cdData[9]);
	cd_read_file("SPLANKS.TMD", &cdData[10]);
	cd_read_file("PLANKS.TMD", &cdData[11]);
	cd_read_file("BEDROCK.TMD", &cdData[12]);
	cd_read_file("SCREEN.TIM", &cdData[13]);
	cd_read_file("CHAIR.TMD", &cdData[14]);
	cd_read_file("DEBUGTV.TMD", &cdData[15]);
	//Stop reading the CD
	cd_close();

	//load the TIM texture into VRAM
	//The number is the slot you want to load from.
	//when we used the cd_read_file function, we
	//stored the CAR.TIM texture in slot 1
    //loadTexture((u_char *)cdData[1]);
    loadTexture((u_char *)cdData[0]);
	
	//sprite_create((u_char *)&cdData[0], 32, 32, &sprites[0],2);//texture atlas
	
	
	
}

//This function runs once right after he Initialize function
//and before the Update function. Do game related stuff
//here before the game begins.
void Start() {

	// Load TMD models

	//ObjectCount is an int defined in 3D.c
	//Every time we load a model, we increment this number.
	//Sometimes a TMD model will have more than one model
	//in the file so the LoadTMD function will return the
	//number of objects it found in whatever TMD file you loaded.

	//The LoadTMD function loads a TMD model, and stores
	//it in the Object variable defined in 3D.c

	//LoadTMD(
    //    the TMD Model to load,
    //    The Object variable to store the TMD model in,
    //    Lighting on=1 off=0
    //);

	
	ObjectCount += LoadTMD(cdData[1], &Object[0], 1);//COBBLE
	ObjectCount += LoadTMD(cdData[2], &Object[1], 1);//GRASS
	ObjectCount += LoadTMD(cdData[3], &Object[2], 1);//DIRT
	ObjectCount += LoadTMD(cdData[4], &Object[3], 1);//STONE
	ObjectCount += LoadTMD(cdData[5], &Object[4], 1);//LOG
    ObjectCount += LoadTMD(cdData[6], &Object[5], 1);//LEAVES
	ObjectCount += LoadTMD(cdData[7], &Object[6], 1);//GRAVEL
	ObjectCount += LoadTMD(cdData[8], &Object[7], 1);//SAND
	ObjectCount += LoadTMD(cdData[9], &Object[8], 1);//MOSCOB
	ObjectCount += LoadTMD(cdData[10], &Object[9], 1);//SPLANKS
	ObjectCount += LoadTMD(cdData[11], &Object[10], 1);//PLANKS
	ObjectCount += LoadTMD(cdData[12], &Object[11], 1);//BEDROCK
	ObjectCount += LoadTMD(cdData[14], &Object[12], 1);//CHAIR
	ObjectCount += LoadTMD(cdData[15], &Object[13], 1);//TV
	
	
	
	//Set all the initial starting positions and
	//rotations here for every loaded object

	//the V in vx, vy, and vz basically stands for Vector

	//Camera
	Camera.position.vx = 2000;
	Camera.position.vy = 2000;
	Camera.position.vz = 2000;

	Camera.rotation.vx = 0;
	//Camera.rotation.vy = 0;
	
	voxel.position.vx = -5000;
	voxel.position.vy = 2500;
	voxel.position.vz = 5000;
	
	Camera.rotation.vy = pa*650.3185 + 1025;

	/////////////////////////////////////////////
	////    Setup the scene lighting here    ////
	/////////////////////////////////////////////

	//The background color of the scene
	//in RGB (values between 0-255)
	SetBGColor(193, 217, 254);
    //SetBGColor(0, 0, 0);
	//Set the color of ambient light in RGB
	SetAmbientLight(67, 67, 67);

	//The sunlight color in RGB
	SetSunColor(255, 255, 255);

	//Sunlight direction
	SetSunDirection(0, -1, 1);

}

//This is where the action happens. This function runs every frame.
void Update () {
    //this gets the status of all the controller buttons
    //like if they are pressed or not.
	padUpdate();

	//do stuff when buttons are pressed (more info below)
	Controls();

}
int chunkcoordsx,chunkcoordsy,chunkcoordsz;
int chunkcoordsturnbecauseaparentlytheirthreeandchantfuckungshareram = 0;
//This function runs right after the Update
//function and displays everything on screen.
void Render () {

	// Prepare for rendering
	clear_display();
    
	
	
	// Render debug text. this is good for seeing what
	//some variables are doing while the game is running
	//or just to display some text to the player.
	//FntPrint("l/r rot:%d\n",Camera.rotation.vy);
	//FntPrint("u/d rot:%d\n",Camera.rotation.vx);
	FntPrint("xpos:%d\n",chunkcoordsx);
	FntPrint("ypos:%d\n",chunkcoordsy);
	FntPrint("zpos:%d\n",chunkcoordsz);
	FntPrint("block under you:%d\n",chunk[chunkcoordsy ][chunkcoordsx*10+chunkcoordsz]);
	//FntPrint("vfx:%d\n",vfx);
	//FntPrint("vfy:%d\n",vfy);
	//FntPrint("vfz:%d\n",vfz);
	//FntPrint("pa:%d\n",pa);
	FntPrint("rx:%d\n",rx);
	FntPrint("ry:%d\n",ry);
	//voxelfunc();
	//FntPrint("Car Position: (%d, %d, %d)\n", car.position.vx, car.position.vy, car.position.vz);
	//FntPrint("Car Rotation: (%d, %d, %d)\n", car.rotation.vx, car.rotation.vy, car.rotation.vz);

	// Calculate the camera and viewpoint
	CalculateCamera();

	// Sort and render objects
	// drawRays2D();
	//Showtime!
	
	//draw_sprite(sprites[0]); 
	sprite_create((u_char *)&cdData[0], 32, 32, &sprites[0],2);
	
	//voxel.position.vx = 1000*(chunkcoordsx);
    // voxel.position.vy = 1000*(chunkcoordsy);
	// voxel.position.vz = 1000*(chunkcoordsz);
	RenderObject(voxel.position, voxel.rotation, &Object[13]);
	
	voxelfunc();
	draw_sprite(sprites[0]);
	Display();

}

//Do stuff when buttons are pressed
void Controls () {

    //used later to store a vector for local forward movement
    VECTOR newMoveVec;
    momentum =0;
	if (padCheck(Pad1Right)) {
		//Turn car Left
        //pa-=0.05; if(pa<   0){ pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;
		//Camera.rotation.vy = pa*650 + 1025;
		
		

		Camera.rotation.vy = Camera.rotation.vy- 30;
		pa=Camera.rotation.vy *0.08780;
		if(pa<   0){ pa+=2*PI;}// pdx=cos(pa)*5; pdy=sin(pa)*5;
	}

	if (padCheck(Pad1Left)) {
		//Turn car Right
        pa=Camera.rotation.vy *0.08780; if(pa>2*PI){ pa-=2*PI;}// pdx=cos(pa)*5; pdy=sin(pa)*5;
		//Camera.rotation.vy = pa*650 + 1025;
        Camera.rotation.vy  = Camera.rotation.vy+ 30;
	}
	
	if (padCheck(Pad1Up)) {
		Camera.rotation.vx = Camera.rotation.vx - 30;
	}
	if (padCheck(Pad1Down)) {
		Camera.rotation.vx = Camera.rotation.vx + 30;
	}
	
	Camrot.rotation.vy = Camera.rotation.vy;
	
	

	if (padCheck(Pad1Triangle)) {
		  momentum = 15;	
	}

	if (padCheck(Pad1Cross)) {
	momentum = -15;
	}
	
	if (padCheck(Pad1Circle)) {
	chunkcoordsturnbecauseaparentlytheirthreeandchantfuckungshareram++;
	}

	if (padCheck(Pad1Select)) {
		//If you drive too far off screen and get lost, you may
		//want to reset your car where you can see it again.

  vfx=0;
  vfy=0;
	}
      
     
     //camera limiting code
     if (Camera.rotation.vx  > 4099)
	 {
	  Camera.rotation.vx = 0;
	 }
	 if (Camera.rotation.vx < 0)
	 {
	  Camera.rotation.vx = 4099;
	 }
	 
	 if (Camera.rotation.vy  > 4099)
	 {
	  Camera.rotation.vy = 0;
	 }
	 if (Camera.rotation.vy < 0)
	 {
	  Camera.rotation.vy = 4099;
	 }
    
     
     if (Camera.rotation.vz  > 4099)
	 {
	  Camera.rotation.vz = 0;
	 }
	 if (Camera.rotation.vz < 0)
	 {
	  Camera.rotation.vz = 4099;
	 }
     

  
      movementSpeed = (momentum + movementSpeed)/2;
    newMoveVec = Translate(Camrot.rotation, 0, 0, movementSpeed * ONE/500);
		  Camera.position.vx += newMoveVec.vx;
		  //Camera.position.vy += newMoveVec.vy;
	      Camera.position.vz -= newMoveVec.vz;
		  
		  
		  /*
		  switch(chunkcoordsturnbecauseaparentlytheirthreeandchantfuckungshareram)
		  {
		   case 0:
		   chunkcoordsx = (Camera.position.vx/1000);
		   break;
		   case 1:
		   chunkcoordsy = (Camera.position.vy/1000);
		   break;
		   case 2:
		   chunkcoordsz = (Camera.position.vz/1000);
		   break;
		   case 3:
		   chunkcoordsturnbecauseaparentlytheirthreeandchantfuckungshareram = 0;
		   break;
		  
          }
		  */
}


int sunnyx, sunnyy, sunnyz;
void voxelfunc () 
{
 vfx=0;
	vfz=0;
    vfy=0;
	
	
	
	
	
  
  vfblocktype=0;
  for(vfy=0;vfy<10;vfy++)
  {
   for(vfx=0;vfx<10;vfx++)
   {
    for(vfz=0;vfz<10;vfz++)
    {
	vfblocktype=chunk[vfy][vfx*10+vfz];
	/*if(vfblocktype !=0) {
	FntPrint("at x:%d",vfx);
	FntPrint(",y:%d",vfy);
	FntPrint(",z:%d",vfz);
	FntPrint(" block:%d\n",vfblocktype);
	}*/
	
	
	
	 voxel.position.vx = 1000*(vfx);
     voxel.position.vy = 1000*(vfy);
	 voxel.position.vz = 1000*(vfz);
	  
	 
	// sunnyx = (Camera.position.vx - voxel.position.vx);
	 //sunnyy = (Camera.position.vy - voxel.position.vy);
	// sunnyz = (Camera.position.vz - voxel.position.vz);
	 
	// sunnyx = (voxel.position.vx - Camera.position.vx  );
	// sunnyy = (voxel.position.vy - Camera.position.vy  );
	 //sunnyz = (voxel.position.vz - Camera.position.vz );
	 
	 //SetSunDirection(sunnyx, sunnyy, sunnyz);
	 
	 
     switch (vfblocktype )
     {
	 case 1://COBBLR
      RenderObject(voxel.position, voxel.rotation, &Object[0]);
	  break;
	 case 2://GRASS
      RenderObject(voxel.position, voxel.rotation, &Object[1]);
	  break;
	  case 3://DIRT
      RenderObject(voxel.position, voxel.rotation, &Object[2]);
	  break;
	  case 4://STONE
      RenderObject(voxel.position, voxel.rotation, &Object[3]);
	  break;
	  case 5://LOG
      RenderObject(voxel.position, voxel.rotation, &Object[4]);
	  break;
	  case 6://LEAVES
      RenderObject(voxel.position, voxel.rotation, &Object[5]);
	  break;
	  case 7://GRAVEL
      RenderObject(voxel.position, voxel.rotation, &Object[6]);
	  break;
	  case 8://SAND
      RenderObject(voxel.position, voxel.rotation, &Object[7]);
	  break;
	  case 9://MOSCOB
      RenderObject(voxel.position, voxel.rotation, &Object[8]);
	  break;
	  case 10://SWAMPPLANKS
      RenderObject(voxel.position, voxel.rotation, &Object[9]);
	  break;
	  case 11://PLANKS
      RenderObject(voxel.position, voxel.rotation, &Object[10]);
	  break;
	  case 12://BEDROCK
      RenderObject(voxel.position, voxel.rotation, &Object[11]);
	  break;
	  case 13://CHAIR
      RenderObject(voxel.position, voxel.rotation, &Object[12]);
	  break;
	  case 14://TV
      RenderObject(voxel.position, voxel.rotation, &Object[13]);
	  break;

	  
	}
   }
  }
 }
}


float Tdis(float ax, float ay, float bx,float by, float ang)
{
  return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );
}

void drawRays2D()
{
  
  //ra=pa-DDDR*30; if(ra<0){ ra+=2*PI;} if(ra>2*PI){ ra-=2*PI;}
  ra=pa;
  for(r=0;r<1;r++)
  {
   //---check horozontal lines---
   dof=0;
   disH=1000000,hx=px,hy=py;
   aTan=-1/tan(ra);
   if(ra>PI){ ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;}//looking up
 else  if(ra<PI){ ry=(((int)py>>6)<<6)+64;     rx=(py-ry)*aTan+px; yo= 64; xo=-yo*aTan;}//looking down
  else if(ra==0 || ra==PI){ rx=px; ry=py; dof=8;}//looking straight left/right
   while(dof<8)
   {
    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
	if(mp>0 && mp<mapX*mapY && chunk[7][mp]==1){ hx=rx; hy=ry; disH=Tdis(px,py,hx,hy,ra); dof=8; }//hit wall
	else{ rx+=xo; ry+=yo; dof+=1;}//nextline
	
   }
  
	 
   //---check vertical lines---
   dof=0;
   disV=1000000,vx=px,vy=py;
   nTan=-tan(ra);
   if(ra>P2 && ra<P3){ rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan;}//looking left
 else  if(ra<P2 || ra>P3){ rx=(((int)px>>6)<<6)+64;     ry=(px-rx)*nTan+py; xo= 64; yo=-xo*nTan;}//looking right
 else  if(ra==0 || ra==PI){ rx=px; ry=py; dof=8;}//looking straight up/down
   while(dof<8)
   {
    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;//  FntPrint("\nrx: %d", rx); FntPrint("\nry: %d", ry);
	if(mp>0 && mp<mapX*mapY && chunk[7][mp]==1){ vx=rx; vy=ry; disV=Tdis(px,py,vx,vy,ra); dof=8; }//hit wall
	else{ rx+=xo; ry+=yo; dof+=1;}//nextline
	
   }
   if(disV<disH){ rx=vx; ry=vy; disT=disV; }
   if(disH<disV){ rx=hx; ry=hy; disT=disH; }
    
	 //---draw 3D walls---
	 ca=pa-ra; if(ca<0){ ca+=2*PI;} if(ca>2*PI){ ca-=2*PI;} disT=disT*cos(ca);
	 lineH=(mapS*320)/disT; if(lineH>320){lineH=320;}
	 lineO=160-lineH/2;
	
	 
	 
	 ra+=DDDR*1; if(ra<0){ ra+=2*PI;} if(ra>2*PI){ ra-=2*PI;}
	 
	 if(rx>5000){rx=5000;}
	 if(ry>5000){ry=5000;}
	 if(rx<-5000){rx=-5000;}
	 if(ry<-5000){ry=-5000;}
	 //if(rx<5000)
	 // {
	 //  if(ry<5000)
	 //  {
	 voxel.position.vx = 1000*(rx)-5000;
     voxel.position.vy = -1000*(7)+10000;
	 voxel.position.vz = 1000*(ry)-5000;
	 RenderObject(voxel.position, voxel.rotation, &Object[9]);
	  // }
	  //}
  }
}
 
 /*
int perlinx;
int perlinz;
 
 void perlingen()
{

    perlinx=0;
	perlinz=0;

  
  perlinblocktype=0;
 
   for(perlinx=0;perlinx<100;perlinx++)
   {
    for(perlinz=0;perlinz<100;perlinz++)
    {
	perlinblocktype=chunk[perlinx*10+perlinz];
	}
   }
  
}
 
 
 
 
 int worldx;
 int worldy;
 int worldz;
 int worldblocktype;
void terraingen()
{

    worldx=0;
	worldz=0;
    worldy=0;
  
  worldblocktype=0;
  for(worldy=0;worldy<10;worldy++)
  {
   for(worldx=0;worldx<10;worldx++)
   {
    for(worldz=0;worldz<10;worldz++)
    {
	worldblocktype=chunk[worldy][worldx*10+worldz];
	}
   }
  }
}
*/