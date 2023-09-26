#include "menu.h"

#include <iostream>

#include "sl.h"

namespace menu
{
const int quantMenuRects = 4;
static MenuRect menuRect[quantMenuRects];
static MenuRect pauseRect;

void writeOnMenuSquare(std::string word, int pos, const int screenWidth, const int fontSize);
bool checkMenuInput(CurrentScreen currentSquare);
bool checkCollision(MenuRect& menuRect, float initWidth, float maxWidth);

void initMenu(const int screenWidth)
{
	int spaceBetweenRects = 20;
	int firstRectYPosition = 120;

	for (int i = 0; i < quantMenuRects; i++)
	{
		menuRect[i].width = 360;
		menuRect[i].height = 80;
		menuRect[i].x = (screenWidth - menuRect[i].x) / 2;
		menuRect[i].y = firstRectYPosition + (menuRect[i].height + spaceBetweenRects) * i;
		menuRect[i].initWidth = menuRect[i].width;
		menuRect[i].maxWidth = menuRect[i].width + 20;
	}

	pauseRect.x = 40;
	pauseRect.y = 745;
	pauseRect.width = 35;
	pauseRect.height = 35;
	pauseRect.initWidth = pauseRect.width;
	pauseRect.maxWidth = pauseRect.width + 10;
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

void printMenu(const int screenWidth, const int screenHeight, const int fontSize, std::string title)
{
	slSetForeColor(1, 0.5, 1, 1);
	slSetFontSize(fontSize + 100);
	slText((screenWidth - slGetTextWidth(title.c_str())) / 2, screenHeight - slGetTextHeight(title.c_str()) - fontSize, title.c_str());

	slSetFontSize(fontSize);

	for (int i = 0; i < quantMenuRects; i++)
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
	return (checkCollision(menuRect[currentSquare], menuRect[currentSquare].initWidth, menuRect[currentSquare].maxWidth) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT));
}

bool checkCollision(MenuRect& menuRect, float initWidth, float maxWidth)
{
	int mouseX = slGetMouseX();
	int mouseY = slGetMouseY();

	if (mouseX >= menuRect.x - menuRect.width / 2 &&
		mouseX <= menuRect.x + menuRect.width / 2 &&
		mouseY >= menuRect.y - menuRect.height / 2 &&
		mouseY <= menuRect.y + menuRect.height / 2) 
	{
		if(menuRect.width < maxWidth)
		{
			menuRect.width += 5;
		}

		return true;
	}
	else
	{
		menuRect.width = initWidth;
		return false;
	}
}


void printPauseButton()
{
	slSetForeColor(1, 1, 1, 1);
	slSetFontSize(25);
	slRectangleFill(pauseRect.x, pauseRect.y, pauseRect.width, pauseRect.height);
	slSetForeColor(1, 0.5, 1, 1);
	slText(pauseRect.x - 10, pauseRect.y - 10, "||");
}

bool isPausePressed()
{
	return checkCollision(pauseRect, pauseRect.initWidth, pauseRect.maxWidth);
}
}