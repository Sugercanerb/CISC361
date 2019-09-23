#Rubai Bian
#9/20/2019
default: mp3 

mp3: mp3.o main.c
	gcc main.c mp3.o -o mp3 -g
mp3.o: mp3.c mp3.h
	gcc -c mp3.c -o mp3.o -g
clean:
	rm *.