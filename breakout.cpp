/*
	Names:		Alven Diaz
				Edgar Buenrostro
				Marvin Becerra
				Allison Escobar
	Date: 		April 2, 2010
	FileName:	breakout.cpp
	Description:	Breakout in OpenGL for CS335
*/

#define LEFT_KEY 97	/* A key */
#define RIGHT_KEY 100	/* D key */
#define UP_KEY 119	/* W key */
#define DOWN_KEY 115	/* S key */

#define P_KEY 101
#define Q_KEY 113	/* Q key */
#define ASCII_ESC 27	/* ESC key */

#define WIDTH 1200	/* Width of our playing field */
#define HEIGHT 600	/* Height of our playing field */

/* Our menu objects */
#define NEWGAME 0
#define MAIN_MENU 1
#define EXITGAME 2
#define PAUSE_GAME 3
#define CREDITS 4
#define HIGH_SCORES 5

/* Game States */
#define GAME_PLAY 0
#define GAME_PAUSED 1
#define GAME_OVER 2
#define GAME_MENU 3
#define GAME_HS 4

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "Ball.h"	
#include "Paddle.h"
#include "Lives.h"
#include "Score.h"
#include "BrickManager.h"
#include "Timer.h"
using namespace std;

Lives lives;
Score score;
Timer timer;
Paddle player;
Ball ball;
BrickManager brickmanager;

int pMenu, mMenu, sMenu, gameTime;

static int gameState = 0;

static int top[5] = { 0, 0, 0, 0, 0 };
char buf[5];

void resetGame()
{
	gameTime = glutGet(GLUT_ELAPSED_TIME);
	brickmanager.InitializeLevel();
	score.resetScore();
	lives.resetLives();
	lives.setLives(5);
	ball.ResetBall();
	player.ResetPaddle();
	gameState = GAME_PLAY;
}

void getScores()
{
	ifstream inFile;
	int i = 0;
	
	inFile.open("top5Scores.txt");
	
	if( !inFile )
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);			
	}
	
	inFile >> top[i];
	
	while( !inFile.eof() )
	{
		i++;
		inFile >> top[i];
	}
	
	inFile.close();
}

void renderStrokeFontString(float x,float y,float z,float size, char *string) 
{  
	y = -y;
	char *c;
	glScalef(size, -size, size);
	glPushMatrix();
	glTranslatef(x/size, y/size, z);
	for (c = string; *c != '\0'; c++) 
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
	glScalef(size, -size, size );//this flips it, so letters aren't upside down.
}

void specialKeyboardPress( int key, int x, int y )
{
	switch(key)
	{
		case GLUT_KEY_UP:
		{
			if( ( player.GetY() - player.GetHeight() ) <= 0 )
				player.SetY( 0.0 + player.GetHeight() );
			else
				player.SetY( player.GetY() - player.GetSpeed() );
			break;				
		}
		case GLUT_KEY_DOWN:
		{
			if( ( player.GetY() + player.GetHeight() ) >= HEIGHT )
				player.SetY( HEIGHT - player.GetHeight() );
			else
				player.SetY( player.GetY() + player.GetSpeed() );
			break;
		}
		case GLUT_KEY_LEFT:
		{
			if( ( player.GetX() - player.GetWidth() ) <= 0 )
				player.SetX( 0.0 + player.GetWidth() );
			else
				player.SetX( player.GetX() - player.GetSpeed()  );
			break;		
		}
		case GLUT_KEY_RIGHT:
		{
			if( ( player.GetX() + player.GetWidth() ) >= WIDTH )
				player.SetX( WIDTH - player.GetWidth() );
			else
				player.SetX( player.GetX() + player.GetSpeed()  );
			break;		
		}
	}
}

/* Keyboard hit detection 
   format: key press, mouse coordinates */
