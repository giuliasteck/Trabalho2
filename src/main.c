#include <imageprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_PROCESSES 4

void blur(imagem *img, int i, int j);

int main() {
	imagem img;
	img = abrir_imagem("data/cachorro.jpg");

	int i=0;
	int j = 0;
	blur(&img,i,j);

	salvar_imagem("cachorro-out.jpg", &img);
	liberar_imagem(&img);
	return 0;
}
      

void blur(imagem *img, int i, int j){
	float alpha = 0.98;
	for (i = 0; i<(img->width); i++){	
		for (j =0; j<(img->height); j++){
			if (i!=0) {
        			img->g[j*img->width + i] = (1-alpha)*img->g[j*img->width + i] +(alpha)* img->g[j*img->width + i -1];
      				img->b[j*img->width+i] = (1-alpha)*img->b[j*img->width + i]+(alpha)*img->b[j*img->width+i-1];
      				img->r[j*img->width+i] = (1-alpha)*img->r[j*img->width+i]+(alpha)*img->r[j*img->width+i-1];
  			}
		}
	}
}


 

