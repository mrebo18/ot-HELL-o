#include "board.hpp"
#include <stdio.h>
#include <stdlib.h>

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

int Board::heuristic(Move *m, Side side) {
    int X = m->getX();
    int Y = m->getY();
    int h;
    if(side == BLACK) {
        h = this->countBlack() - this->countWhite();
    }
    else {
        h = this->countWhite() - this->countBlack();
    }
    if(((X == 0) || (X == 7)) && ((Y == 0) || (Y == 7))) {
        h = h + 10;
    }
    else if(((X == 1) || (X == 6)) && ((Y == 1) || (Y == 6))) {
        h = h - 10;
    }
    else if(((X == 7) || (X == 6)) && ((Y == 7) || (Y == 6))) {
        h = h - 3;
    }
    else if(((X == 1) || (X == 0)) && ((Y == 1) || (Y == 0))) {
        h = h - 3;
    }
    else if(((X == 6) || (X == 0)) && ((Y == 0) || (Y == 6))) {
        h = h - 3;
    }
    else if(((X == 7) || (X == 1)) && ((Y == 7) || (Y == 1))) {
        h = h - 3;
    }
    else if((X == 0) || (X == 7) || (Y == 0) || (Y == 7)) {
        h = h + 3;
    }
    
    return h;
}

Move *Board::minimax(int depth, int max, Side side) {
    Board *copy = this->copy();
    Move *best;
    Move *worst;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if(copy->checkMove(move, side)) {
                if(depth == 0) {
                    move->setHeur(copy->heuristic(move, side));
                    if ((worst == nullptr) || 
                        (move->getHeur() < worst->getHeur())) {
                        worst = move;
                    }
                }
                else {
                    copy->doMove(move, side);
                    Move *temp = copy->minimax(depth - 1, max, side);
                    if ((depth != max) && ((worst == nullptr) ||
                        (temp->getHeur() < worst->getHeur())))
                    {
                        worst = temp;
                    }
                    else
                    {
                        if ((best == nullptr) ||
                            (temp->getHeur() > best->getHeur()))
                        {
                            best = temp;
                        }
                    }
                    // reset board state here; make undoMove?
                    // also need to find some way to get rid of past values of best
                    
                }
            }
            else { delete move; }
        }
    }

    if (depth == max) {
        return best;
    }
    return worst;
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}
