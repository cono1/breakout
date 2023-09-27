#pragma once

namespace player
{
struct Player
{
	int lives;
	int maxLives;
	bool won;
};

void initPlayer(Player& player);
void decreaseLife(Player& player);
void updatePlayer(Player& player, int activeBircksLeft);
}