void keyboardPress( unsigned char key, int x, int y )
{
	switch(key)
	{
		case ASCII_ESC:		/* Escape key */
		{
			exit(0);	/* Terminate program */
			break;
		}
		case Q_KEY:		/* Q key */
		{
			exit(0);	/* Terminate program */
			break;
		}
		case UP_KEY:
		{
			if( ( player.GetY() - player.GetHeight() ) <= 0 )
				player.SetY( 0.0 + player.GetHeight() );
			else
				player.SetY( player.GetY() - player.GetSpeed() );
			break;			
		}
		case DOWN_KEY:
		{
			if( ( player.GetY() + player.GetHeight() ) >= HEIGHT )
				player.SetY( HEIGHT - player.GetHeight() );
			else
				player.SetY( player.GetY() + player.GetSpeed() );
			break;
		}
		case LEFT_KEY:
		{
			if( ( player.GetX() - player.GetWidth() ) <= 0 )
				player.SetX( 0.0 + player.GetWidth() );
			else
				player.SetX( player.GetX() - player.GetSpeed()  );
			break;
		}
		case RIGHT_KEY:
		{
			if( ( player.GetX() + player.GetWidth() ) >= WIDTH )
				player.SetX( WIDTH - player.GetWidth() );
			else
				player.SetX( player.GetX() + player.GetSpeed()  );
			break;
		}
		case P_KEY:
		{
			if(gameState != GAME_PAUSED)
				gameState = GAME_PAUSED;
			else
				gameState = GAME_PLAY;
		}
	}
}



/* Initialize our 3D rendering */
void initRendering()
{
	/* Disable 3D rendering */
	glDisable(GL_DEPTH_TEST);
}

/* Allows us to resize our window */
void resizeWindow( int w, int h )
{
	/* Set our viewport.
	   - x,y 		-> specify the lower left corner of the 
				viewport rectangle, in pixels
	   - width, height 	-> specify the width and height of the 
				viewport, dimensions of window */
	glViewport( 0, 0, w, h );
	
	/* Switches the perspective to a camera perspective */
	glMatrixMode(GL_PROJECTION);
	
	/* Now we configure that perspective from above ^ */
	glLoadIdentity(); 		/* Load/Reset our perspective */
	
	glOrtho(0,WIDTH,HEIGHT,0,0,1);
}

