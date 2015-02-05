//
//  MoleCircle.cpp
//  WhackAMoleGame
//
//  Created by ucuc on 2/5/15.
//
//

#include "MoleCircle.h"
#include <iostream>
#include <chrono>
#include <time.h>

using namespace std;

int MoleCircle::targetCircleNumber = 0;

MoleCircle::MoleCircle()
{
}

MoleCircle::MoleCircle(int id, int number, float x, float y, float r)
{
    circle_id = id;
    circle_number = number;
    circle_x = x;
    circle_y = y;
    circle_r = r;
}

int MoleCircle::getCircle_x()
{
    return circle_x;
}

int MoleCircle::getCircle_y()
{
    return circle_y;
}

float MoleCircle::getCircle_r()
{
    return circle_r;
}

Vec2f MoleCircle::getVec2f()
{
    return Vec2f(circle_x, circle_y);
}

bool MoleCircle::detectCollision(float x, float y)
{
    if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= circle_r * circle_r) {
        checkStartTime();
        return 1;
    }

    startTimeIs = false;
    return 0;
}

void MoleCircle::checkStartTime()
{
    if (!startTimeIs) {
        startTimeIs = true;
        startTime = std::chrono::system_clock::now();
    } else {
        checkEndTime();
    }
}

bool MoleCircle::checkEndTime()
{
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();

    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    if (elapsed_seconds > 2) {
        if (targetCircleNumber == circle_id) {
            cout << "OK - " << circle_id << endl;
            srand((unsigned int)time(NULL));
            targetCircleNumber = rand() % circle_number;
        } else {
            cout << "NG - " << circle_id << endl;
        }

        startTimeIs = false;
        return true;
    }

    return false;
}
