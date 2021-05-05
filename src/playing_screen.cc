#include "playing_screen.h"

namespace galagasimulation {

using glm::vec2;

PlayingScreen::PlayingScreen() {

}
void PlayingScreen::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(100, 100), vec2(600, 800)));
}

void PlayingScreen::AdvanceOneFrame() {
  ++dummy_variable_;
}

}  // namespace galagasimulation
