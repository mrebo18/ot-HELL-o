#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    main_board = new Board();
    my_side = side;

    if (my_side == WHITE)
    {
        op_side = BLACK;
    }
    else
    {
        op_side = WHITE;
    }
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    if (opponentsMove != nullptr)
    {
        //do something with their move
        main_board->doMove(opponentsMove, op_side);
    }

    if (!main_board->hasMoves(my_side))
    {
        return nullptr;
    }
    
    Move *bestMove = nullptr;
    if (testingMinimax == true) { //specific depth search to pass minimax
        bestMove = get_mini(main_board, 2);
    }
    else {
        bestMove = get_mini(main_board, 0);
    }
    main_board->doMove(bestMove, my_side);
    return bestMove;
}

/*
 * Creates a vector of the possible moves given a specific board and side.
 */
std::vector<Move*> Player::possible(Board *board, Side side)
{
    std::vector<Move*> vect;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if(board->checkMove(move, side)) {
                vect.push_back(move);
            }
            else {
                delete move;
            }
        }
    }
    return vect;
}


/*
 * Returns the best possible move after searching a certain depth.
 */
Move *Player::get_mini(Board *board, int end) {
    // get possible moves
    std::vector<Move*> moves = possible(board, my_side);
    int best_h = -10000; //best heuristic
    int temp_h;
    Move *best;

    if (end == 0) {
        for (uint i = 0; i < moves.size(); i++) {
            temp_h = board->heuristic(moves[i], my_side);
            if (temp_h > best_h) {
                best_h = temp_h;
                best = moves[i];
            }
        }
    }
    else {
        for (uint i = 0; i < moves.size(); i++) {
            Board *copied = board->copy();
            temp_h = minimax(copied, 1, end, moves[i], my_side);
            if (temp_h > best_h) {
                best_h = temp_h;
                best = moves[i];
            }
        }
    }
    for (uint i = 0; i < moves.size(); i++) {
        if (moves[i] != best) {
            delete moves[i];
        }
    }
    return best;
}

/*
 * Returns through recursion the minimum possible score that would result from
 * a move after a given depth.
 */
int Player::minimax(Board *board, int depth, int end, Move *move, Side side) {
    std::vector<Move*> moves = possible(board, side);
    int worst_h = 10000;
    int move_h;
    
    if (depth == end) {
        for (uint i = 0; i < moves.size(); i++) {
            move_h = board->heuristic(moves[i], my_side);
            if(move_h < worst_h) {
                worst_h = move_h;
            }
        }
    }
    // opponent's turn, finding & implementing the move that's worst for me
    else if (depth % 2 == 1) {
        for (uint i = 0; i < moves.size(); i++) {
            Board *copied = board->copy();
            copied->doMove(moves[i], side);
            int temp = minimax(copied, depth + 1, end, moves[i], my_side);
            if (temp < worst_h) {
                worst_h = temp;
            }
        }
    }
    // our turn, but not at the lowest level
    else {
        for (uint i = 0; i < moves.size(); i++) {
            Board *copied = board->copy();
            copied->doMove(moves[i], side);
            int temp = minimax(copied, depth + 1, end, moves[i], op_side);
            if (temp < worst_h) {
                worst_h = temp;
            }
        }
    }
    return worst_h;
}