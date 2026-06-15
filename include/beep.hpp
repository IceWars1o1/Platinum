#pragma once
#include <Windows.h>
#include <cstdio>
#include <conio.h>
#include <string>
#include <iostream>
#include "cursor.hpp"

// --- 第0组 ---
#define A0  27
#define A0s 29    // A#0 / Bb0
#define B0b 29
#define B0  31

// --- 第1组 ---
#define C1  33
#define C1s 35    // C#1 / Db1
#define D1b 35
#define D1  37
#define D1s 39    // D#1 / Eb1
#define E1b 39
#define E1  41
#define F1  44
#define F1s 46    // F#1 / Gb1
#define G1b 46
#define G1  49
#define G1s 52    // G#1 / Ab1
#define A1b 52
#define A1  55
#define A1s 58    // A#1 / Bb1
#define B1b 58
#define B1  62

// --- 第2组 ---
#define C2  65
#define C2s 69    // C#2 / Db2
#define D2b 69
#define D2  73
#define D2s 78    // D#2 / Eb2
#define E2b 78
#define E2  82
#define F2  87
#define F2s 93    // F#2 / Gb2
#define G2b 93
#define G2  98
#define G2s 104   // G#2 / Ab2
#define A2b 104
#define A2  110
#define A2s 117   // A#2 / Bb2
#define B2b 117
#define B2  123

// --- 第3组 ---
#define C3  131
#define C3s 139   // C#3 / Db3
#define D3b 139
#define D3  147
#define D3s 156   // D#3 / Eb3
#define E3b 156
#define E3  165
#define F3  175
#define F3s 185   // F#3 / Gb3
#define G3b 185
#define G3  196
#define G3s 208   // G#3 / Ab3
#define A3b 208
#define A3  220
#define A3s 233   // A#3 / Bb3
#define B3b 233
#define B3  247

// --- 第4组 ---
#define C4  262
#define C4s 277   // C#4 / Db4
#define D4b 277
#define D4  294
#define D4s 311   // D#4 / Eb4
#define E4b 311
#define E4  330
#define F4  349
#define F4s 370   // F#4 / Gb4
#define G4b 370
#define G4  392
#define G4s 415   // G#4 / Ab4
#define A4b 415
#define A4  440   // 标准音A
#define A4s 466   // A#4 / Bb4
#define B4b 466
#define B4  494

// --- 第5组 ---
#define C5  523
#define C5s 554   // C#5 / Db5
#define D5b 554
#define D5  587
#define D5s 622   // D#5 / Eb5
#define E5b 622
#define E5  659
#define F5  698
#define F5s 740   // F#5 / Gb5
#define G5b 740
#define G5  784
#define G5s 831   // G#5 / Ab5
#define A5b 831
#define A5  880
#define A5s 932   // A#5 / Bb5
#define B5b 932
#define B5  988

// --- 第6组 ---
#define C6  1047
#define C6s 1109  // C#6 / Db6
#define D6b 1109
#define D6  1175
#define D6s 1245  // D#6 / Eb6
#define E6b 1245
#define E6  1319
#define F6  1397
#define F6s 1480  // F#6 / Gb6
#define G6b 1480
#define G6  1568
#define G6s 1661  // G#6 / Ab6
#define A6b 1661
#define A6  1760
#define A6s 1865  // A#6 / Bb6
#define B6b 1865
#define B6  1976

// --- 第7组 ---
#define C7  2093
#define C7s 2217  // C#7 / Db7
#define D7b 2217
#define D7  2349
#define D7s 2489  // D#7 / Eb7
#define E7b 2489
#define E7  2637
#define F7  2794
#define F7s 2960  // F#7 / Gb7
#define G7b 2960
#define G7  3136
#define G7s 3322  // G#7 / Ab7
#define A7b 3322
#define A7  3520
#define A7s 3729  // A#7 / Bb7
#define B7b 3729
#define B7  3951

// --- 第8组 ---
#define C8  4186

double bpm=120, tone=4;

double baseSpeed(int noteType) {
    return 60000.0 / (bpm * noteType / tone);
}
