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
char figur; // Variable für die aktuelle Figur
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

bool istGueltigerZug(int zeileVon, int spalteVon, int zeileNach, int spalteNach, char figur) {
    // Bauern
    if (figur == 'B' || figur == 'b') {
        // Bauern dürfen nur einen Schritt nach vorne (außer im ersten Zug) und diagonal schlagen
        if (figur == 'B' && zeileNach == zeileVon - 1) { // Weißer Bauer
            return (spalteNach == spalteVon) || (abs(spalteNach - spalteVon) == 1);
        } else if (figur == 'b' && zeileNach == zeileVon + 1) { // Schwarzer Bauer
            return (spalteNach == spalteVon) || (abs(spalteNach - spalteVon) == 1);
        }
        return false;
    }

    // Türme
    if (figur == 'T' || figur == 't') {
        // Türme bewegen sich horizontal oder vertikal
        return (zeileVon == zeileNach) || (spalteVon == spalteNach);
    }

    // Springer
    if (figur == 'S' || figur == 's') {
        // Springer bewegen sich in L-Form: 2 Schritte in eine Richtung, dann 1 Schritt senkrecht dazu
        return (abs(zeileVon - zeileNach) == 2 && abs(spalteVon - spalteNach) == 1) || 
               (abs(spalteVon - spalteNach) == 2 && abs(zeileVon - zeileNach) == 1);
    }

    // Läufer
    if (figur == 'L' || figur == 'l') {
        // Läufer bewegen sich diagonal
        return abs(zeileVon - zeileNach) == abs(spalteVon - spalteNach);
    }

    // Dame
    if (figur == 'D' || figur == 'd') {
        // Die Dame bewegt sich horizontal, vertikal oder diagonal
        return (zeileVon == zeileNach) || (spalteVon == spalteNach) || 
               (abs(zeileVon - zeileNach) == abs(spalteVon - spalteNach));
    }

    // König
    if (figur == 'K' || figur == 'k') {
        // Der König bewegt sich um ein Feld in jede Richtung
        return abs(zeileVon - zeileNach) <= 1 && abs(spalteVon - spalteNach) <= 1;
    }

    return false; // Wenn die Figur nicht erkannt wird oder keine Regel zutrifft
}

// Funktion zum Durchführen eines Zuges
void ziehen(bool wer)
{
    cout << (wer ? spieler[1] : spieler[0]) + " ist am Zug\n";
     // Eingabe des Spielers (z. B. A2A4 für einen Bauernzug)
    string userEingabe;
    int zeileVon, spalteVon, zeileNach, spalteNach;
    bool gueltigerZug = false;


    while (!gueltigerZug) {
        cin >> userEingabe; // Eingabe einlesen
        // Umwandlung der Nutzereingabe in Koordinaten des Arrays
        zeileVon = 9 - userEingabe[1] + 48;
        spalteVon = userEingabe[0] - 64;
        zeileNach = 9 - userEingabe[3] + 48;
        spalteNach = userEingabe[2] - 64;

        char figur = spielBrett.at(zeileVon).at(spalteVon);
        gueltigerZug = istGueltigerZug(zeileVon, spalteVon, zeileNach, spalteNach, figur);

        if (!gueltigerZug) {
            cout << "Ungültiger Zug, bitte erneut eingeben: ";
        }
    }

    // Eingabeaufforderung und Einlesen der Nutzereingabe
    cin >> userEingabe; // Eingabe einlesen
    // Umwandlung der Nutzereingabe in Koordinaten des Arrays
    zeileVon = 9 - userEingabe[1] + 48; // Umrechnung der Zeile (z.B. '2' -> 8)
    spalteVon = userEingabe[0] - 64;    // Umrechnung der Spalte (z.B. 'A' -> 1)
    zeileNach = 9 - userEingabe[3] + 48;
    spalteNach = userEingabe[2] - 64;

    // Zug ausführen, wenn er gültig ist
    spielBrett.at(zeileNach).at(spalteNach) = figur;
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
