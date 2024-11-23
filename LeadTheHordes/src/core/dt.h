#pragma once

namespace LTH {


// doesn't need mutex as it's gonna be managed by a single GameEngine


struct dt { 
	friend struct dt_manager;
private:

	static sf::Int64 microseconds;
	static sf::Int32 milliseconds;
	static float seconds;

	static sf::Clock dtClock;

	static void init() {
		dtClock = sf::Clock();
	}

	static void update() {
		microseconds = dtClock.getElapsedTime().asMicroseconds();
		milliseconds = dtClock.getElapsedTime().asMilliseconds();
		seconds = dtClock.restart().asSeconds();
	}

	dt() = delete;
	dt(const dt &) = delete;
	dt(const dt &&) = delete;
	dt& operator=(dt &) = delete;
	dt& operator=(dt &&) = delete;

public:

	static const sf::Int64 us() {
		return microseconds;
	}

	static const sf::Int32 ms() {
		return milliseconds;
	}

	static const float s() {
		return seconds;
	}

};

struct dt_manager {
	friend class GameEngine;

	static void init() {
		dt::init();
	}
	static void update() {
		dt::update();
	}
};

}