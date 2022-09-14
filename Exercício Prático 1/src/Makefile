all : programa

funcoesFornecidas.o : funcoesFornecidas.c
		gcc -o funcoesFornecidas.o -c funcoesFornecidas.c
		
funcoesComandos.o : funcoesComandos.c
		gcc -o funcoesComandos.o -c funcoesComandos.c

main.o : main.c 
		gcc -o main.o -c main.c

programa : funcoesFornecidas.o main.o funcoesComandos.o
		gcc -o programa funcoesFornecidas.o main.o funcoesComandos.o


run : programa
		./programa

clean : 
		rm -f *.o
		rm -f *programa