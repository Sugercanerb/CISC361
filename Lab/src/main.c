/*
 * main.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: 25006
 */

#include <stdio.h>
#include "mp3.h"

#define BUFFERSIZE 128

int main (int argc, char *argv[])
{
//	mp3_t *mp3 = (mp3_t*) malloc(sizeof(mp3_t));;
//
//	printf("enter a name");
//	fgets(name, 128 , stdin);
//	printf("enter a title");
//	fgets(title, 128, stdin);
//	scanf("%d", &year);
//	scanf("%d", &runtime);
//	mp3 = makemp3(name, title, year, runtime);
//	print_list(mp3);

//	mp3_t *mp3 = (mp3_t*) malloc(sizeof(mp3_t));
//	mp3 = makemp3("adad", "daad",2, 2);
//	mp3_t *mp2 = makemp3("mp3", "mp3", 2, 2);
//	mp3_t *mp4 = makemp3("mp3", "mp3", 2, 2);
//	mp3_t *mp5 = makemp3("mp3", "mp3", 2, 2);
//	mp3_t *mp6 = makemp3("mp3", "mp3", 2, 2);
//	mp3_t *mp7 = makemp3("mp3", "mp3", 2, 2);
//	mp3_t *mp8 = makemp3("mp3", "mp3", 2, 2);
//	push(mp3);
//	push(mp2);
//	push(mp4);
//	push(mp5);
//	push(mp6);
//	push(mp7);
//	push(mp8);
//	//remove_by_name("mp3");
//	print_list(mp3);
	printf("1 ----add-----\n2----delete----\n3 ----print_beg----\n4 ----print_end----\n5 ----exit----\n");
	char instruction[BUFFERSIZE];
	int c = 0;
	do
	{
		fgets(instruction, BUFFERSIZE, stdin);
		instruction[(int) strlen(instruction) - 1] = '\0';
		c = myHash(instruction);
		switch(c)
		{

			default:
				printf("1 ----add-----\n2----delete----\n3 ----print_beg----\n4 ----print_end----\n ----exit----\n");
				break;
			case 1:
				printf("--------------you are creating a mp3----------------\n");
				push(makemp3());
				break;
			case 2:
				printf("--------------enter the name of mp3 you are going to delete-------------\n");
				int l;
				char cur[128];
				fgets(cur, 128, stdin);
				l = (int) strlen(cur);
				cur[l - 1] = '\0';
				remove_by_name(cur);
				break;
			case 3:
				printf("--------------you are printing the mp3s from beginning--------------\n");
				print_list();
				break;
			case 4:
				printf("--------------you are printing the mp3s from the end\n");
				print_end();
				break;
			case 5:
				printf("--------------you are exiting the program--------------");
				exit(5);
				break;
		}
	}while(c != 5);


}

