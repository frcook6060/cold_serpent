#include "sys.h"



static std::ofstream out;

void log_init(std::string fileName)
{
	out.open(fileName);
}

void log_release()
{
	out.close();
}

void log_message(const std::string& message)
{
	std::cout << "LOG> " << message << std::endl;
	out << "LOG> " << message << std::endl;
}

void log_messageFormat(const char* format, ...)
{
	char* msg = nullptr;
	uint32_t len = 0;
	va_list args;
	va_start(args, format);

	len = _vscprintf(format, args) + 1;
	msg = new char[len];
	vsprintf_s(msg, len, format, args);

	log_message(msg);

	va_end(args);

	delete[] msg;
}
