#pragma once
#include "Ball.h"

class Player
{
public:
  Player(int posX, int posY, int playerNr, Color color, Ball* ball);
  Player() = default;

  void drawPlayer();
  void updatePlayer();
  void goUp(float speed);
  void goDown(float speed);

  // Getters and setters
  int getSurfaceX();
  int getTop();
  int getBottom();
  void setGamepad(int gamepad);
  int getGamepad();

private:
  int posX, posY;
  int width, height;
  int speedDefault;
  int playerNr;
  int upKey, downKey;
  int gamepad;
  Color color;
  Ball* ballPtr;

};