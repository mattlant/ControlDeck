// 
// 
// 

#include "MShell.h"

MShellPrograms_BuiltIn::MShellPrograms_BuiltIn()
{
}

bool MShellPrograms_BuiltIn::handles(const char* prog_name)
{
	for (int i = 0; i < num_commands; i++)
	{
		if (strcmp(prog_name, commands[i]) == 0)
			return true;
	}
	return false;
}

byte MShellPrograms_BuiltIn::execute(CommandLine command_line, StandardInput* std_in, StandardOutput* std_out)
{
	if (strcmp(command_line.command, "ver") == 0)
	{
		std_out->print("MTerm v");
		std_out->println("0.1"); //move to macro
	}
	else if (strcmp(command_line.command, "help") == 0)
	{
		std_out->println("Sorry, help is not yet available."); //move to macro
	}

	else if (strcmp(command_line.command, "millis") == 0)
	{
		std_out->print(millis()); //move to macro
		std_out->println();
	}
	return 0;
}

#define MSHELL_VERSION 0.1

void MShell::begin()
{
	stdout_->print("Welcome to MShell");
	stdout_->print(" v");
	stdout_->println(MSHELL_VERSION);
	print_prompt();
}

char buffer[64]; // Adjust the size as needed
int index = 0;
bool is_cmd_ready = false;
CommandLine command_line;

void MShell::print_prompt()
{
	stdout_->print("\nroot@local:(no filesystem)# ");
}

void MShell::print_cmd_info()
{
	stdout_->println("You wrote...");
	stdout_->print("Command:");
	stdout_->println(command_line.command);
	stdout_->print("args:");
	for (int i = 0; i < command_line.args_count; i++)
	{
		stdout_->print(command_line.args[i]);
		stdout_->print(" ");
	}
	stdout_->println();
}

void MShell::print_unknown_cmd()
{
	stdout_->print("unknown command: ");
	stdout_->println(command_line.command);
}

void MShell::execute_command()
{
	auto iter = programs.get_iterator();
	bool found = false;
	while (iter.move_next())
	{
		MShellProgram* prog = static_cast<MShellProgram*>(static_cast<LinkedListItem*>(iter.get_current_item())->data);
		if (prog->handles(command_line.command))
		{
			found = true;
			prog->execute(command_line, stdin_, stdout_);
			break;
		}
	}

	if (found == false)
	{
		print_unknown_cmd();
	}
}

void MShell::process()
{
	while (stdin_->available())
	{
		char ch = stdin_->readChar();
		if (ch == '\b')
		{
			// Handle backspace
			if (index > 0)
			{
				stdout_->print(ch);
				index--; // Move the index back to erase the last character
			}
			else
				stdout_->print('\a'); //bell if cant backspace
		}
		else if (ch == '\n' || ch == '\r')
		{
			stdout_->println();
			buffer[index] = '\0'; // Null-terminate the string
			parse_line(buffer, &command_line);
			index = 0; 
			execute_command();
			print_prompt();
			break;
		}
		else
		{
			stdout_->print(ch);
			if (index < sizeof(buffer) - 1)
			{
				buffer[index++] = ch;
			}
		}
	}
}

void MShell::parse_line(char* line, CommandLine* cmd)
{
	char* token = strtok(line, " ");
	byte argIndex = 0;
	cmd->args_count = 0;

	// The first token is the command
	cmd->command = token;

	// Get subsequent tokens (arguments)
	while ((token = strtok(nullptr, " ")) != NULL)
	{
		cmd->args[argIndex++] = token;
		cmd->args_count++;
	}


	// Null-terminate the arguments array
	cmd->args[argIndex] = NULL;
}
