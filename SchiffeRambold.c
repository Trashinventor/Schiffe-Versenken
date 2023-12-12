#include "SchiffeRambold.h"

char* timePassed;             //verstrichene Zeit seit Spielbeginn ?
extern int player1points;     //Eigene Punkte
extern int player2points;     //Gegnerische Punkte
char spielfeld1[100];         //Eigenes Spielfeld
char spielfeld2[100];         //Gegnerisches Spielfeld

int schiffslaenge;            //Länge des Schiffs in Feldern
int schiffstyp=0;             //Art des Schiffs (siehe switch(schiffstyp))
char richtung;                //Orientierung des Schiffs in Himmelsrichtung (N, O, S, W)
int IntRichtung;              //Orientierung des Schiffs in Zahlen (1-4 im Uhrzeigersinn beginnend bei Norden)
int IntKoordinaten;           //Koordinaten des ersten Schiffsfeldes in Arrayform (Feld Nr. 0-99)
char X;                       //X-Anteil der Koordinaten (A-J)
int Y;                        //Y-Anteil der Koordinaten (1-10)
COORD Cursor;                 //Cursor-Position im cmd-Fenster

//Spielfeld initialisieren
void initSpielfeld(){
    //Initialisierung des Timers
    time_t start = time(NULL);
    timer(start);
    timePassed = timer(start);
    player1points=0;                                   //Eigene Punkte
    player2points=0;                                   //Gegnerische Punkte
    spielfeld1[100];                                  //Eigenes Spielfeld
    spielfeld2[100];                                  //Gegnerisches Spielfeld
    
//Initialisierung des Spielfelds mit Platzhaltersymbolen
    for(int i=0;i<100;i++){
        spielfeld1[i]='~';
        spielfeld2[i]='~';
    }
}

//Mainmenü 
int menu(void){
        system("cls");
    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    COORD Cursor;
        int userinput;
    do{

        b:
        menuPrint(0);
        printf("\n");
        Cursor.X=Screen.dwSize.X/2;
        Cursor.Y=17;
        SetConsoleCursorPosition(hStdOut,Cursor);
        scanf("%d",&userinput);
        if(userinput<1 || userinput>5){
            clear();
            goto b;
        }
        switch(userinput){

            case 1:
                menuPrint(1);
                scanf("%d",&userinput);
                switch(userinput){
                    case 1: settings.gamemode =1; break;
                    case 2: settings.gamemode =2; break;
                    case 3: break;
                } break;
            case 2:
                menuPrint(2);
                scanf("%d",&userinput);
                switch(userinput){
                    case 1: settings.difficulty=1; break;
                    case 2: settings.difficulty=2; break;
                    case 3: settings.difficulty=3; break;
                    case 4: break;
                } break;
            case 3:
                menuPrint(3);
                Cursor.X=(EBENE_1);
                Cursor.Y=23;
                SetConsoleCursorPosition(hStdOut,Cursor);
                printf("\n\n");
                system("pause");
                break;
            case 4:
                settings.play=1; 
                break;
            case 5:
                return 0;
            break;
    }}while(userinput!=4);
    
    system("cls");
}

