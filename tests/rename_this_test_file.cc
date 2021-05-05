#include <galaga_simulation_app.h>
#include <playing_screen.h>

#include <catch2/catch.hpp>

using galagasimulation::PlayingScreen;

TEST_CASE("Ships Colliding with walls") {
  SECTION("Ships Colliding with right wall") {
    galagasimulation::Ships ships =
        galagasimulation::Ships(vec2(581, 280), vec2(601, 300), vec2(6, 0));
    ships.UpdatePosition();
    REQUIRE(ships.GetMovment().x == -6);
  }
  SECTION("Ships Colliding with left wall") {
    galagasimulation::Ships ships =
        galagasimulation::Ships(vec2(99, 280), vec2(119, 300), vec2(6, 0));
    ships.UpdatePosition();
    REQUIRE(ships.GetMovment().x == -6);
  }
  SECTION("Ships Colliding with top wall") {
    galagasimulation::Ships ships =
        galagasimulation::Ships(vec2(400, 99), vec2(420, 119), vec2(0, 2));
    ships.UpdatePosition();
    REQUIRE(ships.GetMovment().y == -2);
  }
  SECTION("Ships colliding with bottom wall") {
    galagasimulation::Ships ships =
        galagasimulation::Ships(vec2(400, 780), vec2(420, 801), vec2(0, 2));
    ships.UpdatePosition();
    REQUIRE(ships.GetMovment().y == -2);
  }
}
TEST_CASE("Missles Colliding with the Ships") {
  galagasimulation::GalagaApp galagaApp;
  galagaApp.MissleCollisions
}
/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
