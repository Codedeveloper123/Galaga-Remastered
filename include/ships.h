//
// Created by joshu on 4/28/2021.
//
#include "cinder/gl/gl.h"
#ifndef IDEAL_GAS_SHIPS_H
#define IDEAL_GAS_SHIPS_H
namespace galagasimulation {
class Ships {
  public:
  Ships(glm::vec2 topleftcorner, glm::vec2 bottomrightcorner, glm::vec2 movment);
  Ships(glm::vec2 settopleftcorner,glm::vec2 setbottomrightcorner, float movment);
  glm::vec2 GetMovment();
  void UpdatePosition();
  void UpdateMisslePosition();
  glm::vec2 Gettopleftcorner();
  glm::vec2 Getbootomrightcorner();
  void setMovment(glm::vec2 setmovment);
  float CalculateWidth();
  float CalculateHeight();
 void CollisionWithWalls();
 private:
  glm::vec2 topleftcorner;
  glm::vec2 bottomrightcorner;
  glm::vec2 movment;
  float width;
  float height;
  float misslemovment;
};
}
#endif  // IDEAL_GAS_SHIPS_H
