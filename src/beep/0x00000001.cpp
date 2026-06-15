#include "base.cpp"

namespace pt{
    const std::wstring name = L"上春山";
    void playShangChunShan() {
        bpm = 132; tone = 4;
        
        CLEAR();
        MOVETO(0, 0);
        std::wstring output = L"Now Playing: " + name + L"\n";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WriteConsoleW(hConsole, output.c_str(), output.length(), nullptr, nullptr);
        printf("BPM: %.2lf, Tone: %.0lf\n", bpm, tone);
        int i = 0;
        e(E5, true);    s(C5s); e(B4);  e(C5s); e(E5);  e(E5);  e(E5);  s(C5s); s(B4);
        e(G4s, true);   s(B4);  e(C5s); e(G4s); e(B4);  e(B4);  e(B4);  e(G4s);
        q(C5s); e(B4);  e(G4s); e(F4s); e(E4);  e(0);   e(C4s);
        q(E4);  e(0);   s(E4);  s(F4s); e(E4);  e(E4);  q(E4);

        q(B4);  q(B4);  q(B4);  e(G4s); e(F4s);
        q(F4s, true);   e(G4s); q(B4);  e(G4s); e(F4s);
        q(E4);  e(E4);  e(C4s); q(E4);  q(F4s);
        q(C5s); e(B4);  e(B4);  h(B4);
        q(C5s); e(B4);  e(C5s); q(E5);  e(C5s); e(B4);
        q(G4s); e(F4s); e(G4s); e(B4);  e(C5s); q(B4);
        e(F4s); e(G4s); e(F4s); e(E4);  q(C4s); e(G4s); e(F4s);
        h(F4s); e(C4s); e(B3);  q(B3);

        for (i = 1; i <= 2; i++){
            q(B4);  q(B4);  q(B4);  e(G4s); e(F4s);
            q(F4s, true);   e(G4s); q(B4);  e(G4s); e(F4s);
            q(E4);  e(E4);  e(C4s); q(E4);  q(F4s);
            q(C5s); e(B4);  e(B4);  h(B4);
            q(C5s); e(B4);  e(C5s); q(E5);  e(C5s); e(B4);
            q(G4s); e(F4s); e(G4s); e(B4);  e(C5s); q(B4);
            e(F4s); e(G4s); e(F4s); e(E4);  q(C4s); e(F4s); e(E4);
            w(E4);
            if (i == 1){e(E5);  s(E5);  s(F5s); e(E5);  e(C5s); e(E5);  e(F5s); q(E5); }

            q(C5s); e(B4);  e(C5s); h(E5);
            e(G4s); s(B4);  s(G4s); e(F4s); e(G4s); h(B4);
            q(C5s); e(B4);  e(G4s); q(F4s); e(E4);  e(C4s); 
            q(C5s); e(B4);  e(F4s); h(G4s);
            q(C5s); e(B4);  e(C5s); h(E5);
            e(G4s); s(B4);  s(G4s); e(F4s); e(G4s); h(B4);
            q(C5s); e(B4);  e(G4s); q(F4s); e(E4);  e(C4s); 
            q(E4);  e(E4);  e(F4s); h(E4);

            if (i == 1){e(B3, true);    s(C4s); e(E4);  e(G4s); e(B4);  e(B4);  e(B4);  e(B4);
                        e(C5s); s(B4);  s(C5s); e(E5);  e(C5s); e(B4);  e(B4);  q(B4);
                        e(B3, true);    s(C4s); e(E4);  e(G4s); e(B4);  e(B4);  e(B4);  e(B4);
                        e(C5s); e(B4);  e(B4);  e(G4s); e(F4s); e(F4s); q(F4s);
                        e(E4, true);    s(E4);  e(E4);  e(C4s); e(E4);  e(E4);  e(E4);  e(G4s);
                        e(C5s); e(B4);  e(B4);  e(G4s); e(C5s); s(B4);  s(C5s); e(B4);  e(G4s);
                        q(F4s, true);   s(F4s); e(F4s); e(G4s); e(F4s); e(E4);  e(C4s); e(B3);
                        q(E4);  e(0);   s(E4);  s(F4s); e(E4);  e(E4);  q(E4);
                        continue;}
            if (i == 2){h(E5);  e(0);   e(B4);  e(G5s); e(F5s);
                        h(E5);  e(0);   e(B4);  e(G5s); e(F5s);
                        q(E5, true);    e(F5s); e(E5);  s(F5s); s(E5);  e(C5s); e(A4);
                        h(B4, true);    e(G4s); e(B4);
                        q(C5s, true);   e(E5);  q(B4);  e(C5s); e(G4s);
                        q(F4s); e(G4s); e(B4);  h(C5s);
                        e(C5s); e(E5);  e(F5s); e(G5s); e(B5);  e(G5s); e(F5s); e(C5s);
                        w(E5);
                        w(F5s);}
        }
        for (i = 1; i <= 2; i++){
            q(D5);  e(C5);  e(D5);  h(F5);
            e(A4);  s(C5);  s(A4);  e(G4);  e(A4);  h(C5);
            q(D5);  e(C5);  e(A4);  q(G4);  e(F4);  e(D4);
            q(D5);  e(C5);  e(G4);  h(A4);
            q(D5);  e(C5);  e(D5);  h(F5);
            e(A4);  s(C5);  s(A4);  e(G4);  e(A4);  h(C5);
            q(D5);  e(C5);  e(A4);  q(G4);  e(F4);  e(D4);
            q(F4);  e(F4);  e(G4);  h(F4);
        }
        q(D5);  e(C5);  e(A4);  q(G4);  e(F4);  e(D4);
        q(F4);  e(F4);  e(G4);  h(F4);
        q(F5);  q(D5);  q(F5);  q(0);
        bpm = 120; tone = 4;
        return;
    }
}