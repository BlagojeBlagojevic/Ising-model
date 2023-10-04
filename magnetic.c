#include<SDL2/SDL.h>
#include<SDL2/SDL_hints.h>
#include<SDL2/SDL_error.h>
#include<SDL2/SDL_log.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_render.h>
#include<SDL2/SDL_pixels.h>
#include<SDL2/SDL_rect.h>
#include<SDL2/SDL_surface.h>
#include<SDL2/SDL_clipboard.h>
#include<SDL2/SDL_events.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDl_timer.h>
#include<assert.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#undef main                //275 183
#define width 200
#define height 200
#define SEED   10
//#define T 0
//#define J 100
#define RED 0x00FF0000
#define BLUE 0x000000FF
float T,J;
float DISTRIBUTION;
float M_TOTAL = 0.0f;
float E = 0.0f;
size_t count = 0; 

void RandSpins(uint32_t spins[height][width]){
	srand(SEED);
	
	for(size_t y = 1;y < height-1;y++){
		for(size_t x = 1;x < width-1;x++){
			if(rand()%((int)(1/DISTRIBUTION))==0){
				spins[y][x]= BLUE;  //BLUE
				M_TOTAL--;
			}
			else{
				spins[y][x]= RED;  //RED
				M_TOTAL++;
			}
		}
	}
}

float CalculateFermiDirackDistribution(float E){
	float k = 1.380649; //MOVED 10E-23 AS COPLING CONSTANT 
	return 1/(expf(E/(k*T))+1); 	
}
float RandF(void){
	return (float)rand()/(float)RAND_MAX;
}
void header(void)
{
	printf("************************************************************\n");
	printf("			Lenz-Ising model\n");
	printf("************************************************************\n");
	printf("\n\nThe Ising model, named after the physicists Ernst Ising and Wilhelm Lenz,\nis a mathematical model of ferromagnetism in statistical mechanics.\nThe model consists of discrete variables\nthat represent magnetic dipole moments\nof atomic spins that can be in one of two states.\n\n");
	printf("LEGENDS: RED: +SPIN BLUE -SPIN\n\n");

}

void UpdateSpins(uint32_t spins[height][width])
{
	//HOW THIS ALGHORRITHM WORK CALCULATING ENERGY FOR A SISTEM AS A -1*J(SIGMA_i *SIGMA_j)
	

	
	float E_LEFT,E_RIGHT,E_TOP,E_BOTHOM;
	//system("pause");
	for(size_t y = 1; y < height-1; y++){
		for(size_t x = 1; x < width-1; x++){
			// CALCULATE ENERGY OF NEIGBRHOD CELLS AND THEN UPDATE SPIN
			
			if(spins[y-1][x]==RED && spins[y][x] == RED){
				E_TOP = 1.0f;
			}
			if(spins[y-1][x]==RED && spins[y][x] == BLUE){
				E_TOP = -1.0f;
			}
			if(spins[y-1][x]== BLUE && spins[y][x] == RED){
				E_TOP = -1.0f;
			}
			if(spins[y-1][x]== BLUE && spins[y][x] == BLUE){
				E_TOP = 1.0f;
			}
			
			//system("pause");
			
			if(spins[y+1][x]==RED && spins[y][x] == RED){
				E_BOTHOM = 1.0f;
			}
			if(spins[y+1][x]==RED && spins[y][x] == BLUE){
				E_BOTHOM = -1.0f;
			}
			if(spins[y+1][x]== BLUE && spins[y][x] == RED){
				E_BOTHOM = -1.0f;
			}
			if(spins[y+1][x]== BLUE && spins[y][x] == BLUE){
				E_BOTHOM = 1.0f;
			}
			//system("pause");
			if(spins[y][x-1]==RED && spins[y][x] == RED){
				E_LEFT = 1.0f;
			}
			if(spins[y][x-1]==RED && spins[y][x] == BLUE){
				E_LEFT = -1.0f;
			}
			if(spins[y][x-1]== BLUE && spins[y][x] == RED){
				E_LEFT = -1.0f;
			}
			if(spins[y][x-1]== BLUE && spins[y][x] == BLUE){
				E_LEFT = 1.0f;
			}
			//system("pause");
			
			if(spins[y][x+1]==RED && spins[y][x] == RED){
				E_RIGHT = 1.0f;
			}
			if(spins[y][x+1]==RED && spins[y][x] == BLUE){
				E_RIGHT = -1.0f;
			}
			if(spins[y][x+1]== BLUE && spins[y][x] == RED){
				E_RIGHT = -1.0f;
			}
			if(spins[y][x+1]== BLUE && spins[y][x] == BLUE){
				E_RIGHT = 1.0f;
			}		
			//system("pause");
			
			
			float E_TOTAL = -1*J*(E_TOP*E_BOTHOM*E_LEFT*E_RIGHT);
			float chance;
			E+=E_TOTAL;
			chance = CalculateFermiDirackDistribution(E_TOTAL);
			//printf("chance: %f\n",chance);
			if(RandF() >= chance&&(E_TOTAL >= 0)){spins[x][y] = RED; M_TOTAL++;}
			if(RandF() >= chance&&(E_TOTAL <= 0)){spins[x][y] = BLUE; M_TOTAL--;}
		}
		count++;
		if(count%10000==0)
		{
			system("cls");
			header();
			printf("M = %f x10^(-3)\n",M_TOTAL/10.0f);
			count = 0; 
		}
		E = 0;
		M_TOTAL = 0;
	}
	//system("pause");
}

void LodingParametars(void)
{
	printf("\nT =  ");
	scanf("%f",&T);
	printf("\n\nJ IS DIVIDED BY 10^-23\n J = ");
	scanf("%f",&J);
	printf("INPUT DISTRIBUTION OF SPINS(0 - 1) ");
	scanf("%f",&DISTRIBUTION);
	assert(DISTRIBUTION > 0.0f);
	assert(DISTRIBUTION < 1.0f);
	
	
}
int main()
{
	header();
	LodingParametars();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_CreateWindowAndRenderer(800,640,NULL,&window,&renderer);
	texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,width,height);
	
	uint32_t spins[height][width];
	RandSpins(&spins);
	printf("%f",M_TOTAL);
	system("pause");
	
	while(1){
		
		//LOCK TEXTURE
		uint32_t *pixels;
		int pitch;        //SIZE BASED ON RESOLUTION
		size_t j = 0;
		
		SDL_LockTexture(texture,NULL,(void**)&pixels,&pitch);
			for(size_t i = 0; i < height; i++){
				for(size_t k = 0; k < width; k++)
				pixels[j++]=spins[i][k];
			}				
		SDL_UnlockTexture(texture);
		//UNLOCK TEXTURE
		
		//RENDER VALUE OF SPINS
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		//
		//UPDATE SPINS
		UpdateSpins(&spins);
		//
	}
	return 0;
}
