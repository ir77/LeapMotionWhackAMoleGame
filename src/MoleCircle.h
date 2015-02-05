//
//  MoleCircle.h
//  WhackAMoleGame
//
//  Created by ucuc on 2/5/15.
//
//

#ifndef __WhackAMoleGame__MoleCircle__
#define __WhackAMoleGame__MoleCircle__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class MoleCircle {
public:
    MoleCircle();
    MoleCircle(int id, int number, float x, float y, float r);
    // MoleCircle(int id, float x, float y, float r, float r_big, float r_small);

    static int targetCircleNumber;

    int getCircle_x();
    int getCircle_y();
    float getCircle_r();
    Vec2f getVec2f();
    bool detectCollision(float x, float y);

private:
    int circle_id;
    int circle_number;
    int circle_y;
    int circle_x;
    float circle_r;

    bool startTimeIs = false;
    std::chrono::time_point<std::chrono::system_clock> startTime;

    void checkStartTime();
    bool checkEndTime();
};

#endif /* defined(__WhackAMoleGame__MoleCircle__) */
