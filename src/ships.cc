//
// Created by joshu on 4/28/2021.
//
#include "ships.h"
namespace galagasimulation {
Ships::Ships(glm::vec2 settopleftcorner, glm::vec2 setbottomrightcorner, glm::vec2 setmovment) {
  topleftcorner = settopleftcorner;
  bottomrightcorner = setbottomrightcorner;
  movment = setmovment;
}
Ships::Ships(glm::vec2 settopleftcorner,glm::vec2 setbottomrightcorner, float movment) {
  topleftcorner = settopleftcorner;
  bottomrightcorner = setbottomrightcorner;
  misslemovment = movment;
}
void Ships:: CollisionWithWalls() {
  if(bottomrightcorner.x > 600 || topleftcorner.x < 100) {
    setMovment(glm::vec2(-1*movment.x,movment.y));
  }
  if(topleftcorner.y < 100 || bottomrightcorner.y > 800) {
    setMovment(glm::vec2(movment.x, -1* movment.y));
  }
}

void Ships::UpdatePosition() {
  CollisionWithWalls();
  topleftcorner.y+= movment.y;
  topleftcorner.x += movment.x;
  bottomrightcorner.x += movment.x;
  bottomrightcorner.y+= movment.y;
}
void Ships::UpdateMisslePosition() {
  topleftcorner.y += misslemovment;
  bottomrightcorner.y += misslemovment;
}
glm::vec2 Ships::Gettopleftcorner() {
  return topleftcorner;
}
float Ships::CalculateWidth() {
float width = bottomrightcorner.x - topleftcorner.x;
  return width;
}
float Ships::CalculateHeight() {
  float height = topleftcorner.y - bottomrightcorner.y;
  return height;
}
void Ships::setMovment(glm::vec2 setmovment) {
  movment= setmovment;
}
glm::vec2 Ships::Getbootomrightcorner() {
  return bottomrightcorner;
}
glm::vec2 Ships::GetMovment() {
  return movment;
}
}