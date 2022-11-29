#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include <cmath>
using namespace std;

// Put your FlyingObject class here
class FlyingObject {
protected:
    Point point;
    Velocity velocity;
    bool alive;
    float angle;
    float rotation;
    float speed;
    int hp;
public:
    FlyingObject();
    Point getPoint();
    Velocity getVelocity();
    bool isAlive();
    float getAngle();
    float getRotation();
    float getSpeed();
    int getHP();
    void setPoint(Point point);
    void setVelocity(Velocity velocity);
    void setAlive(bool alive);
    void setAngle(float angle);
    void setRotation(float rotation);
    void setSpeed(float speed);
    void setHP(int hp);
    void wrapScreen();
    void hit();
    void advance();
};

#endif /* flyingObject_h */
