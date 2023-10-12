// SerialTerminal.h

#ifndef _SERIALTERMINAL_h
#define _SERIALTERMINAL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "../OS/KernelTask.h"
#include "../OS/StdIOBase.h"

struct CommandLine
{
	char* command;
	char* args[8];
	byte args_count;
};

class MShellProgram
{
public:
	virtual bool handles(const char* prog_name) = 0;

	virtual byte execute(CommandLine command_line, StandardInput* std_in, StandardOutput* std_out) = 0;
};

class MShellPrograms_BuiltIn : public MShellProgram
{
public:
	MShellPrograms_BuiltIn();
	bool handles(const char* prog_name);

	byte execute(CommandLine command_line, StandardInput* std_in, StandardOutput* std_out);

private:
	byte num_commands = 3;
	const char* commands[3] = {"ver", "help", "millis"};

};

class MShell
{
protected:
	StandardInput* stdin_;
	StandardOutput* stdout_;
	LinkedList programs;

public:
	MShell(StandardInput* std_in, StandardOutput* std_out)
		: stdin_(std_in),
		  stdout_(std_out)
	{
		programs.append(new LinkedListItem(new MShellPrograms_BuiltIn()));
	}


	void begin();
	void print_prompt();
	void print_cmd_info();
	void print_unknown_cmd();
	void execute_command();
	void process();
	void parse_line(char* line, CommandLine* cmd);
};


#endif
