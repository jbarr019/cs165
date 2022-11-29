#include "flyingObject.h"


// Put your FlyingObject method bodies here
FlyingObject::FlyingObject() {
    setAlive(true);
}
Point FlyingObject::getPoint() {
    return point;
}
Velocity FlyingObject::getVelocity() {
    return velocity;
}
bool FlyingObject::isAlive() {
    return alive;
}
float FlyingObject::getAngle() {
    if (angle > 360)
        angle = 0;
    if (angle < 0)
        angle = 360;
    return angle;
}
float FlyingObject::getRotation() {
    return rotation;
}
float FlyingObject::getSpeed() {
    return speed;
}
int FlyingObject::getHP() {
    return hp;
}
void FlyingObject::setPoint(Point point) {
    this->point = point;
    return;
}
void FlyingObject::setVelocity(Velocity velocity) {
    this->velocity = velocity;
    return;
}
void FlyingObject::setAlive(bool alive) {
    this->alive = alive;
    return;
}
void FlyingObject::setAngle(float angle) {
    this->angle = angle;
    return;
}
void FlyingObject::setRotation(float rotation) {
    this->rotation = rotation;
    return;
}
void FlyingObject::setSpeed(float speed) {
    this->speed = speed;
    return;
}
void FlyingObject::setHP(int hp) {
    this->hp = hp;
    return;
}
void FlyingObject::wrapScreen() {
    //Change X of object's point
    if (point.getX() > 700)
        point.setX(-700);
    if (point.getX() < -700)
        point.setX(700);
    
    //Change Y of object's point
    if (point.getY() > 700)
        point.setY(-700);
    if (point.getY() < -700)
        point.setY(700);
    return;
}
void FlyingObject::hit() {
    setHP(getHP() - 1);
    if(getHP() == 0)
        setAlive(false);
}
void FlyingObject::advance() {
    point.setX(point.getX() + velocity.getDx());
    point.setY(point.getY() + velocity.getDy());
}
