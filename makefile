all:
	gcc -g -Wall -o balcao balcao.c funcoes.c comuns.c
	gcc -g -Wall -o cliente cliente.c funcoes.c comuns.c
	gcc -g -Wall -o medico medico.c funcoes.c comuns.c
balcao:
	gcc -c balcao.c
cliente:
	gcc -c cliente.c
medico:
	gcc -c medico.c
comuns:
	gcc -c comuns.c
funcoes:
	gcc -c funcoes.c
clean:
	$(RM)balcao balcao.o
	$(RM)cliente cliente.o
	$(RM)medico medico.o
	$(RM)comuns comuns.o
	$(RM)funcoes funcoes.o
