#include <imageprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_PROCESSES 4

void blur(imagem *img);

int main() {
	imagem img;
	img = abrir_imagem("data/cachorro.jpg");

	blur(&img);

	salvar_imagem("cachorro-out.jpg", &img);
	liberar_imagem(&img);
	return 0;
}
      

void blur(imagem *img){
	float alpha = 0.98;
	for (int i = 0; i<(img->width); i++){	
		for (int j =0; j<(img->height); j++){
			if (i!=0) {
        			img->g[j*img->width + i] = (1-alpha)*img->g[j*img->width + i] +(alpha)* img->g[j*img->width + i -1];
      				img->b[j*img->width+i] = (1-alpha)*img->b[j*img->width + i]+(alpha)*img->b[j*img->width+i-1];
      				img->r[j*img->width+i] = (1-alpha)*img->r[j*img->width+i]+(alpha)*img->r[j*img->width+i-1];
  			}
		}
	}
}


 

