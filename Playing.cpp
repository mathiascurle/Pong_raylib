#include "Playing.h"
#include "Constants.h"

Playing::Playing(Gamestate* state, Ball* ball, Player* player1, Player* player2, Scoreboard* scoreboard)
{
  m_statePtr = state;
  m_ballPtr = ball;
  m_player1Ptr = player1;
  m_player2Ptr = player2;
  m_scoreboardPtr = scoreboard;
}

void Playing::UpdatePlaying()
{
  if (IsKeyPressed(KEY_M))
  {
    m_scoreboardPtr->resetScore();
    m_ballPtr->setRestart(true); 
    *m_statePtr = Gamestate::START_MENU;
  }

  m_ballPtr->updateBall();
  if (m_ballPtr->isRestart())
  {
    m_ballPtr->setRestart(false);
    m_ballPtr->setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  }
  m_player1Ptr->updatePlayer();
  m_player2Ptr->updatePlayer();
}
void Playing::DrawPlaying()
{
  BeginDrawing();
  ClearBackground(BLACK);

  DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
  m_scoreboardPtr->drawScoreboard();
  m_ballPtr->drawBall();
  m_player1Ptr->drawPlayer();
  m_player2Ptr->drawPlayer();

  EndDrawing();
}