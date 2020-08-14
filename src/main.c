#include <imageprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void blur(imagem *img);

/*definindo a função blur exponencial*/
void blur(imagem *img);

int main() {
	/*iniciando o struct de tempo*/
	struct timeval start, stop;
   	double secs = 0;
	/*iniciando a contagem do tempo*/
	gettimeofday(&start, NULL);

	/*iniciando a imagem e sua leitura*/
	imagem img;
	img = abrir_imagem("data/cachorro.jpg");

	/*aplicando o filtro normalmente*/
	blur(&img);


	/*salvando a nova imagem*/
	salvar_imagem("cachorro-out-main.jpg", &img);
	liberar_imagem(&img);

	/*fim da contagem de tempo*/
	gettimeofday(&stop, NULL);

	/*convertendo o tempo para segundos*/
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("tempo da main simples: %f segundos.\n ", secs);


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


 

