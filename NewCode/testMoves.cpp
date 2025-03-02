#include "pieces.h"

const char characterList[8] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};

int returnFileNum(std::string & squarePos) {
    for (int i = 0; i < 8; i++) {
        if (squarePos[1] == characterList[i]) {
            return i + 1;
        } 
    }
    return 0;
}

bool validateMove(std::string inputPosition, std::string inputMove, piece movingPiece) {
        movingPiece.xPos = returnFileNum(inputPosition);
        int newFileNum = returnFileNum(inputMove);

        movingPiece.yPos = inputPosition[2] - 48;
        int newRankNum = inputMove[2] - 48;

        movingPiece.type = inputMove[0];

        // Making sure that the inputs are within the board and the moving piece is the same

        if (newFileNum > 8 || newRankNum > 8 || inputPosition[0] != inputMove[0]) 
            { return false; }

        // For each piece type, validating the movement based on the rules

        if (movingPiece.type == 'R') {
             if ((movingPiece.xPos == newFileNum || movingPiece.yPos == newRankNum) 
                && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
                { return true; } 
            else { return false; } 
        }

        if (movingPiece.type == 'N') {
            if ((abs(newFileNum - movingPiece.xPos) == 1 && abs(newRankNum - movingPiece.yPos) == 2) 
                || (abs(newFileNum - movingPiece.xPos) == 2 && abs(newRankNum - movingPiece.yPos) == 1))
                { return true; }
        }

        if (movingPiece.type == 'B') {
            if ((newFileNum - movingPiece.xPos == newRankNum - movingPiece.yPos) 
                && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
                { return true; } 
            else { return false; }
        }

        if (movingPiece.type == 'Q') {
            if ((newFileNum - movingPiece.xPos == newRankNum - movingPiece.yPos 
                || movingPiece.xPos == newFileNum 
                || movingPiece.yPos == newRankNum) 
                && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
                { return true; } 
            else { return false; }
        }

        if (movingPiece.type == 'K') {
            if (newFileNum >= movingPiece.xPos - 1 && newFileNum <= movingPiece.xPos + 1 
                && newRankNum >= movingPiece.yPos - 1 
                && newRankNum <= movingPiece.yPos + 1
                && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
                { return true; }
            else { return false; }
        }

        if (movingPiece.type == 'p') {
            if (movingPiece.isWhite) {
                if (movingPiece.yPos == 2) {
                    if (newFileNum == movingPiece.xPos && 
                        (newRankNum == movingPiece.yPos + 1 || newRankNum == movingPiece.yPos + 2)) 
                        { return true; }
                }
                else if (newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos + 1)
                    { return true; }
            }
            else if (movingPiece.yPos == 7) {
                if (newFileNum == movingPiece.xPos && 
                (newRankNum == movingPiece.yPos - 1 || newRankNum == movingPiece.yPos - 2)) 
                { return true; }
            }
            else if (newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos - 1)
                { return true; }
            else { return false; }
        }
    return 0;
} 

/*
Still have to check if a piece is in the way -- not really sure how to do that 
Also have to update the board -- ideally, I just update the two moving squares and print out another board using the createboard printing. 

Need to check if king moves into check - may not do it and just have capturing the king be a win.

*/



int main() {
    bool isWhiteTurn;
    std::string inputPosition;
    std::string inputMove;
    piece movingPiece;

    movingPiece.isWhite = true;

    std::cout << "It is currently " << isWhiteTurn << "'s move. Please enter the position of the piece you want to move: ";
    std::cin >> inputPosition;
    std::cout << "Enter where you would like to move it: ";
    std::cin >> inputMove;

    bool canMove = validateMove(inputPosition, inputMove, movingPiece);

    if (canMove) {
        std::cout << "True" << std::endl;
    } else { std::cout << "False" << std::endl; }
    

}




