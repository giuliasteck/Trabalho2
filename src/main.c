
#include <imageprocessing.h>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 3



/*Definindo variáveis globais*/
pthread_mutex_t trava;
int palavra;
int total_palavras;
int num;
char c;



  float alpha = 0.998;


/*definindo variaveis compartilhadas*/
int pare = 0;
int resultado = 0;
int linha = 0;
unsigned int tmp;
unsigned int tempr;
unsigned int tempg;
unsigned int tempb;
int N = 5;
/*definindo tamanho do vetor como 100*/
int mem_compartilhada[100];


/*Definindo a função do thread*/

void* funcao_thread(void *arg) {


imagem img;
  img = abrir_imagem("data/cachorro.jpg");

/*enquanto a variavel compartilhada de parada for diferente de 1, o thread continua rodando*/
while (pare !=1) {

  pthread_mutex_lock(&trava);/*esperar cada thread rodar, para não ter conflito nas variáveis*/
  
  if (linha == (img.width)) {
    pare = 1; /*quando ler todas as linhas, a variavel de parada é setada*/

    }

  linha++;

  pthread_mutex_unlock(&trava);/*libera para o proximo thread*/
  


  for (int i=0; i<((img.width)); i++) {
    for (int j=0; j<((img.height)); j++) {
	
      for (int k=0;k<2*N;k++) {
	tempr += img.r[j*img.width + i ];
	tempg += img.g[j*img.width + i ];
	tempb += img.b[j*img.width + i ];
      }
	tempr = tempr/(2*N-1);
	tempg = tempg/(2*N-1);
	tempb = tempb/(2*N-1);
	img.r[j*img.width + i] = tempr;
	img.g[j*img.width + i] = tempg;
	img.b[j*img.width + i] = tempb;
	tempr = 0;
	tempg = 0;
	tempb = 0;

/* Ganho no canal R */
     //tmp = img.r[i] + 1;
      //if (tmp > 255) tmp=255;
      //img.r[j*img.width + i] = tmp;

      /* Reducao no canal B */
      //img.b[j*img.width + i] /= 2;
     


     /* Blur exponencial no canal G */
      if (i!=0) {
       // img.g[j*img.width + i] = (1-N)+img.g[j*img.width + i] +(N)+ img.g[j*img.width + i -1];     
	 }

    }
  }

salvar_imagem("cachorro-out.jpg", &img);
  liberar_imagem(&img);
  }

  return NULL;
}

int main (int argc, char **argv) {
  


/*definindo a quantidade de threads que irão iniciar*/
  pthread_t threads[MAX_THREADS];
  int thread_args[MAX_THREADS];

/*iniciando cada thread de acordo com a quantidade de numeros a serem apresentados*/
  for (int i = 0; i < MAX_THREADS; i++ ) { /*i<=total de palavras caso tenha menos palavras do que threads possiveis de serem executadas*/
    thread_args[i] = i;
    pthread_create(&(threads[i]), NULL, funcao_thread, &(thread_args[i])); /*criando os threads*/
  
  }

/* Esperando threads terminarem! */
     for (int i = 0; i < MAX_THREADS; i++) {
     pthread_join(threads[i],NULL);

} 

  
  return 0;
}

