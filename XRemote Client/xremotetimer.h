#ifndef XREMOTETIMER_H
#define XREMOTETIMER_H

#include <QElapsedTimer>

/*Get time elapsed since session start*/
int getElapsedTime(QElapsedTimer timer);

/*Play time delay*/
void timeDelay(QElapsedTimer timer, int timestamp);

#endif // XREMOTETIMER_H
