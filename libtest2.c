//Beispiel für die Verwendung der "SchiffeRambold"-library im main-code
//Alles Untenstehende für Game notwendig!

//Hinweis: 
//"spielfeld2[]" ist zur Anzeige der vom Spieler bereits beschossenen gegnerischen Felder gedacht
//"spielfeld1[]" ist das eigene Spielfeld

#include "SchiffeRambold.h"
    
int player1points=0;                                   //Eigene Punkte
int player2points=0;                                   //Gegnerische Punkte
char spielfeld1[100];                                  //Eigenes Spielfeld
char spielfeld2[100];                                  //Gegnerisches Spielfeld

int main(void){
    
    int minensuchboote = settings.anzahl.Minensuchboote;   //Anzahl verwendbarer Minensuchboote
    int fregatten = settings.anzahl.Fregatten;             //Anzahl verwendbarer Fregatten
    int kreuzer = settings.anzahl.Kreuzer;                 //Anzahl verwendbarer Kreuzer
    int schlachtschiffe = settings.anzahl.Schlachtschiffe; //Anzahl verwendbarer Schlachtschiffe
    //(werden in config.c eingestellt)

    CONSOLE_SCREEN_BUFFER_INFO Screen;
    WORD wOldColAttr;
    HANDLE hStdOut;
    hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdOut, &Screen);
    wOldColAttr = Screen.wAttributes;
    SetConsoleTitleA ("Schiffe versenken");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    SetConsoleOutputCP(CP_UTF8); 
    printf("\e[94m");

    startupscreen();
    wait(2);
    start:
    menu();
    initSpielfeld();
    UserInput();

    //hier beginnt spiel
    time_t spielbegin = time(NULL);
    timer(spielbegin);
    switch(settings.gamemode){

        //Normaler Modus
        case 1:
            while(1){
                //WIE CLOCK IN KONSOLE UPDATEN OHNE USERINPUT ZU BEEINFLUSSEN?
                char* gametime = timer(spielbegin);
                spielfeld(gametime,settings.difficulty,player1points,player2points,spielfeld1,spielfeld2);
                getch();
                system("cls");
            }
        break;

        //Zeitmodus
        case 2:
            while(1){
                //WIE CLOCK IN KONSOLE UPDATEN OHNE USERINPUT ZU BEEINFLUSSEN?
                struct countdowntime{
                    int min;
                    int sec;
                }countdowntime;

                countdowntime.min = 0;
                countdowntime.sec = 10;
                time_t startvalue = (countdowntime.sec + (countdowntime.min * 60));  
                char* gametime = Countdown(spielbegin,startvalue);
                spielfeld(gametime,settings.difficulty,player1points,player2points,spielfeld1,spielfeld2);
                if(strcmp(gametime,"00:00")==0){
                    getch();
                    goto start;   
                }
                getch();
                system("cls");
            }
        break;
    }
    WinnerScreen();
    LoserScreen();
    test();
    system("pause");
}