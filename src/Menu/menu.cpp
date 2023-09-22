#include "menu.h"

#include <string>
#include <iostream>

#include "sl.h"

bool collide = false;
namespace menu
{
const int quantMenuRects = 3;
static MenuRect menuRect[quantMenuRects];

void writeOnMenuSquare(std::string word, int pos, const int screenWidth, const int fontSize);
bool checkMenuInput(CurrentScreen currentSquare);
bool checkCollision(int mouseX, int mouseY, MenuRect menuRect[], CurrentScreen currentSquare);

void initMenu(const int screenWidth)
{
	int spaceBetweenRects = 20;
	int firstRectYPosition = 70;
	for (int i = 0; i <= quantMenuRects; i++)
	{
		menuRect[i].width = 360;
		menuRect[i].height = 80;
		menuRect[i].x = (screenWidth - menuRect[i].x) / 2;
		menuRect[i].y = firstRectYPosition + (menuRect[i].height + spaceBetweenRects) * i;
	}
}

void updateMenu(CurrentScreen& currentScreen)
{
	if (checkMenuInput(PLAY))
	{
		std::cout << "play";
		currentScreen = PLAY;
	}

	if (checkMenuInput(PAUSE))
		currentScreen = PAUSE;

	if (checkMenuInput(RULES))
		currentScreen = RULES;

	if (checkMenuInput(CREDITS))
		currentScreen = CREDITS;

	if (checkMenuInput(EXIT))
		currentScreen = EXIT;
}

void printMenu(const int screenWidth, const int screenHeight, const int fontSize)
{
	slSetForeColor(1, 0.5, 1, 1);
	slText((screenWidth - slGetTextWidth("BREAKOUT")) / 2, screenHeight - slGetTextHeight("BREAKOUT"), "BREAKOUT");

	for (int i = 0; i <= quantMenuRects; i++)
	{
		slSetForeColor(1, 1, 1, 1);
		slRectangleFill(static_cast<int>(menuRect[i].x), static_cast<int>(menuRect[i].y), static_cast<int>(menuRect[i].width), static_cast<int>(menuRect[i].height));

		slSetForeColor(1, 0.5, 1, 1);

		if (i == PLAY)
		{
			writeOnMenuSquare("PLAY", i, screenWidth, fontSize);
		}

		if (i == RULES)
		{
			writeOnMenuSquare("HOW TO PLAY", i, screenWidth, fontSize);
		}

		if (i == CREDITS)
		{
			writeOnMenuSquare("CREDITS", i, screenWidth, fontSize);
		}

		if (i == EXIT)
		{
			writeOnMenuSquare("EXIT", i, screenWidth, fontSize);
		}
	}
}

void writeOnMenuSquare(std::string word, int pos, const int screenWidth, const int fontSize)
{
	int xOffsetText = static_cast<int>(menuRect[pos].x) - slGetTextWidth(word.c_str()) / 2;
	int yOffsetText = (menuRect[pos].height - fontSize) / 2;

	slText(xOffsetText, static_cast<int>(menuRect[pos].y - yOffsetText), word.c_str());;
}

bool checkMenuInput(CurrentScreen currentSquare)
{
	int mousePosX = slGetMouseX();
	int mousePosY = slGetMouseY();

	if (checkCollision(mousePosX, mousePosY, menuRect, currentSquare) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	{
		return true;	
	}
	else
	{
		return false;
	}	
}

bool checkCollision(int mouseX, int mouseY, MenuRect menuRect[], CurrentScreen currentSquare)
{
	if (mouseX >= menuRect[currentSquare].x - menuRect[currentSquare].width / 2 &&
		mouseX <= menuRect[currentSquare].x + menuRect[currentSquare].width / 2 &&
		mouseY >= menuRect[currentSquare].y - menuRect[currentSquare].height / 2 &&
		mouseY <= menuRect[currentSquare].y + menuRect[currentSquare].height / 2) {
		menuRect[currentSquare].width += 5;
		std::cout << "colision";
		return true;
	}
	else
	{
		return false;
	}
}
}