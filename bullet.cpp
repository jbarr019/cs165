#include "bullet.h"
// Later double check on velocity and speed of bullets
// what it means that it starts the same as the ship
// same speed as ship? faster bullets as ship gets faster?

// Put your bullet methods here
Bullet::Bullet(int speed) {
    velocity.setDx(0);
    velocity.setDy(0);
    setFrames(0);
    setSpeed(speed + 5);
    setHP(1);
}
int Bullet::getFrames() {
    return frames;
}
void Bullet::setFrames(int frames) {
    this->frames = frames;
    return;
}
void Bullet::draw() {
    drawCircle(point, 3);
    return;
}
void Bullet::fire(Point point, float angle) {
    setPoint(point);
    setAngle(angle);
    velocity.setDx(getSpeed() * 1.5 *(cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * 1.5 * (sin(angle * M_PI / 180)));
}
