#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
int map[40][120];

int sizeX = 90;
int sizeY = 20;
int score = 0;
int xFood = 4;
int yFood = 10;
typedef struct node{
	int x;
	int y;

	struct node *next;
}node;
node *head=NULL, *tail;
void createBody(int x, int y){
	snake *body = (snake *) malloc (sizeof(snake));
	body->x = x;
	body->y = y;
	if (!head){
		head = tail = body;
	}
	else{
		tail->next = body;
		tail = body;
	}
	tail->next = NULL;
}