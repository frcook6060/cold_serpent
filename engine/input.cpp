#include "sys.h"


class InputStateRelease : public IInputState
{
private:
	InputStateType type = InputStateType::IS_RELEASE;
public:
	virtual InputStateType getInputStateType() override;
	virtual bool isInputStateType(InputStateType type) override;
	virtual void update(IInputState** state) override;
	virtual void isDown(IInputState** state) override;
	virtual void isUp(IInputState** state) override;
	virtual IInputState* next() override;
} inputStateRelease;

class InputStateDown : public IInputState
{
private:
	InputStateType type = InputStateType::IS_DOWN;
public:
	virtual InputStateType getInputStateType() override;
	virtual bool isInputStateType(InputStateType type) override;
	virtual void update(IInputState** state) override;
	virtual void isDown(IInputState** state) override;
	virtual void isUp(IInputState** state) override;
	virtual IInputState* next() override;
} inputStateDown;

class InputStatePress : public IInputState
{
private:
	InputStateType type = InputStateType::IS_PRESS;
public:
	virtual InputStateType getInputStateType() override;
	virtual bool isInputStateType(InputStateType type) override;
	virtual void update(IInputState** state) override;
	virtual void isDown(IInputState** state) override;
	virtual void isUp(IInputState** state) override;
	virtual IInputState* next() override;
} inputStatePress;


class InputStateUp : public IInputState
{
private:
	InputStateType type = InputStateType::IS_UP;
public:
	virtual InputStateType getInputStateType() override;
	virtual bool isInputStateType(InputStateType type) override;
	virtual void update(IInputState** state) override;
	virtual void isDown(IInputState** state) override;
	virtual void isUp(IInputState** state) override;
	virtual IInputState* next() override;
} inputStateUp;

static std::vector<IInputState*> keys(KB_LENGTH);

static std::vector<IInputState*> mouseButtons(MBS_LENGTH);

template<typename T>
void loop(std::vector<T> list, std::function<void(T*)> fun)
{
	for (uint32_t i = 0; i < list.size(); i++)
	{
		fun(&list[i]);
	}
}

void input_init()
{
	
	for (uint32_t i = 0; i < keys.size(); i++)
	{
		keys[i] = &inputStateRelease;
	}

	for (uint32_t i = 0; i < mouseButtons.size(); i++)
	{
		mouseButtons[i] = &inputStateRelease;
	}
}

void input_release()
{
	// Don't know what to do lol
}

std::function<void(SDL_KeyboardEvent&)> keyDown = [&](SDL_KeyboardEvent& key) {
	keys[key.keysym.scancode]->isDown(&keys[key.keysym.scancode]);
};

std::function<void(SDL_KeyboardEvent&)> keyUp = [&](SDL_KeyboardEvent& key) {
	keys[key.keysym.scancode]->isUp(&keys[key.keysym.scancode]);
};

std::function<void(SDL_MouseButtonEvent&)> mouseButtonDown = [&](SDL_MouseButtonEvent& mb) {
	mouseButtons[mb.button - 1]->isDown(&mouseButtons[mb.button - 1]);
};

std::function<void(SDL_MouseButtonEvent&)> mouseButtonUp = [&](SDL_MouseButtonEvent& mb) {
	mouseButtons[mb.button - 1]->isUp(&mouseButtons[mb.button - 1]);
};

void input_event(SDL_Event& e)
{

	switch (e.type)
	{
	case SDL_KEYDOWN:
		keyDown(e.key);
		break;
	case SDL_KEYUP:
		keyUp(e.key);
		break;
	case SDL_MOUSEBUTTONDOWN:
		mouseButtonDown(e.button);
		break;
	case SDL_MOUSEBUTTONUP:
		mouseButtonUp(e.button);
		break;
	}
}

void input_update()
{
	for (uint32_t i = 0; i < keys.size(); i++)
	{
		keys[i]->update(&keys[i]);
	}

	for (uint32_t i = 0; i < mouseButtons.size(); i++)
	{
		mouseButtons[i]->update(&mouseButtons[i]);
	}
}

// Keyboard
bool input_isKeyRelease(const Keyboard& key)
{
	return keys[key]->isInputStateType(InputStateType::IS_RELEASE);
}

bool input_isKeyDown(const Keyboard& key)
{
	return keys[key]->isInputStateType(InputStateType::IS_DOWN);
}

bool input_isKeyPress(const Keyboard& key)
{
	return keys[key]->isInputStateType(InputStateType::IS_PRESS);
}

bool input_isKeyUp(const Keyboard& key)
{
	return keys[key]->isInputStateType(InputStateType::IS_UP);
}

// Mouse Button
bool input_isMouseButtonRelease(const MouseButtons& mb)
{
	return mouseButtons[mb]->isInputStateType(InputStateType::IS_RELEASE);
}

bool input_isMouseButtonDown(const MouseButtons& mb)
{
	return mouseButtons[mb]->isInputStateType(InputStateType::IS_DOWN);
}

bool input_isMouseButtonPress(const MouseButtons& mb)
{
	return mouseButtons[mb]->isInputStateType(InputStateType::IS_PRESS);
}

bool input_isMouseButtonUp(const MouseButtons& mb)
{
	return mouseButtons[mb]->isInputStateType(InputStateType::IS_UP);
}

// Mouse Pointer Location
void input_getMousePosition(int32_t& x, int32_t& y)
{

}

// Input Grab
bool input_isInputGrab()
{
	return false;
}

void input_setInputGrab(bool grab)
{

}

void input_toggleInputGrab()
{

}

// InputStateRelease
InputStateType InputStateRelease::getInputStateType()
{
	return this->type;
}

bool InputStateRelease::isInputStateType(InputStateType type)
{
	return this->type == type;
}

void InputStateRelease::update(IInputState** state)
{}

void InputStateRelease::isDown(IInputState** state)
{
	*state = this->next();
}

void InputStateRelease::isUp(IInputState** state)
{}

IInputState* InputStateRelease::next()
{
	return &inputStateDown;
}

// InputStateDown
InputStateType InputStateDown::getInputStateType()
{
	return this->type;
}

bool InputStateDown::isInputStateType(InputStateType type)
{
	return this->type == type;
}

void InputStateDown::update(IInputState** state)
{
	*state = this->next();
}

void InputStateDown::isDown(IInputState** state) 
{}

void InputStateDown::isUp(IInputState** state) 
{}

IInputState* InputStateDown::next()
{
	return &inputStatePress;
}

// InputStatePress
InputStateType InputStatePress::getInputStateType()
{
	return type;
}

bool InputStatePress::isInputStateType(InputStateType type)
{
	return this->type == type;
}

void InputStatePress::update(IInputState** state)
{}

void InputStatePress::isDown(IInputState** state) 
{}

void InputStatePress::isUp(IInputState** state) 
{
	*state = this->next();
}

IInputState* InputStatePress::next()
{
	return &inputStateUp;
}

// InputStateUp
InputStateType InputStateUp::getInputStateType()
{
	return this->type;
}

bool InputStateUp::isInputStateType(InputStateType type)
{
	return this->type == type;
}

void InputStateUp::update(IInputState** state)
{
	*state = this->next();
}

void InputStateUp::isDown(IInputState** state) 
{}

void InputStateUp::isUp(IInputState** state) 
{}

IInputState* InputStateUp::next()
{
	return &inputStateRelease;
}