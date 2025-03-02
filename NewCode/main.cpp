#include "pieces.h"


bool isWhiteTurn = true;
const int BOARD_WIDTH = 8;

void createBoard (const int, square squares[BOARD_WIDTH][BOARD_WIDTH]);
bool validateMove(std::string inputPosition, std::string inputMove, piece & movingPiece);
int returnFileNum(std::string & squarePos);
bool movePieceConditional (square squares[BOARD_WIDTH][BOARD_WIDTH], piece & movingPiece, std::string pos, std::string move);
void movePiece (square squares[BOARD_WIDTH][BOARD_WIDTH], piece & movingPiece, std::string pos, std::string move);
int * convertInput(std::string inputPos, std::string inputMove);
void updateBoard(const int SIZE, square squaresList[BOARD_WIDTH][BOARD_WIDTH]);
bool hasEnded(square squaresList[BOARD_WIDTH][BOARD_WIDTH], bool isWhiteTurn);

int main () {
    
    square squaresList[BOARD_WIDTH][BOARD_WIDTH];
    
    std::string inputMove;
    std::string inputPosition;
    piece movingPiece;

    // figure out how to pass squaresList by reference

    createBoard(BOARD_WIDTH, squaresList);

    /*
    Ideally, we would create an object for a square and have the board be made up of 64 of them in an array[8][8]

    The format of the squares would be as below (with some changes to layout potentially) where the space in the middle would hold the 
    value of the piece in that square (or no piece)

    Additionally, the pieces would have their own objects (a piece object with the individual pieces each inheriting the class) which have rules about their movement.
        - see pieces.h

    Every turn, we take a validated input in the form [Piece][Rank][File] (Nf3) and move the piece accordingly
    */
   int count = 0;

   while (hasEnded) {

    if (isWhiteTurn) {
    std::cout << "It is currently whites's move. Please enter the position of the piece you want to move: ";
    }
    else {
        std::cout << "It is currently black's move. Please enter the position of the piece you want to move: ";
    }
        
    std::cin >> inputPosition;
    std::cout << "Enter where you would like to move it: ";
    std::cin >> inputMove;

    


    // use the correct square to find piece for validating move.

    if (!(validateMove(inputPosition, inputMove, movingPiece) && movePieceConditional(squaresList, movingPiece, inputPosition, inputMove))) {
        std::cout << "Not a valid move, please enter a correct move - ";
        //std::cout << "piece is at " << movingPiece.xPos << ", " << movingPiece.yPos;
        //std::cout << "input is at " << returnFileNum(inputPosition) << ", " << inputPosition[2] - 48 << "to " << returnFileNum(inputMove) << ", " << inputMove[2] - 48;
    }
    else { 
        // Move Piece func and Update board func
        movePiece(squaresList, movingPiece, inputPosition, inputMove);
        //std::cout << "Well done" << std::endl; 
        updateBoard(BOARD_WIDTH, squaresList);
        isWhiteTurn = !isWhiteTurn;
        //std::cout << "piece is at " << movingPiece.xPos << ", " << movingPiece.yPos;
    }
    count++;
   }
    
      
    

    return 0;

   
}

/*int * convertInput(std::string inputPos) {
    int fileRank[2];

    fileRank[0] = returnFileNum(inputPos);
    fileRank[1] = inputPos[2] - 48;

    return fileRank;


    //Unused RN
} */

int returnFileNum(std::string & squarePos) {
    const char characterList[8] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
    };
    
    for (int i = 0; i < 8; i++) {
        if (squarePos[1] == characterList[i]) {
            return i + 1;
        } 
    }
    return 0;
}

