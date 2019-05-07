#include "AppTest.h"


void AppTest::init()
{
	log_message("Hello, from init()");

	log_messageFormat("Hello, World %d %f %s", 100, 69.5f, "NO!");

}

void AppTest::update()
{
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
