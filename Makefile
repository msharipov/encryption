encrypt: encrypt.c DES.h
	gcc -Wall -o encrypt.exe encrypt.c

DES_tests: DES_tests.c DES.h
	gcc -g -Wall -o DES_tests.exe DES_tests.c

enc_block: enc_block.c DES.h
	gcc -g -Wall -o enc_block.exe enc_block.c