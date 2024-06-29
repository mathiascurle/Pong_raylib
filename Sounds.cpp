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

  SetSoundVolume(ping, 1.0f);
  SetSoundVolume(pong, 1.0f);
  //SetMusicVolume(startMusic, 1.0f);
  SetMasterVolume(s_masterVolume);
}

void Sounds::Close()
{
  UnloadSound(ping);
  UnloadSound(pong);
  UnloadMusicStream(startMusic);

  CloseAudioDevice();
}

void Sounds::setPingPitch(float pitch)
{
  SetSoundPitch(ping, pitch);
}
