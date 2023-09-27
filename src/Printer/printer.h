#pragma once

#include "Player/player.h"

using namespace player;

namespace printer
{
	void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize);
	void printFinalMessage(bool won, const int width, const int height);
	void printRules(Player player, const int width, const int height, int fontSize);
	void printCredits(const int width,  const int height, int fontSize);
}