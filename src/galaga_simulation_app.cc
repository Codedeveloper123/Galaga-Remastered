#include "galaga_simulation_app.h"

namespace idealgas {
using cinder::app::KeyEvent;
GalagaApp::GalagaApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}
void GalagaApp::setup() {
  auto img = loadImage( loadAsset( "AmanShip.png" ) );
  ship = ci::gl::Texture2d::create( img );
}
void GalagaApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::pushModelMatrix();
  ci::gl::translate(x_start + x_movement,y_start + y_movment);
  ci::gl::draw(ship);
  ci::gl::popModelMatrix();
  ci::gl::drawString("GALAGA",vec2(230,50),"Red",
                     ci::Font("",70.0f));
  if(missels2) {
    DrawEnemyShips();
  }
  if(missels) {
    DrawMissles();
    if(missleyposition + movment < 100) {
      missels = false;
      movment = 0;
    }
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
  misslexposition = x_start + x_movement;
  missleyposition = y_start + y_movment;
  ci::gl::drawSolidRect(ci::Rectf(vec2(misslexposition, missleyposition + movment), vec2(misslexposition +10, missleyposition+10 + movment)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(misslexposition + 45, missleyposition + movment), vec2(misslexposition + 55 , missleyposition + 10 + movment)));
}
void GalagaApp:: DrawEnemyShips() {
  ci::gl::color(ci::Color("blue"));
  int x = 0;
  for(int i = 0; i < 11; i++) {
    ci::gl::drawSolidRect(ci::Rectf(vec2(140 + x,120 + movment2),vec2(160 + x,140 + movment2)));
    x += 40;
  }
}
void GalagaApp:: MissleCollisions() {

}
void GalagaApp::update() {
  container_.AdvanceOneFrame();
  if(missels) {
    movment -= 10;
  }
  movment2 += 1;
   i+= 1;
    if(i % 650 == 0) {
      missels2 = false;
      movment2 = 0;
    }
    if(i % 655 == 0) {
      missels2 = true;
    }

}

}  // namespace idealgas
