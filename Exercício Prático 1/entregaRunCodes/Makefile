all : ./bin/programa

./obj/funcoesFornecidas.o : ./src/funcoesFornecidas.c
		gcc -o ./obj/funcoesFornecidas.o -c ./src/funcoesFornecidas.c
		
./obj/funcoesComandos.o : ./src/funcoesComandos.c
		gcc -o ./obj/funcoesComandos.o -c ./src/funcoesComandos.c

./obj/main.o : ./src/main.c 
		gcc -o ./obj/main.o -c ./src/main.c

./bin/programa : ./obj/funcoesFornecidas.o ./obj/main.o ./obj/funcoesComandos.o
		gcc -o ./bin/programa ./obj/funcoesFornecidas.o ./obj/main.o ./obj/funcoesComandos.o


run : ./bin/programa
		./bin/programa

clean : 
		rm -f ./obj/*.o
		rm -f ./bin/*programa
		rm -f ./file/*.bin
