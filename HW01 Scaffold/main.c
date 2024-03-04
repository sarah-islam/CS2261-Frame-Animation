#include "gba.h"
#include "print.h"

// Function Prototypes
void initialize();
void updateGame();
void drawGame();

// dark red
#define RED RGB(25, 0, 0)

// reddish yellow
#define YELLOW RGB(31, 25, 0)

// dark orange
#define ORANGE RGB(28, 13, 2)

// light blue
#define BLUE RGB(0, 20, 30)

// dark green
#define GREEN RGB(0, 15, 5)

void frameZero();
void frameOne();
void frameTwo();
void frameThree();

int currentFrame;
unsigned short oldButtons;
unsigned short buttons;
int isLooping; // 0 is off, 1 is on
int loopCount;
int animationDirection; // 0 is forward (to the right), 1 is backward (to the left)

int frameDelay = 60;

int main() {

    initialize();

    while (1) {
        oldButtons = buttons;
    	buttons = REG_BUTTONS;

        updateGame();
        waitForVBlank();
        drawGame();
    }
    return 0;

}

void initialize() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    currentFrame = 0;

    oldButtons = 0;
    buttons = REG_BUTTONS;

    drawRectangle(0, 0, 240, 89, BLUE);
    drawRectangle(0, 89, 240, 71, GREEN);

}

void updateGame() {
    if (BUTTON_PRESSED(BUTTON_A)) {
        currentFrame++;
        if (currentFrame > 3) {
            currentFrame = 0;
        }
    }
    if (BUTTON_PRESSED(BUTTON_B)) {
        currentFrame--;
        if (currentFrame < 0) {
            currentFrame = 3;
        }
    }
    if (BUTTON_PRESSED(BUTTON_LEFT)) {
        currentFrame = 0;
    
    }
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        currentFrame = 3;
    }

    if (BUTTON_PRESSED(BUTTON_START)) {
        if (isLooping == 0) {
            isLooping = 1;
        } else {
            isLooping = 0;
        }
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        if (animationDirection == 0) {
            animationDirection = 1;
        } else {
            animationDirection = 0;
        }
    }

    // extra credit: speed down
    if (BUTTON_PRESSED(BUTTON_DOWN)) {
        if (frameDelay < 120) {
            frameDelay += 10;
        }
    }
    // extra credit: speed up
    if (BUTTON_PRESSED(BUTTON_UP)) {
        if (frameDelay > 10) {
            frameDelay -= 10;
        }
    }

    if (isLooping == 1) {
        loopCount++;
        if (loopCount > frameDelay) {
            loopCount = 0;
            if (animationDirection == 0) {
                currentFrame++;
                if (currentFrame > 3) {
                    currentFrame = 0;
                }
            } else {
                currentFrame--;
                if (currentFrame < 0) {
                    currentFrame = 3;
                }
            }
        }
    }
}

void drawGame() {
    if (currentFrame == 0) {
        frameZero();
    } else if (currentFrame == 1) {
        frameOne();
    } else if (currentFrame == 2) {
        frameTwo();
    } else if (currentFrame == 3) {
        frameThree();
    }
}


