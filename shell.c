
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
void execute(char **tokenArray);
void clearArgs(char **argArray);
void remove_new_line(char *s);


int main(int argc, char *argv[])
{
 
  char *myArgv[ARGV_SIZE]; 
  char *token;
  pid_t pid;
 
  while(1){//Loops continuously untill "quit" is entered
    if ((pid = fork()) == 0) { //Creats a parent and child fork of the code
    
       
        char commands[80]; //Can handle a imput up to 80 caricters
        int tokenCounter=0;   //The counter for the # of tokens
	clearArgs(myArgv);
        printWorkingDir(); 
        fgets(commands,80, stdin);  
	    
	//myArgv[0]="ls";  //It works when I populate the array in code
	//myArgv[1]="-l";
	//myArgv[2]=NULL;
        token = strtok(commands," ");
        remove_new_line(token);
	//token = strtok(token,"\n");
        printf(token);  
        myArgv[tokenCounter]=token;
	//printf("%s",myArgv[tokenCounter]); // Tester for printing out the tokens saved in the string pointer array

        if((strcmp(token,"ls"))){
          printf("worng\n");
        }
        while(token!=NULL){    //Loop throught the remaining tokens
     
	  token =strtok(NULL," ");
	 
	  if(token!=NULL){
	    tokenCounter++;
	    remove_new_line(token);      
	    myArgv[tokenCounter]=token;
	    printf("%s",myArgv[tokenCounter]); // Tester for printing out the tokens saved in the string pointer array    

	  }
        }
        //myArgv[2]=NULL;
        //execvp(arg[0],arg);
        execute(myArgv);      
  
    }else{
      waitpid(-1,NULL,0);//Parrent process waits for the child process to end
    }
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

void execute(char **tokenArray){
  execvp(tokenArray[0],tokenArray);
}

//clears the array each iteration of the while loop
void clearArgs(char **argArray){
  int i;
  for(i=0;i<10;i++){   
    argArray[i]=NULL;
  }
}


void remove_new_line(char *s) {
  char *t = s;
  while (*s) {
    if (*s == '\n') {
      *s='\0';
    }
    s++;
  }
}


void executeBuiltins(char** input){
	
}