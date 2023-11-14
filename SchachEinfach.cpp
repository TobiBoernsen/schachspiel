#include <iostream>
#include <vector>
#include <string>

// Definieren der Schachbrettgröße
const int BOARD_SIZE = 8;

// Struktur eines einzelnen Feldes auf dem Schachbrett
struct Field {
    char piece;    // 'K', 'Q', 'R', 'B', 'N', 'P' für die Schachfiguren oder ' ' für ein leeres Feld
    bool isWhite;  // Farbe des Feldes: true für hell, false für dunkel
    bool hasPiece; // true, wenn eine Figur auf dem Feld steht, sonst false
};

// Funktion zum Erstellen eines neuen Spiels
void neuesSpiel(std::vector<std::vector<Field>>& board) {
    // Festlegen, wer spielt welche Farbe
    std::string playerOne, playerTwo;
    std::cout << "Spieler 1, wählen Sie Ihre Farbe (W/B): ";
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
    // Hier könnte eine Funktion aufgerufen werden, die das Schachbrett mit den Startpositionen der Figuren befüllt.
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
        // - Spieler machen abwechselnd Züge
        // - Überprüfen der Züge auf Gültigkeit
        // - Aktualisieren des Schachbretts
        // - Überprüfen auf Schachmatt, Patt, Remis oder Aufgabe
        // - Ende des Spiels, wenn eine der Bedingungen erfüllt ist

        // Beispiel für die Implementierung des Spielerwechsels
        // ...

        // Hier würde die Überprüfung der Spielbedingungen stattfinden
        // ...

        // Spielende oder Fortsetzung der Schleife
        // spielLaufen = false; // um die Schleife zu beenden
    }

    // Spielende
    std::cout << "Das Spiel ist beendet.\n";

    return 0;
}
