#pragma once
#include "Gamestate.h"
#include "Player.h"
#include <thread>

class StartMenu
{
public:
  StartMenu(Gamestate* state, Player* player1, Player* player2);
  void UpdateStartMenu();
  void DrawStartMenu();
  void StartMusic();
  
private:
  void setGamestate(Gamestate state);
  void updateMusic();
  void fadeOutMusic(float time);

private:
  Gamestate*   m_statePtr;
  bool         m_status1;
  bool         m_status2;
  Player*      m_player1Ptr;
  Player*      m_player2Ptr;
  int          m_gamepad;
  bool         m_firstUpdate;
  bool         m_musicOn;
  bool         m_fadeOutMusic;
  float        m_setMusicVolume;
  float        m_currentMusicVolume;

};