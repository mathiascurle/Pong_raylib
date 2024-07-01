#include "raylib.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "Sounds.h"

int startSpeed = 5;

/* ------Public------ */
Ball::Ball(int centerX, int centerY, float radius, Color color)
{
  m_centerX = centerX;
  m_centerY = centerY;
  m_radius = radius;
  m_color = color;
  m_speedX = 5;
  m_speedY = 5;
  m_increment = 1.1;
  m_restart = false;
  m_pitch = 1;
}

void Ball::drawBall() const
{
  DrawCircle(m_centerX, m_centerY, m_radius, m_color);
}

void Ball::updateBall()
{
  m_centerX += (int)m_speedX;
  m_centerY += (int)m_speedY;

  // If to the right or left
  if (m_centerX + m_radius >= GetScreenWidth() ||
    m_centerX - m_radius <= 0)
  {
    // game over
    m_restart = true;
    PlaySound(Sounds::pong);
    
    if (m_speedX < 0)
    {
      Scoreboard::addScore(0, 1);
      m_speedX = (float)startSpeed * -1;
    }
    else
    {
      Scoreboard::addScore(1, 0);
      m_speedX = (float)startSpeed;
    }
    m_speedY = (float)startSpeed;
    m_pitch = 1;
    Sounds::setPingPitch(m_pitch);
  }

  // If over or under
  if (m_centerY - m_radius <= 0 ||
    m_centerY + m_radius >= GetScreenHeight())
  {
    PlaySound(Sounds::ping);
    m_pitch += 0.1f;
    Sounds::setPingPitch(m_pitch);
    m_speedY *= -1;
  }
}

void Ball::hitPlayer(float upMov, float downMov)
{
  // Movement
  m_speedX *= -1;
  m_speedY -= upMov/ m_speedY;
  m_speedY += downMov/ m_speedY;
  increaseBallSpeed();

  // Sound
  PlaySound(Sounds::ping);
  m_pitch += 0.1f;
  Sounds::setPingPitch(m_pitch);
}

void Ball::hitCorner(float upMov, float downMov)
{
  m_speedY *= -1;
  hitPlayer(upMov, downMov);
}

Vector2 Ball::getCenter()
{
  return Vector2{(float)m_centerX, (float)m_centerY};
}

bool Ball::isRestart() const
{
  return m_restart;
}

void Ball::setRestart(bool b)
{
  m_restart = b;
}

void Ball::setPos(int x, int y)
{
  m_centerX = x;
  m_centerY = y;
}

int Ball::getDir()
{
  if (m_speedX > 0)
    return 1;
  else
    return -1;
}


/* ------ Private ------ */
void Ball::increaseBallSpeed()
{
  m_speedX *= (float)m_increment;
  m_speedY *= (float)m_increment;
}

void Ball::updatePosY(int y)
{
  m_centerY += y;
}

int Ball::getYspeed() const
{
  return (int)m_speedY;
}

