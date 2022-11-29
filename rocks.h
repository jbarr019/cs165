#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"


// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock

class Rock : public FlyingObject {
private:
    int type;
public:
    Rock();
    int getType();
    void setType(int type);
    int hit(int type);
    virtual void draw();
};
class BigRock : public Rock {
private:
public:
    BigRock();
    void draw();
};
class MediumRock : public Rock {
private:
public:
    MediumRock();
    MediumRock(Rock * currentRock, int count);
    void draw();
};
class SmallRock : public Rock {
private:
public:
    SmallRock();
    SmallRock(Rock * currentRock, int count);
    void draw();
};
#endif /* rocks_h */
