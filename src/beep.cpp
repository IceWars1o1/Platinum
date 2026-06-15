#include "../include/beep.hpp"
#include "beep/0x00000001.cpp"

namespace pt{
    const int COUNT = 1;
    int chooser(){
        printf("List:\n");
        for(int i = 0; i < COUNT; i++){
            printf("%d.\t", i+1);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WriteConsoleW(hConsole, name.c_str(), name.length(), nullptr, nullptr);
            printf("\n");
        }
        printf("Please enter the number: ");
        int choice = 0;
        scanf("%d", &choice);
        return choice;
    }
    void player(){
        switch(chooser()){
            case 1:
                playShangChunShan();
                break;
            default:
                break;
        }
    }
}