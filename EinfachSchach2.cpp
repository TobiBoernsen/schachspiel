#include <iostream> // für Ein-/Ausgabe
#include <array>    // für das Spielbrett (2D-Array)
#include <string>   // für die Verwendung von Strings
using namespace std;

// Globale Variablen

array<array<char, 10>, 10> spielBrett;  // 8x8 Schachbrett mit einer Umrandung, um die Darstellung zu erleichtern
char hell = 176;  // ASCII Zeichen für helles Feld (erweiterter ASCII Zeichensatz)
char dunkel = 32; // ASCII Zeichen für dunkles Feld (Leerzeichen)
array<string, 2> spieler{ "Schwarz", "Weiss" }; // Namen der Spieler
int zugNr = 1; // Zähler für die Zugnummer

//  ----------- Funktionen --------------------

// Funktion zum Aufstellen des Bretts in einem Schachmuster
void brettAufstellen()
{
    for (size_t zeile = 0; zeile < spielBrett.size(); zeile++)
    {
        for (size_t spalte = 0; spalte < spielBrett.at(zeile).size(); spalte++)
        {
            switch (zeile)
            {
            case 0: // oberste und unterste Zeile für Spaltenbeschriftungen
            case 9:
                spielBrett.at(zeile).at(spalte) = (spalte >= 1 && spalte <= 8) ? 64 + spalte : 32;
                break;
            default: // alle anderen Zeilen für das Spielfeld
                if (spalte == 0 || spalte == 9) // Rand für Zeilenbeschriftungen
                {
                    spielBrett.at(zeile).at(spalte) = 57 - zeile;
                }
                else // Schachmuster erstellen
                {
                    spielBrett.at(zeile).at(spalte) = !((zeile + spalte) % 2) ? hell : dunkel;
                }
            }
        }
    }
}

// Funktion zum Darstellen des Bretts
// `richtung` bestimmt, ob das Brett von oben nach unten (true) oder von unten nach oben (false) dargestellt wird
void darstellen(bool richtung)
{
    for (size_t zeile = 0; zeile < spielBrett.size(); zeile++)
    {
        for (size_t spalte = 0; spalte < spielBrett.at(zeile).size(); spalte++)
        {
            int z = (richtung) ? zeile : (spielBrett.size() - 1 - zeile);
            int s = (richtung) ? spalte : (spielBrett.size() - 1 - spalte);

            cout << spielBrett.at(z).at(s);
        }
        cout << endl; // Neue Zeile nach jeder Brettzeile
    }
}

// Funktion zur Grundstellung der Figuren
void grundstellung()
{
    // Bauern in Zeile 2 (schwarz) und 7 (weiß)
    for (int spalte = 1; spalte < 9; spalte++)
    {
        spielBrett.at(7).at(spalte) = 'B'; // Weißer Bauer
        spielBrett.at(2).at(spalte) = 'b'; // Schwarzer Bauer
    }

    // Offiziere in Zeile 1 (schwarz) und 8 (weiß)
    string offz{ " TSLDKLST" }; // Reihenfolge der Offiziere
    for (int spalte = 1; spalte < 9; spalte++)
    {
        spielBrett.at(8).at(spalte) = offz.at(spalte);       // Weiße Offiziere
        spielBrett.at(1).at(spalte) = offz.at(spalte) | 32; // Schwarze Offiziere (Kleinbuchstaben)
    }
}

// Funktion zum Durchführen eines Zuges
void ziehen(bool wer)
{
    cout << (wer ? spieler[1] : spieler[0]) + " ist am Zug\n";
     // Eingabe des Spielers (z. B. A2A4 für einen Bauernzug)
    string userEingabe;
    int zeileVon, spalteVon, zeileNach, spalteNach;

    cin >> userEingabe; // Eingabe einlesen
    // Umwandlung der Nutzereingabe in Koordinaten des Arrays
    zeileVon = 9 - userEingabe[1] + 48; // Umrechnung der Zeile (z.B. '2' -> 8)
    spalteVon = userEingabe[0] - 64;    // Umrechnung der Spalte (z.B. 'A' -> 1)
    zeileNach = 9 - userEingabe[3] + 48;
    spalteNach = userEingabe[2] - 64;

    // Ausführen des Zuges und Aktualisieren des Bretts
    spielBrett.at(zeileNach).at(spalteNach) = spielBrett.at(zeileVon).at(spalteVon);
    spielBrett.at(zeileVon).at(spalteVon) = !((zeileVon + spalteVon) % 2) ? hell : dunkel;
}

// Hauptfunktion
int main()
{
    brettAufstellen(); // Initialisiert das Schachbrett
    grundstellung();   // Setzt die Figuren in die Startposition

    do {
        darstellen(true); // Darstellung des Bretts von oben nach unten
        ziehen(zugNr++ % 2); // Wechsel der Spieler nach jedem Zug
        cout << "\n\n\n\n";
        darstellen(false); // Darstellung des Bretts von unten nach oben
        ziehen(zugNr++ % 2); // erneuter Spielerwechsel
    } while (zugNr < 6); // Schleife für eine festgelegte Anzahl an Zügen (hier: 5 Züge)

    return 0; // Beendigung des Programms
}
