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
  ci::gl::drawStringCentered(std::to_string(score_),glm::vec2(700,500),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered(std::to_string(lives_),glm::vec2(700,700),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("SCORE",glm::vec2(700,400),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("Lives",glm::vec2(700,600),"White",cinder::Font("",30.0f));
  ci::gl::drawStringCentered("PRESS 0 TO START",glm::vec2(710,300),"White",cinder::Font(" ",30.0f));
 // This loop is for making sure the game ends after losing all lives.
  if(lives_ > 0) {
    ci::gl::pushModelMatrix();
    ci::gl::translate(
        x_start_position_for_player_ship_ + x_movement_for_player_ship_,
        y_start_position_for_player_ship_ + y_movement_for_player_ship_);
    ci::gl::draw(ship);
    ci::gl::popModelMatrix();
    ci::gl::drawString("GALAGA", vec2(230, 50), "Red", ci::Font("", 70.0f));
    // This if statement is to make sure the game starts after the start button is pressed.
    if(start_) {
      if (ships_have_been_drawn_) {
        if (timer_ == 5) {
          PopulateShipsVector();
          DrawEnemyShips();
        }
        timer_++;
        DrawEnemyShips();
      }
      if (missiles_have_been_drawn_) {
        if (timer_for_missile_collisions_ == 0) {
          PopulateMissilesVector();
          DrawMissiles();
        }
        DrawMissiles();
        timer_for_missile_collisions_++;
        if (missiles_.at(1).GetTopLeftCorner().y < 100) {
          missiles_have_been_drawn_ = false;
          missiles_.clear();
          timer_for_missile_collisions_ = 0;
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
     if(y_start_position_for_player_ship_ + y_movement_for_player_ship_ > 100) {
       y_movement_for_player_ship_ -= 30;
      }
      break;
    }
    case KeyEvent::KEY_DOWN: {
      if(y_start_position_for_player_ship_ + y_movement_for_player_ship_ < 700){
        y_movement_for_player_ship_ += 30;
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      if(x_start_position_for_player_ship_ + x_movement_for_player_ship_ < 550) {
        x_movement_for_player_ship_ += 30;
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      if(x_movement_for_player_ship_ + x_start_position_for_player_ship_ > 100) {
        x_movement_for_player_ship_ -= 30;
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      missiles_have_been_drawn_ = true;
        break;
    }
    case KeyEvent::KEY_0: {
      start_ = true;
    }
  }
}
void GalagaApp::PopulateMissilesVector() {
  missile_x_position_ =
      x_start_position_for_player_ship_ + x_movement_for_player_ship_;
  missile_y_position_ =
     y_start_position_for_player_ship_ + y_movement_for_player_ship_;
 float mo = -10;
 missiles_.emplace_back(vec2(missile_x_position_, missile_y_position_),vec2(missile_x_position_ + 10, missile_y_position_ + 10),mo);
 missiles_.emplace_back(vec2(missile_x_position_ + 45, missile_y_position_),vec2(missile_x_position_ + 55, missile_y_position_ + 10),mo);
}

void GalagaApp::DrawMissiles() {
  ci::gl::color(ci::Color("green"));
  for(auto & l : missiles_) {
   ci::gl::drawSolidRect(ci::Rectf(l.GetTopLeftCorner(), l.GetBottomRightCorner()));
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
    ships_.emplace_back(vec2(x_positionleft,y_poistionleft), vec2(x_positionright,y_positionright), y_move);
  }
}
void GalagaApp:: DrawEnemyShips() {
  ci::gl::color(ci::Color("blue"));
  for(auto & ship : ships_) {
    ci::gl::drawSolidRect(ci::Rectf(ship.GetTopLeftCorner(), ship.GetBottomRightCorner()));
  }
}
void GalagaApp::MissileCollisions() {
  for (int i = ships_.size() - 1; i >= 0; i--) {
    if (missiles_.size() > 0) {
      for (size_t j = 0; j < missiles_.size(); j++) {
        if (DoOverlap(ships_.at(i), missiles_.at(j)) == true) {
          if (ships_.size() == 1) {
            score_ += 100;
            ships_.clear();
          } else {
            ships_.erase(ships_.begin() + i);
            score_ += 100;
            if (i != 0) {
              i--;
            }
          }
        }
      }
    }
  }
}
void GalagaApp::LifeLost() {
  for(size_t i = 0; i < ships_.size(); i++) {
    if(ShipsCollision(ships_.at(i))) {
        if (ships_.size() == 1) {
          lives_--;
          ships_.clear();
        } else {
          ships_.erase(ships_.begin() + i);
          lives_--;
          if (i != 0) {
            i--;
          }
        }
    }
  }
}
bool GalagaApp:: ShipsCollision(Ships ship1) {
float topleftx =
      x_start_position_for_player_ship_ + x_movement_for_player_ship_;
float toplefty = y_movement_for_player_ship_ + y_start_position_for_player_ship_;
float bottomrightx =
    x_start_position_for_player_ship_ + x_movement_for_player_ship_ + 53;
float bottomrighty = y_movement_for_player_ship_ + y_start_position_for_player_ship_ + 61;
if (ship1.GetBottomRightCorner().x < topleftx) {
  return false;
}
if(ship1.GetBottomRightCorner().y < toplefty) {
  return false;
}
if(ship1.GetTopLeftCorner().x > bottomrighty) {
  return false;
}
if(ship1.GetTopLeftCorner().x > bottomrightx) {
  return false;
}
return true;
}

 bool GalagaApp::DoOverlap(Ships ship1, Ships missle) {
   float h1 = ship1.CalculateHeight();
   float w1 = ship1.CalculateWidth();
   float h2 = missle.CalculateHeight();
   float w2 = ship1.CalculateWidth();
  if(ship1.GetBottomRightCorner().x < missle.GetBottomRightCorner().x - w2) {
    return false;
  }
  if(ship1.GetBottomRightCorner().y < missle.GetTopLeftCorner().y) {
    return false;
  }
  if(ship1.GetTopLeftCorner().y > missle.GetBottomRightCorner().y) {
    return false;
  }
  if(ship1.GetTopLeftCorner().x > missle.GetBottomRightCorner().x) {
    return false;
  }
  return true;
}
void GalagaApp::update() {
  container_.AdvanceOneFrame();
  if(missiles_have_been_drawn_ && ships_have_been_drawn_) {
    if(timer_for_missile_collisions_ >= 1) {
      MissileCollisions();
    }
  }
  if(missiles_have_been_drawn_) {
    for(size_t i = 0; i < missiles_.size(); i++) {
      missiles_.at(i).UpdateMissilePosition();
    }
  }
  if(ships_have_been_drawn_) {
    for (size_t i = 0; i < ships_.size(); i++) {
      ships_.at(i).UpdatePosition();
    }
    LifeLost();
  }
  timer_for_enemy_ships_ += 1;
    if(timer_for_enemy_ships_ % 400 == 0) {
      ships_have_been_drawn_ = false;
      ships_.clear();
      timer_ = 0;
    }
    if(timer_for_enemy_ships_ % 405 == 0) {
      ships_have_been_drawn_ = true;
    }

}

}  // namespace galagasimulation