bool validateMove(std::string inputPosition, std::string inputMove, piece & movingPiece) {

    // Making sure that the inputs are within the board and the moving piece is the same

    // end up using the changing square functions to return a square such that square.xPos = newFileNum and square.yPos = newRankNum 
    // use these statements in those functions to change them

    movingPiece.xPos = returnFileNum(inputPosition);
    int newFileNum = returnFileNum(inputMove);

    movingPiece.yPos = inputPosition[2] - 48;
    int newRankNum = inputMove[2] - 48;

    movingPiece.type = inputMove[0];

    if (newFileNum > 8 || newRankNum > 8 || inputPosition[0] != inputMove[0]) 
        { return false; /* std::cout << "random error"; */}

    // For each piece type, validating the movement based on the rules

    if (movingPiece.type == 'R') {
            if ((movingPiece.xPos == newFileNum || movingPiece.yPos == newRankNum) 
            && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
            { return true; } 
        else { return false; /*std::cout << "rook error"; */} 
    }

    if (movingPiece.type == 'N') {
        if ((abs(newFileNum - movingPiece.xPos) == 1 && abs(newRankNum - movingPiece.yPos) == 2) 
            || (abs(newFileNum - movingPiece.xPos) == 2 && abs(newRankNum - movingPiece.yPos) == 1))
            { return true; /* std::cout << "knight error"; */}
    }

    if (movingPiece.type == 'B') {
        if ((abs(newFileNum - movingPiece.xPos) == abs(newRankNum - movingPiece.yPos)) 
            && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
            { return true; } 
        else { return false; /* std::cout << "bishop error"; */}
    }

    if (movingPiece.type == 'Q') {
        if ((abs(newFileNum - movingPiece.xPos) == abs(newRankNum - movingPiece.yPos)
            || movingPiece.xPos == newFileNum 
            || movingPiece.yPos == newRankNum) 
            && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
            { return true; } 
        else { return false; /*std::cout << "queen error"; */}
    }

    if (movingPiece.type == 'K') {
        if (newFileNum >= movingPiece.xPos - 1 && newFileNum <= movingPiece.xPos + 1 
            && newRankNum >= movingPiece.yPos - 1 
            && newRankNum <= movingPiece.yPos + 1
            && !(newFileNum == movingPiece.xPos && newRankNum == movingPiece.yPos)) 
            { return true; }
        else { return false; /*std::cout << "king error"; */}
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
        else { return false; /*std::cout << "pawn error";*/ }
    }
    return 0;
} 


void createBoard (const int BOARD_WIDTH, square squaresList[8][8]) {
    // establishes the order of the pieces and the types of pieces on the squares
    const int PIECE_ORDER_ROW_1[8]  = { 0, 1, 2, 3, 4, 2, 1, 0 };
    const char pieceValue[6] = { 'R', 'N', 'B', 'Q', 'K', 'p' };
    const int reverseRanks[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    // looping horizontally and vertically
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            std::cout << "------";
            // assigning squares to have correct piece types if on certain rows (or free if not) and their correct positions
            if (i == 0 || i == 7) {
                squaresList[i][j].pieceOnSquare.type = pieceValue[PIECE_ORDER_ROW_1[j]];
                squaresList[i][j].isFree = false;
                    if (i == 0) { squaresList[i][j].pieceOnSquare.isWhite = false; }
                    else { squaresList[i][j].pieceOnSquare.isWhite = true; }
            }
            else if (i == 1 || i == 6) {
                squaresList[i][j].pieceOnSquare.type = 'p';
                squaresList[i][j].isFree = false;
                    if (i == 1) { squaresList[i][j].pieceOnSquare.isWhite = false; }
                    else { squaresList[i][j].pieceOnSquare.isWhite = true; }
            } 

            else { 
                squaresList[i][j].pieceOnSquare.type = ' '; 
                squaresList[i][j].isFree = true;
            }
            squaresList[i][j].xPos = j + 1;
            squaresList[i][j].yPos = reverseRanks[i];
        }
        
        std::cout << "-" << std::endl;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < BOARD_WIDTH; k++) {
                squaresList[i][k].printSquare(j);
            }
        std::cout << "|" << std::endl;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
            std::cout << "------";
        }    
    std::cout << "-" << std::endl;
}

bool movePieceConditional (square squares[BOARD_WIDTH][BOARD_WIDTH], piece & movingPiece, std::string inputPos, std::string inputMove) {
    /*
    This is going into the validateMove function
    check whether there is a piece on the moving and og square of the same color.
    Check whether the piece is the same color as the moving side
    */

    int ogFileNum = returnFileNum(inputPos);
    int newFileNum = returnFileNum(inputMove);

    int ogRankNum = inputPos[2] - 48;
    int newRankNum = inputMove[2] - 48;

    // this part gets a little ugly imma be honest -- squaresList does not line up with the conventional grid system even though the xPos and yPos's do 

    if (squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.type != inputPos[0] || squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.isWhite != isWhiteTurn) {
        //std::cout << "no piece or wrong color" << std::endl;
        //std::cout << squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.type << ", " << inputPos[0] << std::endl;
        //std::cout << squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.isWhite << ". " << isWhiteTurn << std::endl;
        return false;
    }
    if (squares[8 - newRankNum][newFileNum - 1].pieceOnSquare.isWhite == squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.isWhite && squares[8 - newRankNum][newFileNum - 1].isFree == false) {
        // std::cout << "moving to a square with same color piece";
        return false;
    }
    
    return true;

}
//test

void movePiece (square squares[BOARD_WIDTH][BOARD_WIDTH], piece & movingPiece, std::string inputPosition, std::string inputMove) {
    /*
    change movingPiece xpos and ypos to the inputMove rank and file, 
    free the old square, 
    and update the new square 
    */

    int ogFileNum = returnFileNum(inputPosition);
    int newFileNum = returnFileNum(inputMove);

    int ogRankNum = inputPosition[2] - 48;
    int newRankNum = inputMove[2] - 48;

    movingPiece.xPos = squares[8 - newRankNum][newFileNum - 1].xPos;
    movingPiece.yPos = squares[8 - newRankNum][newFileNum - 1].yPos;

    // std::cout << "Moved Piece to " << movingPiece.xPos << ", " << movingPiece.yPos;

    squares[8 - ogRankNum][ogFileNum - 1].isFree = true;
    squares[8 - ogRankNum][ogFileNum - 1].pieceOnSquare.type = ' ';


    squares[8 - newRankNum][newFileNum - 1].isFree = false;
    squares[8 - newRankNum][newFileNum - 1].pieceOnSquare.type = inputMove[0];
    squares[8 - newRankNum][newFileNum - 1].pieceOnSquare.isWhite = isWhiteTurn;



}


void updateBoard(const int SIZE, square squaresList[BOARD_WIDTH][BOARD_WIDTH]) {
    // establishes the order of the pieces and the types of pieces on the squares
    const int PIECE_ORDER_ROW_1[8]  = { 0, 1, 2, 3, 4, 2, 1, 0 };
    const char pieceValue[6] = { 'R', 'N', 'B', 'Q', 'K', 'p' };
    const int reverseRanks[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    // looping horizontally and vertically
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            std::cout << "------";
        }
        
        std::cout << "-" << std::endl;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < BOARD_WIDTH; k++) {
                squaresList[i][k].printSquare(j);
            }
        std::cout << "|" << std::endl;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
            std::cout << "------";
        }    
    std::cout << "-" << std::endl;
}



bool hasEnded(square squaresList[BOARD_WIDTH][BOARD_WIDTH], bool isWhiteTurn) {
    /*for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (squaresList[i][j].pieceOnSquare.type == 'K' && squaresList[i][j].pieceOnSquare.isWhite != isWhiteTurn) {
                return false;
            }
        }
    }
    return true; */
    return false;
}


// Test Comment