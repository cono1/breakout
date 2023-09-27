#include "printer.h"

#include <sl.h>
#include <string>

namespace printer
{
void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize)
{
    slSetForeColor(1, 1, 1, 1);
    slSetFontSize(fontSize);
    std::string lives = std::to_string(player.lives);
    slText((screenWidth - slGetTextWidth(lives.c_str())), screenHeight - slGetTextHeight(lives.c_str()), lives.c_str());
}

void printFinalMessage(bool won, const int width, const int height)
{
    slSetForeColor(1, 1, 1, 1);
    std::string text2 = "Press enter to play again";
    if (won)
    {
        std::string text1 = "You won";
        slText(width / 2 - slGetTextWidth(text1.c_str()) / 2, height / 2 - slGetTextHeight(text1.c_str()) / 2, text1.c_str());
        slText(width / 2 - slGetTextWidth(text2.c_str()) / 2, height / 2 - slGetTextHeight(text2.c_str()) - slGetTextHeight(text1.c_str()) / 2, text2.c_str());
    }
    else
    {
        std::string text1 = "You lost";
        slText(width / 2 - slGetTextWidth(text1.c_str()) / 2, height / 2 - slGetTextHeight(text1.c_str()) / 2, text1.c_str());
        slText(width / 2 - slGetTextWidth(text2.c_str()) / 2, height / 2 - slGetTextHeight(text2.c_str()) - slGetTextHeight(text1.c_str()) / 2, text2.c_str());
    }
}

void printRules(Player player, const int width, const int height, int fontSize)
{
    slSetForeColor(1, 1, 1, 1);
    std::string lives = std::to_string(player.maxLives);
    std::string text1 = "\t\t\t\tMOVE: \nUse left and right arrow.\n\n\t\t\t\tOBJECTIVE: \n Break all the bricks\n on screen using the ball.\n\n\t\t\t\tYou have " + lives + " lives.\n If the ball falls you loose one\n If you have 0 lives you loose.";

    slText(width / 10, height - fontSize, text1.c_str());
}

void printCredits(const int width, const int height, int fontSize)
{
    slSetForeColor(1, 1, 1, 1);
    std::string text1 = "Game developed by Daniela Gonzalez";
    std::string text2 = "Paddle texture by Grapho Boy";
    slText(width / 2 - slGetTextWidth(text1.c_str()) / 2, height / 2 - slGetTextHeight(text1.c_str()) / 2, text1.c_str());
    slText(width / 2 - slGetTextWidth(text2.c_str()) / 2, height / 2 - slGetTextHeight(text2.c_str()) - slGetTextHeight(text1.c_str()) / 2 - fontSize, text2.c_str());
}
}