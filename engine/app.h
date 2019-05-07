#pragma once

// About 60 frame persecond
#define APP_TIME_60 0.0166667f

class IApp
{
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void render() = 0;
	virtual void release() = 0;
};


struct AppConfig
{
	std::string caption;
	uint32_t width;
	uint32_t height;
	IApp* app = nullptr;

	// Stuff you don't need to worry about...
	bool isRunning = true;
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

	// Timeing
	uint32_t pre = 0;
	uint32_t curr = 0;
	float delta = 0.0f;
	float fixedDelta = 0.0f;

	// SDL Event
	SDL_Event evt;
};


void app_init(AppConfig* config);

void app_update();

void app_release();

AppConfig* app_getConfig();

void app_quit();
