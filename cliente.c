//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include "comuns.h"
#include "funcoes.h"

int main(int argc, char **argv, char **envp){

  int b_fifo_fd;
  int c_fifo_fd;
  int m_fifo_fd;
  utent_t utente;
  balcao_t balcao;
  medic_t  medic;
  char p_fifo_fname[25];
  char m_fifo_fname[25];
  int read_res;
 
  struct sigaction sigac;
  sigac.sa_handler = clienteSigHandler;
  sigemptyset(&sigac.sa_mask);
  sigac.sa_flags = SA_RESTART || SA_SIGINFO;
  sigaction(SIGINT, &sigac, NULL);

  if(argc < 2){
    fprintf(stdout,"Faltam parametros!!!.\n Ex: ./utente <nome utente>\n Nome 'default' por defeito\n");
    argv[1] = PORDEF;
  }

  //Cria o FIFO do utente
  strcpy(utente.nome,argv[1]);
  utente.pid_utent = getpid();

  sprintf(p_fifo_fname, getenv("CLIENT_FIFO"), utente.pid_utent);

/*  if(mkfifo(p_fifo_fname, 0777) == -1){
    perror("\nUtente deu erro");
    exit(EXIT_FAILURE);
  }
*/
  criaFIFO(p_fifo_fname);

  b_fifo_fd = open(getenv("BALC_FIFO"), O_WRONLY);

  if(b_fifo_fd == -1){
    fprintf(stderr, "\nO Balcao não esta a correr\n");
    unlink(p_fifo_fname);
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"\nBalcao aberto ao atendimento");

  c_fifo_fd = openFIFO_rdwr(p_fifo_fname);
  
  if(c_fifo_fd == -1){
    perror("\nErro ao abrir utente");
    close(c_fifo_fd);
    unlink(p_fifo_fname);
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "\nUtente pronto");

  memset(utente.palavra, '\0', TAM_MAX);

  while(1){

    printf("\nSr/a %s digite os sintomas: >",argv[1]);

    fgets(utente.palavra, TAM_MAX, stdin);

    if(!strcmp(utente.palavra,"fimb\n") || !strcmp(utente.palavra,"#fim\n")){
      write(b_fifo_fd, &utente, sizeof(utente));
      close(c_fifo_fd);
      unlink(p_fifo_fname);
      break;
    }

    // B) Envia ao balcao
    write(b_fifo_fd, &utente, sizeof(utente));

    // c) recebe do balcao
    read_res = read(c_fifo_fd, &balcao, sizeof(balcao));

    if(read_res == sizeof(balcao)){
      printf("\nNome -> %s Sintoma -> %s PID -> %d" , balcao.pnome, balcao.palavra,balcao.pid);
    }else{
      printf("\nSem resposta do balcao" "[bytes lidos: %d]", read_res);
    }
}

  close(c_fifo_fd);
  close(b_fifo_fd);
  unlink(p_fifo_fname);

  return 0;
}
