#include "galaga_simulation_app.h"

namespace galagasimulation  {
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
  ci::gl::drawStringCentered(std::to_string(score),glm::vec2(700,500),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered(std::to_string(lives),glm::vec2(700,700),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("SCORE",glm::vec2(700,400),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("Lives",glm::vec2(700,600),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("PRESS 0 TO START",glm::vec2(710,300),"White",cinder::Font(" ",30.0f));
 if(lives > 0) {
    ci::gl::pushModelMatrix();
    ci::gl::translate(x_start + x_movement, y_start + y_movment);
    ci::gl::draw(ship);
    ci::gl::popModelMatrix();
    ci::gl::drawString("GALAGA", vec2(230, 50), "Red", ci::Font("", 70.0f));
    if(start) {
      if (missels2) {
        if (timer == 5) {
          PopulateShipsVector();
          DrawEnemyShips();
        }
        timer++;
        DrawEnemyShips();
      }
      if (missels) {
        if (timer2 == 0) {
          PopulateMisselsVector();
          DrawMissles();
        }
        DrawMissles();
        timer2++;
        if (missel.at(1).Gettopleftcorner().y < 100) {
          missels = false;
          missel.clear();
          timer2 = 0;
        }
      }
    }
    container_.Display();
  } else {
   ci::gl::drawStringCentered("GAMEOVER",glm::vec2(400,400),"White",cinder::Font("",55.0f));
  }
}
void GalagaApp::keyDown(KeyEvent event) {
  switch(event.getCode()) {
    case KeyEvent::KEY_UP: {
     if(y_start + y_movment > 100) {
        y_movment -= 30;
      }
      break;
    }
    case KeyEvent::KEY_DOWN: {
      if(y_start + y_movment < 700){
        y_movment += 30;
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      if(x_start + x_movement < 550) {
        x_movement += 30;
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      if(x_movement + x_start > 100) {
        x_movement -= 30;
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
        missels = true;
        break;
    }
    case KeyEvent::KEY_0: {
      start = true;
    }
  }
}
void GalagaApp::PopulateMisselsVector() {
 misslexposition = x_start + x_movement;
 missleyposition = y_start + y_movment;
 float mo = -10;
 missel.emplace_back(vec2(misslexposition,missleyposition),vec2(misslexposition + 10,missleyposition + 10),mo);
 missel.emplace_back(vec2(misslexposition + 45,missleyposition),vec2(misslexposition + 55,missleyposition + 10),mo);
}

void GalagaApp::DrawMissles() {
  ci::gl::color(ci::Color("green"));
  for(auto & l : missel) {
   ci::gl::drawSolidRect(ci::Rectf(l.Gettopleftcorner(),l.Getbootomrightcorner()));
  }
}
void GalagaApp:: PopulateShipsVector() {
  int x = 0;
  srand((int) time(0));
  for(int i = 0; i < 10; i++) {
    int x_positionleft = 140 + x;
    int y_poistionleft = 120;
    int x_positionright = 160+x;
    int y_positionright = 140;
    int x_velocity = rand() % 4 + 1;
    int y_velocity = rand() % 4 + 1;
    glm::vec2 y_move = glm::vec2(x_velocity,y_velocity);
    x += 40;
    ships.emplace_back(vec2(x_positionleft,y_poistionleft), vec2(x_positionright,y_positionright), y_move);
  }
}
void GalagaApp:: DrawEnemyShips() {
  ci::gl::color(ci::Color("blue"));
  for(auto & ship : ships) {
    ci::gl::drawSolidRect(ci::Rectf(ship.Gettopleftcorner(),ship.Getbootomrightcorner()));
  }
}
void GalagaApp:: MissleCollisions() {
  for (int i = ships.size() - 1; i >= 0; i--) {
    if (missel.size() > 0) {
      for (size_t j = 0; j < missel.size(); j++) {
        if (doOverlap(ships.at(i), missel.at(j)) == true) {
          if (ships.size() == 1) {
            score += 100;
            ships.clear();
          } else {
            ships.erase(ships.begin() + i);
            score += 100;
            if (i != 0) {
              i--;
            }
          }
        }
      }
    }
  }
}
void GalagaApp:: lifelost() {
  for(size_t i = 0; i < ships.size(); i++) {
    if(ShipsCollision(ships.at(i))) {
        if (ships.size() == 1) {
          lives--;
          ships.clear();
        } else {
          ships.erase(ships.begin() + i);
          lives--;
          if (i != 0) {
            i--;
          }
        }
    }
  }
}
bool GalagaApp:: ShipsCollision(Ships ship1) {
float topleftx = x_start + x_movement;
float toplefty = y_movment + y_start;
float bottomrightx = x_start + x_movement + 53;
float bottomrighty = y_movment + y_start + 61;
if (ship1.Getbootomrightcorner().x < topleftx) {
  return false;
}
if(ship1.Getbootomrightcorner().y < toplefty) {
  return false;
}
if(ship1.Gettopleftcorner().x > bottomrighty) {
  return false;
}
if(ship1.Gettopleftcorner().x > bottomrightx) {
  return false;
}
return true;
}

 bool GalagaApp::doOverlap(Ships ship1, Ships missle) {
   float h1 = ship1.CalculateHeight();
   float w1 = ship1.CalculateWidth();
   float h2 = missle.CalculateHeight();
   float w2 = ship1.CalculateWidth();
  if(ship1.Getbootomrightcorner().x < missle.Getbootomrightcorner().x - w2) {
    return false;
  }
  if(ship1.Getbootomrightcorner().y < missle.Gettopleftcorner().y) {
    return false;
  }
  if(ship1.Gettopleftcorner().y > missle.Getbootomrightcorner().y) {
    return false;
  }
  if(ship1.Gettopleftcorner().x > missle.Getbootomrightcorner().x) {
    return false;
  }
  return true;
}
void GalagaApp::update() {
  container_.AdvanceOneFrame();
  if(missels && missels2) {
    if(timer2 >= 1) {
      MissleCollisions();
    }
  }
  if(missels) {
    for(size_t i = 0; i < missel.size(); i++) {
      missel.at(i).UpdateMisslePosition();
    }
  }
  if(missels2) {
    for (size_t i = 0; i < ships.size(); i++) {
      ships.at(i).UpdatePosition();
    }
    lifelost();
  }
   i+= 1;
    if(i % 400 == 0) {
      missels2 = false;
      ships.clear();
      timer = 0;
    }
    if(i % 405 == 0) {
      missels2 = true;
    }

}

}  // namespace galagasimulation
