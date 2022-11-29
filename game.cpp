/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#define OFF_SCREEN_BORDER_AMOUNT 5
#define CLOSE_ENOUGH 15
#define SHIP_RADIUS 20
#define LARGE_RADIUS 32
#define MED_RADIUS 20
#define SM_RADIUS 10
#define BULLET_RADIUS 5

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/*
 *Changes to make it more like original:
 * 3 ship lives - DONE
 * Flames when thrusting upwards
 * Levels (each time the rocks vector hits 0, make a new vector with more rocks to start) - DONE
 * Bigger window dimensions - DONE
 * Accurate scores - DONE
 * Display level on top - DONE
 * Display lives right under score on top left - DONE
 * Incorporate UFOs
 * Wait/loading screen when level goes up
 * Rocks on new level spawn on border! That way no worry about spawning on ship
 * Still need to figure out how to "scan" so the ship doesnt spawn in the middle of a rock
 */



/*
 * Construct initial conditions of the game
 */
Game:: Game(Point tl, Point br) : topLeft(tl), bottomRight(br) {
    count = 0;
    score = 0;
    level = 1;
    lives = 3;
    gameAlive = false;
    gameWait = false;
    
    for (int i = 0; i < 30; i++) {
        Rock * newRock = NULL;
        if (i < 10)
            newRock = new BigRock();
        else if (i >= 10 && i < 20)
            newRock = new MediumRock();
        else if (i >= 20 && i < 30)
            newRock = new SmallRock;
        
        rocks.push_back(newRock);
    }
    currentRock = NULL;
    ship = NULL;
}
Game::~Game() {
    if (currentRock != NULL)
        delete currentRock;
}
/*
 * Handles input from the user interface
 */
void Game::handleInput(const Interface &ui) {
    if (ship != NULL) {
        if (ui.isLeft()) {
            ship->moveLeft();
        }
        if (ui.isRight()) {
            ship->moveRight();
        }
        if (ui.isUp()) {
            ship->moveUp();
        }
        if (ui.isSpace() && ship->isAlive()) {
            Bullet newBullet(ship->getSpeed());
            newBullet.fire(ship->getPoint(), ship->getAngle());
            bullets.push_back(newBullet);
        }
        
    }
    if (ui.isSpace() && !gameAlive && lives > 0) {
        gameAlive = true;
        gameWait = true;
    }
    if (ui.isDown() && !gameAlive) {
        gameAlive = true;
        gameWait = true;
        if (lives == 0) {
            lives = 3;
            score = 0;
            level = 1;
        }
    }
    return;
}

/*
 * Advances the game one unit of time
 */
void Game::advance() {
    if (gameAlive && gameWait) {
        vector<Rock*>::iterator rocksIt = rocks.begin();
        while (rocksIt != rocks.end()) {
            Rock * rockToDelete = *rocksIt;
            rockToDelete = NULL;
            delete rockToDelete;
            rocks.erase(rocksIt);
        }
        count++;
        if (count == 80) {
            gameWait = false;
            ship = new Ship();
            ship->setAlive(true);
            if (rocks.size() == 0) {
                for (int i = 0; i < 5; i++) {
                    Rock * newRock = new BigRock();
                    rocks.push_back(newRock);
                }
            }
        }
        advanceBullets();
        return;
    }
    if (gameAlive && ship == NULL) {
        createShip();
    }
    
    advanceBullets();
    advanceRocks();
    advanceShip();
    
    handleCollisions();
    cleanUpZombies();
    if (lives == 0) {
        gameAlive = false;
    }
    return;
}

/*
 * Advances the bullets if they are alive
 */
void Game::advanceBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].getFrames() == 40) {
            bullets[i].hit();
            bullets[i].setFrames(0);
        }
        if (bullets[i].isAlive()) {
            bullets[i].setFrames(bullets[i].getFrames() + 1);
            bullets[i].advance();
        }
        if (!isOnScreen(bullets[i].getPoint())) {
            bullets[i].wrapScreen();
        }
    } //loop through bullets
    return;
}

/*
 * Advances Rocks if they are alive
 */
void Game::advanceRocks() {
    // Advance rocks that are alive
    for (int i = 0; i < rocks.size(); i++) {
        if (rocks[i]->isAlive()) {
            rocks[i]->advance();
        }
        if (!isOnScreen(rocks[i]->getPoint())) {
            rocks[i]->wrapScreen();
        }
    }
    if (currentRock != NULL) {
        createRock();
    }
    
    //No rocks, next level
    if (rocks.size() == 0) {
        level++;
        for (int i = 0; i < (5 + level); i++) {
            Rock * newRock = new BigRock();
            rocks.push_back(newRock);
        }
        if (lives < 3) {
            lives++;
        }
    }
    return;
}

/*
 * Advances ship if alive
 */
void Game::advanceShip() {
    if (ship != NULL) {
        if (ship->isAlive()) {
            ship->advance();
            
            if (!isOnScreen(ship->getPoint())) {
                ship->wrapScreen();
            }
        }
    }
    
    return;
}
/*
 * Creates rocks when needed
 */
void Game:: createRock() {
    int count = 0;
    Rock * newRock = NULL;
    
    switch (currentRock->getType()) {
        case 3: {
            while (count < 3) {
                if (count != 2)
                    newRock = new MediumRock(currentRock, count);
                else
                    newRock = new SmallRock(currentRock, count);
                rocks.push_back(newRock);
                count++;
            } //loop that creates 2 medium and 1 small
        }//if its a large rock
            break;
        case 2:
            while (count < 2) {
                newRock = new SmallRock(currentRock, count);
                rocks.push_back(newRock);
                count++;
            } // loop that creates 2 small rocks
            break;
        default:
            break;
    }
    currentRock = NULL;
    return;
}

