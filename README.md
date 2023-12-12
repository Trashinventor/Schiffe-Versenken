# Schiffe-Versenken

## config:
default-Einstellungen für "Schiffe versenken"

  |**Einstellung**|**Wert**|**Beschreibung**|
  |---------------|--------|----------------|
  |difficulty|2|default Schwierigkeit|
  |gamemode|1|default Spielmodus|
  |anzahl.Minensuchboote|4|default Anzahl der Minensuchboote|
  |anzahl.Fregatten|4|default Anzahl der Fregatten|
  |anzahl.Kreuzer|2|default Anzahl der Kreuzer|
  |anzahl.Schlachtschiffe|2|default Anzahl der Schlachtschiffe|
  

## SchiffeRambold:
library mit den Funktionen für GUI, Menu & Userinput für das Spiel "Schiffe versenken"

### Funktionen:

| Funktion | Beschreibung|
|----------|-------------|
|**startupscreen()**| Vorspann des Spiels mit ASCII-Art Schriftzug "Schiffe Versenken"|
|**wait(** *seconds* **)**| Pausieren des Programms für angegebene Zeit in Sekunden|
|**menuPrint(** *page* **)**| Darstellung einer Seite des Menüs|
|**menu()**|Ausführen des gesamten Menüs|
|**SchiffSetzen(** *Intkoordinaten, Intrichtung, schiffslaenge, spielfeld1[]* **)**|Platzierung des Schiffs => Füllen der Felder des Schiffs auf dem Spielfeld mit 'X'|
|**Spielfeld(** *timePassed, player1points, player2points, spielfeld1[], spielfeld2[]* **)**|Darstellung des Spielfelds|
|**checkPos(** *schiffslaenge, Intrichtung, Intkoordinaten, spielfeld1[]* **)**|Setzbarkeit des Schiffs überprüfen|
|**coordsToField(** *X, Y* **)**|Konvertierung der Benutzereingabe (z.B. A9) in Array-freundliches Format(0-99)|
|**clear()**|Leeren des Eingabe-Puffers in *scanf()* |
|**TextCentered(** *text[], zeile, sonderzeichen, color[]* **)**|Text zentriert ausgeben - TextCentered("text", zeilennummer, anzahl eventueller Sonderzeichen die bei strlen mitgezählt aber nicht angezeigt werden, Schrifteigenschaften)|
|**setDecMode()**|Modus zum Zeichnen des Rahmens aktivieren|
|**drawBox(** *heigth, width* **)**|Rahmen zeichnen|
|**timer(** *starttime* **)**|Timer für Spieldauer|
|**Countdown(** *starttime, countdownlength* **)**|Countdown für den Zeitmodus|
|**Winnerscreen()**|Wird bei gewinnen des Spiels ausgegeben, ASCII-Art Schriftzug "SIEG"|
|**Loserscreen()**|Wird bei verlieren des Spiels ausgegeben, ASCII-Art Schriftzug "NIEDERLAGE"|
|**undecidedScreen()**|Wird bei unentschiedenem Spiel ausgegeben, ASCII-Art Schriftzug "UNENTSCHIEDEN|
|**initSpielfeld()**|Initialisierung des Spielfelds zu Spielbeginn|
|**UserInput()**|gesamte Platzierung der Schiffe durch Benutzer|
|**test()**|Funktion zum testen der Library (Überbleibsel aus der Entwicklung), gibt "TEST FUNCTION" aus|


### Erklärung der Parameter

  |**Datentyp**|**Parameter**|**Beschreibung**|
  |-------------|------------|----------------|
  |unsigned int|seconds|Zeit in Sekunden|
  |char*|timePassed|vergangene Zeit seit Spielbeginn|
  |int|player1points|eigener Punktestand|
  |int|player2points|gegnerischer Punktestand|
  |char[]|spielfeld1[]|Array mit den Zeichen pro Feld -> für eigenes Spielfeld |
  |char[]|spielfeld2[]|Array mit den Zeichen pro Feld -> für Bereits beschossene gegnerische Felder |
  |int|Intkoordinaten|Koordinaten des ersten Schiffsfeldes in Arrayform (Feld Nr. 0-99)|
  |int|Intrichtung|Orientierung des Schiffs in Zahlen (1-4 im Uhrzeigersinn beginnend bei Norden)|
  |int|schiffslaenge|Länge des Schiffs in Feldern|
  |char|X|X-Anteil der Koordinaten (A-J)|
  |int|Y|Y-Anteil der Koordinaten (1-10)|
  |char|text[]|zu positionieren- und formatierender Text|
  |short|zeile|Zeilennummer im cmd-Fenster|
  |int|sonderzeichen|Anzahl eventueller Sonderzeichen die bei *strlen()* mitgezählt aber nicht angezeigt werden|
  |char|color[]|siehe unten|
  |int|heigth|Höhe der zu zeichnenden Box in Zeilen|
  |int|width|Breite der zu zeichnenden Box in Zeichen|
  |time_t|starttime|Zeit zu Beginn des Spiels|
  |time_t|countdownlength|Länge des Countdowns|

  
### Erklärung weiterer einzelner Parameter

  |**Wert von "page"**|**Beschreibung**|
  |-------------------|----------------|
  |0|Main-Menu|
  |1|Spielmodus|
  |2|Schwierigkeit|
  |3|Spielanleitung|
  

  |**Wert von "color[]"**|**Beschreibung**|**code**|
  |----------------------|----------------|--------|
  |COLOR_YELLOW_BOLD |gelber, dicker Text|`"\033[1;33m"`|
  |COLOR_RED_BOLD|roter, dicker Text|`"\033[1;31m"`|
  |COLOR_BRIGHT_BLUE|hellblauer, normaler Text|`"\e[94m"`|
  |COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE|hellblauer, dicker, blinkender Text|`"\e[1;5;94m"`|
  |END_TEXT|zurücksetzen auf hellblauen, normalen Text (nach der Formatierung eines Textes notwendig)| `"\033[m""\033[94m"`|
  |UEBERSCHRIFT|dicker, unterstrichener Text (für Überschriften)| `"\e[1;4m"`|
  |BOLD|dicker Text|`"\033[1m"`|
  
  
  

  


