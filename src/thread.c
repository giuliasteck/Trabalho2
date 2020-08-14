#include <imageprocessing.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 100

/*definindo a função blur exponencial e variaveis*/
void *blur(void *arg);
double tempos[];
double soma_tempos;
double media;


/*definindo as threads*/
pthread_t worker1, worker2, worker3;

imagem img;

int main() {
	/*iniciando o struct de tempo*/
	struct timeval start, stop;
   	double secs = 0;
<<<<<<< HEAD
=======
	/*iniciando a contagem do tempo*/
	gettimeofday(&start, NULL);

	/*iniciando a imagem e sua leitura*/
	img = abrir_imagem("data/cachorro.jpg");

	pthread_t worker1, worker2, worker3;
	void *a1 = malloc(sizeof(float*)); 
	a1 = img.r;
	void *a2 = malloc(sizeof(float*));
	a2 = img.g;
	void *a3 = malloc(sizeof(float*));
	a3 = img.b;

	/*Criando as threads, cada uma irá tratar uma cor*/
	pthread_create(&(worker1), NULL, blur, a1);
	pthread_create(&(worker2), NULL, blur, a2);
	pthread_create(&(worker3), NULL, blur, a3);

	pthread_join(worker1, NULL);
	pthread_join(worker2, NULL);
	pthread_join(worker3, NULL);

	/*salvando a nova imagem*/
        salvar_imagem("cachorro-out-thread.jpg", &img);
        liberar_imagem(&img);
>>>>>>> ee5be34c4a7475703c7973970b2bf1c3c9b74478
	
	for (int aux = 0 ; aux<M; aux++){
		/*iniciando a contagem do tempo*/
		gettimeofday(&start, NULL);
	
		/*iniciando a imagem e sua leitura*/
		img = abrir_imagem("src/data/cachorro.jpg");

		pthread_t worker1, worker2, worker3;
		void *a1 = malloc(sizeof(float*)); 
		a1 = img.r;
		void *a2 = malloc(sizeof(float*));
		a2 = img.g;
		void *a3 = malloc(sizeof(float*));
		a3 = img.b;

		/*Criando as threads, cada uma irá tratar uma cor*/
		pthread_create(&(worker1), NULL, blur, a1);
		pthread_create(&(worker2), NULL, blur, a2);
		pthread_create(&(worker3), NULL, blur, a3);

		pthread_join(worker1, NULL);
		pthread_join(worker2, NULL);
		pthread_join(worker3, NULL);
	
		/*salvando a nova imagem*/
       		 salvar_imagem("cachorro-out-thread.jpg", &img);
       	 	liberar_imagem(&img);
	
		/*Fim da contagem de tempo*/
		gettimeofday(&stop, NULL);

		/*convertendo o tempo para segundos*/
		secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
		tempos[aux] = secs;
		/*tirar print depois do gráficooooo*/
		printf("tempo da %d main simples: %f segundos.\n ",aux, tempos[aux]);		
		soma_tempos += tempos[aux];
	}    

	media = soma_tempos/M;


	printf("tempo multithreads: %f segundos.\n", secs);

        return 0;

}


void *blur(void *arg){
	float alpha = 0.98;
	float* matriz = malloc(sizeof(float)*img.height*img.width);
	memcpy(matriz, arg, (sizeof(float)*img.height*img.width));
        for (int i = 0; (unsigned int)i<(img.width); i++){
                for (int j =0; (unsigned int) j<(img.height); j++){
                        if (i!=0) {
                               matriz[j*img.width + i] = (1-alpha)*matriz[j*img.width + i] +(alpha)*matriz[j*img.width + i -1];
                        }
	((float*)arg)[j*img.width+i] = matriz[j*img.width + i];
		}
	}
}

