#include <src/imageprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>


/*definindo a função blur exponencial*/

void *blur(float *arg, float* matriz, imagem*img);

int main() {
	/*iniciando o struct de tempo*/
	struct timeval start, stop;
   	double secs = 0;
	/*iniciando a contagem do tempo*/
	gettimeofday(&start, NULL);

	/*iniciando a imagem e sua leitura*/
	imagem img;
        img = abrir_imagem("src/data/cachorro.jpg");

	/*memoria compartilhada entre os processos*/
	float *matriz1 = (float*)mmap(NULL, sizeof(float)*img.width*img.height, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,0,0);
	float *matriz2 = (float*)mmap(NULL, sizeof(float)*img.width*img.height, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,0,0);
	float *matriz3 = (float*)mmap(NULL, sizeof(float)*img.width*img.height, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,0,0);

        float* a1 = img.r;
        float* a2 = img.g;
        float* a3 = img.b;

	/*iniciando os processos, cada filho irá tratar de uma cor*/
	pid_t p1, p2, p3;

	p1= fork();
	if (p1==0){
		blur(a1,matriz1,&img);
	exit(0);
	}

	p2 = fork();
	if (p2==0){
		blur(a2,matriz2,&img);	
	exit(0);
	}	

	p3 = fork();
	if (p3==0){
		blur(a3, matriz3,&img);
	exit(0);
	}

	/*aguardando todos os processos terminarem*/
	waitpid(p1,NULL,0);
	waitpid(p2,NULL,0);
	waitpid(p3,NULL,0);

	/*salvando a nova imagem*/
        salvar_imagem("cachorro-out-process.jpg", &img);
        liberar_imagem(&img);

	/*fim da contagem de tempo*/
	gettimeofday(&stop, NULL);

	/*convertendo o tempo para segundos*/
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("tempo multiprocess: %f segundos.\n", secs);

        return 0;
}


void *blur(float* arg, float *matriz, imagem*img){
        float alpha = 0.98;
        for (int i = 0; (unsigned int)i<(img->width); i++){
                for (int j =0;(unsigned int) j<(img->height); j++){
                        if (i!=0) {
                               arg[j*img->width + i] = (1-alpha)*arg[j*img->width + i] +(alpha)*arg[j*img->width + i -1];
                        }
			matriz[j*img->width+i] = arg[j*img->width + i];

		}
        }
}
