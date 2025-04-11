//============================================================================
// Name        : Awais ali
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of snake...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>
// #include<cstdlib>
#include <ctime>
#include <fstream>
#include <string>
// #include<sys/wait.h>
// #include<stdlib.h>
// #include<stdio.h>
#include <unistd.h>
#include <sstream>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 650, 0, 680, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int s_len = 3;
int snake_dir = 1;

int i = 0;
int mx[5];
int my[5];
int food_size = 5;
int highS = 0;
// int mx1;
// int my1;
bool meal[] = {true, true, true, true, true};
// bool meal1=true;
int score = 0;
int Display1 = 1;
bool gameover = false;
bool pow1 = false;
int count_time1 = 0;
int count_time2 = 0;
int r;
int a = 0;
int x_cir=-500;
int y_cir=-500;
int x_cord[60] = {263, 275, 300};
int y_cord[60] = {312, 300, 300};
int hurd_x1[] = {29, 79, 129, 179, 229, 279, 329, 379, 429, 479, 529, 579, 629, 25, 75, 125, 175, 225, 275, 325, 375, 425, 100, 125, 275};
int hurd_y1[] = {25, 75, 125, 175, 225, 275, 325, 175, 75, 25, 225, 425, 125, 45, 95, 145, 195, 245, 295, 345, 395, 445, 495, 545, 595};
int hurd_x2[] = {29, 79, 129, 179, 229, 279, 329, 379, 429, 479, 529, 579, 629, 600, 350, 425, 400, 375, 425, 525, 625, 550, 325, 425,475};
int hurd_y2[] = {325, 275, 400, 425, 325, 375, 525, 550, 300, 275, 425, 500, 325, 45, 95, 145, 195, 245, 295, 345, 395, 445, 495, 545,595};
bool hurdle = true;
void print_s()
{
	for (int i = s_len - 1; i > 0; i--)
	{
		if (snake_dir == 1)
		{
			x_cord[i] = x_cord[i - 1];
			y_cord[i] = y_cord[i - 1];
			if (i == 1)
			{
				x_cord[i] = x_cord[i - 1] - 13;
				y_cord[i] = y_cord[i - 1] - 13;
			}
			
		}
		if (snake_dir == 2)
		{
			x_cord[i] = x_cord[i - 1];
			y_cord[i] = y_cord[i - 1];
			if (i == 1)
			{
				x_cord[i] = x_cord[i - 1] - 13;
				y_cord[i] = y_cord[i - 1] - 13;
			}
			
		}
		if (snake_dir == 3)
		{
			x_cord[i] = x_cord[i - 1];
			y_cord[i] = y_cord[i - 1];
			if (i == 1)
			{
				x_cord[i] = x_cord[i - 1] - 13;
				y_cord[i] = y_cord[i - 1] - 13;
			}
			
		}
		if (snake_dir == 4)
		{
			x_cord[i] = x_cord[i - 1];
			y_cord[i] = y_cord[i - 1];
			if (i == 1)
			{
				x_cord[i] = x_cord[i - 1] - 13;
				y_cord[i] = y_cord[i - 1] - 13;
			}
		}
	}

	if (snake_dir == 1)
		x_cord[0] -= 25;
	else if (snake_dir == 2)
		x_cord[0] += 25;
	else if (snake_dir == 3)
		y_cord[0] += 25;
	else if (snake_dir == 4)
		y_cord[0] -= 25;

	for (int j = 0; j < s_len; j++)
	{
		if (j == 0)
			DrawCircle(x_cord[j], y_cord[j], 12, colors[5]);
		else
			DrawSquare(x_cord[j], y_cord[j], 25, colors[BLUE]);
	}

	for (int n = 0; n < food_size; n++)
	{
		if (x_cord[0] == (mx[n] + 13) && y_cord[0] == (my[n] + 12))
		{
			if (s_len <= 60)
				s_len++;

			score += 5;
			// score_string = score_string + to_string(score);
			meal[n] = true;
		}
	}

	for (int i = 1; i < s_len; i++)
	{
		if ((x_cord[0] == x_cord[i] + 13) && (y_cord[0] == y_cord[i] + 13))
			gameover = true;
	}

	if (r <= 12)
	{
		if (((x_cord[0] == hurd_x1[r] + 9) && (y_cord[0] == hurd_y1[r] + 12)) || ((x_cord[0] == hurd_x2[r] + 9) && (y_cord[0] + 13 == hurd_y2[r])) || ((x_cord[0] == hurd_x2[r] + 9) && ((y_cord[0] + 13 <= hurd_y2[r]) && (y_cord[0] + 13 >= hurd_y1[r]))))
			gameover = true;
	}
	if (r > 12)
	{
		if ((((x_cord[0] - 13) == hurd_x1[r]) && (y_cord[0] == hurd_y1[r] - 8)) || ((x_cord[0] == hurd_x2[r] - 12) && (y_cord[0] == hurd_y2[r] - 8)) || (((x_cord[0] >= hurd_x1[r]) && (x_cord[0] <= hurd_x2[r])) && (y_cord[0] == hurd_y2[r] - 8)))
			gameover = true;
	}

	if ((x_cord[0] == -12))
	{
		x_cord[0] = 638;
	}
	else if ((x_cord[0] == 663))
	{
		x_cord[0] = -12;
	}
	else if ((y_cord[0] == -13))
	{
		y_cord[0] = 637;
	}
	else if ((y_cord[0] == 662))
	{
		y_cord[0] = -13;
	}

	if (((x_cord[0] == (x_cir + 13)) || ((x_cord[0]) == (x_cir + 38))) && ((y_cord[0] == (y_cir + 12)) || (y_cord[0] == (y_cir + 37))))
	{

		score += 20;
		pow1 = true;
	}
}

