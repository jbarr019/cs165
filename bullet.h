#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"


// Put your Bullet class here
class Bullet : public FlyingObject {
private:
    int frames;
public:
    Bullet(int speed);
    int getFrames();
    void setFrames(int frames);
    void draw();
    void fire(Point point, float angle);
};



#endif /* bullet_h */
