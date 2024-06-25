#include "Sounds.h"

Sound Sounds::ping;
Sound Sounds::pong;
Music Sounds::startMusic;

float Sounds::s_masterVolume = 0.5f;

void Sounds::Init()
{
  InitAudioDevice();

  ping = LoadSound("resources/Ping.wav");
  pong = LoadSound("resources/Pong.wav");
  startMusic = LoadMusicStream("resources/Ambient Pluck.wav");

  SetSoundVolume(ping, 1);
  SetSoundVolume(pong, 1);
  SetMusicVolume(startMusic, 1);
  SetMasterVolume(s_masterVolume);
}

void Sounds::Close()
{
  UnloadSound(ping);
  UnloadSound(pong);
  UnloadMusicStream(startMusic);

  CloseAudioDevice();
}

