#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "StartMenu.h"
#include "Constants.h"
#include "Sounds.h"

#define MAX_AMOUNT_CONTROLLERS_TO_LOOK_THROUGH 5

StartMenu::StartMenu(Gamestate* state, Player* player1, Player* player2)
{
  m_statePtr = state;
  m_status1 = false;
  m_status2 = false;
  m_player1Ptr = player1;
  m_player2Ptr = player2;
  m_gamepad = 0;
  m_firstUpdate = true;
  m_musicOn = true;
  m_fadeMusicToLoad = false;
  m_chosenMusicVolume = 0.5f;
  m_currentMusicVolume = m_chosenMusicVolume;
}

float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]

void StartMenu::UpdateStartMenu()
{
  // Music
  if (m_firstUpdate && m_musicOn)
    StartMusic();
  updateMusic();

  // Inputs
  if (IsKeyPressed(KEY_ENTER))
  {
    m_fadeMusicToLoad = true;
  }

  // Assigning gamepad if up button is pressed
  if (IsGamepadAvailable(m_gamepad))
  {
    if (IsGamepadButtonDown(m_gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
    {
      if (!m_status1)
      {
        m_status1 = true;
        m_player1Ptr->setGamepad(m_gamepad);
      }
      else if (m_gamepad != m_player1Ptr->getGamepad())
      {
        m_status2 = true;
        m_player2Ptr->setGamepad(m_gamepad);
      }
    }
  }
  if (++m_gamepad >= MAX_AMOUNT_CONTROLLERS_TO_LOOK_THROUGH) m_gamepad = 0;
}

void StartMenu::DrawStartMenu()
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Buttons
  if (GuiButton(Rectangle{ 10,200,100,50 }, "Toggle music"))
    m_musicOn = !m_musicOn;


  // Text
  DrawText(TextFormat("Press up on controller %d", m_status1 ? 2 : 1), 10, 25, 50, GRAY);
  DrawText(TextFormat("Player 1 controller status: %s", m_status1 ? "ready!" : "waiting"), 10, 100, 20, GRAY);
  DrawText(TextFormat("Player 2 controller status: %s", m_status2 ? "ready!" : "waiting"), 10, 150, 20, GRAY);

  if (m_status1 && m_status2) // If both controllers are assigned
  {
    DrawText("Press enter or 'A' to start", 10, SCREEN_HEIGHT - 200, 70, RED);
    if (IsGamepadButtonDown(m_player1Ptr->getGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) *m_statePtr = PLAYING;
    if (IsGamepadButtonDown(m_player2Ptr->getGamepad(), GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) *m_statePtr = PLAYING;
  }

  EndDrawing();
}

void StartMenu::StartMusic()
{
  m_firstUpdate = false;
  m_currentMusicVolume = m_chosenMusicVolume;
  SetMusicVolume(Sounds::startMusic, m_chosenMusicVolume);
  PlayMusicStream(Sounds::startMusic);
}


void StartMenu::updateMusic()
{
  if (!m_musicOn)
  {
    if (!IsMusicStreamPlaying(Sounds::startMusic))
      return;
    fadeOutMusic(2.0f);
  }
  else if (m_fadeMusicToLoad)
    fadeOutMusic(3.0f);

  // Music
  UpdateMusicStream(Sounds::startMusic);

  // Get normalized time played for current music stream
  timePlayed = GetMusicTimePlayed(Sounds::startMusic) / GetMusicTimeLength(Sounds::startMusic);

  if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music

}

void StartMenu::setGamestate(Gamestate state)
{
  m_firstUpdate = true;
  *m_statePtr = state;
}

void StartMenu::fadeOutMusic(float timeToFade)
{
  float deltaAmount = 1.0f / (timeToFade * (60 / m_chosenMusicVolume));
  m_currentMusicVolume -= deltaAmount;

  if (m_currentMusicVolume <= 0)
  {
    StopMusicStream(Sounds::startMusic);
    //m_currentMusicVolume = m_chosenMusicVolume;
    m_firstUpdate = true;
    if (m_fadeMusicToLoad)
      setGamestate(Gamestate::PLAYING);
    m_fadeMusicToLoad = false;
    return;
  }
  SetMusicVolume(Sounds::startMusic, m_currentMusicVolume);
}