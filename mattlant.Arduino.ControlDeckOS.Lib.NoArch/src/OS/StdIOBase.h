#pragma once
#ifndef M_STANDARD_IO_COMMON_h
#define M_STANDARD_IO_COMMON_h


class StandardInput
{
public:
	StandardInput() = default;
	virtual ~StandardInput() = default;
	virtual char readChar() = 0;
	virtual bool available() = 0;
};

class StandardOutput
{
public:
	StandardOutput() = default;
	virtual ~StandardOutput() = default;
	virtual void print(const char* str) = 0;
	virtual void print(char c) = 0;
	virtual void print(int c) = 0;
	virtual void print(long c) = 0;
	virtual void print(unsigned long c) = 0;
	virtual void println(const char* str) = 0;
	virtual void println() = 0;
	virtual void println(float value) = 0;
};


#endif
