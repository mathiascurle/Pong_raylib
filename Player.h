#pragma once
#include "Ball.h"

class Player
{
public:
  Player(int posX, int posY, int playerNr, Color color, Ball* ball);

  void drawPlayer();
  void updatePlayer();

  // Getters and setters
  void setGamepad(int gamepad);
  int getGamepad();

private:
  void goUp(float speed);
  void goDown(float speed);
  void collisionDetect(float speedUp, float speedDown);

  // Getters and setters
  int getSurfaceX();
  int getTop();
  int getBottom();

private:
  int     m_posX, m_posY;
  int     m_width, m_height;
  int     m_speedDefault;
  int     m_playerNr;
  int     m_upKey, m_downKey;
  int     m_gamepad;
  Color   m_color;
  Ball*   m_ballPtr;

};