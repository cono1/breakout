#pragma once

namespace player
{
struct Player
{
	int lives;
	bool won;
};

void initPlayer(Player& player);
void decreaseLife(Player& player);
void checkPayerStatus(Player player, int activeBircksLeft);
}