//Vorspann des Spiels
void startupscreen(){

    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    
    drawBox(Screen.dwSize.Y-1,Screen.dwSize.X);

    COORD Cursor;
    Cursor.Y=(Screen.dwSize.Y/2)-7;

    TextCentered("_______.  ______  __    __   __   _______  _______  _______",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("/       | /      ||  |  |  | |  | |   ____||   ____||   ____|",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("|   (----`|  ,----'|  |__|  | |  | |  |__   |  |__   |  |__   ",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("\\   \\    |  |     |   __   | |  | |   __|  |   __|  |   __|  ",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered(".----)   |   |  `----.|  |  |  | |  | |  |     |  |     |  |____    ",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("|_______/     \\______||__|  |__| |__| |__|     |__|     |_______|   ",Cursor.Y,0,BOLD);
    Cursor.Y+=2;
    TextCentered("____    ____  _______ .______          _______. _______ .__   __.  __  ___  _______ .__   __. ",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("\\   \\  /   / |   ____||   _  \\        /       ||   ____||  \\ |  | |  |/  / |   ____||  \\ |  | ",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("\\   \\/   /  |  |__   |  |_)  |      |   (----`|  |__   |   \\|  | |  '  /  |  |__   |   \\|  |",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("\\      /   |   __|  |      /        \\   \\    |   __|  |  . `  | |    <   |   __|  |  . `  |",Cursor.Y,0,BOLD);
    Cursor.Y++;
    TextCentered("\\    /    |  |____ |  |\\  \\----.----)   |   |  |____ |  |\\   | |  .  \\  |  |____ |  |\\   |",Cursor.Y,2,BOLD);
    Cursor.Y++;
    TextCentered("\\__/     |_______|| _| `._____|_______/    |_______||__| \\__| |__|\\__\\ |_______||__| \\__|",Cursor.Y,2,BOLD);
    //printf("--------------------------------------------------------------------------------------------------\n");
}

//Darstellung des Spielfelds
int spielfeld(char* timePassed, int player1_points, int player2_points, char spielfeld1[], char spielfeld2[]){
    
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;

    
    drawBox(Screen.dwSize.Y-1,Screen.dwSize.X);
    TextCentered("A B C D E F G H I J           A B C D E F G H I J",2,0,BOLD);
    TextCentered("+---------------------+-------+---------------------+",3,0,COLOR_BRIGHT_BLUE);

    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=4;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"1"END_TEXT" | %c %c %c %c %c %c %c %c %c %c | "COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE"%s"END_TEXT" | %c %c %c %c %c %c %c %c %c %c | "BOLD"1"END_TEXT,spielfeld1[0],spielfeld1[1],spielfeld1[2],spielfeld1[3],spielfeld1[4], spielfeld1[5],spielfeld1[6],spielfeld1[7],spielfeld1[8],spielfeld1[9],timePassed,spielfeld2[0],spielfeld2[1],spielfeld2[2],spielfeld2[3],spielfeld2[4],spielfeld2[5],spielfeld2[6], spielfeld2[7],spielfeld2[8],spielfeld2[9]);
    
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=5;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"2"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"2"END_TEXT,spielfeld1[10],spielfeld1[11],spielfeld1[12],spielfeld1[13],spielfeld1[14], spielfeld1[15],spielfeld1[16],spielfeld1[17],spielfeld1[18],spielfeld1[19],spielfeld2[10],spielfeld2[11],spielfeld2[12],spielfeld2[13],spielfeld2[14],spielfeld2[15],spielfeld2[16], spielfeld2[17],spielfeld2[18],spielfeld2[19]);
        
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=6;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"3"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"3"END_TEXT,spielfeld1[20],spielfeld1[21],spielfeld1[22],spielfeld1[23],spielfeld1[24], spielfeld1[25],spielfeld1[26],spielfeld1[27],spielfeld1[28],spielfeld1[29],spielfeld2[20],spielfeld2[21],spielfeld2[22],spielfeld2[23],spielfeld2[24],spielfeld2[25],spielfeld2[26], spielfeld2[27],spielfeld2[28],spielfeld2[29]);
        
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=7;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"4"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"4"END_TEXT,spielfeld1[30],spielfeld1[31],spielfeld1[32],spielfeld1[33],spielfeld1[34], spielfeld1[35],spielfeld1[36],spielfeld1[37],spielfeld1[38],spielfeld1[39],spielfeld2[30],spielfeld2[31],spielfeld2[32],spielfeld2[33],spielfeld2[34],spielfeld2[35],spielfeld2[36], spielfeld2[37],spielfeld2[38],spielfeld2[39]);
        
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=8;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"5"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"5"END_TEXT,spielfeld1[40],spielfeld1[41],spielfeld1[42],spielfeld1[43],spielfeld1[44], spielfeld1[45],spielfeld1[46],spielfeld1[47],spielfeld1[48],spielfeld1[49],spielfeld2[40],spielfeld2[41],spielfeld2[42],spielfeld2[43],spielfeld2[44],spielfeld2[45],spielfeld2[46], spielfeld2[47],spielfeld2[48],spielfeld2[49]);    
        
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=9;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"6"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"6"END_TEXT,spielfeld1[50],spielfeld1[51],spielfeld1[52],spielfeld1[53],spielfeld1[54], spielfeld1[55],spielfeld1[56],spielfeld1[57],spielfeld1[58],spielfeld1[59],spielfeld2[50],spielfeld2[51],spielfeld2[52],spielfeld2[53],spielfeld2[54],spielfeld2[55],spielfeld2[56], spielfeld2[57],spielfeld2[58],spielfeld2[59]);
    
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=10;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"7"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"7"END_TEXT,spielfeld1[60],spielfeld1[61],spielfeld1[62],spielfeld1[63],spielfeld1[64], spielfeld1[65],spielfeld1[66],spielfeld1[67],spielfeld1[68],spielfeld1[69],spielfeld2[60],spielfeld2[61],spielfeld2[62],spielfeld2[63],spielfeld2[64],spielfeld2[65],spielfeld2[66], spielfeld2[67],spielfeld2[68],spielfeld2[69]);
        
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=11;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"8"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"8"END_TEXT,spielfeld1[70],spielfeld1[71],spielfeld1[72],spielfeld1[73],spielfeld1[74], spielfeld1[75],spielfeld1[76],spielfeld1[77],spielfeld1[78],spielfeld1[79],spielfeld2[70],spielfeld2[71],spielfeld2[72],spielfeld2[73],spielfeld2[74],spielfeld2[75],spielfeld2[76], spielfeld2[77],spielfeld2[78],spielfeld2[79]);
    
    Cursor.X=((Screen.dwSize.X/2)-(57/2));
    Cursor.Y=12;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"9"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"9"END_TEXT,spielfeld1[80],spielfeld1[81],spielfeld1[82],spielfeld1[83],spielfeld1[84], spielfeld1[85],spielfeld1[86],spielfeld1[87],spielfeld1[88],spielfeld1[89],spielfeld2[80],spielfeld2[81],spielfeld2[82],spielfeld2[83],spielfeld2[84],spielfeld2[85],spielfeld2[86], spielfeld2[87],spielfeld2[88],spielfeld2[89]);
    
    Cursor.X=((Screen.dwSize.X/2)-(59/2));
    Cursor.Y=13;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf(BOLD"10"END_TEXT" | %c %c %c %c %c %c %c %c %c %c |       | %c %c %c %c %c %c %c %c %c %c | "BOLD"10"END_TEXT,spielfeld1[90],spielfeld1[91],spielfeld1[92],spielfeld1[93],spielfeld1[94], spielfeld1[95],spielfeld1[96],spielfeld1[97],spielfeld1[98],spielfeld1[99],spielfeld2[90],spielfeld2[91],spielfeld2[92],spielfeld2[93],spielfeld2[94],spielfeld2[95],spielfeld2[96], spielfeld2[97],spielfeld2[98],spielfeld2[99]);
    
    TextCentered("+---------------------+-------+---------------------+",14,0,COLOR_BRIGHT_BLUE);
    
    Cursor.X=((Screen.dwSize.X/2)-(53/2));
    Cursor.Y=15;
    SetConsoleCursorPosition(hStdOut,Cursor);
    printf("| "BOLD"Spieler1:      %03d"END_TEXT"  |       | "BOLD"Spieler2:      %03d"END_TEXT"  |",player1_points,player2_points);
    
    TextCentered("+---------------------+-------+---------------------+",16,0,COLOR_BRIGHT_BLUE);
}

