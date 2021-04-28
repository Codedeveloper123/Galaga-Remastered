#pragma once

#include <cinder/app/KeyEvent.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "playing_screen.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
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
  bool missels = false;
  bool missels2 = true;
  int i = 1;
  /**
   * This  draws the missles shot by the ship.
   */
  void DrawMissles();
  /**
   * This handles the collisions of the ships missiles hitting the enemy ships.
   */
  void MissleCollisions();
  /**
   * This draws the enemy ships for the game.
   */
  void DrawEnemyShips();
  PlayingScreen container_;
 float x_movement = 0;
 float y_movment = 0;
 float x_start = 300;
 float movment2 = 0;
 float y_start = 700;
 float misslexposition;
 float movment = 0;
 float missleyposition;
};

}  // namespace idealgas
