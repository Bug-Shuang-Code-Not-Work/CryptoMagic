#
# this makefile will compile and and all source
# found in the ~/develop/cryptoMagic directory.  
# 
# 
# =======================================================
#               
# =======================================================
# FINAL BINARY Target
./bin/cryptoMagic : ./obj/main.o ./obj/functions.o
	cc ./obj/main.o ./obj/functions.o -o ./bin/cryptoMagic
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/main.o : ./src/main.c ./inc/crypto.h
	cc -c  ./src/main.c -o ./obj/main.o

./obj/functions.o : ./src/functions.c ./inc/crypto.h
	cc -c  ./src/functions.c -o ./obj/functions.o

#
# =======================================================
# Other Targets
# =======================================================                     
all : ./bin/cryptoMagic

clean :
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~

