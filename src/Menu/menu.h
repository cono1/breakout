#pragma once

#include <string>

#include "sl.h"

namespace menu
{
enum CurrentScreen { EXIT, CREDITS, RULES, PLAY, MENU, PAUSE };

struct MenuRect
{
	int x;
	int y;
	float width;
	float height;
	float initWidth;
	float maxWidth;
};

void initMenu(const int screenWidth);
void updateMenu(CurrentScreen& currentScreen);
void printMenu(const int screenWidth, const int screenHeight, const int fontSize, std::string title);
void printBackButton(bool pause);
bool isPausePressed();
}