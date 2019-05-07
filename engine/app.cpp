#include "sys.h"

static AppConfig* g_config = nullptr;

void app_init(AppConfig* config)
{
	g_config = config;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	g_config->window = SDL_CreateWindow(
		g_config->caption.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		g_config->width,
		g_config->height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	g_config->context = SDL_GL_CreateContext(g_config->window);

	glewInit();


	std::stringstream ss;

	ss << "log/debug_" << time(nullptr) << ".txt";

	log_init(ss.str());

	input_init();

	if (g_config->app)
	{
		g_config->app->init();
	}
}

void app_update()
{
	g_config->pre = SDL_GetTicks();

	while (g_config->isRunning)
	{
		g_config->curr = SDL_GetTicks();

		g_config->delta = (g_config->curr - g_config->pre) / 1000.0f;

		g_config->fixedDelta += g_config->delta;

		while (SDL_PollEvent(&g_config->evt))
		{
			if (g_config->evt.type == SDL_QUIT)
			{
				app_quit();
			}

			input_event(g_config->evt);
		}

		if (g_config->app)
		{
			g_config->app->update();

			if (g_config->fixedDelta >= APP_TIME_60)
			{
				g_config->app->fixedUpdate();
			}

			g_config->app->render();
		}


		if (g_config->fixedDelta >= APP_TIME_60)
		{
			g_config->fixedDelta = 0.0f;
		}

		input_update();

		SDL_GL_SwapWindow(g_config->window);
	}
}

void app_release()
{
	if (g_config->app)
	{
		g_config->app->release();
	}

	input_release();

	log_release();

	SDL_GL_DeleteContext(g_config->context);
	SDL_DestroyWindow(g_config->window);
	SDL_Quit();

	g_config = nullptr;
}

AppConfig* app_getConfig()
{
	return g_config;
}

void app_quit()
{
	g_config->isRunning = false;
}
