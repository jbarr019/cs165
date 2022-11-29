#include "rocks.h"

// Put your Rock methods here
//Base Rock class
Rock::Rock() {
    setHP(1);
    setAngle(random(0, 361));
    setAlive(true);
}
int Rock::getType() {
    return type;
}
void Rock::setType(int type) {
    this->type = type;
    return;
}
int Rock::hit(int type) {
    setHP(getHP() - 1);
    if (getHP() == 0)
        setAlive(false);
    switch (type) {
        case 3:
            return 20;
            break;
        case 2:
            return 50;
            break;
        case 1:
            return 100;
            break;
        default:
            break;
    }
    return 1;
}
void Rock::draw() {
    return;
}
/*
 * Large Asteroid
 */
BigRock::BigRock() {
    setType(3);
    Point beginningLocation;
    long begX = 0;
    long begY = 0;
    switch (random(0, 2)) {
        case 0:
            begX = random(-700, -100);
            break;
        case 1:
            begX = random(100, 700);
        default:
            break;
    }
    switch (random(0, 2)) {
        case 0:
            begY = random(-700, -100);
            break;
        case 1:
            begY = random(100, 700);
        default:
            break;
    }
    beginningLocation.setX(begX);
    beginningLocation.setY(begY);
    setPoint(beginningLocation);
    setSpeed(5);
    velocity.setDx(getSpeed() * (cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * sin(angle * M_PI / 180));
    setRotation(BIG_ROCK_SPIN);
}
void BigRock::draw() {
    drawLargeAsteroid(point, getRotation());
    setRotation(getRotation() + BIG_ROCK_SPIN);
    return;
}
/*
 * Medium Asteroid
 */
MediumRock::MediumRock() {
    setType(2);
    Point beginningLocation;
    long begX = 0;
    long begY = 0;
    switch (random(0, 2)) {
        case 0:
            begX = random(-700, -100);
            break;
        case 1:
            begX = random(100, 700);
        default:
            break;
    }
    switch (random(0, 2)) {
        case 0:
            begY = random(-700, -100);
            break;
        case 1:
            begY = random(100, 700);
        default:
            break;
    }
    beginningLocation.setX(begX);
    beginningLocation.setY(begY);
    setPoint(beginningLocation);
    setSpeed(5);
    velocity.setDx(getSpeed() * (cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * sin(angle * M_PI / 180));
    setRotation(MEDIUM_ROCK_SPIN);
}
MediumRock::MediumRock(Rock * currentRock, int count) {
    setType(2);
    setPoint(currentRock->getPoint());
    setSpeed(7.5);
    velocity.setDx(getSpeed() * (cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * sin(angle * M_PI / 180));
    setRotation(MEDIUM_ROCK_SPIN);
    switch (count) {
        case 0:
            velocity.setDy(currentRock->getVelocity().getDy() + 1);
            break;
        case 1:
            velocity.setDy(currentRock->getVelocity().getDy() - 1);
            break;
            
        default:
            break;
    }
}
void MediumRock::draw() {
    drawMediumAsteroid(point, getRotation());
    setRotation(getRotation() + MEDIUM_ROCK_SPIN);
    return;
}
/*
 * Small Asteroid
 */
SmallRock::SmallRock() {
    setType(1);
    Point beginningLocation;
    long begX = 0;
    long begY = 0;
    switch (random(0, 2)) {
        case 0:
            begX = random(-700, -100);
            break;
        case 1:
            begX = random(100, 700);
        default:
            break;
    }
    switch (random(0, 2)) {
        case 0:
            begY = random(-700, -100);
            break;
        case 1:
            begY = random(100, 700);
        default:
            break;
    }
    beginningLocation.setX(begX);
    beginningLocation.setY(begY);
    setPoint(beginningLocation);
    setSpeed(5);
    velocity.setDx(getSpeed() * (cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * sin(angle * M_PI / 180));
    setRotation(SMALL_ROCK_SPIN);
}
SmallRock::SmallRock(Rock * currentRock, int count) {
    setType(1);
    setPoint(currentRock->getPoint());
    setSpeed(10);
    velocity.setDx(getSpeed() * (cos(angle * M_PI / 180)));
    velocity.setDy(getSpeed() * sin(angle * M_PI / 180));
    setRotation(SMALL_ROCK_SPIN);
    switch (count) {
        case 0:
            velocity.setDx(currentRock->getVelocity().getDx() + 3);
            break;
        case 1:
            velocity.setDx(currentRock->getVelocity().getDx() - 3);
            break;
        case 2:
            velocity.setDx(currentRock->getVelocity().getDx() + 2);
            break;
            
        default:
            break;
    }
}
void SmallRock::draw() {
    drawSmallAsteroid(point, getRotation());
    setRotation(getRotation() + SMALL_ROCK_SPIN);
    return;
}
