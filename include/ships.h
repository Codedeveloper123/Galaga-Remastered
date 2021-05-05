//
// Created by joshu on 4/28/2021.
//
#include "cinder/gl/gl.h"
#ifndef IDEAL_GAS_SHIPS_H
#define IDEAL_GAS_SHIPS_H
namespace galagasimulation {
class Ships {
  public:
  /**
   * This constructor is for the enemies ships_.
   * @param topleftcorner
   * @param bottomrightcorner
   * @param movment
   */
   Ships(glm::vec2 topleftcorner, glm::vec2 bottomrightcorner, glm::vec2 movment);

   /**
    * This contrucotr is for the missiles shot from the players ship.
    * @param settopleftcorner
    * @param setbottomrightcorner
    * @param movment
    */
  Ships(glm::vec2 settopleftcorner,glm::vec2 setbottomrightcorner, float movment);

  /**
   * This gets the velocity vector for the enemy ships_.
   * @return
   */
  glm::vec2 GetMovement();

  /**
   * This moves the enemy ships_ each frame.
   */
  void UpdatePosition();

  /**
   * This moves the missiles shot by the players ship each frame.
   */
  void UpdateMissilePosition();

  /**
   * This gets the top left corner of either the ship or missiles object.
   * @return
   */
  glm::vec2 GetTopLeftCorner();

  /**
   * This gets the bottom right corner of either the ship or missiles objects.
   * @return
   */
  glm::vec2 GetBottomRightCorner();

  /**
   * This sets the y velocity of the missiles fired from the players ship.
   * @param setmovment
   */
  void SetMovement(glm::vec2 setmovment);

  /**
   * This calculates the width_ of the enemy ships_.
   * @return
   */
  float CalculateWidth();

  /**
   * This calculates the height_ of the enemy ships_.
   */
  float CalculateHeight();

  /**
   * This checks whether enemy ships_ collide with the walls of the screen.
   */
 void CollisionWithWalls();
 private:
  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
  glm::vec2 movment_;
  float width_;
  float height_;
  float missile_movement_;
};
}
#endif  // IDEAL_GAS_SHIPS_H