//Platzierung des Schiffs => Füllen der Felder des Schiffs auf dem Spielfeld mit 'X'
void SchiffSetzen(int Intkoordinaten,int Intrichtung, int schiffslaenge, char spielfeld1[]){
        switch(Intrichtung){
        //nord
        case 1:
            for(int i=0; i<schiffslaenge;i++){
                int p =(Intkoordinaten-(10*i));
               // printf("\n%d",p);
                spielfeld1[p] = 'X';
            }
            getch();
        break;
        //ost
        case 2:
            for(int i=0; i<schiffslaenge;i++){
                spielfeld1[(Intkoordinaten+i)]= 'X';
            }
        break;        
        //süd
        case 3:
            for(int i=0; i<schiffslaenge;i++){
                spielfeld1[(Intkoordinaten+(10*i))]= 'X';
            }
        break;
        //west
        case 4:
            for(int i=0; i<schiffslaenge;i++){
                spielfeld1[(Intkoordinaten-i)]= 'X';
            }
        break;
    }
}

//Warten des Programms für n Sekunden
void wait(unsigned int sec){

    unsigned int retTime = time(0)+sec;
    while(time(0)<retTime);
}

//Setzbarkeit des Schiffs überprüfen
int checkPos(int schiffslaenge, int Intrichtung, int Intkoordinaten, char spielfeld1[]){
    switch (Intrichtung) {
    // Nord
    case 1:
        for (int i = 0; i < schiffslaenge; i++) {
            if ((spielfeld1[Intkoordinaten - (10 * i)] == 'X')||((Intkoordinaten-(schiffslaenge*10))<0)) {
                return 0; // Nicht platzierbar
            }
        }
        return 1; // Platzierbar
        break;

    // Ost
    case 2:
        for (int i = 0; i < schiffslaenge; i++) {
            if ((spielfeld1[Intkoordinaten + i] == 'X')||((10-((Intkoordinaten)%10))<schiffslaenge)) {
                return 0; // Nicht platzierbar
            }
        }
        return 1; // Platzierbar
        break;

    // Süd
    case 3:
        for (int i = 0; i < schiffslaenge; i++) {
            if ((spielfeld1[Intkoordinaten + (10 * i)] == 'X')||((Intkoordinaten+(schiffslaenge*10))>99)) {
                return 0; // Nicht platzierbar
            }
        }
        return 1; // Platzierbar
        break;

    // West
    case 4:
        for (int i = 0; i < schiffslaenge; i++) {
            if ((spielfeld1[Intkoordinaten - i] == 'X')||(((Intkoordinaten)%10)<=schiffslaenge)) {
                return 0; // Nicht platzierbar
            }
        }
        return 1; // Platzierbar
        break;
}

}

