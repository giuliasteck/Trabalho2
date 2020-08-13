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

        salvar_imagem("cachorro-out.jpg", &img);
        liberar_imagem(&img);
        return 0;
}


void *blur(void *arg){
	float alpha = 0.98;
        for (int i = 0; i<(img.width); i++){
                for (int j =0; j<(img.height); j++){
                        if (i!=0) {
                               arg[j*img.width + i] = (1-alpha)*arg[j*img.width + i] +(alpha)*arg[j*img.width + i -1];
                        }
                }
        }
}
