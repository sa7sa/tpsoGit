//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include "comuns.h"

//Função de verificação da existência de clientes
int Verifica_cliente(utent c1, char cname[]){
  utent aux;
  aux=c1;

  while(aux != NULL){
    if(strcmp(aux->nome,cname)==0){
      return 0;
    }
    aux = aux->next;
  }

  return 1;
}

//Função de verificação da existência de clientes
int Mostra_cliente(utent c1){
  utent aux;
  aux=c1;

  while(aux != NULL){

   printf("Nome: %s\n",aux->nome);
    aux = aux->next;
  }

  return 1;
}

//Função de escrita dos dados de cada cliente
utent criaCliente(utent c1, utent_t copia){
  utent novo;

  novo=malloc(sizeof(utent_t));

  if(novo==NULL){
    return NULL;
  }else{
    novo->pid_utent = copia.pid_utent;
    strcpy(novo->nome, copia.nome);
    strcpy(novo->palavra, copia.palavra);
    strcpy(novo->sint, copia.sint);
    novo->next= NULL;

    if(c1==NULL)
    c1 = novo;
    else
    { novo->next = c1;
      c1 = novo;
    }
  }
  if(c1!=NULL)
    fprintf(stderr,"\nCliente %s gravado\n", novo->nome);

  return c1;
}