//Konvertierung der Benutzereingabe in Array-freundliches Format(0-99)
int coordsToField(char X,int Y){
    
    int x = X -'A';
    int fieldnumber = (Y-1)*10+x;
    return fieldnumber;
}

//Darstellung des Menüs - menu(Seitenzahl)
int menuPrint(int page){

    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO Screen;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    drawBox(Screen.dwSize.Y-1,Screen.dwSize.X);
    TextCentered(".___  ___.  _______ .__   __.  __    __",2,0,BOLD);
    TextCentered("|   \\/   | |   ____||  \\ |  | |  |  |  |",3,2,BOLD);
    TextCentered("|  \\  /  | |  |__   |   \\|  | |  |  |  |",4,2,BOLD);
    TextCentered("|  |\\/|  | |   __|  |  . `  | |  |  |  |",5,1,BOLD);
    TextCentered("|  |  |  | |  |____ |  |\\   | |  `--'  |",6,1,BOLD);
    TextCentered("|__|  |__| |_______||__| \\__|  \\______/ ",7,2,BOLD);
    
    switch(page){
        //main-menu
        case 0: 
        TextCentered("1. Spielmodus",10,0,BOLD);
        TextCentered("2. Schwierigkeit",11,0,BOLD);
        TextCentered("3. Tutorial",12,0,BOLD);
        TextCentered("4. Start",13,0,BOLD);
        TextCentered("5. beenden",14,0,BOLD);
        TextCentered("Menünummer eingeben: ",16,0,BOLD);
        break;
        //spielmodus
        case 1:
        TextCentered("Spielmodus",9,0,UEBERSCHRIFT);
        TextCentered("1. Normalmodus",11,0,BOLD);
        TextCentered("2. Zeitmodus",12,0,BOLD);
        TextCentered("3. <-zurück",13,0,BOLD);
        TextCentered("Menünummer eingeben: ",16,0,BOLD);
        break;
        //schwierigkeit
        case 2:
        TextCentered("Schwierigkeit",9,0,UEBERSCHRIFT);
        TextCentered("1. Einfach",11,0,BOLD);
        TextCentered("2. Mittel",12,0,BOLD);
        TextCentered("3. Schwer",13,0,BOLD);
        TextCentered("4. <-zurück>",14,0,BOLD);
        TextCentered("Menünummer eingeben: ",16,0,BOLD);
        break;
        //Tutorial
        case 3:
        system("cls");
        printf(UEBERSCHRIFT"Spielanleitung\n"END_TEXT);
        printf("\nWillkommen bei Schiffe versenken!");
        printf("\nDas Spielfeld hat die Größe 10x10\n");
        printf("\nIm Zeitmodus haben Sie 5 Minuten Zeit, um alle Schiffe zu versenken.\n");
        printf("Sie bekommen für jeden Treffer 25 Punkte.\n");
        printf("Sie bekommen für jeden Fehlschuss 2 Punkte abgezogen.\n");
        printf("Der Spieler, mit den meisten Punkten gewinnt.\n");
        printf("Das Spiel ist beendet, wenn alle Schiffe versenkt wurden oder die Zeit abgelaufen ist.\n");
        printf("\nIm Standardmodus geht es darum, alle Schiffe zu versenken.\n");
        printf("Der Spieler der zuerst alle Schiffe des Gegners versenkt, gewinnt.\n\n");
        
        break;    
    } 
}

