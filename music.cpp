#include "music.h"

void playBackgroundMusic(const wchar_t* filename) {
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void stopMusic() {
    PlaySound(NULL, NULL, 0);
}
void playSoundEffect(const wchar_t* filename) {
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}