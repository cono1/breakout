#include "game.h"

#include <iostream>

#include "sl.h"

#include "Menu/menu.h"
#include "Paddle/paddle.h"
#include "Ball/ball.h"
#include "Bricks/bricks.h"
#include "Player/player.h"

extern int offset;

namespace game
{
using namespace menu;
using namespace paddle;
using namespace ball;
using namespace bricks;
using namespace player;

static const int width = 1024;
static const int height = 768;
static const int fontSize = 50;
static int activeBricksLeft = quantX * quantY;
static bool shouldExit = false;

void gameLoop();
void initializeGameObjects(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player);
void updateGameLogic(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player, CurrentScreen& currentScreen);
void drawGameObjects(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player, CurrentScreen& currentScreen);
bool checkBallToPaddCollision(Ball& ball, Paddle paddle);
void checkBallToBrickCollision(Ball ball, Brick brick[quantY][quantX]);
void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle, Player& player);
void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize);
void printFinalMessage(bool won);
void printRules(Player player);
void printCredits();

void gameLoop()
{
    Paddle paddle;
    Ball ball;
    Brick brick[quantY][quantX];
    Player player;

    slWindow(width, height, "BREAKOUT", false);

    int font = slLoadFont("res/PermanentMarker-Regular.ttf");
    slSetFont(font, fontSize);
    CurrentScreen currentScreen = MENU;

    initMenu(width);
    initializeGameObjects(paddle, ball, brick, player);


    while (!shouldExit)
    {
        updateGameLogic(paddle, ball, brick, player, currentScreen);
        drawGameObjects(paddle, ball, brick, player, currentScreen);

        slRender();
    }

    slClose();
}

void initializeGameObjects(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player)
{
    initPaddle(paddle, width, height);
    initBall(ball, paddle.x, paddle.y);
    initBrick(brick);
    initPlayer(player);
    activeBricksLeft = quantX * quantY;
}

void updateGameLogic(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player, CurrentScreen& currentScreen)
{
    if (currentScreen == PLAY)
    {
        updatePaddle(paddle, width);
        updateBall(ball);
        checkBallLimits(ball, width, height, paddle, player);
        checkBallToBrickCollision(ball, brick);
        updatePlayer(player, activeBricksLeft);

        if (player.won && currentScreen != PAUSE || player.lives <= 0)
        {
            clearBall(ball);
            clearPaddle(paddle);
            clearBricks(brick);
            printFinalMessage(player.won);
            if (slGetKey(SL_KEY_ENTER))
            {
                initializeGameObjects(paddle, ball, brick, player);
            }
        }

        if (isPausePressed() && slGetMouseButton(SL_MOUSE_BUTTON_LEFT) || slGetKey(SL_KEY_ESCAPE))
        {
            currentScreen = PAUSE;
        }
    }
        if (slShouldClose() || slGetKey(SL_KEY_ESCAPE) && currentScreen == MENU)
        {
            shouldExit = true;
        }

        if (isPausePressed() && slGetMouseButton(SL_MOUSE_BUTTON_LEFT) && currentScreen != PAUSE)
        {
            currentScreen = MENU;
        }
    
}

void drawGameObjects(Paddle& paddle, Ball& ball, Brick brick[quantY][quantX], Player& player, CurrentScreen& currentScreen)
{
    slSetBackColor(0.5, 0.75, 1.0);
    slSetForeColor(1, 1, 1, 1);
    slSetFontSize(fontSize);

    switch (currentScreen)
    {
    case menu::EXIT:
        shouldExit = true;
        break;
    case menu::CREDITS:
        printCredits();
        break;
    case menu::RULES:
        printRules(player);
        break;
    case menu::PLAY:
        drawPaddle(paddle);
        drawBrick(brick);
        drawBall(ball);
        printBackButton(true);
        printLives(player, width, height, fontSize);
        break;
    case menu::MENU:
        updateMenu(currentScreen);
        printMenu(width, height, fontSize, "BREAKOUT");
        break;
    case menu::PAUSE:
        updateMenu(currentScreen);
        printMenu(width, height, fontSize, "PAUSED");
        break;
    default:
        break;
    }


    if (currentScreen == CREDITS || currentScreen == RULES)
    {
        printBackButton(false);
    }
}

void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle, Player& player)
{
    if (checkBallToPaddCollision(ball, paddle))
    {
        ball.y = paddle.y + ball.height + offset;

        //ball.dirY *= -1;
        ball.speedY *= -1;
        ball.speedX = (ball.x - paddle.x) / (paddle.width / 2) * 5;
    }

    if (ball.x < 0 || ball.x > windowWidth)
    {
        if (ball.x < 0)
            ball.x += ball.width;

        if (ball.x > windowWidth)
            ball.x -= ball.width;

        ball.dirX *= -1.f;
    }

    if (ball.y >= windowHeight)
    {
        ball.y -= ball.width;
        ball.dirY *= -1.f;
    }

    if (ball.y < 0)
    {
        restartBall(ball, static_cast<float>(paddle.x), static_cast<float>(paddle.y));
        decreaseLife(player);
    }
}

bool checkBallToPaddCollision(Ball& ball, Paddle paddle)
{
    return (paddle.x + (paddle.width / 2) >= ball.x &&
        paddle.x - (paddle.width / 2) <= ball.x + ball.width &&
        paddle.y + (paddle.height / 2) >= ball.y &&
        paddle.y - (paddle.width / 2) <= ball.y + ball.height);
}

void checkBallToBrickCollision(Ball ball, Brick brick[quantY][quantX])
{
    for (int i = 0; i < quantY; i++)
    {
        for (int j = 0; j < quantX; j++)
        {
            if (brick[i][j].x + (brick[i][j].width / 2) >= ball.x &&
                brick[i][j].x - (brick[i][j].width / 2) <= ball.x + ball.width &&
                brick[i][j].y + (brick[i][j].height / 2) >= ball.y &&
                brick[i][j].y - (brick[i][j].width / 2) <= ball.y + ball.height)
            {
                deactiveBrick(brick, i, j, activeBricksLeft);
            }

        }
    }
}

void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize)
{
    slSetForeColor(1, 1, 1, 1);
    slSetFontSize(fontSize);
    std::string lives = std::to_string(player.lives);
    slText((screenWidth - slGetTextWidth(lives.c_str())), screenHeight - slGetTextHeight(lives.c_str()), lives.c_str());
}

void printFinalMessage(bool won)
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

void printRules(Player player)
{
    slSetForeColor(1, 1, 1, 1);
    std::string lives = std::to_string(player.maxLives);
    std::string text1 = "\t\t\t\tMOVE: \nUse left and right arrow.\n\n\t\t\t\tOBJECTIVE: \n Break all the bricks\n on screen using the ball.\n\n\t\t\t\tYou have " + lives + " lives.\n If the ball falls you loose one\n If you have 0 lives you loose.";

    slText(width / 10, height - fontSize, text1.c_str());
}

void printCredits()
{
    slSetForeColor(1, 1, 1, 1);
    std::string text1 = "Game developed by Daniela Gonzalez";
    std::string text2 = "Paddle texture by Grapho Boy";
    slText(width / 2 - slGetTextWidth(text1.c_str()) / 2, height / 2 - slGetTextHeight(text1.c_str()) / 2, text1.c_str());
    slText(width / 2 - slGetTextWidth(text2.c_str()) / 2, height / 2 - slGetTextHeight(text2.c_str()) - slGetTextHeight(text1.c_str()) / 2 - fontSize, text2.c_str());
}
}