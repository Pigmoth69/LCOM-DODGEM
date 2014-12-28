
#include "bitmap.h"
#include "stdio.h"
#include "graphics.h"
#include "utilities.h"
#include "string.h"




Bitmap* loadBitmap(const char* filename) {
    // allocating necessary size
    Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

    // open filename in read binary mode
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, 2, 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.type != 0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    int rd;
    do {
        if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
            break;
    } while (0);

    if (rd = !1) {
        fprintf(stderr, "Error reading file\n");
        exit(-1);
    }

    // read the bitmap info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

    // move file pointer to the begining of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // allocate enough memory for the bitmap image data
    unsigned char* bitmapImage = (unsigned char*) malloc(
            bitmapInfoHeader.imageSize);

    // verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    // close file and return bitmap image data
    fclose(filePtr);

    bmp->bitmapData = bitmapImage;
    bmp->bitmapInfoHeader = bitmapInfoHeader;

    return bmp;
}

void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;

    if (alignment == ALIGN_CENTER)
        x -= width / 2;
    else if (alignment == ALIGN_RIGHT)
        x -= width;

    if (x + width < 0 || x > MODE1024_H_RES || y + height < 0
            || y > MODE1024_V_RES)
        return;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > MODE1024_H_RES)
            drawWidth = MODE1024_H_RES;
    } else if (x + drawWidth >= MODE1024_H_RES) {
        drawWidth = MODE1024_H_RES - x;
    }

    char* bufferStartPos;
    char* imgStartPos;

    int i;
    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= MODE1024_V_RES)
        	continue;

        bufferStartPos = (char*)getVideoBuffer();
        bufferStartPos += x * 2 + pos * MODE1024_H_RES * 2;

        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

        memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
    }
}

int number_draw_width(int number)
{
	if(number == 10)
		return 20;
	else
		return 39;
}

void drawBitmapNumber(Bitmap* bmp, int x, int y,int number, Alignment alignment) {


	if (bmp == NULL)
		return;


	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;


	int drawWidth = number_draw_width(number);
	int xCorrection=0;

	if(number == 0)
		xCorrection=0;
	else if(number == 1)
		xCorrection+= 40;
	else
		xCorrection+=(number-1)*40+40;



	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	if (x + width < 0 || x > MODE1024_H_RES || y + height < 0
			|| y > MODE1024_V_RES)
		return;


	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > MODE1024_H_RES)
			drawWidth = MODE1024_H_RES;
	} else if (x + drawWidth >= MODE1024_H_RES) {
		drawWidth = MODE1024_H_RES - x;
	}

	char* bufferStartPos;
	char* imgStartPos;


	int i;
	for (i = 0; i < height; i++) {
		int pos = y + height - 1 - i;

		if (pos < 0|| pos >= MODE1024_V_RES)
			continue;

		bufferStartPos = (char*)getVideoBuffer();
		bufferStartPos += x * 2 + pos * MODE1024_H_RES * 2;

		imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
	}
}

void drawScore(int x_inicial,int y_inicial,int segundos,int centesimas)
{
	/*drawBitmapNumber(game->Numbers,800, 690,segundos, ALIGN_LEFT);*/



	unsigned char string[50];

	sprintf(string,"%d",segundos);

	int i = 0;
	for(i; i < strlen(string);i++)
	{
		drawBitmapNumber(game->Numbers,x_inicial, y_inicial,string[i]-'0', ALIGN_LEFT);
		x_inicial+=number_draw_width(string[i]-'0');
	}

	if (centesimas == -1)
		return;


	drawBitmapNumber(game->Numbers,x_inicial,y_inicial ,10, ALIGN_LEFT);
	x_inicial+=number_draw_width(10);


	i = 0;
	sprintf(string,"%d",centesimas);

	for(i; i < strlen(string);i++)
	{
		drawBitmapNumber(game->Numbers,x_inicial, y_inicial,string[i]-'0', ALIGN_LEFT);
		x_inicial+=number_draw_width(string[i]-'0');
	}

}

void drawPart(Bitmap* bmp, int x, int y, int x_inicial, int y_inicial, int x_final, int y_final, Alignment alignment){


	if (bmp == NULL)
		return;


	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;


	int drawWidth = x_final - x_inicial;
	int xCorrection = 0;

	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	if (x + width < 0 || x > MODE1024_H_RES || y + height < 0
			|| y > MODE1024_V_RES)
		return;


	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > MODE1024_H_RES)
			drawWidth = MODE1024_H_RES;
	} else if (x + drawWidth >= MODE1024_H_RES) {
		drawWidth = MODE1024_H_RES - x;
	}

	char* bufferStartPos;
	char* imgStartPos;


	int i;
	for (i = 0; i < height; i++) {
		int pos = y + height - 1 - i;

		if (pos < 0|| pos >= MODE1024_V_RES)
			continue;

		bufferStartPos = (char*)getVideoBuffer();
		bufferStartPos += x * 2 + pos * MODE1024_H_RES * 2;

		imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
	}
}

void deleteBitmap(Bitmap* bmp) {
    if (bmp == NULL)
        return;

    free(bmp->bitmapData);
    free(bmp);
}

void drawLosingText(int segundos, int centesimas){
    drawBitmap(game->ScoreBackground, 450, 250, ALIGN_LEFT);
    drawScore(580,350,segundos,centesimas);
    memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);
}
