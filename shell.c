
/***********************************************************
 * Name of program: shell
 * Authors: Aaron Houtz and Geoffrey Miller
 * Description:  A program to open a shell that is able to execute commands from the command prompt
**********************************************************/


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define ARGV_SIZE 10

void printWorkingDir();//Prints the current working directory path
void printInColor(char *stringToColor); //Takes in the address of a string and prints it in red

int main(int argc, char *argv[])
{
	
  
	char *myArgv[ARGV_SIZE];  // an array of pointers to strings, possibly move inside while loop so that array is cleared each time
	char *token;
	pid_t pid;

	if ((pid = fork()) == 0) { //Creats a parent and child fork of the code
		int i;
		while(1){              //Loops continuously untill "quit" is entered
			char commands[80];//Can handle a imput up to 80 caricters
			int tokenCounter=0;   //The counter for the # of tokens

			for(i=0;i<10;i++){   //clears the array each iteration of the while loop
				myArgv[i]=NULL;
			}
     
			printWorkingDir();   
			scanf("%[^\n]%*c",commands);    


			token = strtok(commands," ");   //Get the first token from the sentence to see if it is "exit"
			if(!(strcmp(token,"exit"))){  
				//printf("%sExit\n");
				return 0;
			}
			tokenCounter++;
 
			myArgv[tokenCounter]=token; 
			printf("%s\n",myArgv[tokenCounter]);// Tester for printing out the tokens saved in the string pointer array


			while(token!=NULL){    //Loop throught the remaining tokens
     
				token =strtok(NULL," ");

				if(token!=NULL){
					tokenCounter++;      
					myArgv[tokenCounter]=token;
					printf("%s\n",myArgv[tokenCounter]); // Tester for printing out the tokens saved in the string pointer array    

				}
			}
      
			if(execvp(*myArgv,myArgv)<0);{  //Still trying to get execvp to work correctly
				return 0;   
			}
		}
	}else{
		waitpid(-1,NULL,0);//Parrent process waits for the child process to end
	}

 return 0;
}


//Takes in the address of a string and prints it in red
void printInColor(char *stringToColor){
	
	printf(RED  "%s$ "RESET, stringToColor);
}

//Prints the current working directory path
void printWorkingDir(){
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL){  //Gets current working directory
		printInColor(cwd);
	}
}
