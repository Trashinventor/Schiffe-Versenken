# Schiffe-Versenken

## config:
default-Einstellungen für Spiel
  - Anzahl der Schiffe
  - default Schwierigkeit
  - default Spielmodus

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
|**initSpielfeld()**|Initialisierung des Spielfelds zu Spielbeginn|
|**UserInput()**|gesamte Platzierung der Schiffe durch Benutzer|
|**test()**|Funktion zum testen der Library (Überbleibsel aus der Entwicklung), gibt "TEST FUNCTION" aus|

### Erklärung der Parameter

  |**Datentyp**|**Parameter**|**Beschreibung**|
  |-------------|------------|----------------|
  |unsigned int|seconds|Zeit in Sekunden|
  |char*|timePassed|vergangene Zeit seit Spielbeginn|
  |int|player1points|Punktestand von Spieler 1|
  |int|player2points|Punktestand von Spieler 2|
  |char[]|spielfeld1[]|Array mit den Zeichen pro Feld -> für eigenes Spielfeld |
  |char[]|spielfeld2[]|Array mit den Zeichen pro Feld -> für Bereits beschossene gegnerische Felder |
  
  
### Erklärung weiterer einzelner Parameter

  |**Wert von "page"**|**Beschreibung**|
  |-------------------|----------------|
  |0|Main-Menu|
  |1|Spielmodus|
  |2|Schwierigkeit|
  |3|Spielanleitung|

  |**Wert von "bla"**|**Beschreibung**|
  |-------------------|----------------|

  


