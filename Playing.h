#pragma once
#include "Gamestate.h"
#include "Ball.h"
#include "Player.h"
#include "Scoreboard.h"

class Playing
{
public:
  Playing(Gamestate* state, Ball* ball, Player* player1, Player* player2, Scoreboard* scoreboard);
  void UpdatePlaying();
  void DrawPlaying();

private:
  Gamestate*    m_statePtr;
  Ball*         m_ballPtr;
  Player*       m_player1Ptr;
  Player*       m_player2Ptr;
  Scoreboard*   m_scoreboardPtr;

};

