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
  void GalagaApp::setup();
  void GalagaApp::keyDown(cinder::app::KeyEvent event);
  void draw() override;
  void update() override;
  ci::gl::Texture2dRef		mTex;
  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
  PlayingScreen container_;
};

}  // namespace idealgas
