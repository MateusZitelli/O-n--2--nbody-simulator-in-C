#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#define WIDTH 1000
#define HEIGHT 1000
#define BPP 4
#define DEPTH 32
#define NB 3000

void setpixel(SDL_Surface * screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0) return;
	Uint32 *pixmem32;
	Uint32 colour;

	colour = SDL_MapRGB(screen->format, r, g, b);

	pixmem32 = (Uint32 *) screen->pixels + screen->w * y + x;
	*pixmem32 = colour;
}

int main(void){
	SDL_Surface *screen;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {
		SDL_Quit();
		return 1;
	}
	int keypress = 0;
	int k, i, j;
	double ft, D, dx, dy;
	double *px;
	double *py;
	double *m;
	double *fx;
	double *fy;
	double *vx;
	double *vy;
	px = (double *) malloc(sizeof(double) * NB);
	py = (double *) malloc(sizeof(double) * NB);
	m = (double *) malloc(sizeof(double) * NB);
	fx = (double *) malloc(sizeof(double) * NB);
	fy = (double *) malloc(sizeof(double) * NB);
	vx = (double *) malloc(sizeof(double) * NB);
	vy = (double *) malloc(sizeof(double) * NB);
	srand(time(0));
	for(i = 0; i < NB + 1; i++){
		px[i] = rand() % WIDTH;
		py[i] = rand() % HEIGHT;
		m[i] = rand() % 10 + 1;
		fx[i] = 0;
		fy[i] = 0;
		vx[i] = 0;
		vy[i] = 0;
	}
	while(1){
		for(i = 0; i < NB; i++){
			for(j = 0; j < NB; j++){
				if(i == j) continue;
				dx = px[j] - px[i];
				dy = py[j] - py[i];
				D = sqrt(dx * dx + dy * dy);
				if(D < 5) D = 5;
				ft = m[i] * m[j] / (D * D);
				fx[i] += ft * dx / D;
				fy[i] += ft * dy / D;
			}
		}
		for(i = 0; i < NB; i++){
			vx[i] += fx[i] / m[i];
			vy[i] += fy[i] / m[i];
			fx[i] = 0;
			fy[i] = 0;
			px[i] += vx[i];
			py[i] += vy[i];
			setpixel(screen, px[i], py[i], 255, 255, 255);
		}
		SDL_Flip(screen);
		SDL_FillRect(screen, NULL, 0x000000);
	}
	return(0);
}
