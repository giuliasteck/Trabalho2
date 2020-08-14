#include <src/imageprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


void blur(imagem *img, int i, int j);

int main() {
	struct timeval start, stop;
  	double secs = 0;

	gettimeofday(&start,NULL);
	imagem img;
	img = abrir_imagem("src/data/cachorro.jpg");

	int i=0;
	int j = 0;
	blur(&img,i,j);

	salvar_imagem("cachorro-out-main.jpg", &img);
	liberar_imagem(&img);

	gettimeofday(&stop, NULL);
gettimeofday(&stop, NULL);

    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken main simples: %f\n", secs);


return 0;
}
      

void blur(imagem *img, int i, int j){
	float alpha = 0.98;
	for (i = 0;(unsigned int) i<(img->width); i++){	
		for (j =0; (unsigned int) j<(img->height); j++){
			if (i!=0) {
        			img->g[j*img->width + i] = (1-alpha)*img->g[j*img->width + i] +(alpha)* img->g[j*img->width + i -1];
      				img->b[j*img->width+i] = (1-alpha)*img->b[j*img->width + i]+(alpha)*img->b[j*img->width+i-1];
      				img->r[j*img->width+i] = (1-alpha)*img->r[j*img->width+i]+(alpha)*img->r[j*img->width+i-1];
  			}
		}
	}
}


 

