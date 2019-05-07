#include "AppTest.h"

int main(int argc, char** argv)
{
	AppTest test;
	AppConfig config;

	config.caption = "Cold Serpent Engine Test";
	config.width = 1280;
	config.height = 720;
	config.app = &test;

	app_init(&config);
	app_update();
	app_release();

	return 0;
}