void hurd()
{
	// DrawLine( hurd_x1[5] , hurd_y1[5],  hurd_x2[5] , hurd_y2[5] , 20, colors[YELLOW]);
	//if (hurdle)
	//{ // DrawLine( hurd_x1[0] , hurd_y1[0],  hurd_x2[0] , hurd_y2[0] , 20, colors[YELLOW]
		if(count_time1%112==0)
		hurd_pos(r);
		
		for (int i = 0; i < 5; i++)
		{
			if ((hurd_x1[r] != mx[i]) && (hurd_y1[r] != my[i]) && (hurd_x2[r] != mx[i]) && (hurd_y2[r] != my[i]))
			{
				for (int m = 1; m < s_len; m++)
				{
					if ((hurd_x1[r] != x_cord[m]) && (hurd_y1[r] != y_cord[m]) && (hurd_x2[r] != x_cord[m]) && (hurd_y2[r] != y_cord[m]))
					{

					if (r <= 12)

					{
						DrawLine(hurd_x1[r], hurd_y1[r], hurd_x2[r], hurd_y2[r], 20, colors[YELLOW]);
						DrawLine(hurd_x1[r] + 6, hurd_y1[r], hurd_x2[r] + 6, hurd_y2[r], 20, colors[YELLOW]);
						DrawLine(hurd_x1[r] + 12, hurd_y1[r], hurd_x2[r] + 12, hurd_y2[r], 20, colors[YELLOW]);
						DrawLine(hurd_x1[r] + 18, hurd_y1[r], hurd_x2[r] + 18, hurd_y2[r], 20, colors[YELLOW]);
						
					}
					else
					{
						DrawLine(hurd_x1[r], hurd_y1[r], hurd_x2[r], hurd_y2[r], 20, colors[YELLOW]);
						DrawLine(hurd_x1[r], hurd_y1[r] - 6, hurd_x2[r], hurd_y2[r] - 6, 20, colors[YELLOW]);
						DrawLine(hurd_x1[r], hurd_y1[r] - 12, hurd_x2[r], hurd_y2[r] - 12, 20, colors[YELLOW]);
						DrawLine(hurd_x1[r], hurd_y1[r] - 18, hurd_x2[r], hurd_y2[r] - 18, 20, colors[YELLOW]);
					}
					}
				}
			}
		
		}
		
	//}

	
	
	
	
	
}
void hurd_pos(int &rm)
{
	srand(time(0));
	rm = rand() % 26;
}

