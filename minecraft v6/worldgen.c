



int worldchunk[99][999];
int perlin[999];
int pnx, pny;
void perlingeneration () 
{
 pnx=0;
    pny=0;
	
	srand(395248);

  
  
   for(pnx=0;pnx<100;pnx++)
   {
    for(pny=0;pny<100;pny++)
    {
	
	perlin[vfx*100+vfy] = 31;
	//pixel(vfx,vfy,chunk[vfx*100+vfy]); 
	  
	
   }
  }
 
}

void generateworld(int seed) 
{
  perlingeneration(); 
 
}