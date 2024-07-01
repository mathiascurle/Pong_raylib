#include "raylib.h"
#include "Player.h"

/* ------Public------ */
Player::Player(int posX, int posY, int playerNr, Color color, Ball* ball)
{
  m_posX = posX;
  m_posY = posY;
  m_color = color;
  m_playerNr = playerNr;
  m_ballPtr = ball;
  m_width = 25;
  m_height = 100;
  m_speedDefault = 5;
  m_gamepad = -1;

  m_upKey = 0;
  m_downKey = 0;
  if (playerNr == 1)
  { m_upKey = KEY_W;
  m_downKey = KEY_S;}
  else if (playerNr == 2)
  { m_upKey = KEY_UP;
  m_downKey = KEY_DOWN;}
}

void Player::drawPlayer()
{
  DrawRectangle(m_posX, m_posY, m_width, m_height, m_color);
}

void Player::updatePlayer()
{
  float speedUp = 0.0f;
  float speedDown = 0.0f;
  Vector2 ballPos = m_ballPtr->getCenter();

  // ------ Inputs ------

  // // A button - speed boost
  if (IsGamepadButtonDown(m_gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    m_speedDefault = 7;
  else m_speedDefault = 5;

  // D-pad/Keyboard - up
  if (IsKeyDown(m_upKey) || IsGamepadButtonDown(m_gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
    speedUp = (float)m_speedDefault;
  else if (GetGamepadAxisMovement(m_gamepad, 1) <= 0) // Joystick - up
    speedUp = GetGamepadAxisMovement(m_gamepad, 1) * ((m_speedDefault + 2) * -1);

  // D-pad/Keyboard - down
  if (IsKeyDown(m_downKey) || IsGamepadButtonDown(m_gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    speedDown = (float)m_speedDefault;
  else if (GetGamepadAxisMovement(m_gamepad, 1) >= 0) // Joystick - down
    speedDown = GetGamepadAxisMovement(m_gamepad, 1) * (m_speedDefault + 2);

  goUp(speedUp);
  goDown(speedDown);

  // ------ Ball hit ------
  collisionDetect(speedUp, speedDown);
}

// Getters and setters
void Player::setGamepad(int gamepad)
{
  m_gamepad = gamepad;
}

int Player::getGamepad()
{
  return m_gamepad;
}



/* ------Private------ */
void Player::goUp(float speed)
{
  if (m_posY <= 0) m_posY = 0;
  else m_posY -= (int)speed;
}

void Player::goDown(float speed)
{
  if (m_posY + m_height >= GetScreenHeight()) m_posY = GetScreenHeight() - m_height;
  else m_posY += (int)speed;
}

// Skriv om!!!
void Player::collisionDetect(float speedUp, float speedDown)
{
  Vector2 ballPos = m_ballPtr->getCenter();

  // int ballSide = 0;
  // if (m_playerNr == 1)
  // {
  //   ballSide = ballPos.x - 20; // left
  //   if (ballSide <= getSurfaceX())
  //   {
  //     if (ballPos.y >= getTop() &&
  //       ballPos.y <= getBottom())
  //     {
  //       m_ballPtr->hitPlayer(speedUp, speedDown);
  //     }
  //   }
  // }
  // else if (m_playerNr == 2)
  // {
  //   ballSide = ballPos.x + 20; // right
  //   if (ballSide >= getSurfaceX())
  //   {
  //     if (ballPos.y >= getTop() &&
  //       ballPos.y <= getBottom())
  //     {
  //       m_ballPtr->hitPlayer(speedUp, speedDown);
  //     }
  //   }
  // }

  // if (CheckCollisionCircleRec(ballPos, 20.f, { (float)m_posX, (float)m_posY, (float)m_width, (float)m_height }))
  // {
  //   if (m_playerNr == 1)
  //   {
  //     if (m_ballPtr->getDir() == -1)
  //     {
  //       m_ballPtr->hitPlayer(speedUp, speedDown);
  //     }
  //   }
  //   else if (m_playerNr == 2)
  //   {
  //     if (m_ballPtr->getDir() == 1)
  //     {
  //       m_ballPtr->hitPlayer(speedUp, speedDown);
  //     }
  //   }
  // }


  // make get function
  float radius = 20.f;

  if (m_playerNr == 1)
  {
    if (ballPos.x - radius <= getSurfaceX() &&
      m_ballPtr->getDir() == -1) // if ball surface is beyond paddle face
    {
      if (ballPos.y <= m_posY + m_height &&
        ballPos.y >= m_posY) // if ball is between paddle top and bottom
      {
        m_ballPtr->hitPlayer(speedUp, speedDown);
      }
      else // if over or under paddle
      {
        if (ballPos.x - (radius / 1.4f) < getSurfaceX()) // if corner of ball is beyond paddle surface
        {
          if (ballPos.y < m_posY) // if over paddle
          {
            if (ballPos.y + (radius / 1.4f) > m_posY) // if ball corner y is in paddle
            {
              m_ballPtr->hitCorner(speedUp, speedDown);
            }
          }
          else if (ballPos.y > m_posY) // if under paddle
          {
            if (ballPos.y - (radius / 1.4f) < m_posY + m_height) // if ball corner y is in paddle
            {
              m_ballPtr->hitCorner(speedUp, speedDown);
            }
          }
        }
      }
    }
  }
  else if (m_playerNr == 2)
  {
    if (ballPos.x + radius >= getSurfaceX() &&
        m_ballPtr->getDir() == 1) // if ball surface is beyond paddle face
    {
      if (ballPos.y <= m_posY + m_height &&
          ballPos.y >= m_posY) // if ball is between paddle top and bottom
      {
        m_ballPtr->hitPlayer(speedUp, speedDown);
      }
      else // if over or under paddle
      {
        if (ballPos.x + (radius / 1.4f) > getSurfaceX()) // if corner of ball is beyond paddle surface
        {
          if (ballPos.y < m_posY) // if over paddle
          {
            if (ballPos.y + (radius / 1.4f) > m_posY) // if ball corner y is in paddle
            {
              m_ballPtr->hitCorner(speedUp, speedDown);
            }
          }
          else if (ballPos.y > m_posY) // if under paddle
          {
            if (ballPos.y - (radius / 1.4f) < m_posY + m_height) // if ball corner y is in paddle
            {
              m_ballPtr->hitCorner(speedUp, speedDown);
            }
          }
        }
      }
    }
  }

}

// Getters and setters
int Player::getSurfaceX()
{
  if (m_playerNr == 1) return m_posX + m_width;
  else if (m_playerNr == 2) return m_posX;
  return 0;
}

int Player::getTop()
{
  return m_posY;
}

int Player::getBottom()
{
  return m_posY + m_height;
}

