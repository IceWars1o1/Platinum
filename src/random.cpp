#include "../include/random.hpp"

namespace pt{
    int random() {
        return random(0, 100);
    }
    int random(int min_val, int max_val) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min_val, max_val);
        return dis(gen);
    }
}