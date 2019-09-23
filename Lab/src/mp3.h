/*
 * mp3.h
 *
 *  Created on: Sep 3, 2019
 *      Author: 25006
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef MP3_H_
#define MP3_H_

typedef struct mp3{
	char* name;
	char* title;
	int year;
	int runtime;
	struct mp3* next;
	struct mp3* prev;

}mp3_t;

// consumes: a mp3_t object
// if there is no mp3 in this list, the add this mp3 as a the head node
// else this will ad the mp3 to the end of the list
void push(mp3_t *cur);
// this function will consumes an author name and remove all mp3 whose authors are input parameter
void remove_by_name(char* name);
// this function consumes nothing and will print all the mp3 in the list from the beginning
void print_list();
// this funcions consumes nothing and will print the Mp3 list from the end
void print_end();
// this function consumes nothing and will create a mp3 object
// this functio will print several message prompt user to enter certain thing
mp3_t* makemp3();
// this is the Hash function that will convert the instruction of input to number
int myHash(char *str);
// this is the function that will eliminate all the memories that occupied by mp3s
void exit(int status);




#endif /* MP3_H_ */
