#pragma warning(disable : 4996)

#include"SFML/Window.h"
#include"SFML/Graphics.h"
#include"SFML/OpenGL.h"
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<stdio.h>
#include<string.h>



int c = 3;
int secret_code[3];
bool flag=true;
int guess[3];
int mat_no_mat[2] = { 0,0 };


void code_generator(int sec[3], int c, int size)
{
	for (int i = 0; i < size; i++)
	{
		sec[i] = (rand() % c) + 1;
	}

}

void print_sec(int size)
{
	for (int i = 0; i < size; i++)
	{
		printf(" %d", secret_code[i]);
	}
	printf("\n");
}

void input_from_user(int guess[3], int size)
{
	printf("This is the Input function.\n");
	printf("Enter the Number.\n");
	for (int i = 0; i < size; i++)
	{
		 scanf(" %d", &guess[i]);
	}

	
	printf("Your input is as follow.\n");
	for (int i = 0; i < size; i++)
	{
		printf(" %d", guess[i]);
	}
	printf("\n");
}


void check_code(int sec[3], int gu[3], int mn[2], int size)
{
	bool temp[3] = { 1,1,1 };
	bool temp1[3] = { 1 ,1,1 };
	mn[0] = 0;
	mn[1] = 0;


	for (int i = 0; i < size; i++)
	{
		if (sec[i] == gu[i])
		{
			temp[i] = 0;
			temp1[i] = 0;
			mn[0]++;
		}
	}

	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (sec[i] == gu[j] && i != j && temp[i] && temp1[j])
			{
				mn[1]++;
				temp[i] = 0;
				temp1[j] = 0;
			}
		}
	}

}

int main()
{
	sfVideoMode vm = { 500,300,32 };
	sfRenderWindow * win=sfRenderWindow_create(vm, "Master Mind Game",sfDefaultStyle,NULL);
	
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 50.0f);

	sfCircleShape* circle1 = sfCircleShape_create();
	sfCircleShape_setRadius(circle1, 50.0f);

	sfCircleShape* circle2 = sfCircleShape_create();
	sfCircleShape_setRadius(circle2, 50.0f);

	sfEvent ev;

	srand(time(0));
	/*printf("Enter the number of C in the game:");
	scanf(" %d", &c);*/
	code_generator(secret_code, c, 3);
	int i1 = 0;
	


	while (sfRenderWindow_isOpen(win))
	{
		
		while (sfRenderWindow_pollEvent(win, &ev))
		{
			if (ev.type == sfEvtClosed || flag==false)
			{
				sfRenderWindow_close(win);
			}
		}
		for (i1 = 0; i1 < 4; i1++)
		{
			input_from_user(guess, 3);
			check_code(secret_code, guess, mat_no_mat, 3);
			printf("Matching %d\n", mat_no_mat[0]);
			printf("Non Matching %d\n", mat_no_mat[1]);
			if (guess[0] == 1)
			{
				sfVector2f v1 = { 1,1 };
				sfCircleShape_setFillColor(circle, sfGreen);
				sfCircleShape_setPosition(circle, v1);
				sfRenderWindow_drawCircleShape(win, circle, NULL);
				//sfRenderWindow_display(win);
				
			}
			if (guess[1] == 2)
			{
				sfVector2f v2 = { 80,1 };
				sfCircleShape_setFillColor(circle1, sfBlue);
				sfCircleShape_setPosition(circle1, v2);
				sfRenderWindow_drawCircleShape(win, circle1, NULL);
				//sfRenderWindow_display(win);
				
				
			}
			if (guess[2] == 3)
			{
				sfVector2f v3 = {170,1};
				sfCircleShape_setFillColor(circle2, sfRed);
				sfCircleShape_setPosition(circle2, v3);
				sfRenderWindow_drawCircleShape(win, circle2, NULL);
			}

			sfRenderWindow_display(win);
		    if (mat_no_mat[0] == 3)
			{
				printf("Code Breker Wins the game.\n");
				flag = 0;
				break;
			}
			
		}

		if (i1 == 4 && flag != 0)
		{
			flag = 0;
			printf("You Lost the Game.\n");
			break;
		}

		sfRenderWindow_clear(win, sfColor_fromRGBA(1, 0, 0, 0));
		sfRenderWindow_display(win);
	}

	return 0;
}