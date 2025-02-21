#pragma once

#include <SFML/Graphics.hpp>

// windows settings
constexpr const char *WINDOW_TITLE = "Millennium";
constexpr const int WINDOW_WIDTH = 1000;
constexpr const int WINDOW_HEIGHT = 1000;
constexpr const int WINDOW_STYLE = sf::Style::Default;

// particle settings
constexpr const float PARTICLE_RADIUS = 1.f;
constexpr const float PARTICLE_MASS = 1.f;

constexpr const unsigned int PARTICLE_COUNT = 10000u;

// simulation settings
constexpr const float UNIVERSE_SIZE = 1000.f;

// camera settings
constexpr const float CAMERA_INITIAL_ZOOM = 1.f;
constexpr const float CAMERA_INITIAL_OFFSET_X = 500.f;
constexpr const float CAMERA_INITIAL_OFFSET_Y = 500.f;
constexpr const float CAMERA_SPEED = 10.f;

// barnes-hut settings
constexpr const float THETA = 50.f;
constexpr const float G = 6.67430e-11f;
constexpr const float EPSILON = 1.f;
constexpr const size_t MAX_CAPACITY = 8u;