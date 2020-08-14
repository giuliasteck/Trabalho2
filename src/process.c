#include <imageprocessing.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>

#define M 50

/*definindo a função blur exponencial*/

void *blur(float* matriz,float* arg, imagem*img);

double tempos[M];
double soma_tempos;
double media;

int main() {
	/*iniciando o struct de tempo*/
	struct timeval start, stop;
   	double secs = 0;
	
	for(int aux=0; aux<M; aux++){
		/*iniciando a contagem do tempo*/
		gettimeofday(&start, NULL);

		/*iniciando a imagem e sua leitura*/
		imagem img;
	        img = abrir_imagem_process("data/cachorro.jpg");

		int protection = PROT_READ | PROT_WRITE;
		int visibility = MAP_SHARED | MAP_ANONYMOUS;

		float *arg1 = img.r;
		float *arg2 = img.g;
		float *arg3 = img.b;

		/*memoria compartilhada entre os processos*/
		float *a1 = (float*)mmap(NULL, sizeof(float)*img.height*img.width, protection, visibility,0,0);

		/*iniciando os processos, cada filho irá tratar de uma cor*/
		pid_t p1, p2, p3;

		p1= fork();
		if (p1==0){
			blur(a1,arg1,&img);
			exit(0);
		}

		p2 = fork();
		if (p2==0){
			blur(a1,arg2,&img);	
			exit(0);
		}	

		p3 = fork();
		if (p3==0){
			blur(a1,arg3,&img);
			exit(0);
		}

		/*aguardando todos os processos terminarem*/
		waitpid(p1,NULL,0);
		waitpid(p2,NULL,0);
		waitpid(p3,NULL,0);

		/*salvando a nova imagem*/
	        salvar_imagem("cachorro-out-process.jpg", &img);
	        liberar_imagem_process(&img);

		/*fim da contagem de tempo*/
		gettimeofday(&stop, NULL);

		/*convertendo o tempo para segundos*/
    		secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
		
		tempos[aux] = secs;
		soma_tempos+= tempos[aux];
	}
	media = soma_tempos/M;
	printf("média de tempo multiprocess para M = %d: %f segundos.\n",M, secs);
        return 0;
}


void *blur(float* matriz,float* arg, imagem*img){
        float alpha = 0.98;
        for (int i = 0; (unsigned int)i<(img->width); i++){
                for (int j =0;(unsigned int) j<(img->height); j++){
                        if (i!=0) {
                               arg[j*img->width + i] = (1-alpha)*arg[j*img->width + i] +(alpha)*arg[j*img->width + i -1];
                        }

			matriz[j*img->width + i] = arg[j*img->width + i];
		}
        }
}
