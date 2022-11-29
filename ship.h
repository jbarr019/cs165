#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"


// Put your Ship class here
class Ship : public FlyingObject {
private:
    float tmpAngle;
public:
    Ship();
    float getTmpAngle();
    void setTmpAngle(float tmpAngle);
    void draw();
    void moveLeft();
    void moveRight();
    void moveUp();
};

#endif /* ship_h */
