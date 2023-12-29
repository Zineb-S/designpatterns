#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <cstdlib>

class RandomNumberGenerator {
private:
    static RandomNumberGenerator* instance;

    RandomNumberGenerator() {}

public:
    RandomNumberGenerator(const RandomNumberGenerator&) = delete;
    RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;

    static RandomNumberGenerator* getInstance();

    int getRandomNumber();
};

#endif // RANDOMNUMBERGENERATOR_H
