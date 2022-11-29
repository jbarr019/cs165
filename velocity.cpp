#include "velocity.h"


// Put your velocity methods here
float Velocity::getDx() {
    return Dx;
}
float Velocity::getDy() {
    return Dy;
}
void Velocity::setDx(float Dx) {
    this->Dx = Dx;
    return;
}
void Velocity::setDy(float Dy) {
    this->Dy = Dy;
    return;
}
