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
#define width 300
#define height 300
#define SEED   500
//#define T 0
//#define J 100
#define RED   0x00000000
#define BLUE  0x0000FF00
size_t iter=0;
float T,J,J_spin[height][width];
float DISTRIBUTION;
float M_TOTAL = 0.0f;
float E = 0.0f;
size_t count = 0; 

float RandF(void){
	return (float)rand()/(float)RAND_MAX;
}


void InitJ()
{
		for(size_t y = 0;y < height;y++){
		for(size_t x = 0;x < width;x++){
			J_spin[y][x]=J;
		
		}
		}

}


void RandSpins(uint32_t spins[height][width]){
		srand(time(0));
	  //srand(SEED);
	for(size_t y = 1;y < height;y++){
		for(size_t x = 1;x < width;x++){
	
			//J_spin[y][x]=sin(y)*1000+RandF();
	


				
				
			if(RandF() < DISTRIBUTION){
				spins[y][x]= RED;  //BLUE
				M_TOTAL++;
			}
			else{
				spins[y][x]= BLUE;  //RED
				M_TOTAL--;
			}
		}
	}
}

void ParaSpines(uint32_t spins[height][width])
{
		for(size_t y = 1;y < height;y++){
		for(size_t x = 1;x < width;x++){
			if((x*y)%2==0){
				spins[y][x]= RED;
			}
			else
				spins[y][x]= BLUE;
		}
		}
}

float CalculateFermiDirackDistribution(float E){
	float k = 1.380649; //MOVED 10E-23 AS COPLING CONSTANT 
	//return 1;
	return 1.0f/(expf((E)/(k*(T+0.001)))+1); 	
}

void header(void)
{
	printf("************************************************************\n");
	printf("			Lenz-Ising model\n");
	printf("************************************************************\n");
	printf("\n\nThe Ising model, named after the physicists Ernst Ising and Wilhelm Lenz,\nis a mathematical model of ferromagnetism in statistical mechanics.\nThe model consists of discrete variables\nthat represent magnetic dipole moments\nof atomic spins that can be in one of two states.\n\n");
	printf("LEGENDS: BLACK: +SPIN WHITE -SPIN\n\n");

}
void LodingParametars(void)
{
	printf("\nT =  ");
	scanf("%f",&T);
	printf("\n\nJ IS DIVIDED BY 10^-23\nJ = ");
	scanf("%f",&J);
	printf("INPUT DISTRIBUTION OF SPINS(0 - 1) ");
	scanf("%f",&DISTRIBUTION);
	assert(DISTRIBUTION > 0.0f);
	assert(DISTRIBUTION < 1.0f);
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
			//J_spin[y][x]=J_spin[y][x-1];
			float E_TOTAL = -1.0f*J_spin[x][y]*(E_TOP*E_BOTHOM*E_LEFT*E_RIGHT);
			float chance;
			E+=E_TOTAL;
			chance = CalculateFermiDirackDistribution(E_TOTAL);
			if((RandF() <= chance)&&(E_TOTAL >= 0)){spins[x][y] = RED;
			if(x!=width)
			{
				if((x!=width-2)&&(y!=height-1))
				{
					x++;
					x++;
				
				}
			} 
			}
			if((RandF() <= chance)&&(E_TOTAL <= 0))
			{
				spins[x][y] = BLUE;
				if((x!=width-2)&&(y!=height-1))
				{
					x++;
					x++;
				}
				
			 
			}

		
		}
		count++;
		if(count%10000==0)
		{
			
			printf("\nT =  ");
			scanf("%f",&T);
			system("cls");
			
			header();
			M_TOTAL=0;
			for(size_t y = 1;y < height-1;y++){
			for(size_t x = 1;x < width-1;x++){
			if(spins[y][x]==BLUE){M_TOTAL--;}
			else{M_TOTAL++;}
			count = 0;
		}
	}
			
			printf("M(%d) = %f x10^(-3)\n",(int)T,(M_TOTAL)/(float)(width*height));
			
			//count = 0; 
		}
		E = 0;
		M_TOTAL = 0;
	}
	//system("pause");
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
	InitJ();
	//ParaSpines(&spins);
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
