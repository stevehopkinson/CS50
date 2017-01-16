//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// width of paddle in pixels
#define PADDLEWIDTH 80

// height of paddle in pixel
#define PADDLEHEIGHT 15

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // horizontal velocity of ball initially
    double xvelocity = (drand48() - 0.5) * 0.05;
    
    // vertical velocity of ball initially
    double yvelocity = 0.07;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // update ball position
        double x = getX(ball) + xvelocity;
        if (x < 0)
        {
            x = 0;
            xvelocity *= -1;
        }
        else if (x > WIDTH - RADIUS * 2)
        {
            x = WIDTH - RADIUS * 2;
            xvelocity *= -1;
        }
        double y = getY(ball) + yvelocity;
        if (y < 0)
        {
            y = 0;
            yvelocity *= -1;
        }
        else if (y > HEIGHT - RADIUS * 2)
        {
           lives -= 1;
           waitForClick();
           xvelocity = (drand48() - 0.5) * 0.05;
           yvelocity = 0.07;
           x = WIDTH / 2 - RADIUS; 
           y = HEIGHT / 2 - RADIUS;
        }
        setLocation(ball, x, y);
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor
                double x = getX(event) - PADDLEWIDTH / 2;
                double y = HEIGHT - (PADDLEHEIGHT + 4);
                if (x < 4) {
                    x = 4;
                } 
                else if (x > WIDTH - (PADDLEWIDTH + 4))
                {
                    x = WIDTH - (PADDLEWIDTH + 4);
                }
                setLocation(paddle, x, y);
            }
        }
        
        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
            yvelocity *= -1;
        }
        else if (object == NULL || object == label)
        {
            continue;
        }
        else
        {
            removeGWindow(window, object);
            points += 1;
            bricks -= 1;
            updateScoreboard(window, label, points);
            yvelocity *= -1;
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double space = 4;
    double width = WIDTH / COLS - space;
    double height = 15;

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            double x = (space / 2) + i * (width + space); 
            double y = (space / 2) + j * (height + space) + 50;
            GRect brick = newGRect(x, y, width, height);
            setFilled(brick, true);
            setColor(brick, "RED");
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = WIDTH / 2 - RADIUS;
    int y = HEIGHT / 2 - RADIUS;
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    double x = WIDTH / 2 - PADDLEWIDTH / 2; 
    double y = HEIGHT - (PADDLEHEIGHT + 4);
    GRect paddle = newGRect(x, y, PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setLocation(scoreboard, 10, 20);
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // position label in top left of window
    double x = 10;
    double y = 20;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