//Timer für Spieldauer
char* timer(time_t starttime){
    time_t nowtime;
    time(&nowtime);
    time_t timervalue = nowtime-starttime;
    int minutes = (int)(timervalue / 60);
    int seconds = (int)(timervalue % 60);
    char* timeString = (char*)malloc(10 * sizeof(char));
    sprintf(timeString, "%02d:%02d", minutes, seconds);
    return timeString;
}

//Countdown für Zeitmodus
char* Countdown(time_t starttime, time_t countdownlength){
    time_t nowtime;
    time(&nowtime);
    time_t timepassed = nowtime-starttime;
    time_t timervalue = countdownlength-timepassed;
    if(timervalue>0){
        int minutes = (int)(timervalue / 60);
        int seconds = (int)(timervalue % 60);
        char* timeString = (char*)malloc(10 * sizeof(char));
        sprintf(timeString, "%02d:%02d", minutes, seconds);
        return timeString;
    }
    else{
        char* timeString = (char*)malloc(10 * sizeof(char));
        sprintf(timeString, "00:00");
        return timeString;
    }
}

//Leeren des Eingabe-Puffers in scanf()
void clear (void)
{
    while ( getchar() != '\n' );
}    

//Text zentriert ausgeben - TextCentered("text", zeilennummer, anzahl eventueller Sonderzeichen die bei strlen mitgezählt aber nicht angezeigt werden, Schrifteigenschaften)
void TextCentered(char text[], short zeile,int sonderzeichen, char color[]){

    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    short columns, rows;
    
    columns = Screen.dwSize.X;
    rows = Screen.dwSize.Y;
    COORD Mitte;
    Mitte.X=columns/2;
    Mitte.Y=rows/2;
    short laenge = strlen(text);
    COORD Cursor;
    Cursor.X=Mitte.X-((laenge-sonderzeichen)/2);
    Cursor.Y=zeile;
    SetConsoleCursorPosition(hStdOut,Cursor);
    if(color==BOLD){
       printf(BOLD"%s\n"END_TEXT,text); 
    }
    else if(color==UEBERSCHRIFT){
        printf(UEBERSCHRIFT"%s\n"END_TEXT,text);  
    }
    else if(color==COLOR_BRIGHT_BLUE){
        printf(COLOR_BRIGHT_BLUE"%s\n"END_TEXT,text);
    }
    else if(color==COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE){
        printf(COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE"%s\n"END_TEXT,text);
    }
}

//Modus zum Zeichnen des Rahmens aktivieren
void setDecMode() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hStdOut, &dwMode);
    dwMode |= 0x0004; // Enable VT100 mode
    SetConsoleMode(hStdOut, dwMode);
}

//Rahmen zeichnen - drawBox(Höhe, Breite)
void drawBox(int height, int width) {
    printf("\x1B(0"); // Wechsel in den DEC-Zeichenmodus
    printf("\x6C");   // Obere linke Ecke
    for (int i = 0; i < width - 2; i++) {
        printf("\x71"); // Horizontale Linie
    }
    printf("\x6B\n"); // Obere rechte Ecke

    for (int i = 0; i < height - 2; i++) {
        printf("\x78"); // Vertikale Linie
        for (int j = 0; j < width - 2; j++) {
            printf(" "); // Leerzeichen für den Inhalt
        }
        printf("\x78\n"); // Vertikale Linie
    }

    printf("\x6D"); // Untere linke Ecke
    for (int i = 0; i < width - 2; i++) {
        printf("\x71"); // Horizontale Linie
    }
    printf("\x6A\n"); // Untere rechte Ecke

    printf("\x1B(B"); // Wechsel zurück zum normalen Zeichensatz
    SetConsoleCP(CP_UTF8);
}

