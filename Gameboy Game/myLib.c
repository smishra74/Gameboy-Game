#include "myLib.h"

unsigned short *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int c, u16 color)
{
	videoBuffer[OFFSET(row, c, 240)] = color;
}


void drawImage3(int r, int c, int width, int height, const u16* image) 
{
	for (int x = 0; x < height; x++) {
		DMA[3].src = image + OFFSET(x, 0, width);
		DMA[3].dst = videoBuffer + OFFSET(r + x, c, 240);
		DMA[3].cnt = width | DMA_ON;
	}
}


void fillScreen3(unsigned short color)
{
	unsigned short *ptr = videoBuffer;
	for(int i = 0; i < 38400; i++)
	{
		*ptr++ = color;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

int collision(int bCol, int bRow, int sCol, int sRow)
{
	if (sRow < (bRow + 5) && (sRow + 22) > bRow)
	{
		if (sCol < (bCol + 5) && (sCol + 5) > bCol)
		{
			return 1;
		}
	}
	return 0;
}

void drawObstacle(int r, int c, u16 color1, u16 colorX)
{
	for (int row = 0; row < 5; row++)                                 //MAKING EACH OBSTACLE BY SEETING EACH PIXEL OF THE OBSTACLE
    {
        for (int col = 0; col < 5; col++)
        {
            setPixel(r + row, c + col, color1);
        }
    }

    setPixel(r + 1, c + 1, colorX);
    setPixel(r + 1, c + 3, colorX);
    setPixel(r + 2, c + 2, colorX);
    setPixel(r + 3, c + 1, colorX);
    setPixel(r + 3, c + 3, colorX);
}

void drawPlayer(int row, int col, u16 color, u16 color1, u16 color2, u16 color3)
{
	for (int i = 0; i < 5; i++)
	{
		drawPlayer0(row + i, col, color, color1);
	}

	for (int i = 5; i < 15; i++)
	{
		drawPlayer1(row + i, col, color, color1);
	}
	for (int i = 15; i < 20; i++)
	{
		drawPlayer2(row + i, col, color);
	}

	drawRect(row + 3, col + 2, 1, 10, color2);
	
	setPixel(row + 6, col + 2, color3);
	setPixel(row + 7, col + 2, color3);
	setPixel(row + 8, col + 2, color3);
	setPixel(row + 9, col + 2, color3);
	
}

void drawPlayer0(int row, int col, u16 color, u16 color1)
{
	for (int i = 0; i < 5; i++)
	{
		setPixel(row, col + i, color1);
	}
	setPixel(row, col + 2, color);
}

void drawPlayer1(int row, int c, u16 color, u16 color1)
{
	for (int i = 0; i < 5; i++)
	{
		setPixel(row, c + i, color1);
	}
	for (int i = 1; i < 4; i++)
	{
		setPixel(row, c + i, color);
	}
}

void drawPlayer2(int row, int c, u16 color1)
{
	for (int i = 0; i < 5; i++)
	{
		setPixel(row, c + i, color1);
	}
}

void drawRect(int r, int c, int width, int height, u16 color)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            setPixel(r + row, c + col, color);
        }
    }
}

void drawHollowRect(int row, int c, int width, int height, u16 color)
{
	for (int i = 0; i < width; i++) {
		setPixel(row, i + c, color);
		setPixel(row + height, i + c, color);
	}

	for(int j = 0; j < height; j++) {
		setPixel(j + row, c, color);
		setPixel(j + row, c + width, color);
	}
}

void drawChar(int row, int col, char ch, unsigned short color)
{
	for(int r=0; r<8; r++)
	{
		for(int c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6) + ch * 48])
			{
				setPixel(row + r, col + c, color);
			}
		}
	}
}

void drawString3(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col +=6;
	}
}
