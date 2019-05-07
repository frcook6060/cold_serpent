#pragma once



void log_init(std::string fileName);

void log_release();

void log_message(const std::string& message);

void log_messageFormat(const char* format, ...);