void power()
{
	
	if(pow1)
	{	x_cir=-500,y_cir=-500;
		pow1=false;
	}
		if(count_time2%224==0)
		rando(x_cir, y_cir);
		
		
	if(count_time2==224)
	{
		count_time2=0;
	}
	
	for (int i = 0; i < 5; i++)
	{
		if ((x_cir != mx[i]) && (y_cir != my[i]))
			if(count_time2<=56)
			DrawSquare(x_cir, y_cir, 50, colors[BLACK]);
	}
	for (int i = 1; i <s_len; i++)
	{
		if (((x_cir != x_cord[i]) && (y_cir != y_cord[i]))||((x_cir+25 != x_cord[i]) && (y_cir != y_cord[i]))||((x_cir != x_cord[i]) && (y_cir+25 != y_cord[i]))||((x_cir+25 != x_cord[i]) && (y_cir+25 != y_cord[i])))
			if(count_time2<=56)
			DrawSquare(x_cir, y_cir, 50, colors[BLACK]);
	}
	
}
void rando(int &a, int &b)
{
	srand(time(0));

	a = 25 + (rand() % 24) * 25;
	b = 25 + (rand() % 24) * 25;
}

void food()
{
	
	for (int z = 0; z < food_size; z++)
	{
		srand(time(0));
		if (meal[z])
		{

			int count = 1;
			while (count != 0)
			{
				count = 0;
				cout << "Meal " << z + 1 << " x = " << mx[z] << " y = " << my[z] << endl;

				mx[z] = 25 + (rand() % 25) * 25;
				my[z] = 25 + (rand() % 25) * 25;
				for (int i = 1; i < s_len; i++)
				{
					if (((mx[0] != x_cord[i]) && (my[0] != y_cord[i])) || ((mx[1] != x_cord[i]) && (my[1] != y_cord[i])) || ((mx[2] != x_cord[i]) && (my[2] != y_cord[i])) || ((mx[3] != x_cord[i]) && (my[4] != y_cord[i])) || ((mx[4] != x_cord[i]) && (my[4] != y_cord[i])))
				{	mx[z] = 25 + (rand() % 25) * 25;
					my[z] = 25 + (rand() % 25) * 25;
				}
				}

				if (z == 0 && ((mx[0] == mx[4]) || (mx[0] == mx[3]) || (mx[0] == mx[2]) || (mx[0] == mx[1])))
				{

					count++;
				}
				if (z == 1 && ((mx[1] == mx[4]) || (mx[1] == mx[3]) || (mx[1] == mx[2]) || (mx[1] == mx[0])))
				{

					count++;
				}

				if (z == 2 && ((mx[2] == mx[4]) || (mx[2] == mx[3]) || (mx[2] == mx[1]) || (mx[2] == mx[0])))
				{

					count++;
				}
				if (z == 3 && ((mx[3] == mx[4]) || (mx[3] == mx[2]) || (mx[3] == mx[1]) || (mx[3] == mx[0])))
				{

					count++;
				}
				if (z == 4 && ((mx[4] == mx[3]) || (mx[4] == mx[2]) || (mx[4] == mx[1]) || (mx[4] == mx[0])))
				{

					count++;
				}
				if (z == 0 && ((mx[0] == mx[4]) || (mx[0] == mx[3]) || (mx[0] == mx[2]) || (mx[0] == mx[1])))
				{

					count++;
				}
				if (z == 0 && ((my[0] == my[4]) || (my[0] == my[3]) || (my[0] == my[2]) || (my[0] == my[1])))
				{

					count++;
				}
				if (z == 1 && ((my[1] == my[4]) || (my[1] == my[3]) || (my[1] == my[2]) || (my[1] == my[0])))
				{

					count++;
				}

				if (z == 2 && ((my[2] == my[4]) || (my[2] == my[3]) || (my[2] == my[1]) || (my[2] == my[0])))
				{

					count++;
				}
				if (z == 3 && ((my[3] == my[4]) || (my[3] == my[2]) || (my[3] == my[1]) || (my[3] == my[0])))
				{

					count++;
				}
				if (z == 4 && ((my[4] == my[3]) || (my[4] == my[2]) || (my[4] == my[1]) || (my[4] == my[0])))
				{

					count++;
				}
				if (z == 0 && ((my[0] == my[4]) || (my[0] == my[3]) || (my[0] == my[2]) || (my[0] == my[1])))
				{

					count++;
				}
				if (z == 0 && ((mx[0] == my[0]) || (mx[0] == my[1]) || (mx[0] == my[2]) || (mx[0] == my[3]) || (mx[0] == my[4])))
				{

					count++;
				}
				if (z == 1 && ((mx[1] == my[2]) || (mx[1] == my[3]) || (mx[1] == my[4])))
				{

					count++;
				}

				if (z == 2 && ((mx[2] == my[3]) || (mx[2] == my[4])))
				{

					count++;
				}
				if (z == 3 && ((mx[3] == my[4])))
				{

					count++;
				}

				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (mx[i] + my[j] == 625)
							count++;
					}
				}
			}
			meal[z] = false;
		}
	}
	
		for (int i = 0; i<5; i++)
		{
			
			DrawSquare(mx[i], my[i], 25, colors[RED]);
			if(count_time1%56==0)
			{meal[i] = true;}
		}
}
	

	
double startx = 320, starty = 400;

