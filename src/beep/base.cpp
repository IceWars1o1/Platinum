#include "../../include/beep.hpp"

namespace pt{
    void playNote(int sound, int noteType, bool dot = false) {
        double duration = baseSpeed(noteType);
        if (dot) duration *= 1.5;
        if (sound) Beep(sound, (int)duration);
        else Sleep(duration);
        printf("Freq: %d, Duration: %.1f ms\n", sound, duration);
        // Sleep(50);
    }
    void w(int sound, bool dot = false) { playNote(sound,  1, dot); }
    void h(int sound, bool dot = false) { playNote(sound,  2, dot); }
    void q(int sound, bool dot = false) { playNote(sound,  4, dot); }
    void e(int sound, bool dot = false) { playNote(sound,  8, dot); }
    void s(int sound, bool dot = false) { playNote(sound, 16, dot); }
}