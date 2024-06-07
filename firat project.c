#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

typedef struct snake{
	int x;
	int y;
	struct snake *next;
}node;
 node *head, *tail;

int pos[100][200];

int X = 75;
int Y = 25;
int score = 0;
int fx = 4;
int fy = 10;

void snakebody(int x, int y){
	node *body = (node *) malloc (sizeof(node));
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

void gotoxy(int x, int y){
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void createboundary(){
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			if (i == 0 || i == Y - 1 || j == 0 || j == X - 1)
                pos[i][j] = 1;
			else
                pos[i][j] = 0;
		}
	}
	pos[fy][fx] = 3;
}

void fruit(){
	srand(time(NULL));
	pos[fy][fx] = 0;
	do{
		fx = rand() % (X - 1) + 1;
		fy = rand() % (Y - 1) + 1;
	} while (pos[fy][fx] != 0);
	pos[fy][fx] = 3;
	gotoxy(fx, fy);
	printf("*");
}

void printboundary(){
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			if (pos[i][j] == 1) printf("#");
			else if (pos[i][j] == 3) printf("*");
			else printf(" ");
		}
		puts("");
	}
}

int run(int x, int y){
	node *cur = head;
	int h;
	int k;
	int temp_x;
	int temp_y;
	while (cur){		
		if (cur == head){
			pos[cur->y][cur->x] = 0;
			if (head->x == fx && head->y == fy){
				int newX = tail->x - x;
				int newY = tail->y - y;
				snakebody(newX, newY);
				score += 10;
				fruit();
			}
            if(head->x + x < 1 || head->x + x > X - 2 || head->y + y < 1 || head->y + y > Y - 2)
				return 0;
			gotoxy(cur->x, cur->y);
			printf(" ");
			h = cur->x;
			k = cur->y;
			cur->x = cur->x + x;
			cur->y = cur->y + y;		
		} else{
			pos[cur->y][cur->x] = 0;
			gotoxy(cur->x, cur->y);
			printf(" ");
			temp_x = h;
			temp_y = k;
            h=cur->x;
            k=cur->y;
			cur->x = temp_x;
			cur->y = temp_y;
		}
		pos[cur->y][cur->x] = 2;
		gotoxy(cur->x, cur->y);
		printf("$");
		cur = cur->next;
	}
	return 1;
}

void play(){
	int direction = 4;
	boolean walk = TRUE;
	int speed;
	score = 0;
	while(walk){
		if(score>50)
            speed=100;
		else if(score<100) 
            speed=80;
		else 
            speed=150;
		
		if (kbhit()){
			switch(getch()){
			case 'w':
				if (direction != 3) 
                    direction = 1;
				if(direction==1)
                    speed/=4;
				break;
			case 'a':
				if (direction != 4) 
                    direction = 2;
				if(direction==2)
                    speed/=8;
				break;
			case 's':
				if (direction != 1) 
                    direction = 3;
				if(direction==3)
                    speed/=4;
				break;
			case 'd':
				if (direction != 2) 
                    direction = 4;
				if(direction==4)
                    speed/=8;
				break;
			}
		}

		switch(direction){
		case 1:
			walk = run(0, -1);
			break;
		case 2:
			walk = run(-1, 0);
			break;
		case 3:
			walk = run(0, 1);
			break;
		case 4:
			walk = run(1, 0);
			break;
		}

		gotoxy(2, Y + 4);
		printf("Score : %d", score);

		Sleep(speed);
	}
}
void deleteall(){
	while(head!=NULL){
		node *cur=head;
		head=head->next;
		free(cur);
	}
}

int main(){
	int a=0;
    int i,j;
	while(a!=2){
		system("cls");
        printf("\t\t-----------SNAKE GAME-----------\n");
        printf("\t\t---Rules ot the game---\n\t\t1.Collect as many fruits as possible\n");
        printf("\t\t2.Avoid hitting the wall\n\t\t3.Do not colide with the snake body\n");
        printf("\t\t4.For moving the snake use\n\t\ti.UP->'w'\n\t\tii.DOWN->'s'\n\t\tiii.LEFT->'d'\n\t\tiv.RIGHT->'a'\n");
        printf("\t\tPress 1 if you wish to play\n");
		printf("\t\t1.play\n\t\t2.exit\n"); 
		scanf("%d",&a);
		if(a==1){
			system("cls");
			snakebody(35,12);
			createboundary();
			printboundary();
			play();
            gotoxy(30,10);
			printf("GAME OVER!!!!\n");
            gotoxy(30,12);
            printf("YOUR SCORE=%d",score);
            deleteall();
            sleep(1000);
		}
	}
    for(i=0;i<Y;i++)
        for(j=0;j<X;j++)
            pos[i][j]=0;
	return 0;
}