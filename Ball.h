#pragma once
#include "raylib.h"

class Ball
{
private:
  int centerX, centerY;
  float speedX, speedY;
  double increment;
  float radius;
  Color color;
  bool restart;
  float pitch;

public:
  Ball(int centerX, int centerY, float radius, Color color);

  Ball() = default;

  void drawBall() const;

  void updateBall();

  void increaseBallSpeed();

  Vector2 getCenter();

  void hitPlayer();

  void setRestart(bool b);

  bool isRestart() const;

  void setPos(int x, int y);

  void updatePosY(int y);

  int getYspeed() const;

};