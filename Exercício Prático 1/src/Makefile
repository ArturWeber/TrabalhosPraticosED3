all : programa

funcoesPadrao.o : funcoesPadrao.c
		gcc -o funcoesPadrao.o -c funcoesPadrao.c

funcoesCustomizadas.o : funcoesCustomizadas.c
		gcc -o funcoesCustomizadas.o -c funcoesCustomizadas.c

main.o : main.c 
		gcc -o main.o -c main.c

programa : funcoesPadrao.o funcoesCustomizadas.o main.o
		gcc -o programa funcoesPadrao.o funcoesCustomizadas.o main.o


run : programa
		./programa

clean : 
		rm -f *.o
		rm -f *programa