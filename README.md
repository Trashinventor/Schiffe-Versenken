# Schiffe-Versenken

## config:
default-Einstellungen für Spiel
  - Anzahl der Schiffe
  - default Schwierigkeit
  - default Spielmodus

## SchiffeRambold:
library mit den Funktionen für GUI, Menu & Userinput

Funktionen:
  - **startupscreen()** => Vorspann des Spiels mit ASCII-Art Schriftzug "Schiffe Versenken"
  - **wait(int seconds)** => Pausieren des Programms für angegebene Zeit in Sekunden
  - **menuPrint(int page)** => Darstellung einer Seite des Menüs
   
    Seiten:
    - 0 -> Mainmenu
    - 1 -> Spielmodus
    - 2 -> Schwierigkeit
    - 3 -> Spielanleitung
      
  - **spielfeld(char'*' timePassed, int player1points, int player2points, char spielfeld1[], char spielfeld2[])**

    Darstellung des Spielfelds

    Parameter:
    - timePassed -> vergangene Zeit seit Spielbeginn
    - player1points -> Punktestand von Spieler 1
    - player2points -> Punktestand von Spieler 2
    - spielfeld1[] -> Array mit den Zeichen pro Feld 
                   -> für eigenes Spielfeld 
    - spielfeld2[] -> Array mit den Zeichen pro Feld
                   -> für Bereits beschossene gegnerische Felder 
  
  - **menu()**

    Ausführen des gesamten Menüs

  - **Schiffsetzen()**

    Platzierung des Schiffs => Füllen der Felder des Schiffs auf dem Spielfeld mit 'X'
