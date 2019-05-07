#include "AppTest.h"


void AppTest::init()
{
	log_message("Hello, from init()");

	log_messageFormat("Hello, World %d %f %s", 100, 69.5f, "NO!");

}

void AppTest::update()
{

	if (input_isKeyUp(Keyboard::KB_LEFT))
	{
		log_message("Hello, from LEFT KEY");
	}

	if (input_isKeyUp(Keyboard::KB_RIGHT))
	{
		log_message("Hello, from right key");
	}

	if (input_isMouseButtonUp(MouseButtons::MBS_LEFT))
	{
		log_message("Hello, from mouse left");
	}
}

void AppTest::fixedUpdate()
{

}

void AppTest::render()
{

}

void AppTest::release()
{
	log_message("Hello, from release()");
}
