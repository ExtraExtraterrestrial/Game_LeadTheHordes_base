#pragma once
namespace LTH {


class GameEngine
{
public:
	GameEngine();
	~GameEngine() {}

private: // initializers
	inline void initWindow();
	inline void initKeys();
	inline void initStates();

public: // methods
	void run();

private: //  methods
	void update();
	void update_SFMLEvents();

	void render();

	void exitGame();

private: // members
	sf::RenderWindow window;

private: // structs


	struct Settings {
		// config files path
		std::string win_configFile;
		std::string keyBinds_configFile;
		
		// window settings
		std::unordered_map<std::string, std::string> win_ini;
		std::unordered_map<std::string, int16_t> keyBinds_map;

		float fps;
		std::string win_title;

		sf::VideoMode win_videoMode;
		sf::ContextSettings win_contextSettings;
		sf::Uint32 win_style;


		Settings(std::string_view winpath, std::string_view keypath, float fps, std::string_view title) 
			: win_contextSettings(sf::ContextSettings()),
			  win_configFile(winpath), keyBinds_configFile(keypath),
			  fps(fps), win_title(title)
		{
		}

		void changeVideomode(int width, int height) {
			for (sf::VideoMode preset : sf::VideoMode::getFullscreenModes()) {
				if (preset.height == height && preset.width == width) {
					win_videoMode = preset;
					return;
				}
			}

			LOG_ERR("Video mode not found!", (std::string)"Videomode dimensions: " + std::to_string(width) + ", " + std::to_string(height) + ".");

			win_videoMode = sf::VideoMode::getDesktopMode();
		}
	} settings { "configs/window_settings.ini", "configs/keys.ini", 60, "Lead The Hordes!" };
};


}