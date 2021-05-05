#pragma once

#include <cinder/app/KeyEvent.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "playing_screen.h"
#include "ships.h"

namespace galagasimulation {

/**
 * An app for playing the classic arcade game Galaga.
 */
class GalagaApp : public ci::app::App {
 public:
  GalagaApp();
  /**
   * This function runs once when the app boots up.
   */
  void GalagaApp::setup();
  /**
   * This function handles keyinputs from the user.
   * @param event
   */
  void GalagaApp::keyDown(cinder::app::KeyEvent event);
  void draw() override;
  void update() override;
  //Represents the galaga ship.
  ci::gl::Texture2dRef		ship;
  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
  bool missiles_have_been_drawn_ = false;
  bool ships_have_been_drawn_ = true;
  int timer_for_enemy_ships_ = 1;
  int score_ = 0;
  /**
   * This  draws the missles shot by the ship.
   */
  void DrawMissiles();
  /**
   * This handles the collisions of the ships_ missiles hitting the enemy ships_.
   */
  void MissileCollisions();
  /**
   * This draws the enemy ships_ for the game.
   */
  void DrawEnemyShips();
  PlayingScreen container_;
  std::vector<Ships> ships_;
  std::vector<Ships> missiles_;
  float timer_for_missile_collisions_ = 0;
  /**
   * This  creates all the enemy ships and adds them to the vector.
   */
  void PopulateShipsVector();
  /**
   * This  checks if the enemy ships and missiles are overlapping.
   * @param ship1
   * @param missle
   * @return
   */

  bool DoOverlap(Ships ship1, Ships missle);
  /**
   * This checks if the enemy ships have hit the players ship.
   * @param ship1
   * @return
   */

  bool ShipsCollision(Ships ship1);
  /**
   * This populates the vector that stores the players missiles fired.
   */

  void PopulateMissilesVector();
  /**
   * This function checks to see if a player should lose a life.
   */
   void LifeLost();
  float x_movement_for_player_ship_ = 0;
  int lives_ = 3;
 float y_movement_for_player_ship_ = 0;
 const float x_start_position_for_player_ship_ = 300;
 float y_start_position_for_player_ship_ = 700;
 float missile_x_position_;
 float missile_y_position_;
 bool start_ = false;
 int timer_ = 0;
};

}  // namespace galagasimulation