void Display()
{
	// set the background color using function glClearColotgr.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0 /*Red Component*/, 0.0 /*Green Component*/,
				 0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);	
	
	if (Display1 == 1)
	{
		DrawString(50, 525, "Start Game", colors[YELLOW] );
		DrawString(50, 475, "Resume Game", colors[YELLOW] );
		DrawString(50, 405, "Change Level", colors[YELLOW] );
		DrawString(50, 335, "High Score", colors[YELLOW] );
		DrawString(50, 280, "Game History", colors[YELLOW] );
		DrawString(50, 180, "Exit", colors[YELLOW] );
	}
	
	if (Display1 == 2)
	{
		// This will draw a square shape of size 100x100  at x=300 and y=300
	// This will draw a circle at x=200,y=200 of radius 50
	// FOR printing the grid;
	
	//cout << "count is" << count_time1;
	int arr1[26];
	int arr2[26];
	int squaresize = 25;
	int i = 0;
	int j = 0;
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			DrawSquare(i * squaresize, j * squaresize, 25, colors[GREEN]);
		}
		cout << endl;
	}

	if(gameover==false)
	{
		print_s();
	}
	food();
	
	hurd();
	
	
	power();
	// score_string = score_string + to_string(score);
	// food1();
	// DrawString( 50, 600, "Score=",to_string(score), colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
	DrawString(50, 658, "Score=", colors[MISTY_ROSE]);
	DrawString(130, 658, to_string(score), colors[MISTY_ROSE]);
	// DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570

	

	if (gameover)
	{
		int a = 0;
		ifstream var;
		var.open("high.txt");
		var >> a;
		var.close();

		if (score > a)
		{
			ofstream var;
			var.open("high.txt");
			var << score;
			var.close();
		}
		DrawSquare(0,0, 20000, colors[BLACK]);
		
		DrawString(220, 458, "GAME OVER", colors[BLUE]);
		DrawString(200, 398, "Your score is=", colors[BLUE]);
		DrawString(350, 398, to_string(score), colors[RED]);
		
		
		DrawString(220, 458, "GAME OVER", colors[BLUE]);
		if(score>=a)
		{ 
			DrawString(29, 350, "YOU HAVE BROKEN ALL THE PREVIOUS RECORDS", colors[YELLOW]);
			DrawString(29, 330, "AND YOUR CURRENT SCORE=", colors[YELLOW]);
			DrawString(390, 330, to_string(score), colors[RED]);
		}
	}
	}
	
	if (Display1 == 3)
	{
	int arr1[26];
	int arr2[26];
	int squaresize = 25;
	int i = 0;
	int j = 0;
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			DrawSquare(i * squaresize, j * squaresize, 25, colors[GREEN]);
		}
		cout << endl;
	}

	if(gameover==false)
	{
		print_s();
	}
	food();
	
	
	power();
	// score_string = score_string + to_string(score);
	// food1();
	// DrawString( 50, 600, "Score=",to_string(score), colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
	DrawString(50, 658, "Score=", colors[MISTY_ROSE]);
	DrawString(130, 658, to_string(score), colors[MISTY_ROSE]);
	// DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570

	

	if (gameover)
	{
		
		ifstream var;
		var.open("high.txt");
		var >> a;
		var.close();

		if (score > a)
		{
			ofstream var;
			var.open("high.txt");
			var << score;
			var.close();
		}
		DrawSquare(0,0, 20000, colors[BLACK]);
		
		DrawString(220, 458, "GAME OVER", colors[BLUE]);
		DrawString(200, 398, "Your score is=", colors[BLUE]);
		DrawString(350, 398, to_string(score), colors[RED]);
		
		DrawString(220, 458, "GAME OVER", colors[BLUE]);
		if(score>=a)
		{ 
			DrawString(29, 350, "YOU HAVE BROKEN ALL THE PREVIOUS RECORDS", colors[YELLOW]);
			DrawString(29, 330, "AND YOUR CURRENT SCORE=", colors[YELLOW]);
			DrawString(390, 330, to_string(score), colors[RED]);
		}
	}
	}	
	if (Display1 == 4)
	{	
		DrawString(150, 398,"The highest score is =", colors[YELLOW]);	
		DrawString(380, 398, to_string(a), colors[YELLOW]);
	}
	if (Display1 == 5)
	{	
		DrawString(150, 498,"Mati Ur_Rehman = 140", colors[YELLOW]);	
		DrawString(150, 398,"Umer Minhaas = 145", colors[YELLOW]);
		DrawString(150, 298,"Zakrya = 180", colors[YELLOW]);
		DrawString(150, 198,"Awais Ali = 500", colors[YELLOW]);			
	}
	if (Display1 == 6)
	{
		exit(1);
	}
	
	glutSwapBuffers(); // do not modify this line..
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		if (snake_dir != 2)
		{
			snake_dir = 1;
		}
		// what to do when left key is pressed...
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
		if (snake_dir != 1)
		{
			snake_dir = 2;
		}
	}
	else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
	{

		if (snake_dir != 4)
		{
			snake_dir = 3;
		}
	}
	else if (key == GLUT_KEY_DOWN) /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
	{
		if (snake_dir != 3)
		{
			snake_dir = 4;
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == KEY_ESC /* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'A' || key == 'a' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 = 2;
		}
	}
	if (key == 'B' || key == 'b' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 =2 ;
		}
	}
	if (key == 'C' || key == 'c' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 =3 ;
		}
	}
	if (key == 'D' || key == 'd' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 =4 ;
		}
	}
	if (key == 'E' || key == 'e' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 =5 ;
		}
	}
	if (key == 'F' || key == 'f' /* Escape key ASCII*/)
	{
		if(Display1 == 1)
		{
			Display1 =6 ;
		}
	}
	if (key == 'G' || key == 'g' /* Escape key ASCII*/)
	{
		if(Display1 == 2)
		{
			Display1 =2 ;
		}
	}
	if (key == 'z' || key == 'Z' /* Escape key ASCII*/)
	{
		if(Display1 == 2)
		{
			exit(1);
		}
	}
	
	
	else if (int(key) == 13)
	{
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m)
{
	count_time1++;
	count_time2++;
	glutPostRedisplay();
	// implement your functionality here
	
	glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{
	srand(time(0));
	int width = 650, height = 680; // i have set my window size to be 800 x 600
	InitRandomizer();			   // seed the random number generator...
	glutInit(&argc, argv);		   // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50);				  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("PF's Snake Game");		  // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display);		   // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
									   // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(5.0 / FPS, Timer, 0);
	// glutTimerFunc(15000.0 / FPS, food, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Snake Game */
