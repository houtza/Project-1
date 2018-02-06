
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
void removeNewLine(char *s);
void parseInput(char* commands, char **myArgv);
void executeBuiltins(char** args);


int main(int argc, char *argv[])
{
 
  char *myArgv[ARGV_SIZE]; 
  pid_t pid;
 
  while(1){//Loops continuously untill "quit" is entered
    if ((pid = fork()) == 0) { //Creats a parent and child fork of the code
    
       
        char commands[80]; //Can handle a imput up to 80 caricters
      
	clearArgs(myArgv);
        printWorkingDir(); 
        fgets(commands,80, stdin);  
        parseInput(commands,myArgv);//parses the tokens from the imput and inserts them into the myArgv array	    
	// if(myArgv[0]=="exit"){
	//executeBuiltins(myArgv);
	// }
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

//clears the array each iteration of the main while loop
void clearArgs(char **argArray){
  int i;
  for(i=0;i<10;i++){   
    argArray[i]=NULL;
  }
}


//removes the newline char from each token passed in
void removeNewLine(char *s) {
  char *t = s;
  while (*s) {
    if (*s == '\n') {
      *s='\0';
    }
    s++;
  }
}


void executeBuiltins(char** args){
  int builtinChoice;
  //char* builtin={"exit","cd","showpid"};
  
  char* builtin[3];
  builtin[0]="exit";
  builtin[1]="cd";
  builtin[2]="showpid";
 
  for(builtinChoice=1;builtinChoice<4;builtinChoice++){
    if(args[0]==builtin[builtinChoice]){
      break;
    }
  }

  switch (builtinChoice){
  case 1:
    printf("exit");
    exit(0);
  case 2:
    //cd();

  case 3:
    //showpid();

  default:
    break;
  }
}


//Takes in a pointer to a  string from the prompt, parses it into tokens and saves them to an array of char pointers
void parseInput(char* commands, char **myArgv){
  char *token;
  int tokenCounter=0;   //The counter for the # of tokens

  token = strtok(commands," ");
  removeNewLine(token);

  printf(token);
  myArgv[tokenCounter]=token;
  while(token!=NULL){    //Loop throught the remaining tokens

    token =strtok(NULL," ");

    if(token!=NULL){
      tokenCounter++;
      removeNewLine(token);
      myArgv[tokenCounter]=token;
    }
  }
}
