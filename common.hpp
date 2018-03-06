#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y, h;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }
    int getHeur() {return h; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setHeur(int h) { this->h = h; }
};

#endif
