#include "raylib.h"
#include "Constants.h"
#include "Ball.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Gamestate.h"
#include "StartMenu.h"
#include "Playing.h"
#include "Sounds.h"

int main()
{
  // Init stuff
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Pong Game!");
  SetTargetFPS(60);
  Sounds::Init();
  
  // Init objects
  Gamestate state = START_MENU;
  Scoreboard scoreboard(SCREEN_WIDTH, SCREEN_HEIGHT);
  Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20.f, WHITE);
  Player player1(10, (int)(SCREEN_HEIGHT / 2 - 60), 1, WHITE, &ball);
  Player player2(SCREEN_WIDTH - 35, (int)(SCREEN_HEIGHT / 2 - 60), 2, WHITE, &ball);

  // State classes
  StartMenu startMenu(&state, &player1, &player2);
  Playing playing(&state, &ball, &player1, &player2, &scoreboard);

  // Game loop
  while (!WindowShouldClose())
  {
    switch (state)
    {
      case (START_MENU):
        startMenu.UpdateStartMenu();
        startMenu.DrawStartMenu();
        break;
      case (PLAYING):
        playing.UpdatePlaying();
        playing.DrawPlaying();
        break;
      case (PAUSE_MENU):
        break;
      default:
        break;
    }
  }

  // Close stuff
  Sounds::Close();
  CloseWindow();
  return 0;
}
