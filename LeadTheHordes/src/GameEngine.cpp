#include "Hordes_pch.h"

#include "GameEngine.h"

namespace LTH {

GameEngine::GameEngine()
	: window(sf::VideoMode(640, 320), "Made by EET") {
	dt_manager::init();

	initWindow();
	initKeys();
	initStates();
}


// initializers
#include <iostream>
inline void GameEngine::initWindow() {

	settings.win_ini = Utils::mapFromIni(settings.win_configFile);

	LOG_ASSERT(settings.win_ini["__error__"] != "", settings.win_ini["__error__"], "Please check the file at: " + settings.win_configFile);

	settings.win_contextSettings.antialiasingLevel = std::stoi(settings.win_ini["antialiasing"]);

	settings.changeVideomode(std::stoi(settings.win_ini["window_width"]), std::stoi(settings.win_ini["window_height"]));

	window.create(
		settings.win_videoMode,
		settings.win_title,
		sf::Style::Titlebar | sf::Style::Close | (Utils::str2bool(settings.win_ini["fullscreen"]) ? sf::Style::Fullscreen : 0),
		settings.win_contextSettings
	);

	window.setFramerateLimit(std::stoi(settings.win_ini["fps_limit"]));
	window.setVerticalSyncEnabled(Utils::str2bool(settings.win_ini["vsync"]));
}

inline void GameEngine::initKeys() {
	std::unordered_map<std::string, std::string> keysIni = Utils::mapFromIni(settings.keyBinds_configFile);

	LOG_ASSERT(keysIni["__error__"] != "", keysIni["__error__"], "Please check the file " + settings.keyBinds_configFile);
	keysIni.erase("__error__");

	for (auto pair : keysIni) {
		settings.keyBinds_map[pair.first] = std::stoi(pair.second);
	}
}

inline void GameEngine::initStates() {

	//state_menu.init();
	//state_game.init();
	//state_editor.init();

	//state_current = &state_menu;
	//state_current->activateState();
}


// public methods

void GameEngine::run() {

	float frame = 0;
	while (window.isOpen()) {
		update();

		frame += dt::s();
		if (frame > settings.defaultFrameDuration) {
			render();
			frame = 0;
		}
	}
}


// private methods

void GameEngine::update() {
	dt_manager::update();

	update_SFMLEvents();
}

void GameEngine::update_SFMLEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			exitGame();
		}
	}
}
void GameEngine::render() {
	sf::CircleShape shape(100.f);

	window.clear();

	window.draw(shape);
	window.display();
}


void GameEngine::exitGame() {
	window.close();
}

}
