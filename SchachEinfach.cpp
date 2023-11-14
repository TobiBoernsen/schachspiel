#include <iostream>
#include <vector>
#include <string>

// Definieren der Schachbrettgr��e
const int BOARD_SIZE = 8;

// Struktur eines einzelnen Feldes auf dem Schachbrett
struct Field {
    char piece;    // 'K', 'Q', 'R', 'B', 'N', 'P' f�r die Schachfiguren oder ' ' f�r ein leeres Feld
    bool isWhite;  // Farbe des Feldes: true f�r hell, false f�r dunkel
    bool hasPiece; // true, wenn eine Figur auf dem Feld steht, sonst false
};

// Funktion zum Erstellen eines neuen Spiels
void neuesSpiel(std::vector<std::vector<Field>>& board) {
    // Festlegen, wer spielt welche Farbe
    std::string playerOne, playerTwo;
    std::cout << "Spieler 1, w�hlen Sie Ihre Farbe (W/B): ";
    std::cin >> playerOne;
    playerTwo = (playerOne == "W" ? "B" : "W");
    std::cout << "Spieler 1 spielt mit " << playerOne << ", Spieler 2 spielt mit " << playerTwo << ".\n";

    // Initialisieren des Schachbretts mit 64 Feldern (8x8)
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::vector<Field> row;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Field field;
            field.isWhite = (i + j) % 2 == 0;
            field.hasPiece = (i == 0 || i == 1 || i == 6 || i == 7); // Setzen der Figuren auf die ersten und letzten zwei Reihen
            field.piece = ' '; // Initial leer
            row.push_back(field);
        }
        board.push_back(row);
    }

    // Setzen der Figuren auf die Anfangspositionen
    // Hier k�nnte eine Funktion aufgerufen werden, die das Schachbrett mit den Startpositionen der Figuren bef�llt.
}

// Hauptfunktion des Programms
int main() {
    // Erstellen des Schachbretts als zweidimensionales Feld-Array
    std::vector<std::vector<Field>> schachbrett;

    // Starten eines neuen Spiels
    neuesSpiel(schachbrett);

    // Hauptspiel-Schleife
    bool spielLaufen = true;
    while (spielLaufen) {
        // Implementieren der Spiellogik:
        // - Spieler machen abwechselnd Z�ge
        // - �berpr�fen der Z�ge auf G�ltigkeit
        // - Aktualisieren des Schachbretts
        // - �berpr�fen auf Schachmatt, Patt, Remis oder Aufgabe
        // - Ende des Spiels, wenn eine der Bedingungen erf�llt ist

        // Beispiel f�r die Implementierung des Spielerwechsels
        // ...

        // Hier w�rde die �berpr�fung der Spielbedingungen stattfinden
        // ...

        // Spielende oder Fortsetzung der Schleife
        // spielLaufen = false; // um die Schleife zu beenden
    }

    // Spielende
    std::cout << "Das Spiel ist beendet.\n";

    return 0;
}
