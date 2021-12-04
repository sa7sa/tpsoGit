//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include "comuns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void balcSigHandler(int sig){
    char escolha[2];
        do{
            fprintf(stderr, "\nPrecionou ctrl-C:\n Tem a certeza que deseja sair?\n");
            fprintf(stderr, "'s' para sair, 'n' para cancelar\n");
            fgets(escolha, sizeof(escolha), stdin);
        
         }while((strcmp(escolha, "s") != 0) && (strcmp(escolha, "n") != 0));

         if(strcmp(escolha, "n") == 0){
            fprintf(stderr, "\nContinuar...\n");
            return;
            }
         if(strcmp(escolha, "s") == 0){
            printf("\nTerminado via teclado (ctrl-C) pelo utilizador\n");
            unlink(getenv("BALC_FIFO"));
            exit(EXIT_SUCCESS);
            }
}


void clienteSigHandler(int sigc){
    char cPID[25];
    char escolha[2];
    utent_t utente;

    sprintf(cPID, getenv("CLIENT_FIFO"), getpid());

    printf("%d\n", getpid());

        do{
            fprintf(stderr, "\nPrecionou ctrl-C:\n Tem a certeza que deseja sair?\n");
            fprintf(stderr, "'s' para sair, 'n' para cancelar\n");
            fgets(escolha, sizeof(escolha), stdin);
        
         }while((strcmp(escolha, "s") != 0) && (strcmp(escolha, "n") != 0));

         if(strcmp(escolha, "n") == 0){
            fprintf(stderr, "\nContinuar...\n");
            return;
            }
         if(strcmp(escolha, "s") == 0){
            printf("\nTerminado via teclado (ctrl-C) pelo utilizador\n");
            unlink(cPID);
            exit(EXIT_SUCCESS);
            }
}

void criaFIFO(char *fifo){
    int res;

    res = mkfifo(fifo, 0777);

    if(res == -1){
        perror("\nNão foi possivel abrir o Balcao");
        exit(EXIT_FAILURE);
        }
    }

int openFIFO_rdwr(char *ofifo){
    int intFifo;

    intFifo = open(ofifo, O_RDWR);

    if(intFifo == -1){
        printf("\nErro ao abrir %s", ofifo);
        exit(EXIT_FAILURE);
        }
    return intFifo;exit

    }