void updateBall()
{
	if( ball.GetX() + ball.GetHorizontalDirection() < WIDTH)
	{
		ball.SetX( ball.GetX() + ball.GetHorizontalDirection() );
	}

	if( ball.GetY() + ball.GetVerticalDirection() < HEIGHT)
	{
		ball.SetY( ball.GetY() + ball.GetVerticalDirection() );
	}
	
	//Wall collisions 
	//bottom
	if( ( ball.GetY() + ball.GetHeight() ) >= HEIGHT)// - ball.GetHeight() )
	{
    	//ball.SetVerticalDirection(ball.GetVerticalDirection() * -1);	
		//resets once it hits the ground
	    ball.ResetBall();
	    player.ResetPaddle();
	    lives.setLives(-1);
	}
	//top
	if( ( ball.GetY()/* + ball.GetHeight() */) <= 0 )
	{
    	ball.SetVerticalDirection(ball.GetVerticalDirection() * -1);
	}
	//right
	if( ( ball.GetX() + ball.GetWidth() ) >= WIDTH)// - ball.GetWidth() )
    {
    	ball.SetHorizontalDirection(ball.GetHorizontalDirection() * -1);
    }
	//left
    if( ( ball.GetX() - ball.GetWidth() ) <= 0 )
    {
    	ball.SetHorizontalDirection(ball.GetHorizontalDirection() * -1);
    }
}
void checkCollisions()
{
	player.PaddleCollision(ball);
	brickmanager.CheckCollisions(ball,score);
	
	if( lives.getLives() <= 0 ) 
	{ 
		score.getHighScores();
		glutSetMenu(mMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		gameState = GAME_OVER; 
	}
	
	if( ((glutGet(GLUT_ELAPSED_TIME) - gameTime) / 1000) == 90 )
	{
		score.getHighScores();
		glutSetMenu(mMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		gameState = GAME_OVER;
	}
}

void idle( void )
{
	switch(gameState)
	{
		case GAME_PLAY:
			updateBall();
			checkCollisions();
			glutPostRedisplay();
			break;
		case GAME_PAUSED:
			glutPostRedisplay();
			break;
		case GAME_HS:
			glutPostRedisplay();
			break;
		case GAME_MENU:
			glutPostRedisplay();
			break;
		case GAME_OVER:
			glutPostRedisplay();
			break;
	}
}

/* Create our three dimensional area */
void drawScene()
{
	switch(gameState)
	{
		case GAME_PLAY:
		{
			/* Clear previous drawScene() */
			glClear( GL_COLOR_BUFFER_BIT );

			/* Switch to drawing mode and reset */
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
	
			// Move our starting position for drawing 
			glTranslatef(0.375, 0.375, 0);	

			glColor3f(1.0f,0.5f,0.0f);		/* r,g,b -> orange lol*/

			/* We will now draw a square to the screen, in the following format 
			   glBegin(object)
			   n# of glVertex2f(float coordinate,coordinate,coordinate) depending on shape
			   glEnd() to end drawing of object */
			glBegin(GL_QUADS);			/* Start of GL_QUADS */
			/* x , y, z */
			glVertex2f(player.GetX() - player.GetWidth(), player.GetY() + player.GetHeight()); 	/* Top left */
			glVertex2f(player.GetX() + player.GetWidth(), player.GetY() + player.GetHeight());	/* Top right */
			glVertex2f(player.GetX() + player.GetWidth(), player.GetY() - player.GetHeight());	/* Bottom Right */
			glVertex2f(player.GetX() - player.GetWidth(), player.GetY() - player.GetHeight());	/* Bottom Left */
	
			glColor3f(0.0f,0.5f,0.0f);
			glVertex2f(ball.GetX() - ball.GetWidth(), ball.GetY() + ball.GetHeight()); 	/* Top left */
			glVertex2f(ball.GetX() + ball.GetWidth(), ball.GetY() + ball.GetHeight());	/* Top right */
			glVertex2f(ball.GetX() + ball.GetWidth(), ball.GetY() - ball.GetHeight());	/* Bottom Right */
			glVertex2f(ball.GetX() - ball.GetWidth(), ball.GetY() - ball.GetHeight());	/* Bottom Left */
	
			//draws from brick manager. I'll change it later so we won't have OpenGL in our objects.
			brickmanager.Draw();	

			glEnd(); 				/* End our GL_QUADS */


			/*The following is an attempt at writing strings to the screen
			 * output is a function that takes the x, y coordinates of the 
			 * lower left corner of the string, and then the string, and 
			 * the size. It messes up when you call it again with different
			 * strings. The x & y coordinates are off because they count off
			 * the previous word's coordinates...or something */
			glColor3f(0.0f,0.5f,0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);             
			
			renderStrokeFontString(300,400,0, 1, (char*) "Breakout");
	
			renderStrokeFontString(0,29, 0,.25, (char*) "Lives:");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", lives.getLives() );
			renderStrokeFontString(90,29, 0,.25, (char*) buf);
			renderStrokeFontString(0, 0, 0, 4, (char*) "");

			renderStrokeFontString(1050,29, 0, .25, (char*) "Score:");
			renderStrokeFontString(0, 0, 0, 4, (char*) "");
			sprintf(buf, "%d", score.getScore() );
			renderStrokeFontString(1150,29, 0,.25, (char*) buf);
			
			renderStrokeFontString(0, 0, 0, 4, (char*) "");
			renderStrokeFontString(1050,575, 0, .10, (char*) "Time:");
			renderStrokeFontString(0, 0, 0, 10, (char*) "");
			sprintf(buf, "%d", (glutGet(GLUT_ELAPSED_TIME) - gameTime) / 1000 );
			renderStrokeFontString(1150,575, 0,.10, (char*) buf);		

			/* Send scene from the buffer to the screen for display */
			glutSwapBuffers();
			break;
		}
		case GAME_MENU:
		{
			/* Clear previous drawScene() */
			glClear( GL_COLOR_BUFFER_BIT );

			/* Switch to drawing mode and reset */
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glColor3f(1.0f,0.5f,0.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);       
			// Move our starting position for drawing 
			glTranslatef(0.375, 0.375, 0);	
			
			renderStrokeFontString(300,200,0, 1, (char*) "BREAKOUT");

			glutSwapBuffers();			
			break;
		}
		case GAME_PAUSED:
		{
			/* Clear previous drawScene() */
			glClear( GL_COLOR_BUFFER_BIT );

			/* Switch to drawing mode and reset */
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glColor3f(0.0f,0.5f,0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);       
			// Move our starting position for drawing 
			glTranslatef(0.375, 0.375, 0);	
			
			renderStrokeFontString(300,400,0, .75, (char*) "PAUSED");

			glutSwapBuffers();
			break;
		}
		case GAME_OVER:
		{
			/* Clear previous drawScene() */
			glClear( GL_COLOR_BUFFER_BIT );

			/* Switch to drawing mode and reset */
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glColor3f(0.0f,0.5f,0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);       
			// Move our starting position for drawing 
			glTranslatef(0.375, 0.375, 0);	
			
			renderStrokeFontString(400,200,0, .75, (char*) "CREDITS");
			renderStrokeFontString(810,500,0, .25, (char*) "~ Marvin Becerra ~ ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			renderStrokeFontString(800,550,0, .25, (char*) " ~ Edgar Buenrostro ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			renderStrokeFontString(810,600,0, .25, (char*) " ~ Allison Escobar ~");
			renderStrokeFontString(0, 0 , 0, 4, (char*)"");	
			glColor3f(1.0f,0.5f,0.0f);		
			renderStrokeFontString(845,650,0, .25, (char*) " ~ Alven Diaz ~");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");			

			glutSwapBuffers();		
			break;
		}
		case GAME_HS:
		{
			/* Clear previous drawScene() */
			glClear( GL_COLOR_BUFFER_BIT );

			/* Switch to drawing mode and reset */
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glColor3f(0.0f,0.5f,0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);       
			// Move our starting position for drawing 
			glTranslatef(0.375, 0.375, 0);
			
			getScores();	
		
			glColor3f(1.0f,.5f,1.0f);	
			renderStrokeFontString(350,200,0, .75, (char*) "High Scores");
			glColor3f(0.34f,0.5f,0.23f);
			
			renderStrokeFontString(800,500,0, .25, (char*) "1. ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", top[0] );
			renderStrokeFontString(835,500,0, .25, (char*) buf );
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			
			renderStrokeFontString(800,550,0, .25, (char*) "2. ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", top[1] );
			renderStrokeFontString(835,550,0, .25, (char*) buf );
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			
			renderStrokeFontString(800,600,0, .25, (char*) "3. ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", top[2] );
			renderStrokeFontString(835,600,0, .25, (char*) buf );
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");		
			
			renderStrokeFontString(800,650,0, .25, (char*) "4. ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", top[3] );
			renderStrokeFontString(835,650,0, .25, (char*) buf );
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			
			renderStrokeFontString(800,700,0, .25, (char*) "5. ");
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");
			sprintf(buf, "%d", top[4] );
			renderStrokeFontString(835,700,0, .25, (char*) buf );
			renderStrokeFontString(0, 0 , 0, 4, (char*) "");		

			glutSwapBuffers();				
			break;
		}
	}
}

void pauseMenu(int option)
{
	switch(option)
	{
		case MAIN_MENU:
		{
			glutSetMenu(mMenu);
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			gameState = GAME_MENU;
			break;
		}
		case NEWGAME:
		{
			resetGame();
			sleep(1);
			break;
		}
		case EXITGAME:
		{
			exit(0);
			break;
		}
		case PAUSE_GAME:
		{
			if( gameState != GAME_PAUSED )
			{
				glutSetMenu(pMenu);
				glutAttachMenu(GLUT_RIGHT_BUTTON);
				gameState = GAME_PAUSED;
			}
			else
			{
				glutSetMenu(pMenu);
				glutAttachMenu(GLUT_RIGHT_BUTTON);
				gameState = GAME_PLAY;
			}
			break;
		}
		default:
			break;
	}
}

void mainMenu(int option)
{
	switch(option)
	{
		case NEWGAME:
		{
			glutSetMenu(pMenu);
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			resetGame();
			break;
		}
		case EXITGAME:
		{
			exit(0);
			break;
		}
		case HIGH_SCORES:
		{
			gameState = GAME_HS;
			break;
		}
		case CREDITS:
		{
			gameState = GAME_OVER;
			break;
		}
		default:
			break;
	}
}

void createGLUTMenus()
{
	pMenu = glutCreateMenu(pauseMenu);
	glutAddMenuEntry("New Game", NEWGAME);
	glutAddMenuEntry("(Un)Pause Game", PAUSE_GAME);
	glutAddMenuEntry("Main Menu", MAIN_MENU);
	glutAddMenuEntry("Exit", EXITGAME);
	
	mMenu = glutCreateMenu(mainMenu);
	glutAddMenuEntry("New Game", NEWGAME);
	glutAddMenuEntry("High Scores", HIGH_SCORES);
	glutAddMenuEntry("Credits", CREDITS);
	glutAddMenuEntry("Exit", EXITGAME);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main( int argc, char** argv ) 
{
	gameState = GAME_MENU;
	brickmanager.InitializeLevel();
	lives.setLives(5);
	score.getHighScores();

	//Initialize GLUT	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT); //Set the window size

	//Create the window
	glutCreateWindow("Breakout - teamNaranja");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboardPress);
	glutSpecialFunc(specialKeyboardPress);
	glutIdleFunc(idle);

	createGLUTMenus();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.

	return 0; //This line is never reached
}
/* Developed by teamNaranja.ZaidOS */
/* Also developed by teamNaranja.What? */

