#include <string>
#include <iostream>
#include <iomanip>

class piece {

    public:
    bool isWhite;
    int xPos;
    int yPos;
    

    char type;
    
};

class square {
    public:

    int xPos;
    int yPos;

    bool isFree;

    piece pieceOnSquare;
    void printSquare(int index) {
        if (index == 0 || index == 2) {
            std::cout << "|     ";
        } else if (index == 1) {
            std::cout << "|  " << pieceOnSquare.type << "  ";
        }
    }

    /* square(int x, int y) { // Constructor
        xPos = x;
        yPos = y;
    } */
};