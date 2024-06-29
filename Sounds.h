#pragma once
#include "raylib.h"

class Sounds
{
public:
  static void Init();
  static void Close();

  static void setPingPitch(float pitch);

public:
  static Sound ping;
  static Sound pong;

  static Music startMusic;

  static float s_masterVolume;

};