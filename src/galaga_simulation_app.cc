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
  ci::gl::translate(x_start + x_movement,y_start + y_movment);
  ci::gl::draw(mTex);
  ci::gl::popModelMatrix();
  if(missels) {
    DrawMissles();
  }
  container_.Display();
}
void GalagaApp::keyDown(KeyEvent event) {
  switch(event.getCode()) {
    case KeyEvent::KEY_UP: {
     if(y_start + y_movment > 100) {
        y_movment -= 10;
      }
      break;
    }
    case KeyEvent::KEY_DOWN: {
      if(y_start + y_movment < 700){
        y_movment += 10;
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      if(x_start + x_movement < 550) {
        x_movement += 10;
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      if(x_movement + x_start > 100) {
        x_movement -= 10;
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
        missels = true;
        break;
    }
  }
}
void GalagaApp::DrawMissles() {
  ci::gl::color(ci::Color("green"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(misslexposition, missleyposition), vec2(misslexposition +10, missleyposition+10)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(misslexposition + 45, missleyposition), vec2(misslexposition + 55 , missleyposition + 10)));
}
void GalagaApp::update() {
  container_.AdvanceOneFrame();
  if(missels) {
    missleyposition -= 10;
  }

}

}  // namespace idealgas
