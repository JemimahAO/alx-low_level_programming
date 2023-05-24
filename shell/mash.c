#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>

// exit the shell
void kash_exit (char **args)
{
	exit(0);
}

//change working directory.
void kash_cd(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "kash: cd: missing argument\n");
	}
	else
	{
		if(chdir (args[1]) != 0)
		{
			perror("kash: cd");
		}
	}

}

//printing the shell's help text
void kash_help(char **args)
{
	char *helptext =
		"Kash - the kinda aimeless shell."
		"the following are built-in commands:\n"
		"  cd     change working directory"
		"  exit   exit the shell.\n"
		"  help   print this help text.\n"
		;
	printf("%s", helptext);
}

//built-in instance associated with the handler functions
struct builtin
{
	char *name;
	void (*func)(char **args);
};

//array of the built in commands
struct builtin builtins[] =
		{
		{"help", kash_help},
		{"exit", kash_exit},
		{"cd", kash_cd},
		};

//returns number of built in commands
int kash_num_builtins()
{
	return sizeof(builtins) / sizeof(struct builtin);
}

//executing the commands...lauching
void kash_exec(char **args)
{
	for (int i =0; i < kash_num_builtins(); i++)
	{
		if(strcomp(args[0], builtins[1].name) == 0)
		{
			builtins[i].func(args);
			return;
		}
	}

	pid_t child_pid = fork();

	if (child_pis == 0)
	{
		execvp(args[0], args);
		perror("kash");
		exit(1);
	}
	else if (child_pid > 0)
	{
		int status;
		do
		{
			waitpid(child_pid, &status,WUNTRACED);
		}
		while ( WIFEXITED(status) && WIFSIGNALED(status));
	}
	else
	{
		perror("kash");
	}
}

// tokenisation
char** kash_split_line(char *line)
{
	int length = 0;
	int capacity = 16;

	char **tokens = malloc(capacity *sizeof(char*));
	if(!tokens)
	{
		perror("kash");
		exit(1);
	}

	char *delimeters = "\t\r\n";
	char *token = strtok(line, delimeters);

	while (token != NULL)
	{
		tokens[length] = token;
		length++;

		if (length >= capacity)
		{
			capacity = (int) (capacity * 1.5);
			tokens = realloc(tokens, capacity *sizeof(char*));

			if(!tokens)
			{
				perror("kash");
				exit(1);
			}
		}

		token = strtok(NULL, delimeters);
	}

	tokens[length] = NULL;
	return tokens;
}

//reding the line
char* kash readline()
{
	char *line = NULL;
	size_t buflen = 0;
	errno = 0;
	ssize_t strlen = getline(&len, &buflen, stdin);

	if (strlen <0)
	{
		if(errno)
		{
			perror("kash");
		}
		exit(1);
	}
	return line;
}

//entry point.../... main method

int main()
{
	while(true)
	{
		printf("> ");
		char *line = kash_read_line();
		char **tokens = kash_split_line;

		if (tokens[0] != NULL)
		{
			kash_exec(tokens)
		}

		free(tokens);
		free(line);
	}
}