//Wird bei gewinnen des Spiels ausgegeben
void WinnerScreen(){
    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    drawBox(Screen.dwSize.Y-1,Screen.dwSize.X);
    COORD Cursor;
    Cursor.Y=(Screen.dwSize.Y/2)-7;

    TextCentered("     _______. __   _______   _______ ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++;
    TextCentered("    /       ||  | |   ____| /  _____|",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++;   
    TextCentered("   |   (----`|  | |  |__   |  |  __  ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++;
    TextCentered("    \\   \\    |  | |   __|  |  | |_ | ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 
    TextCentered(".----)   |   |  | |  |____ |  |__| | ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 
    TextCentered("|_______/    |__| |_______| \\______|",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 

    //Hier noch Punkte, Zeit anzeigen
}

//Wird bei verlieren des Spiels ausgegeben
void LoserScreen(){
    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    
    drawBox(Screen.dwSize.Y-1,Screen.dwSize.X);

    COORD Cursor;
    Cursor.Y=(Screen.dwSize.Y/2)-7;

    TextCentered(".__   __.  __   _______  _______   _______ .______       __          ___       _______  _______ ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++;
    TextCentered("|  \\ |  | |  | |   ____||       \\ |   ____||   _  \\     |  |        /   \\     /  _____||   ____|",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++;   
    TextCentered("|   \\|  | |  | |  |__   |  .--.  ||  |__   |  |_)  |    |  |       /  ^  \\   |  |  __  |  |__   ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 
    TextCentered("|  . `  | |  | |   __|  |  |  |  ||   __|  |      /     |  |      /  /_\\  \\  |  | |_ | |   __|  ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 
    TextCentered("|  |\\   | |  | |  |____ |  '--'  ||  |____ |  |\\  \\----.|  `----./  _____  \\ |  |__| | |  |____ ",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 
    TextCentered("|__| \\__| |__| |_______||_______/ |_______|| _| `._____||_______/__/     \\__\\ \\______| |_______|",Cursor.Y,0,COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE);
    Cursor.Y++; 

    //Hier noch Punkte, Zeit anzeigen
}

//Funktion zum testen der Library
void test(){
    printf("\nTEST FUNCTION");
}

//Benutzereingabe der Schiffe
void UserInput(){
    int minensuchboote = settings.anzahl.Minensuchboote;   //Anzahl verwendbarer Minensuchboote
    int fregatten = settings.anzahl.Fregatten;             //Anzahl verwendbarer Fregatten
    int kreuzer = settings.anzahl.Kreuzer;                 //Anzahl verwendbarer Kreuzer
    int schlachtschiffe = settings.anzahl.Schlachtschiffe; //Anzahl verwendbarer Schlachtschiffe
    do{
        a:
        system("cls");
        
        spielfeld(timePassed,player1points,player2points,spielfeld1,spielfeld2);
        CONSOLE_SCREEN_BUFFER_INFO Screen;
        WORD wOldColAttr;
        HANDLE hStdOut;
        hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo (hStdOut, &Screen);
        wOldColAttr = Screen.wAttributes;

        COORD Cursor;
        
        Cursor.X=((Screen.dwSize.X/2)-(59/2));
        Cursor.Y=18;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf("1. Minensuchboote (XX): %d",minensuchboote);

        Cursor.X=((Screen.dwSize.X/2)-(59/2));
        Cursor.Y=19;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf("2. Fregatten (XXX): %d",fregatten);

        Cursor.X=((Screen.dwSize.X/2)-(59/2));
        Cursor.Y=20;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf("3. Kreuzer (XXXX): %d",kreuzer);

        Cursor.X=((Screen.dwSize.X/2)-(59/2));
        Cursor.Y=21;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf("4. Schlachtschiffe (XXXXX): %d",schlachtschiffe);

        Cursor.X=EBENE_1;
        Cursor.Y=23;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf(BOLD"Schiffstyp eingeben (1-4): "END_TEXT);
        scanf("%d",&schiffstyp);
        if(schiffstyp>4 || schiffstyp <1){
            Cursor.X=EBENE_1;
            Cursor.Y=25;
            SetConsoleCursorPosition(hStdOut,Cursor);
            printf("Schiffstyp muss im Bereich 1 bis 4 liegen!");
            getch();
            goto a;
        }
        int test = schiffstyp;

        //Einstellung der Schiffslänge
        switch(schiffstyp){
            //Minensuchboot (typ 1)
            case 1:
                if(minensuchboote==0){
                    Cursor.X=EBENE_1;
                    Cursor.Y=25;
                    SetConsoleCursorPosition(hStdOut,Cursor);
                    printf("Keine Minensuchboote zur Platzierung vorhanden!");
                    getch();
                    goto a;
                }
                else{schiffslaenge=2; } 
                break;
            //Fregatten (typ 2)
            case 2:
                if(fregatten==0){
                    Cursor.X=EBENE_1;
                    Cursor.Y=25;
                    SetConsoleCursorPosition(hStdOut,Cursor);
                    printf("Keine Fregatten zur Platzierung vorhanden!");
                    getch();
                    goto a;
                }
                else{schiffslaenge=3;}
                break;
            //Kreuzer (typ 3)
            case 3:
                if(kreuzer==0){
                    Cursor.X=EBENE_1;
                    Cursor.Y=25;
                    SetConsoleCursorPosition(hStdOut,Cursor);                    
                    printf("Keine Kreuzer zur Platzierung vorhanden!");
                    getch();
                    goto a;
                }
                else{schiffslaenge=4;}
                break;
            //Schlachtschiff (typ 4)
            case 4:
                if(schlachtschiffe==0){
                    Cursor.X=EBENE_1;
                    Cursor.Y=25;
                    SetConsoleCursorPosition(hStdOut,Cursor);
                    printf("Keine Schlachtschiffe zur Platzierung vorhanden!");
                    getch();
                    goto a;
                }
                else{schiffslaenge=5;}
                break;
        }
        clear();
        Cursor.X=EBENE_1;
        Cursor.Y=24;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf(BOLD"Koordinaten eingeben: "END_TEXT);
        scanf("%c%d",&X,&Y);
        clear();
        if((X<65 || X>74)||(Y<1||Y>10)){ //Eingabe auf Richtigkeit prüfen
            Cursor.X=EBENE_1;
            Cursor.Y=25;
            SetConsoleCursorPosition(hStdOut,Cursor);
            printf("Koordinaten müssen im Bereich (A - J) und (1 - 10) liegen!");
            getch();
            goto a;
        }

        Cursor.X=EBENE_1;
        Cursor.Y=25;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf(BOLD"Richtung eingeben (N,O,S,W): "END_TEXT);
        scanf("%s",&richtung);
        clear();
        IntKoordinaten = coordsToField(X,Y);
       
    //printf("\n%d", schiffslaenge);
    //Umwandlung von char Himmelsrichtung in int Intrichtung (Zahl 1-4)
    switch(richtung){
            //Nord
            case 'N': IntRichtung=1; break;
            case 'n': IntRichtung=1; break;
            //Ost
            case 'o': IntRichtung=2; break;
            case 'O': IntRichtung=2; break;
            case 'e': IntRichtung=2; break;
            case 'E': IntRichtung=2; break;
            //Süd
            case 's': IntRichtung=3; break;
            case 'S': IntRichtung=3; break;
            //West
            case 'w': IntRichtung=4; break;
            case 'W': IntRichtung=4; break;
            default:
                Cursor.X=EBENE_1;
                Cursor.Y=26;
                SetConsoleCursorPosition(hStdOut,Cursor);
                printf("Richtung muss mit (N, O, S, W) eingegeben werden!");
                getch();
            goto a;
        }
    if(checkPos(schiffslaenge, IntRichtung, IntKoordinaten, spielfeld1)==1){
        //printf("%d",schiffstyp);
        SchiffSetzen(IntKoordinaten,IntRichtung,schiffslaenge, spielfeld1);
        switch(test){
            case 1: minensuchboote--; break;
            case 2: fregatten--; break;
            case 3: kreuzer--; break;
            case 4: schlachtschiffe--; break;
        }
    }
    else{
        Cursor.X=EBENE_1;
        Cursor.Y=27;
        SetConsoleCursorPosition(hStdOut,Cursor);
        printf("Schiff konnte nicht platziert werden!");
        getch();
    }

    }while(minensuchboote+fregatten+kreuzer+schlachtschiffe!=0);

    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;

    Cursor.X=EBENE_1;
    Cursor.Y=27;
    SetConsoleCursorPosition(hStdOut,Cursor);
    system("pause");
}