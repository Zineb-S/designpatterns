#include "RandomNumberGenerator.h"

RandomNumberGenerator* RandomNumberGenerator::instance = nullptr;

RandomNumberGenerator* RandomNumberGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new RandomNumberGenerator();
    }
    return instance;
}

int RandomNumberGenerator::getRandomNumber() {
    return rand();
}
