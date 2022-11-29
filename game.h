/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "point.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include "velocity.h"
#include "uiInteract.h"
#include "uiDraw.h"

class Game {
private:
    Point topLeft;
    Point bottomRight;
    int score;
    std::vector<Bullet> bullets;
    std::vector<Rock*> rocks;
    //Ship ship;
    
    /*
     * Modifications
     */
    int level;
    int lives;
    bool gameAlive;
    bool gameWait;
    int count;
    Ship * ship;
    void createShip();

    /*
     * Private methods for game logic
     */
    void advanceBullets();
    void advanceRocks();
    void advanceShip();
    void handleCollisions();
    void cleanUpZombies();
    bool isOnScreen(const Point & point);
    void createRock();
    Rock * currentRock;
    
    float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2);
public:
    /*
     * Constructors
     */
    Game(Point tl, Point br);
    ~Game();
    
    /*
     * Handle Input from user
     */
    void handleInput(const Interface & ui);
    
    /*
     * Advance the game one unit of time
     */
    void advance();
    
    /*
     * Draw everything for game
     */
    void draw(const Interface & ui);
};



#endif /* GAME_H */
