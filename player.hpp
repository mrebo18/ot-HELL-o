#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    std::vector<Move*> possible(Board board, Side side);
    //Move *minimax(Board board, int level, int depth, int max);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
    Board main_board;
    Side my_side;
    Side op_side;
};

#endif