/*
 * Creates ship if crashed and lives are remaining
 */
void Game::createShip() {
    if (gameAlive && ship == NULL) {
        count++;
        if (count == 40) {
            ship = new Ship();
        }
    }
    return;
}
/*
 * Handle collisions between objects
 */
void Game::handleCollisions() {
    //Rock and Ship Collision
    if (ship != NULL && ship->isAlive()) {
        for (int i = 0; i < rocks.size(); i++) {
            bool collision = false;
            float dist = getClosestDistance(*ship, *rocks[i]);
            if (rocks[i]->isAlive()) {
                if (rocks[i]->getType() == 3) {
                    if (dist <= (LARGE_RADIUS + SHIP_RADIUS))
                        collision = true;
                }
                else if (rocks[i]->getType() == 2) {
                    if (dist <= (MED_RADIUS + SHIP_RADIUS))
                        collision = true;
                }
                else if (rocks[i]->getType() == 1) {
                    if (dist <= (SM_RADIUS + SHIP_RADIUS))
                        collision = true;
                }
                if (collision && ship->isAlive()) {
                    ship->hit();
                    lives--;
                    count = 0;
                }
            }
        }
    }
    
    
    // Rock and Bullet Collision
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].isAlive()) {
            for (int j = 0; j < rocks.size(); j++) {
                if (rocks[j]->isAlive()) {
                    bool collision = false;
                    float dist = getClosestDistance(bullets[i], *rocks[j]);
                    
                    //Change collision distance depending on rock type
                    if (rocks[j]->getType() == 3) {
                        if (dist <= LARGE_RADIUS + BULLET_RADIUS)
                            collision = true;
                    }
                    else if (rocks[j]->getType() == 2) {
                        if (dist <= MED_RADIUS + BULLET_RADIUS)
                            collision = true;
                    }
                    else if (rocks[j]->getType() == 1) {
                        if (dist <= SM_RADIUS + BULLET_RADIUS)
                            collision = true;
                    }
                    if (collision) {
                        //Bullet is now dead
                        bullets[i].hit();
                        
                        //Hit the rock
                        int points = rocks[j]->hit(rocks[j]->getType());
                        score += points;
                        
                        // Set as current rock
                        currentRock = rocks[j];
                        
                    }//hit between bullet and rock
                }//if rock is alive
            }//loop through rocks
        } //if bullet is alive
    }//loop through bullets
    return;
}

/*
 * Clean up zombies left by objects that die
 */
void Game::cleanUpZombies() {
    // Look for dead bullets
    vector<Bullet>::iterator bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        Bullet bullet = *bulletIt;
        
        if (!bullet.isAlive()) {
            bullets.erase(bulletIt);    //remove bullet from list
        }
        else {
            bulletIt++; //advance
        }
    }//bullet loop
    
    // Look for dead rocks
    vector<Rock*>::iterator rockIt = rocks.begin();
    while (rockIt != rocks.end()) {
        Rock * rockToDelete = *rockIt;
        
        if (!rockToDelete->isAlive()) {
            rockToDelete = NULL;
            delete rockToDelete;
            rocks.erase(rockIt);        //remove rock from list
        }
        else {
            rockIt++; //advance
        }
    }//rock loop
    
    // Look for dead ship
    if (ship != NULL && !ship->isAlive()) {
        ship = NULL;
        delete ship;
    }
    return;
}

/*
 * Detects if object is on the screen or not
 */
bool Game::isOnScreen(const Point &point) {
    return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
    && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
    && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
    && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance( FlyingObject &obj1, FlyingObject &obj2)
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/*
 * Draw everything needed for the game
 */
void Game::draw(const Interface &ui) {

    // Draw text to start game
    Point startGame;
    if (!gameAlive && lives > 0) {
        startGame.setX(startGame.getX() - 100);
        drawText(startGame, "START GAME");
        drawText(Point(startGame.getX() - 50, startGame.getY() - 50), "PRESS SPACE BAR");
    }
    // Draw text to indicate Player 1 and then start game with ship and rocks
    Point player1;
    player1.setX(-60);
    player1.setY(350);
    if (gameWait) {
        drawText(player1, "PLAYER 1");
    }
    //Draw ship
    if (ship != NULL && ship->isAlive()) {
        ship->draw();
    }
    
    //Draw rocks
    for (int i = 0; i < rocks.size(); i++) {
        if (rocks[i]->isAlive())
            rocks[i]->draw();
    }
    
    //Draw bullets
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].isAlive())
            bullets[i].draw();
    }
    
    //Draw score
    Point scoreLocation;
    scoreLocation.setX(topLeft.getX() + 5);
    scoreLocation.setY(topLeft.getY() - 5);
    drawNumber(scoreLocation, score);
    
    //Draw lives
    Point shipLivesLocation;
    shipLivesLocation.setX(scoreLocation.getX() + 20);
    shipLivesLocation.setY(scoreLocation.getY() - 50);
    for (int i = 0; i < lives; i++) {
        drawShip(shipLivesLocation, 0);
        shipLivesLocation.setX(shipLivesLocation.getX() + 40);
    }
    
    //Draw level
    Point levelLocation;
    levelLocation.setX(0);
    levelLocation.setY(topLeft.getY() - 20);
    drawNumber(levelLocation, level);
    
    //Game over
    if (lives == 0 && !gameAlive) {
        Point endGame;
        endGame.setX(endGame.getX() - 100);
        drawText(endGame, "GAME OVER");
        drawText(Point(endGame.getX() - 100, endGame.getY() - 50), "Press DOWN to Play Again");
    }
    return;
}
