#include "ship.h"

// Put your ship methods here
Ship::Ship() {
    setPoint(Point());
    velocity.setDx(0);
    velocity.setDy(0);
    setRotation(0);
    setAngle(90);
    setSpeed(1);
    setHP(1);
    setTmpAngle(getAngle());
}
float Ship::getTmpAngle() {
    return tmpAngle;
}
void Ship::setTmpAngle(float tmpAngle) {
    this->tmpAngle = tmpAngle;
    return;
}
void Ship::draw() {
    drawShip(point, getRotation());
    return;
}
void Ship::moveLeft() {
    setRotation(getRotation() + ROTATE_AMOUNT);
    setAngle(getAngle() + ROTATE_AMOUNT);
    return;
}
void Ship::moveRight() {
    setRotation(getRotation() - ROTATE_AMOUNT);
    setAngle(getAngle() - ROTATE_AMOUNT);
    return;
}
void Ship::moveUp() {
    
    if (getTmpAngle() == getAngle())
        setSpeed(getSpeed() + THRUST_AMOUNT);
    else {
        setSpeed(1);
        setTmpAngle(getAngle());
    }
    setPoint(point);
    velocity.setDx(getSpeed() * (cos(getAngle() * M_PI / 180)));
    velocity.setDy(getSpeed() * (sin(getAngle() * M_PI / 180)));
    return;
}
