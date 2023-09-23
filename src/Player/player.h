#pragma once

namespace player
{
struct Player
{
	int lives;
};

void initPlayer(Player& player);
void decreaseLife(Player& player);
}