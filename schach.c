/*
Bastian Ruppert
*/


#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>

int W = 320;
int H = 240;
int Q = 10;

SDL_Surface * pS;
Uint32 s; 
Uint32 w;

Uint32 toggleColor(void)
{
  static Uint32 * plast = &s;
  if(plast==&s){
    plast=&w;
    return w;
  }else{
    plast=&s;
    return s;
  } 
}

static Uint8 r1 = 0;
static Uint8 g1 = 0;
static Uint8 b1 = 0;

static Uint8 r2 = 255;
static Uint8 g2 = 255;
static Uint8 b2 = 255;

#define TESTIMAGE 0x00000001

static char * testImages[] = {"allInOne.bmp",\
			      "blume.bmp",\
			      "palette.bmp",\
			      "testbild.bmp",\
			      "testbild2.bmp",\
			      "paprika.bmp",\
			    "obst.bmp",};
static int testImagesLength = 7;

static int showTestImage(char * filename);

static int iFlag = 0;

int main(int argl, const char* args[])
{
  int i,ii,ret;
  

  
  argl--;

  if(argl>0){
    for(i=1;i<argl+1;i++)
      {
	
	if(!strcmp(args[i],"-help")){
	  printf("usage: ./schach [FLAG][-vga]\n");
	  printf("FLAGS:for coloring the complete Surface\n");
	  printf("-black\n");
	  printf("-white\n");
	  printf("-red\n");
	  printf("-green\n");
	  printf("-blue\n");
	  printf("-testimage\n");
	  return 0;
	}
	if(!strcmp(args[i],"-white")){
	  r1 = 255;
	  g1 = 255;
	  b1 = 255;
	  
	  r2 = 255;
	  g2 = 255;
	  b2 = 255; 
	}
	if(!strcmp(args[i],"-red")){
	  r1 = 255;
	  g1 = 0;
	  b1 = 0;
	  
	  r2 = 255;
	  g2 = 0;
	  b2 = 0; 
	}
	if(!strcmp(args[i],"-green")){
	  r1 = 0;
	  g1 = 255;
	  b1 = 0;
	  
	  r2 = 0;
	  g2 = 255;
	  b2 = 0; 
	}
	if(!strcmp(args[i],"-blue")){
	  r1 = 0;
	  g1 = 0;
	  b1 = 255;
	  
	  r2 = 0;
	  g2 = 0;
	  b2 = 255; 
	}
	if(!strcmp(args[i],"-black")){
	  r1 = 0;
	  g1 = 0;
	  b1 = 0;
	  
	  r2 = 0;
	  g2 = 0;
	  b2 = 0; 
	}
	if(!strcmp(args[i],"-vga")){
	  W=640;
	  H=480;
	}
	if(!strcmp(args[i],"-testimage")){
	  iFlag |= TESTIMAGE; 
	}
      }
  }

  if(SDL_Init(SDL_INIT_VIDEO)==-1){
    return -1;
  }
  else{
    atexit(SDL_Quit);
  }
  
  pS = SDL_SetVideoMode(W,				\
			H,				\
			16,				\
			SDL_SWSURFACE);//SDL_HWSURFACE|SDL_DOUBLEBUF);//SDL_FULLSCREEN
  if(!pS){ 
    printf("SDL_SetVideoMode failed: %s\n",SDL_GetError());
    return -1;
  }
  
  s = SDL_MapRGB(SDL_GetVideoSurface()->format,		\
			r1,					\
			g1,					\
			b1); 

  w = SDL_MapRGB(SDL_GetVideoSurface()->format,		\
			r2,					\
			g2,					\
			b2);   
  SDL_Rect rect;
  rect.x=0;
  rect.y=0;
  rect.w=Q;
  rect.h=Q;

  for(ii=0;ii<(H/Q);ii++)
    {
      for(i = 0;i<(W/Q);i++)
	{
	  ret=SDL_FillRect(pS,&rect,toggleColor());
	  if(ret)return -2;
	  rect.x+=Q;
	}
      toggleColor(); 
      rect.x=0;
      rect.y +=Q;
    }

  SDL_UpdateRect(pS,0,0,0,0);

 SDL_Event theEvent;
 int index = 0;
  for(;;){
    if(iFlag == TESTIMAGE)
      {
	showTestImage(testImages[index]);
	index++;
	if(index>=testImagesLength)
	  {
	    index = 0;
	  }
	
	while(SDL_PollEvent(&theEvent))
	  {
	    if(theEvent.type==SDL_QUIT){
	      return 0;
	    }
	  }
	SDL_Delay(2000);
      }
    else
      {
	if(SDL_WaitEvent(&theEvent)==0){
	  //printf("error while waiting for event\n");
	  return -1; 
	}
	if(theEvent.type==SDL_QUIT){
	  return 0;
	}
      }
  }
  
  return 0;  
}

static int showTestImage(char * filename)
{
  SDL_Surface * pImg1;
  int i,ii,ret;

  SDL_Rect rect;
  rect.x=0;
  rect.y=0;
  rect.w=Q;
  rect.h=Q;

  for(ii=0;ii<(H/Q);ii++)
    {
      for(i = 0;i<(W/Q);i++)
	{
	  ret=SDL_FillRect(pS,&rect,toggleColor());
	  if(ret)return -2;
	  rect.x+=Q;
	}
      toggleColor(); 
      rect.x=0;
      rect.y +=Q;
    }


    if(TESTIMAGE==iFlag)
    {
      pImg1 = SDL_LoadBMP(filename);
      if (pImg1 == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", filename, SDL_GetError());
	return -1;
      }
      
      if(SDL_BlitSurface(pImg1,NULL,pS,NULL))
	{
	  fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	  return -1;
	}
      SDL_FreeSurface(pImg1);
    }
    SDL_UpdateRect(pS,0,0,0,0);
    return 0;
}
