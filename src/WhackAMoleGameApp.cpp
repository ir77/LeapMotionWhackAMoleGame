#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WhackAMoleGameApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void WhackAMoleGameApp::setup()
{
}

void WhackAMoleGameApp::mouseDown( MouseEvent event )
{
}

void WhackAMoleGameApp::update()
{
}

void WhackAMoleGameApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( WhackAMoleGameApp, RendererGl )
