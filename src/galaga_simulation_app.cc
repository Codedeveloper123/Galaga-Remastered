#include "galaga_simulation_app.h"

namespace idealgas {
using cinder::app::KeyEvent;
GalagaApp::GalagaApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}
void GalagaApp::setup() {
  auto img = loadImage( loadAsset( "AmanShip.png" ) );
  mTex = ci::gl::Texture2d::create( img );}
void GalagaApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::pushModelMatrix();
  ci::gl::translate(300,700);
  ci::gl::draw(mTex);
  ci::gl::popModelMatrix();
  container_.Display();
}
void GalagaApp::keyDown(KeyEvent event) {
  switch(event.getCode()) {
    case KeyEvent::KEY_UP: {

    }
    case KeyEvent::KEY_DOWN: {

    }
    case KeyEvent::KEY_RIGHT:{
    }
    case KeyEvent::KEY_LEFT: {

    }
  }


}
void GalagaApp::update() {
  container_.AdvanceOneFrame();

}

}  // namespace idealgas
