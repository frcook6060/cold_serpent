#pragma once



#include <sys.h>

class AppTest : public IApp
{
public:

	virtual void init() override;
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void render() override;
	virtual void release() override;
};


