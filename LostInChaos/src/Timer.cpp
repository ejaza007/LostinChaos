#include "../include/Timer.h"

Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    played = true;
}

void Timer::start() {
    played = true;
    paused = false;

    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop() {
    played = false;
    paused = true;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause() {
    if (played && !paused) {
        paused = true;

        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    if (played && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;
    if (played) {
        if (paused) {
            time = pausedTicks;
        }
        else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool Timer::isStarted() {
    return played;
}

bool Timer::isPaused() {
    return paused && played;
}