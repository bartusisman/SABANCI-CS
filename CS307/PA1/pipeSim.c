#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	printf("I’m SHELL process, with PID: %d - Main command is: man grep ls | grep -A2 -e '-n, --line-number'   \n", getpid());
	int fd[2]; //fd[0] for read, fd[1] for write
	pipe(fd);
	
	int child1 = fork();
	
	if (child1 == -1) //error message and abort program
	{
		printf("Error: child 1 can not be created \n");
		return 1;
	}
	
	else if (child1 == 0)//child1 process
	{
		close(fd[0]); // no need to read in MAN process so we close it at the beggining
		printf("I’m MAN process, with PID: %d- My command is: man grep ls \n", getpid());
		
		dup2(fd[1], STDOUT_FILENO); // fd[1] is coppied into STDOUT_FILENO
		close(fd[1]); // close reading since it now exist in STDOUT_FILENO
		
		char *man_parts[4] = {"man", "grep", "ls", NULL}; // man parts
		
		execvp("man", man_parts ); // MAN process is executed
	}
	
	else // parent process
	{
		int child2 = fork();
		
		if (child2 == -1) //error message and abort program
		{
			printf("Error: child 2 can not be created! \n");
			return 1;
		}
		
		else if (child2 == 0) // child2 process
		{
			wait(NULL); // makes sure to wait for chidl1
			
			
			close(fd[1]); //writing is closed
			printf("I’m GREP process, with PID: %d- My command is: grep -A2 -e '-n, --line-number' \n", getpid());
			
			dup2(fd[0], STDIN_FILENO); // f[0} is coppied into STDIN_FILENO
			close(fd[0]);
			
			char* grep_parts[5] = {"grep", "-A2", "-e", "-n, --line-number", NULL};
			
			close(STDOUT_FILENO); // closed STDOUT_FILENO so data will be streamed through other file directort which is'nt created yet
			
			open("output.txt", O_CREAT|O_WRONLY|O_TRUNC, 0777); // open returns a file directory, which is the only file directory rn in the program so data will be streamed through it
			execvp("grep", grep_parts); // exec of grep with the data it got from the file which came from chidl1
			
			
		}
		else // SHELL
		{
			wait(NULL); // making sure all child processes are finished

			printf("I’m SHELL process, with PID: %d - execution is completed, you can find the results in output.txt \n", getpid());
			
		}
		
	}
	 
	
	
	return 0;	
}
