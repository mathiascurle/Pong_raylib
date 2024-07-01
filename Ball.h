#pragma once
#include "raylib.h"

class Ball
{
private:
  int     m_centerX, m_centerY;
  float   m_speedX, m_speedY;
  double  m_increment;
  float   m_radius;
  Color   m_color;
  bool    m_restart;
  float   m_pitch;

public:
  Ball(int centerX, int centerY, float radius, Color color);
  void drawBall() const;
  void updateBall();
  void hitPlayer(float upMov, float downMov);
  void hitCorner(float upMov, float downMov);
  Vector2 getCenter();
  bool isRestart() const;
  void setRestart(bool b);
  void setPos(int x, int y);
  int getDir();

private:
  void increaseBallSpeed();
  void updatePosY(int y);
  int getYspeed() const;

};