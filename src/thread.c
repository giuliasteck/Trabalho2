#include <imageprocessing.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *blur(void *arg);

pthread_t worker1, worker2, worker3;

imagem img;

int main() {
	img = abrir_imagem("data/cachorro.jpg");

	pthread_t worker1, worker2, worker3;
	void *a1 = malloc(sizeof(float*)); 
	a1 = img.r;
	void *a2 = malloc(sizeof(float*));
	a2 = img.g;
	void *a3 = malloc(sizeof(float*));
	a3 = img.b;

	pthread_create(&(worker1), NULL, blur, a1);
	pthread_create(&(worker2), NULL, blur, a2);
	pthread_create(&(worker3), NULL, blur, a3);

	pthread_join(worker1, NULL);
	pthread_join(worker2, NULL);
	pthread_join(worker3, NULL);

        salvar_imagem("cachorro-thread.jpg", &img);
        liberar_imagem(&img);
        return 0;
}


void *blur(void *arg){
	float alpha = 0.98;
	float* matriz = malloc(sizeof(float)*img.height*img.width);
	memcpy(matriz, arg, (sizeof(float)*img.height*img.width));
        for (int i = 0; i<(img.width); i++){
                for (int j =0; j<(img.height); j++){
                        if (i!=0) {
                               matriz[j*img.width + i] = (1-alpha)*matriz[j*img.width + i] +(alpha)*matriz[j*img.width + i -1];
                        }
	((float*)arg)[j*img.width+i] = matriz[j*img.width + i];
		}
	}
}

