/*
 * mp3.c
 *
 *  Created on: Sep 3, 2019
 *      Author: 25006
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#define MAX_LIMIT 128

// use to record the head of the list of mp3
mp3_t* head = NULL;

// consumes: a mp3_t object
// if there is no mp3 in this list, the add this mp3 as a the head node
// else this will ad the mp3 to the end of the list
void push(mp3_t* cur)
{
	if(head == NULL)
		head = cur;
	else
	{
		mp3_t* tmp = head;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}

		tmp->next = cur;
		cur->prev = tmp;
	}

}

// this function consumes nothing and will print all the mp3 in the list from the beginning
void print_list()
{
	mp3_t* cur = head;

	while(cur != NULL)
	{
		printf("name is [%s]\n", cur->name);
		printf("title is [%s]\n", cur->title);
		printf("published in [%d]\n", cur->year);
		printf("runtime: [%d]\n", cur->runtime);
		cur = cur->next;
	}
}

// this function will consumes an author name and remove all mp3 whose authors are input parameter
void remove_by_name(char* name)
{
	mp3_t* cur = head;
	while(cur != NULL)
	{
		mp3_t* tmp;
		if(strcmp(cur->name, name) == 0)
		{
			if(cur->prev == NULL)
			{
				if(cur->next != NULL)
					cur->next->prev = cur->prev;
				head = cur->next;
			}
			else
			{
				cur->prev->next = cur->next;
				if(cur->next != NULL)
					cur->next->prev = cur->prev;
			}
			tmp = cur->next;
			free(cur);
			cur = tmp;
		}
		else
		{
			cur = cur->next;
		}
	}

}

// this funcions consumes nothing and will print the Mp3 list from the end
void print_end()
{
	mp3_t* cur = head;

	while(cur->next != NULL)
	{
		cur = cur->next;
	}

	while(cur != NULL)
	{
		printf("name is [%s]\n", cur->name);
		printf("title is [%s]\n", cur->title);
		printf("published in [%d]\n", cur->year);
		printf("runtime: [%d]\n", cur->runtime);
		cur = cur->prev;
	}
}

// this is the Hash function that will convert the instruction of input to number
int myHash(char *str)
{
	if(strcmp("add", str) == 0)
		return 1;
	else if(strcmp(str, "delete") == 0)
		return 2;
	else if(strcmp(str, "print_beg") == 0)
		return 3;
	else if(strcmp(str, "print_end") == 0)
		return 4;
	else if(strcmp(str, "exit") == 0)
		return 5;
	else
		return 0;
}

// this function consumes nothing and will create a mp3 object
// this functio will print several message prompt user to enter certain thing
mp3_t* makemp3()
{
	char str[MAX_LIMIT];
	int tmp;
	mp3_t *mp3;
	mp3 = (mp3_t*) malloc(sizeof(mp3_t));
	int len;
	printf("enter a name \n");
	if(fgets(str, MAX_LIMIT, stdin) != NULL)
	{
		len = (int) strlen(str);
		str[len - 1] = '\0';
		mp3->name = (char*) malloc(len);
		strcpy(mp3->name, str);
	}

	printf("enter a title \n");
	if(fgets(str, MAX_LIMIT, stdin) != NULL)
	{
		len = (int) strlen(str);
		str[len -1] ='\0';
		mp3->title = (char*) malloc(len);
		strcpy(mp3->title, str);
	}
	printf("enter a year \n");
	if(scanf("%d", &tmp) != 0)
	{
		mp3->year = tmp;
	}
	printf("enter a runtime \n");
	if(scanf("%d", &tmp) != 0)
	{
		mp3->runtime = tmp;
	}
	mp3->next = NULL;
	mp3->prev = NULL;


	return mp3;
}


// this is the function that will eliminate all the memories that occupied by mp3s
void exit(int status)
{
	if(status == 5){
	mp3_t* cur = head;
	mp3_t* tmp;
	while(cur != NULL)
	{
		tmp = cur->next;
		free(cur->name);
		free(cur->title);
		free(cur);
		cur = tmp;
	}
	}
}

