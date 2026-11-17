#include "snake.hpp"

#include <ncurses.h>

#include <cstdio>
#include <optional>

#include "graphics.hpp"

void Snake::draw() const {
    for (auto point : points_) {
        gfx::put_char(point.x, point.y, 'o');
    }

    gfx::put_char(points_.front().x, points_.front().y, '0');
}

void Snake::handle_input(int key) {
    if (key == ' ') {
        increase_length();
    }

    auto dir = key_to_dir(key);
    if (!dir) return;
    if (*dir == -direction_) return;
    pending_ = *dir;
}

std::optional<glm::ivec2> Snake::key_to_dir(int key) {
    switch (key) {
        case 'w':
        case KEY_UP:
            return glm::ivec2(0, -1);

        case 's':
        case KEY_DOWN:
            return glm::ivec2(0, 1);

        case 'a':
        case KEY_LEFT:
            return glm::ivec2(-1, 0);

        case 'd':
        case KEY_RIGHT:
            return glm::ivec2(1, 0);

        default:
            return std::nullopt;  // not a movement key
    }
}

void Snake::update(double dt) {
    timer_ += dt;
    while (timer_ >= step_) {
        timer_ -= step_;
        direction_ = pending_;  // commit the turn here
        head_ += direction_;    // integer grid movement

        points_.push_front(head_);
        points_.pop_back();
    }
}

std::size_t Snake::snake_length() const {
    return points_.size();
}

Snake::Snake() {
    points_.push_back(head_);
}

void Snake::increase_length() {
    direction_ = pending_;
    head_ += direction_;  // integer grid movement

    points_.push_front(head_);
}

void Snake::on_collide(){

    increase_length();

}