void frameZero() { // princess zelda faced forward
    drawRectangle(112, 73, 16, 16, BLUE);
    drawRectangle(117, 73, 2, 3, ORANGE);
    drawRectangle(121, 73, 2, 3, ORANGE);

    drawRectangle(115, 76, 2, 5, ORANGE);
    drawRectangle(123, 76, 2, 5, ORANGE);

    drawRectangle(119, 76, 2, 2, YELLOW);
    drawRectangle(119, 78, 2, 2, ORANGE);

    drawRectangle(114, 81, 2, 3, ORANGE);
    drawRectangle(124, 81, 2, 3, ORANGE);

    drawRectangle(118, 81, 4, 2, RED);
    drawRectangle(117, 84, 6, 2, RED);
    drawRectangle(115, 86, 10, 3, RED);

    drawRectangle(119, 73, 2, 1, ORANGE);

    setPixel(116, 74, YELLOW);
    drawRectangle(119, 74, 2, 1, YELLOW);
    setPixel(123, 74, YELLOW);

    setPixel(116, 75, YELLOW);
    setPixel(123, 75, YELLOW);
    drawRectangle(119, 75, 2, 1, ORANGE);

    setPixel(117, 76, ORANGE);
    setPixel(118, 76, RED);
    setPixel(121, 76, RED);
    setPixel(122, 76, ORANGE);

    setPixel(117, 77, YELLOW);
    setPixel(118, 77, ORANGE);
    setPixel(121, 77, ORANGE);
    setPixel(122, 77, YELLOW);

    drawRectangle(117, 78, 2, 1, YELLOW);
    drawRectangle(121, 78, 2, 1, YELLOW);

    setPixel(117, 79, ORANGE);
    setPixel(118, 79, YELLOW);
    setPixel(121, 79, YELLOW);
    setPixel(122, 79, ORANGE);

    drawRectangle(117, 80, 2, 1, RED);
    drawRectangle(119, 80, 2, 1, YELLOW);
    drawRectangle(121, 80, 2, 1, RED);

    setPixel(116, 81, YELLOW);
    setPixel(117, 81, RED);
    setPixel(122, 81, RED);
    setPixel(123, 81, YELLOW);

    drawRectangle(116, 82, 2, 1, YELLOW);
    drawRectangle(122, 82, 2, 1, YELLOW);

    setPixel(116, 83, YELLOW);
    setPixel(117, 83, RED);
    setPixel(118, 83, ORANGE);
    drawRectangle(119, 83, 2, 1, YELLOW);
    setPixel(121, 83, ORANGE);
    setPixel(122, 83, RED);
    setPixel(123, 83, YELLOW);

    setPixel(114, 84, ORANGE);
    drawRectangle(115, 84, 2, 1, YELLOW);
    drawRectangle(123, 84, 2, 1, YELLOW);
    setPixel(125, 84, ORANGE);

    drawRectangle(114, 85, 2, 1, ORANGE);
    setPixel(116, 85, RED);
    setPixel(123, 85, RED);
    drawRectangle(124, 85, 2, 1, ORANGE);

    setPixel(114, 86, ORANGE);
    setPixel(125, 86, ORANGE);

    setPixel(114, 87, ORANGE);
    setPixel(125, 87, ORANGE);

    setPixel(114, 88, RED);
    setPixel(125, 88, RED);
}

void frameOne() { // princess zelda twirling right facing
    drawRectangle(112, 73, 16, 16, BLUE);
    drawRectangle(117, 74, 2, 2, ORANGE);
    drawRectangle(120, 73, 3, 3, ORANGE);
    drawRectangle(116, 76, 4, 4, ORANGE);
    drawRectangle(121, 78, 3, 2, YELLOW);
    drawRectangle(115, 81, 3, 2, ORANGE);
    drawRectangle(120, 81, 4, 2, RED);
    drawRectangle(118, 84, 6, 4, RED);
    drawRectangle(115, 85, 2, 2, ORANGE);
    drawRectangle(116, 87, 2, 2, RED);

    drawRectangle(118, 73, 2, 1, ORANGE);
    setPixel(123, 73, ORANGE);

    setPixel(119, 74, YELLOW);
    drawRectangle(123, 74, 2, 1, YELLOW);

    setPixel(119, 75, YELLOW);
    drawRectangle(123, 75, 2, 1, ORANGE);

    setPixel(120, 76, ORANGE);
    setPixel(121, 76, YELLOW);
    setPixel(122, 76, RED);
    setPixel(123, 76, YELLOW);

    drawRectangle(120, 77, 2, 1, YELLOW);
    setPixel(122, 77, ORANGE);
    setPixel(123, 77, YELLOW);

    setPixel(120, 78, YELLOW);
    setPixel(124, 78, YELLOW);

    setPixel(120, 79, ORANGE);

    drawRectangle(116, 80, 2, 1, ORANGE);
    drawRectangle(118, 80, 4, 1, RED);
    setPixel(122, 80, YELLOW);

    setPixel(118, 81, RED);
    setPixel(119, 81, YELLOW);

    drawRectangle(118, 82, 2, 1, YELLOW);
    drawRectangle(115, 83, 2, 1, ORANGE);
    drawRectangle(117, 83, 2, 1, YELLOW);
    setPixel(119, 83, RED);
    setPixel(120, 83, ORANGE);
    setPixel(121, 83, YELLOW);
    setPixel(122, 83, ORANGE);
    setPixel(123, 83, YELLOW);

    setPixel(115, 84, ORANGE);
    drawRectangle(116, 84, 2, 1, YELLOW);
    setPixel(124, 84, YELLOW);

    setPixel(117, 85, RED);

    setPixel(117, 86, RED);
    setPixel(124, 86, RED);

    setPixel(115, 87, ORANGE);
    setPixel(124, 87, RED);

    drawRectangle(114, 88, 2, 1, RED);
    drawRectangle(118, 88, 3, 1, RED);
    drawRectangle(121, 88, 2, 1, ORANGE);
    drawRectangle(123, 88, 3, 1, RED);
}
void frameTwo() { // princess zelda back facing
    drawRectangle(112, 73, 16, 16, BLUE);
    drawRectangle(117, 73, 2, 3, ORANGE);
    drawRectangle(121, 73, 2, 3, ORANGE);
    drawRectangle(115, 76, 10, 5, ORANGE);
    drawRectangle(114, 81, 12, 7, ORANGE);
    drawRectangle(114, 88, 12, 1, RED);

    drawRectangle(119, 73, 2, 1, ORANGE);

    setPixel(116, 74, YELLOW);
    setPixel(119, 74, YELLOW);
    setPixel(120, 74, YELLOW);
    setPixel(123, 74, YELLOW);

    setPixel(116, 75, YELLOW);
    setPixel(119, 75, ORANGE);
    setPixel(120, 75, ORANGE);
    setPixel(123, 75, YELLOW);
}

