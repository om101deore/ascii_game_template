#pragma once

#include <ncurses.h>

#include <deque>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/vec2.hpp>
#include <optional>

#include "object.hpp"

class Snake : public GameObject {
public:

    Snake();

    void draw() const override;
    void handle_input(int key) override;
    void update(double dt) override;
    void on_collide() override;
    static std::optional<glm::ivec2> key_to_dir(int key);

private:
    double timer_ = 0.0;
    double step_ = 0.15;  // seconds per cell

    glm::ivec2 direction_{1.0f, 0.0f};
    glm::ivec2 pending_{1, 0};

    glm::vec2 head_{COLS / 2, LINES / 2};

    std::deque<glm::ivec2> points_{};

private:
    std::size_t snake_length() const;
    void increase_length();
};
