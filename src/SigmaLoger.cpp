#include "SigmaLoger.h"

void SigmaLoger::Log(SigmaLogLevel level)
{
	if (timestamp != NULL)
	{
		loger->prefix(timestamp());
	}
	if (publisher != NULL)
	{
		publisher(level, loger->c_str());
	}
	loger->clear();
}
 
SigmaLoger::SigmaLoger(int size, SigmaLogPublisher publisher, SigmaLogTimestamp timestamp)
	: size(size), publisher(publisher), timestamp(timestamp)
{
	loger_SAFEBUFFER = new char[size + 1];
	loger = new SafeString(size, loger_SAFEBUFFER, "");
}

SigmaLoger &SigmaLoger::printf(const char *format, va_list args)
{
	int maxSize = size - loger->length() - 1;	// -1 for the trailing '\0'
	int len = vsnprintf(NULL, 0, format, args); // calculate size of the string
	if (len <= maxSize)
	{
		char *buffer = new char[len + 1];
		vsnprintf(buffer, len + 1, format, args);
		loger->concat(buffer);
		delete[] buffer;
	}
	else
	{
		char *buffer = new char[maxSize + 1];
		vsnprintf(buffer, maxSize + 1, format, args);
		loger->concat(buffer);
		delete[] buffer;
	}
	return *this;
}

void SigmaLoger::SerialPrint(SigmaLogLevel level, const char *message)
{
	Serial.println(message);
}

const char *SigmaLoger::Timestamp()
{
	static char timest[20];
	unsigned long ts = millis();
	int l;
	timest[0] = '[';
	itoa(ts / 1000, timest + 1, 10);
	l = strlen(timest);
	timest[l] = '.';
	itoa(ts % 1000, timest + l + 1, 10);
	l = strlen(timest);
	timest[l] = ']';
	timest[l + 1] = 0;
	return timest;
}

SigmaLoger *Log;