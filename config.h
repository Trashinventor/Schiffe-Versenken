#pragma once

typedef struct setting{
    int difficulty;
    int gamemode;
    int play;
     struct anzahl{
        int Minensuchboote;
        int Fregatten;
        int Kreuzer;
        int Schlachtschiffe;
    }anzahl;
}setting;
extern setting settings;