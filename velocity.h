#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
class Velocity {
private:
    float Dx;
    float Dy;
public:
    float getDx();
    float getDy();
    void setDx(float Dx);
    void setDy(float Dy);
};

#endif /* velocity_h */
