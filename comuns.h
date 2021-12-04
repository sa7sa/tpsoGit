//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>

#define  TAM_MAX 50
#define  SINT_MAX 8
#define  PORDEF "default"

//Estrutura de acondicionamento de dados do cliente
typedef struct cliente utent_t, *utent;
struct cliente{
 pid_t pid_utent;
 char nome[TAM_MAX];
 char palavra[TAM_MAX];
 char sint[TAM_MAX];
 utent next;
};

//Estrutura de acondicionamento de dados do balcao
typedef struct balcao balcao_t, *balc;
struct balcao{
  int pid;
  char pnome[TAM_MAX];
  char palavra[TAM_MAX];
};

//Estrutura de acondicionamento de dados do medico
typedef struct medico medic_t, *medic;
struct medico{
  pid_t pid_medic;
  char mnome[TAM_MAX];
  char espec[TAM_MAX];
  char unome[TAM_MAX];
  char pr[TAM_MAX];
  medic next;
};

int Verifica_cliente(utent c1, char cname[]);
int Mostra_cliente(utent c1);
utent criaCliente(utent c1, utent_t copia);