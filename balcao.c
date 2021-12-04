/* Trabalho prático Sistemas Operativos */
/* Meta 1                               */
/* Celso Jordão, nº.2003008910          */
/* Fábio Campobianchi, nº.2018915299    */

#include "comuns.h"
#include "funcoes.h"
#include <signal.h>
#include <sys/wait.h>

int b_fifo_fd;
int c_fifo_fd;
int m_fifo_fd;

int main(int argc, char **argv, char **envp){

  int bal_to_cla[2];
  int cla_to_bal[2];
  int id, res, size;

  pipe(bal_to_cla);
  pipe(cla_to_bal);

  utent lista = NULL, aux = NULL;
  utent_t utente;
  balcao_t balc;

  char c_fifo_fname[50];
  char m_fifo_fname[50];
  char sintomas[100];
  char instrucao[TAM_MAX];
  char respostaClassificador[100];

  struct sigaction siga;
  siga.sa_handler = balcSigHandler;
  sigemptyset(&siga.sa_mask);
  siga.sa_flags = SA_RESTART || SA_SIGINFO;
  sigaction(SIGINT, &siga, NULL);

  fprintf(stdout,"\nMEDICALso\n");

/*  res = mkfifo(getenv("BALC_FIFO"), 0777);//Criação do FIFO do balcao

  if (res == -1){
    perror("\nNao foi possivel abrir o Balcao");
    exit(EXIT_FAILURE);
  }
*/
  criaFIFO(getenv("BALC_FIFO"));

/*  b_fifo_fd = open(getenv("BALC_FIFO"), O_RDWR);//Abertura para leitura/escrita do FIFO do balcão

  if (b_fifo_fd == -1){
    perror("\nErro ao abrir Balcao");
    exit(EXIT_FAILURE);
  }
*/

  openFIFO_rdwr(getenv("BALC_FIFO"));

  fprintf(stderr, "\n Bom Dia\n Balcao aberto para atendimento\n");

  memset(utente.palavra, '\0', TAM_MAX);

id = fork();

if(id == 0){
  close(0);
  dup(bal_to_cla[0]);
  close(bal_to_cla[0]);
  close(bal_to_cla[1]);

  close(1);
  dup(cla_to_bal[1]);
  close(cla_to_bal[1]);
  close(cla_to_bal[0]);

  execl("classificador", "classificador",NULL);

  exit(33);

}else{
  close(cla_to_bal[1]);
  close(bal_to_cla[0]);

do{
    printf("\n Aguarda os Clientes:\n");

    fprintf(stderr, "Digite a instrução:");
    fgets(instrucao, sizeof(instrucao), stdin);

    if(strcmp(instrucao, "cliente\n") == 0)
        res = read(b_fifo_fd, &utente, sizeof(utente));

    if(res < sizeof(utente)){
      fprintf(stderr,"\nMensagem ilegivel");
      continue;
    }

    fprintf(stderr,"\nRecebido de %s sintoma %s\n",utente.nome, utente.palavra);

    if(!strcmp(utente.palavra, "fimb\n")){
      close(b_fifo_fd);
      close(c_fifo_fd);
      unlink(getenv("BALC_FIFO"));
      break;
    }
   if(!strcmp(utente.palavra, "espera\n")){
    Mostra_cliente(lista);
}
    strcpy(balc.palavra, utente.palavra);
    strcpy(balc.pnome, utente.nome);
    balc.pid = utente.pid_utent;

    sprintf(c_fifo_fname, getenv("CLIENT_FIFO"), utente.pid_utent);

    c_fifo_fd = open(c_fifo_fname, O_WRONLY); //Abertura para leitura do FIFO do cliente

    if(c_fifo_fd == -1)
      printf("O Cliente %s nao esta disponivel",utente.nome);
    else{

    strcpy(sintomas, utente.palavra);

    if (strcmp(sintomas,"#fim\n")!=0){
      write(bal_to_cla[1], sintomas, strlen(sintomas));
      size=read(cla_to_bal[0], respostaClassificador, sizeof(respostaClassificador));
      respostaClassificador[size]='\0';
      strcpy(balc.palavra,respostaClassificador);//////
      strcpy(utente.sint,respostaClassificador);
    }else{
      printf("fim");
      write(bal_to_cla[1], "#fim\n",5);
      wait(&id);
    }
    if(Verifica_cliente(lista,utente.nome)!=0){
      aux = criaCliente(lista,utente);
      lista = aux;
  }

    res = write(c_fifo_fd, &balc, sizeof(balc)); //Escrita dos dados recebidos do cliente para o balcão

    if(res == sizeof(balc))
      fprintf(stderr,"\nescreveu ao Cliente %s\n",balc.palavra);
    else
      perror("\nerro a escrever ao Cliente");


    b_fifo_fd = open(getenv("BALC_FIFO"), O_RDWR);

    if (b_fifo_fd == -1){
      perror("\nErro ao abrir Balcao");
      exit(EXIT_FAILURE);
    }
  }

  }while (strcmp(sintomas, "#fim\n")!=0);
}

close(b_fifo_fd);
unlink(getenv("BALC_FIFO"));

return 0;
}
