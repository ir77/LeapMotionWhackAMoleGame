#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Leap.h"
#include "LeapMath.h"
#include "MoleCircle.h"

#include <iostream>
#include <stdio.h>
#include <new>
#include <math.h>
#include <time.h>

#define CIRCLE_NUMBER 16 // 3*3, 4*4, 5*5, …
// TODO : Click Mode, Grasp Mode
#define GAME_MODE = 1 // Game Mode -> Time, Click, Grasp

using namespace ci;
using namespace ci::app;
using namespace std;

// ---------------------------------------
//
// ---------------------------------------
class WhackAMoleGameApp : public AppNative {
public:
    void setup();
    void update();
    void draw();

private:
    Leap::Controller leap;
    MoleCircle moleCircle[CIRCLE_NUMBER];

    int windowWidth = 150 * sqrt(CIRCLE_NUMBER) + 75;
    int windowHeight = 150 * sqrt(CIRCLE_NUMBER) + 75;

    void drawCircle(float x, float y);
    void drawPointCircle(float x, float y, Leap::Pointable pointable);
};

// ---------------------------------------
//
// ---------------------------------------
void WhackAMoleGameApp::setup()
{
    this->setWindowSize(windowWidth, windowHeight);
    this->setFrameRate(120);
    gl::enableAlphaBlending();

    for (int i = 0; i < sqrt(CIRCLE_NUMBER); i++) {
        for (int j = 0; j < sqrt(CIRCLE_NUMBER); j++) {
            new (moleCircle + (i * (int)sqrt(CIRCLE_NUMBER)) + j) MoleCircle((i * (int)sqrt(CIRCLE_NUMBER)) + j, CIRCLE_NUMBER, 100 + i * 160, 100 + j * 160, 75);
        }
    }
    
    srand((unsigned int)time(NULL));
    moleCircle[0].targetCircleNumber = rand() % CIRCLE_NUMBER;
}

void WhackAMoleGameApp::update()
{
}

// ポーリング形式でフレームを取得
// Leap Motionのフレーム処理には、コールバック形式とポーリング形式の2つがある
/*
 （1）コールバック方式
 　　・C++でフレームワークは使わない。自分でメイン・ループを実装してもいいが、コードが増えてきたときにクラス化されていた方が何かと実装しやすい
 　　・C#でWPFを使って実装する。メイン・ループを自前で実装するのが難しいのでコールバック方式で実装する。
 
 （2）ポーリング方式
 　　・C++でOpenGLを使って実装する。OpenGLのDrawのタイミングでデータを取得し、処理する
 　　・C#でWPFを使って実装する。C#の「Touch
 Emulationサンプル（英語）」にもあるように、レンダリング（＝CompositionTargetクラス（System.Windows.Media名前空間）のRenderingイベント）のタイミングで処理する
 */
void WhackAMoleGameApp::draw()
{
    // clear out the window with black
    gl::clear(Color(.97, .93, .79));

    // フレームデータの取得

    // Leap::PointableListオブジェクトは、名前のとおりLeap::Pointableオブジェクトのリストである
    // 指やツール（＝棒状のもの）をひとまとめにして表す
    // Leap::PointableList pointables = leap.frame().pointables();

    // 人差し指のリスト
    Leap::FingerList indexFingerList = leap.frame().fingers().fingerType(Leap::Finger::Type::TYPE_INDEX);
    Leap::InteractionBox iBox = leap.frame().interactionBox();

    if (!indexFingerList.isEmpty()) {
        Leap::Vector normalizedPosition = iBox.normalizePoint(indexFingerList[0].stabilizedTipPosition());

        float x = normalizedPosition.x * windowWidth;
        float y = windowHeight - normalizedPosition.y * windowHeight;

        drawCircle(x, y);
        drawPointCircle(x, y, indexFingerList[0]);
    } else {
        drawCircle(0, 0);
    }
}

void WhackAMoleGameApp::drawCircle(float x, float y)
{
    gl::color(0, 0, 0, 1);
    for (int i = 0; i < CIRCLE_NUMBER; i++) {
        if (moleCircle[i].detectCollision(x, y)) {
            gl::color(0.7, 0.7, 0.7, 1);
        } else if (i == moleCircle[i].targetCircleNumber) {
            gl::color(0.7, 0.0, 0.0, 1);
        } else {
            gl::color(0, 0, 0, 1);
        }
        gl::drawSolidCircle(moleCircle[i].getVec2f(), moleCircle[i].getCircle_r());
    }
}

void WhackAMoleGameApp::drawPointCircle(float x, float y, Leap::Pointable pointable)
{
    // ホバー状態
    if (pointable.touchDistance() > 0 && pointable.touchZone() != Leap::Pointable::Zone::ZONE_NONE) {
        gl::color(0, 1, 0, 1 - pointable.touchDistance());
    }
    // タッチ状態
    else if (pointable.touchDistance() <= 0) {
        gl::color(1, 0, 0, -pointable.touchDistance());
    }
    // タッチ対象外
    else {
        gl::color(0, 0, 1, .05);
    }

    gl::drawSolidCircle(Vec2f(x, y), 30);
}

CINDER_APP_NATIVE(WhackAMoleGameApp, RendererGl)
