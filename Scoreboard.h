#pragma once
class Scoreboard
{
public:
  static int player1, player2;

public:
  Scoreboard(int width, int height);

  static void drawScoreboard();

  static void addScore(int x1, int x2);

  static void resetScore();

};