void frameThree() { // princess zelda twirling/jumping left facing
    drawRectangle(112, 73, 16, 16, BLUE);
    drawRectangle(117, 73, 3, 3, ORANGE);
    drawRectangle(121, 74, 2, 2, ORANGE);
    drawRectangle(120, 76, 4, 4, ORANGE);
    drawRectangle(118, 77, 2, 2, YELLOW);
    drawRectangle(116, 78, 2, 2, YELLOW);
    drawRectangle(122, 80, 2, 2, ORANGE);
    drawRectangle(118, 80, 2, 3, RED);
    drawRectangle(116, 81, 2, 2, RED);
    drawRectangle(116, 84, 4, 4, RED);
    drawRectangle(120, 84, 2, 3, RED);
    drawRectangle(123, 84, 2, 2, ORANGE);
    drawRectangle(122, 86, 2, 2, RED);

    setPixel(116, 73, ORANGE);
    drawRectangle(120, 73, 2, 1, ORANGE);

    drawRectangle(115, 74, 2, 1, YELLOW);
    setPixel(120, 74, YELLOW);

    drawRectangle(115, 75, 2, 1, ORANGE);
    setPixel(120, 75, YELLOW);

    setPixel(116, 76, YELLOW);
    setPixel(117, 76, RED);
    setPixel(118, 76, YELLOW);
    setPixel(119, 76, ORANGE);

    setPixel(116, 77, YELLOW);
    setPixel(117, 77, ORANGE);

    setPixel(115, 78, YELLOW);

    setPixel(118, 79, YELLOW);
    setPixel(119, 79, ORANGE);

    setPixel(117, 80, YELLOW);
    drawRectangle(120, 80, 2, 1, RED);

    drawRectangle(120, 81, 2, 1, YELLOW);
    setPixel(124, 81, ORANGE);

    setPixel(115, 82, YELLOW);
    setPixel(120, 82, RED);
    drawRectangle(121, 82, 2, 1, YELLOW);
    drawRectangle(123, 82, 2, 1, ORANGE);

    drawRectangle(114, 83, 2, 1, YELLOW);
    setPixel(117, 83, ORANGE);
    setPixel(118, 83, YELLOW);
    setPixel(119, 83, ORANGE);
    setPixel(120, 83, RED);
    drawRectangle(121, 83, 2, 1, ORANGE);
    drawRectangle(123, 83, 2, 1, YELLOW);

    setPixel(122, 84, ORANGE);

    setPixel(122, 85, RED);

    setPixel(115, 86, RED);
    setPixel(124, 86, ORANGE);

    drawRectangle(114, 87, 2, 1, RED);
    drawRectangle(120, 87, 2, 1, ORANGE);
    drawRectangle(124, 87, 2, 1, RED);
}