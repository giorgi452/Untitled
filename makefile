all:
	gcc -c src/main.c
	gcc -c src/utils/utils.c
	gcc main.o utils.o -o main.exe
	rm -rf main.o utils.o
