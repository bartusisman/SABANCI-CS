#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

int main (int argc, char* argv[]) 
{
	
	char str[1024];
	char *com_parts[1024];
	
 	FILE* fptr = fopen("commands.txt","r");
 	FILE* wptr = fopen("parse.txt","w");
 	
 	while(fgets(str,1024,fptr))
 	{
 		char* token = strtok(str," ");
 		int count = 0;
 		
 		
 		while(token != NULL)
 		{
			str[strcspn(str, "\n")] = 0;
 			com_parts[count] = token;
 			token = strtok(NULL," ");
 			count++;
 		}
 		
 		
 		char* real_arr[count + 1];
 		
 		for(int i = 0; i < count + 1; i++)
 		{
 			real_arr[i] = com_parts[i];
 		}
 		
 		fprintf(wptr,"----------\n");
 		fprintf(wptr,"Command: %s\n", real_arr[0]);

		if(real_arr[1] == NULL || real_arr[1][0] == '&')
 		{
 			fprintf(wptr,"Inputs: \n");
 			fprintf(wptr, "Options: \n");	
 			fprintf(wptr, "Redirection: -\n");
 		}
 		else if( (real_arr[1][0] == '-') && (isalpha(real_arr[1][1])) && ( strlen(real_arr[1]) == 2) )
 		{
 			fprintf(wptr,"Inputs: \n");
 			fprintf(wptr,"Options: %s\n",real_arr[1]);
 			if ( (real_arr[2][0] == '<') || (real_arr[2][0] == '>') )
 			{
 				fprintf(wptr, "Redirection: %s\n", real_arr[2]);
 			}
 			else
 			{
 				fprintf(wptr, "Redirection: -\n");
 			}
 		}
 		
 		else if ( (real_arr[1][0] == '<') || (real_arr[1][0] == '>') )
 		{
 			fprintf(wptr,"Inputs: \n");
 			fprintf(wptr, "Options: \n");	
 			fprintf(wptr, "Redirection: %s\n", real_arr[1]);	
 			
 		}
 		
 		else if (real_arr[1][0] != '&')
 		{
 			fprintf(wptr,"Inputs: %s\n", real_arr[1]);
 			
 			if((real_arr[2][0] == '-') && (isalpha(real_arr[2][1])) && ( strlen(real_arr[2]) == 2) ) 
 			{
 				fprintf(wptr, "Options: %s\n",real_arr[2]);	
 				if( (real_arr[3][0] == '<') || (real_arr[3][0] == '>') )
 				{
 					fprintf(wptr, "Redirection: %s\n", real_arr[3]);
 				}
 				else
 				{
 					fprintf(wptr, "Redirection: - \n");
 				}
 			}
 			
 			if ( (real_arr[2][0] == '<') || (real_arr[2][0] == '>') )
	 		{
	 			fprintf(wptr, "Options: \n");	
	 			fprintf(wptr, "Redirection: %s\n", real_arr[2]);	
	 		}
 			
 		}
 		
 		if(real_arr[count-1][0] == '&')
 		{
 			fprintf(wptr,"Background Job: y\n");
 		}
 		else
 		{
 			fprintf(wptr,"Background Job: n\n");
 		}
 		
 		fprintf(wptr,"----------\n");
 		
 		int ID = fork();
 		
 		if (ID != 0)
 		{
 		
 			for(int i = 0; i < ( sizeof(real_arr) / sizeof(real_arr[0]) ); i++)
 			{
 			
 				if(real_arr[i][0] == '<')
 				{
 					close(STDIN_FILENO);
 					open(real_arr[i + 1], O_RDONLY,0777);
 					
 					if(real_arr[i+2] != NULL)
 					{
 						real_arr[i] = real_arr[i+2];
 						real_arr[i+2] = NULL;
 					}
 					else
 					{
 						real_arr[i] = NULL;
 					}
 					
 					real_arr[i + 1] = NULL;
 					break;								
 				}
 				
 				else if(real_arr[i][0] == '>')
 				{
 					close(STDOUT_FILENO);
 					open(real_arr[i + 1],O_CREAT|O_WRONLY|O_TRUNC, 0777);
 					
 					if(real_arr[i+2] != NULL)
 					{
 						real_arr[i] = real_arr[i+2];
 						real_arr[i+2] = NULL;
 					}
 					
 					else
 					{
 						real_arr[i] = NULL;
 					}
 					real_arr[i + 1] = NULL;		
 					break;	
 					
 				}
 				
 				
 				
 			}
 			
 			
 			bool is_background = false;
 			for(int i = 0; i < ( sizeof(real_arr) / sizeof(real_arr[0]) ); i++ )
 			{
 				if(real_arr[i][0] == '&')
 				{
 					is_background = true;
 					real_arr[i] = NULL;
 					break;
 				}
 			}
 			
 			if(is_background)
 			{
 				execvp(real_arr[0],real_arr);
 			}
 			else
 			{
 				wait(NULL);
 				execvp(real_arr[0],real_arr);
 			}
 			
 			
 		}
 		else
 		{
 			wait(NULL);
 		}
 		
 		

 		memset(real_arr, 0, sizeof(real_arr));
 		memset(com_parts, 0, sizeof(com_parts));
 	}
   	fclose(fptr);
   	fclose(wptr);
   	
	return 0;
}
