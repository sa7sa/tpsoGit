/* Trabalho prático Sistemas Operativos */
/* Meta 1                               */
/* Celso Jordão, nº.2003008910          */
/* Fábio Campobianchi, nº.2018915299    */

#ifndef _FUNCOES_H
#define _FUNCOES_H
#include <signal.h>

void balcSigHandler(int sig);

void clienteSigHandler(int sigc);

void criaFIFO(char *fifo);

int openFIFO_rdwr(char *ofifo);

#endif /* _FUNCOES_H */
