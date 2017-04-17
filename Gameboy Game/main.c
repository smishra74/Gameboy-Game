
#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "winFace.h"
#include "loseFace.h"
#include "life.h"
#include "welcomeGameScreen.h"

// **Game Items**
typedef struct
{
	int row;
	int col;
	int drow;
	int dcol;
} OBSTACLE;

typedef struct
{
	int row;
	int col;
} PLAYER;

enum GBAstate {
	WELCOME,
	INSTRUCTIONS,
	GAME,
	WIN,
	LOSE
};

void welcome();
void instructions();
int game();
void winGame();
void loseGame();

char scoreBuffer[8];
char lifeBuffer[8];
int lives;

int main(void)
{
	enum GBAstate state = WELCOME;
	waitForVblank();
	while(1)
	{
		switch(state)                              //DIFFERENT STATES IN THE GAME
		{
			case WELCOME:
				welcome();
				state = INSTRUCTIONS;
				break;
			case INSTRUCTIONS:
				instructions();
				state = GAME;
				break;
			case GAME:
				state = game();
				break;
			case WIN:
				winGame();
				state = INSTRUCTIONS;
				break;
			case LOSE:
				loseGame();
				state = INSTRUCTIONS;
			default:
				break;
		}
	}
}

void welcome()
{
	REG_DISPCNT = MODE3 | BG2_EN;

	

	drawImage3(0, 0, WELCOMEGAMESCREEN_WIDTH, WELCOMEGAMESCREEN_HEIGHT, welcomeGameScreen);                    //DISPLAYS ALL THE TEXT ON THE WELCOME SCREEN
	 
	drawString3(10, 0, "WELCOME TO THE GAME", YELLOW);
	drawString3(30, 0, "YOU GOT THIS!", YELLOW);

	drawString3(130, 12, "PRESS ENTER TO GO TO THE INSTRUCTIONS", WHITE);

	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

void instructions()
{
	REG_DISPCNT = MODE3 | BG2_EN;

	fillScreen3(BLACK);
	drawString3(10, 55, "GAMEBOY INSTRUCTIONS", WHITE);                                         //DISPLAYS ALL THE TEXT ON THE INSTRUCTIONS SCREEN
	drawString3(25, 0, "TO WIN, SCORE ABOVE 25!!", YELLOW);       
	drawString3(38, 0, "AVOID COLLISIONS WITH THE BOUNCING BALLS", YELLOW);
	drawString3(50, 0, "YOU HAVE 4 LIVES", YELLOW);
	drawString3(62, 0, "YOU CAN USE ALL 4 ARROW KEYS TO MOVE", YELLOW);


	drawPlayer(82, 10, YELLOW, BLACK, BLUE, RED);
	drawString3(90, 30, " THIS IS YOUR SPACESHIP!", ORANGE);

	drawObstacle(112, 5, RED, YELLOW);
	drawObstacle(112, 15, RED, YELLOW);
	drawObstacle(122, 10, RED, YELLOW);
	drawObstacle(132, 5, RED, YELLOW);
	drawObstacle(132, 15, RED, YELLOW);

	drawString3(115, 30, "THESE ARE YOUR ENEMIES! AVOID ", ORANGE);
	drawString3(125, 30, "COLLIDING WITH THESE ASTEROIDS", ORANGE);

	

	drawString3(148, 11, "PRESS ENTER TO ENJOY YOUR SPACE RIDE", WHITE);

	lives = 4;                                                                           //EACH TIME THE PLAYER DECIDES TO PLAY AGAIN, THE LIVES ARE SET TO 4

	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

int game(void)
{
	REG_DISPCNT = MODE3 | BG2_EN;
	fillScreen3(BLACK);

	OBSTACLE obstacles[OBSTACLES];
	OBSTACLE obstacles1[OBSTACLES];
	OBSTACLE *current;

	
	int d[] = {-3, -2, -1, 1, 2, 3};                                                    //SPEED AND MOVEMENT OF THE BALLS  
	int num1 = sizeof(d) / sizeof(d[0]);


	

	for (int i = 0; i < OBSTACLES; i++)                                                //ASTEROIDS ARE POSITIONED IN RANDOM POSITIONS 
	{
		obstacles[i].row = rand()%50 + 31;
		obstacles[i].col = rand()%50 + 31;
		obstacles[i].drow = d[rand()%num1];
		obstacles[i].dcol = d[rand()%num1];
		obstacles1[i] = obstacles[i];
	}


	drawHollowRect(30, 0, 239, 129, YELLOW);                                               //THIS IS WHERE THE GAME IS PLAYED
	

	drawImage3(3, 175, LIFE_WIDTH, LIFE_HEIGHT, life);
	drawString3(11, 200, "x ", WHITE);

	
	PLAYER player = {136, 120};                                                          //PLAYER'S POSITION
	PLAYER player1 = player;

	int score = 0;

	
	drawString3(11, 5, "SCORE: ", WHITE);
	drawChar(11, 50, '0', WHITE);

	
	
	
	drawPlayer(player.row, player.col,  YELLOW, BLACK, BLUE, RED);                      //THE PLAYER, OBSTACLES AND THE SHIELD ARE PLACED ON THE BOARD

	for (int i = 0; i < OBSTACLES; i++)
	{
		drawObstacle(obstacles[i].row, obstacles[i].col, RED, YELLOW);
		obstacles1[i] = obstacles[i];
	}

	

	//COUNTDOWN
	drawChar(76, 117, '3', YELLOW);
	for (int i = 0; i < 500; i++)
	{
		waitForVblank();
	}
	drawRect(76, 117, 6, 8, BLACK);                                                      //CREATES BLACK RECTANGLE EVERYTIME TO AVOID OVERLAPPING OF NOS

	//COUNTDOWN
	drawChar(76, 117, '2', YELLOW);
	for (int i = 0; i < 500; i++)
	{
		waitForVblank();
	}
	drawRect(76, 117, 6, 8, BLACK);                                                     //CREATES BLACK RECTANGLE EVERYTIME TO AVOID OVERLAPPING OF NOS

	//COUNTDOWN
	drawChar(76, 117, '1', YELLOW);
	for (int i = 0; i < 500; i++)
	{
		waitForVblank();
	}
	drawRect(76, 117, 6, 8, BLACK);                                                        //CREATES BLACK RECTANGLE EVERYTIME TO AVOID OVERLAPPING OF NOS

	drawString3(76, 117, "GO!", YELLOW);
	for (int i = 0; i < 500; i++)
	{
		waitForVblank();
	}
	drawRect(76, 117, 25, 25, BLACK);                                                   //HELPS DISAPPEAR THE COUNTDOWN
	

	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			return WELCOME;
		}

		if(KEY_DOWN_NOW(BUTTON_UP))                                                   //PLAYER MOVING UP USING UP ARROW
		{
			
			player.row--;
			if (player.row < 31)
			{
				player.row = 31;
			}
		} 
		if(KEY_DOWN_NOW(BUTTON_DOWN))                                                  //PLAYER MOVING DOWN USING DOWN ARROW 
		{
			
			player.row++;
			if (player.row > 136)
			{
				player.row = 136;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))                                            //PLAYER MOVING LEFT USING LEFT ARROW
		{
			
			player.col--;
			if (player.col < 2)
			{
				player.col = 2;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))                                               //PLAYER MOVING RIGHT USING RIGHT ARROW
		{
			
			player.col++;
			if (player.col > 232)
			{
				player.col = 232;
			}
		}
		

		for (int i = 0; i < OBSTACLES; i++)                                          //ASTEROIDS MOVING
		{
			current = obstacles + i;
			current -> row = current -> row + current -> drow;
			current -> col = current -> col + current -> dcol;
			if(current -> row < 31)
			{
				current -> row = 31;
				current -> drow = -current -> drow;
			}
			if(current -> row > 153)
			{
				current -> row = 153;
				current -> drow = -current -> drow;
			}

			if(current -> col < 1)
			{
				current -> col = 1;
				current -> dcol = -current -> dcol;
			}
			if(current -> col > 233)
			{
				current -> col = 233;
				current -> dcol =-current -> dcol;
			}			
			

			if (collision(current -> col, current -> row, player.col, player.row))                     //CHECKING FOR COLLISIONS
			{
				lives--;
				if(lives > 0)
				{
					if(score >= 250)
					{
						return WIN;
					}
					else
					{
						return GAME;
					}
				}
				else
				{
					if (score < 250)
					{
						return LOSE;
					}
					else
					{
						return WIN;
					}
				}
			}
		}

		score++;
		if (score > 5000)
		{
			return WIN;
		}
		sprintf(scoreBuffer, "%i", score / 10);

		waitForVblank();

		drawRect(11, 50, 20, 8, BLACK);                                                          //DRAWS A RECTANGLE TO DISPLAY THE SCORE
		drawString3(11, 50, scoreBuffer, WHITE);

		sprintf(lifeBuffer, "%i", lives);

		waitForVblank();

		drawRect(11, 120, 0, 8, BLACK);                                                         //DRAWS A RECTANGLE TO DISPLAY THE SCORE
		drawString3(11, 215, lifeBuffer, WHITE);

		
		drawRect(player1.row, player1.col, 5, 22, BLACK);                                        //THIS BELOW CODE MAKES SURE THAT THE PATH LEFT BEHIND BY THE SPACESHIP IS BLACK
		player1 = player;
		drawPlayer(player.row, player.col, YELLOW, BLACK, BLUE, RED);

		for (int i = 0; i < OBSTACLES; i++)
		{
			
			drawRect(obstacles1[i].row, obstacles1[i].col, 5, 5, BLACK);                      //THIS BELOW CODE MAKES SURE THAT THE PATH LEFT BEHIND BY THE ASTEROIDS IS BLACK
		}
		for (int i = 0; i < OBSTACLES; i++)
		{
			drawObstacle(obstacles[i].row, obstacles[i].col, RED, YELLOW);
			obstacles1[i] = obstacles[i];
		}
	}
}

void winGame()
{
	drawImage3(0, 0, WINFACE_WIDTH, WINFACE_HEIGHT, winFace);                                   //DRAWS THE IMAGE ON THE GAME OVER SCRREN SCREEN

	drawString3(95, 100, "WOHOO!! YOU WON!", BLACK);                                            //DISPLAYS ALL THE TEXT ON THE WIN SCREEN       
	drawString3(105,100, "SCORE: ", BLACK);        
	drawString3(105, 150, scoreBuffer, BLUE);

	drawString3(132, 45, "PRESS ENTER TO PLAY AGAIN", RED);

	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

void loseGame()
{
	fillScreen3(WHITE);
	drawImage3(0, 0, LOSEFACE_WIDTH , LOSEFACE_HEIGHT, loseFace);                                 //DRAWS THE IMAGE ON THE GAME OVER SCRREN SCREEN

	drawString3(5, 30, "DAMN!! YOU LOST!", BLACK);                                                //DISPLAYS ALL THE TEXT ON THE LOSE SCREEN
	drawString3(20, 30, "SCORE:", BLACK);
	drawString3(20, 80, scoreBuffer, BLUE);

	drawString3(132, 45, "PRESS ENTER TO PLAY AGAIN", YELLOW);

	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}
