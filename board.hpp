#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    short h[8][8] = {{30, -20,  5,  5,  5,  5, -20, 30},
                    {-20,-30, 1, 1, 1, 1,-30, -20},
                    {5, 1,  1,  1,  1,  1, 1,  5},
                    {5, 1,  1,  1,  1,  1, 1,  5},
                    {5, 1,  1,  1,  1,  1, 1,  5},
                    {5, 1,  1,  1,  1,  1, 1,  5},
                    {-20,-30,  1,  1,  1,  1,-30, -20},
                    {30, -20,  5,  5,  5,  5, -20, 30} };
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    int heuristic(Move *m, Side side);
    int mobility(Side side);

    void setBoard(char data[]);
};

#endif
