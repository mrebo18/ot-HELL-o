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
    
    // is there a more efficient way to implement the move function?
    Move *bestMove = nullptr;
    int bestH = -100000000;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if(main_board->checkMove(move, my_side)) {
                int temp = main_board->heuristic(move, my_side);
                std::cerr << temp << std::endl;
                std::cerr << i << " ," << j << std::endl;
                if( temp > bestH) {
                    if(bestMove) {
                        delete bestMove;
                    }
                    bestMove = move;
                    bestH = temp;
                }
                else {
                    delete move;
                }
            }
        }
    }

    std::cerr << " CHOSE: " << bestMove->getX() << " " << bestMove->getY() << "  " << bestH << std::endl;

    main_board->doMove(bestMove, my_side);
    return bestMove;

    return nullptr;


}


std::vector<Move*> Player::possible(Board board, Side side)
{
    std::vector<Move*> vect;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if(board.checkMove(move, side)) {
                vect.push_back(move);
            }
            else {
                delete move;
            }
        }
    }
    return vect;
}


// Move *Player::minimax(Board board, int level, int depth, bool top) {
//     std::vector<Move*> allMoves = possible(board, my_side);
//     Move *max;
//     Move *min;

//     for(int i = 1; i < 5; i++) {}
//     if(depth == 0) {
//         move->setHeur(copy->heuristic(move, side));
//         if ((worst == nullptr) || 
//             (move->getHeur() < worst->getHeur())) {
//             worst = move;
//         }
//     }
//     else {
//         copy->doMove(move, side);
//         Move *temp = copy->minimax(depth - 1, max, side);
//         if ((depth != max) && ((worst == nullptr) ||
//             (temp->getHeur() < worst->getHeur())))
//         {
//             worst = temp;
//         }
//         else
//         {
//             if ((best == nullptr) ||
//                 (temp->getHeur() > best->getHeur()))
//             {
//                 best = temp;
//             }
//         }
//         // reset board state here; make undoMove?
//         // also need to find some way to get rid of past values of best
        
//     }
            
//     else { delete move; }
        
    

//     if (depth == max) {
//         return best;
//     }
//     return worst;
// }