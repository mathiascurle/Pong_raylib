#include "Scoreboard.h"
#include "raylib.h"
#include <string>

int Scoreboard::player1 = 0;
int Scoreboard::player2 = 0;

int x1, x2, y, size;
Vector2 pos1, pos2, org1, org2;
Font font;

Scoreboard::Scoreboard(int width, int height)
{
  x1 = width / 3;
  x2 = x1 * 2;
  y = height / 10;
  size = height / 6;
  org1.x = (float)x1; org1.y = (float)y;
  org2.x = (float)x2; org2.y = (float)y;
  pos1.x = org1.x;
  pos2.x = org2.x - size / 2;
  //font = LoadFont("resources/fonts/mecha.png");
}

void Scoreboard::drawScoreboard()
{
  DrawText(std::to_string(player1).c_str(), (int)pos1.x, y, size, WHITE);
  DrawText(std::to_string(player2).c_str(), (int)pos2.x, y, size, WHITE);
  //DrawTextPro(font, std::to_string(player1).c_str(), pos1, org1, 0, size, 0, WHITE);
  //DrawTextPro(font, std::to_string(player2).c_str(), pos2, org2, 0, size, 0, WHITE);
}

void Scoreboard::addScore(int x1, int x2)
{
  player1 += x1;
  player2 += x2;
}

void Scoreboard::resetScore()
{
  player1 = 0;
  player2 = 0;
}