#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <iostream>
#include <windows.h>


void playBackgroundMusic(const wchar_t* filename);
void stopMusic();
void playSoundEffect(const wchar_t* filename);

#endif // MUSIC_H