#include "xremotetimer.h"

#include <iostream>

/*Get time elapsed since session start*/
int getElapsedTime(QElapsedTimer timer){

    return (int)timer.elapsed() / 60000;
}

/*Play time delay*/
void timeDelay(QElapsedTimer timer, int timestamp){

    /*Delete token, sign out client and go back to sign in window*/
    if(getElapsedTime(timer) == timestamp){

        printf("Game over !\n");
    }

    return;
}
