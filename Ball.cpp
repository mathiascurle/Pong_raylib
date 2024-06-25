//#include <iostream>
#include "raylib.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "Sounds.h"

int startSpeed = 5;

Ball::Ball(int centerX, int centerY, float radius, Color color)
{
  this->centerX = centerX;
  this->centerY = centerY;
  this->radius = radius;
  this->color = color;
  speedX = 5;
  speedY = 5;
  increment = 1.1;
  restart = false;
  pitch = 1;
}

void Ball::drawBall() const
{
  DrawCircle(centerX, centerY, radius, color);
}

void Ball::updateBall()
{
  centerX += (int)speedX;
  centerY += (int)speedY;

  // If to the right or left
  if (centerX + radius >= GetScreenWidth() ||
    centerX - radius <= 0)
  {
    // game over
    restart = true;
    PlaySound(Sounds::pong);
    if (speedX < 0)
    {
      Scoreboard::addScore(0, 1);
      speedX = (float)startSpeed * -1;
    }
    else
    {
      Scoreboard::addScore(1, 0);
      speedX = (float)startSpeed;
    }
    speedY = (float)startSpeed;
    SetSoundPitch(Sounds::ping, 1);
  }

  // If over or under
  if (centerY - radius <= 0 ||
    centerY + radius >= GetScreenHeight())
  {
    PlaySound(Sounds::ping);
    pitch += 0.1;
    SetSoundPitch(Sounds::ping, pitch);
    speedY *= -1;
  }
}

void Ball::increaseBallSpeed()
{
  speedX *= (float)increment;
  speedY *= (float)increment;
}

Vector2 Ball::getCenter()
{
  return Vector2{(float)centerX, (float)centerY};
  //outCenter.x = (float)this->centerX;
  //outCenter.y = (float)this->centerY;
  //return outCenter;
}

void Ball::hitPlayer()
{
  speedX *= -1;
  PlaySound(Sounds::ping);
  pitch += 0.1;
  SetSoundPitch(Sounds::ping,pitch);
  increaseBallSpeed();
}

void Ball::setRestart(bool b)
{
  restart = b;
}

bool Ball::isRestart() const
{
  return restart;
}

void Ball::setPos(int x, int y)
{
  centerX = x;
  centerY = y;
}

void Ball::updatePosY(int y)
{
  centerY += y;
}

int Ball::getYspeed() const
{
  return (int)speedY;
}
