encrypt: encrypt.c DES.h
	gcc -Wall -o encrypt encrypt.c

DES_tests: tests/DES_tests.c DES.h DES.c
	gcc -g -Wall -o tests/DES tests/DES_tests.c

polyalg_tests: tests/polyalg_tests.c polyalg.h polyalg.c
	gcc -g -Wall -o tests/polyalg tests/polyalg_tests.c

tests: DES_tests polyalg_tests
