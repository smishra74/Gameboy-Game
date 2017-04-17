typedef unsigned short u16;
typedef unsigned int u32;

typedef struct
{
	const volatile void *src;
	volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;


#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3


#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)


#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)





#define OFFSET(r,c, numcols) ((r)*(numcols) + (c))
unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006




#define REG_DISPCNT *(unsigned short*) 0x4000000
#define MODE3 3
#define BG2_EN (1<<10) // bit 10





#define COLOR(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)



//**OBSTACLES**
#define OBSTACLES 5



#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130



// **Prototypes**
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);

void drawPlayer(int r, int c, u16 color, u16 color1, u16 color2, u16 color3);
void drawPlayer0(int r, int c, u16 color, u16 color1);
void drawPlayer1(int r, int c, u16 color, u16 color1);
void drawPlayer2(int r, int c, u16 color);

void drawObstacle(int r, int c, u16 color1, u16 colorX);

int collision(int bCol, int bRow, int sCol, int sRow);
void drawImage3(int r, int c, int width, int height, const u16* image);

void fillScreen3(unsigned short color);

void waitForVblank();
void drawChar(int row, int col, char ch, unsigned short color);
void drawString3(int row, int col, char *str, unsigned short color);




