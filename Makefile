encrypt: encrypt.c DES.h
	gcc -Wall -o encrypt.exe encrypt.c

DES_tests: DES_tests.c DES.h DES.c
	gcc -g -Wall -o DES_tests.exe DES_tests.c

polyalg_tests: polyalg_tests.c polyalg.h polyalg.c
	gcc -g -Wall -o polyalg_tests.exe polyalg_tests.c
