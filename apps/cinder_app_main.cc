#include "galaga_simulation_app.h"

using idealgas::GalagaApp;

void prepareSettings(GalagaApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(GalagaApp, ci::app::RendererGl, prepareSettings);
