#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
void MakeStringToArray(char **input_array, char *input);
int main()
{

	char **input_array = malloc(sizeof(char *) * 4);
	char input[20];
	pid_t pid;
	while (1)
	{
		printf(">>");
		fgets(input, 20, stdin);
		MakeStringToArray(input_array, input);
		pid = fork();
		
		if (pid == 0)
		{
			execvp(input_array[0], input_array);
		}
		else
		{
			wait(NULL);
		}
	}
	free(input_array);
	return 0;
}

void MakeStringToArray(char **input_array, char *input)
{
	char *word = NULL;
	size_t i = 0;
	word = strtok(input, " \n");
	while (word)
	{
		input_array[i] = word;

		word = strtok(NULL, " \n");
		++i;
	}
	input_array[i] = NULL;
}