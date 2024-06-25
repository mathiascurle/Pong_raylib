#include "raylib.h"
#include "Player.h"

Player::Player(int posX, int posY, int playerNr, Color color, Ball* ball)
{
  this->posX = posX;
  this->posY = posY;
  this->color = color;
  this->playerNr = playerNr;
  this->ballPtr = ball;
  width = 25;
  height = 100;
  speedDefault = 5;
  gamepad = 0;

  upKey = 0;
  downKey = 0;
  if (playerNr == 1)
  { upKey = KEY_W;
    downKey = KEY_S;}
  else if (playerNr == 2)
  { upKey = KEY_UP;
    downKey = KEY_DOWN;}
}

void Player::drawPlayer()
{
  DrawRectangle(posX, posY, width, height, color);
}

void Player::updatePlayer()
{
  int ballX = (int)ballPtr->getCenter().x;
  int ballY = (int)ballPtr->getCenter().y;

  // ------ Ball hit ------
  int ballSide = 0;
  if (playerNr == 1)
  {
    ballSide = ballX - 20; // left
    if (ballSide <= getSurfaceX())
    {
      if (ballY >= getTop() &&
        ballY <= getBottom())
      {
        ballPtr->hitPlayer();
      }
    }
  }
  else if (playerNr == 2)
  {
    ballSide = ballX + 20; // right
    if (ballSide >= getSurfaceX())
    {
      if (ballY >= getTop() &&
        ballY <= getBottom())
      {
        ballPtr->hitPlayer();
      }
    }
  }

  // ------ Inputs ------
  
  // A button - speed boost
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    speedDefault = 7;
  else speedDefault = 5;

  // D-pad/Keyboard - up/down
  if (IsKeyDown(upKey) || IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
    goUp((float)speedDefault);
  if (IsKeyDown(downKey) || IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    goDown((float)speedDefault);

  // Joystick - up/down
  if (GetGamepadAxisMovement(gamepad, 1) <= 0)
    goUp(GetGamepadAxisMovement(gamepad, 1) * ((speedDefault+2) * -1));
  if (GetGamepadAxisMovement(gamepad, 1) >= 0)
    goDown(GetGamepadAxisMovement(gamepad, 1) * (speedDefault + 2));
}

void Player::goUp(float speed)
{
  if (posY <= 0) posY = 0;
  else posY -= (int)speed;
}

void Player::goDown(float speed)
{
  if (posY + height >= GetScreenHeight()) posY = GetScreenHeight() - height;
  else posY += (int)speed;
}


// Getters ant setters
int Player::getSurfaceX()
{
  if (playerNr == 1) return posX + width;
  else if (playerNr == 2) return posX;
  return 0;
}

int Player::getTop()
{
  return posY;
}

int Player::getBottom()
{
  return posY + height;
}

void Player::setGamepad(int gamepad)
{
  this->gamepad = gamepad;
}

int Player::getGamepad()
{
  return gamepad;
}
