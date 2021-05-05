//
// Created by joshu on 4/28/2021.
//
#include "ships.h"
namespace galagasimulation {
Ships::Ships(glm::vec2 settopleftcorner, glm::vec2 setbottomrightcorner, glm::vec2 setmovment) {
  top_left_corner_ = settopleftcorner;
  bottom_right_corner_ = setbottomrightcorner;
  movment_ = setmovment;
}
Ships::Ships(glm::vec2 settopleftcorner,glm::vec2 setbottomrightcorner, float movment) {
  top_left_corner_ = settopleftcorner;
  bottom_right_corner_ = setbottomrightcorner;
  missile_movement_ = movment;
}
void Ships:: CollisionWithWalls() {
  if(bottom_right_corner_.x > 600 || top_left_corner_.x < 100) {
    SetMovement(glm::vec2(-1 * movment_.x, movment_.y));
  }
  if(top_left_corner_.y < 100 || bottom_right_corner_.y > 800) {
    SetMovement(glm::vec2(movment_.x, -1 * movment_.y));
  }
}

void Ships::UpdatePosition() {
  CollisionWithWalls();
  top_left_corner_.y+= movment_.y;
  top_left_corner_.x += movment_.x;
  bottom_right_corner_.x += movment_.x;
  bottom_right_corner_.y+= movment_.y;
}
void Ships::UpdateMissilePosition() {
  top_left_corner_.y += missile_movement_;
  bottom_right_corner_.y += missile_movement_;
}
glm::vec2 Ships::GetTopLeftCorner() {
  return top_left_corner_;
}
float Ships::CalculateWidth() {
float width = bottom_right_corner_.x - top_left_corner_.x;
  return width;
}
float Ships::CalculateHeight() {
  float height = top_left_corner_.y - bottom_right_corner_.y;
  return height;
}
void Ships::SetMovement(glm::vec2 setmovment) {
  movment_ = setmovment;
}
glm::vec2 Ships::GetBottomRightCorner() {
  return bottom_right_corner_;
}
glm::vec2 Ships::GetMovement() {
  return movment_;
}
}