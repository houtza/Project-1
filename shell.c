
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
int executeBuiltins(char**arg,int*pidArray);
void printPid(int*pidArray);


int main(int argc, char *argv[])
{

  char *myArgv[ARGV_SIZE];
  pid_t pid;
  int pidSelect=0;
  int pidValues[5]={0,0,0,0,0,};
  int exeFlag;


  while(1){//Loops continuously untill "quit" is entered

    char commands[80]; //Can handle a imput up to 80 caricters

    clearArgs(myArgv);
    printWorkingDir();
    fgets(commands,80, stdin);
    parseInput(commands,myArgv);//parses the tokens from the imput and inserts them into the myArgv array
    exeFlag=executeBuiltins(myArgv,pidValues);
    if(exeFlag==0){
     if ((pid = fork()) == 0) { //Creats a parent and child fork of the code

          execute(myArgv);

      }else{

       pidValues[pidSelect] =waitpid(-1,NULL,0);//Parrent process waits for the child process to end
       pidSelect++;
       pidSelect=pidSelect%5;
      }
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
  if( execvp(tokenArray[0],tokenArray)<0){
    printf("invalid input\n");
  }
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


int executeBuiltins(char** args,int* pidArray){
  int builtinChoice;
  //char* builtin={"exit","cd","showpid"};
  //printf("test1");
  char* builtin[3];
  builtin[0]="exit";
  builtin[1]="cd";
  builtin[2]="showpid";

  for(builtinChoice=0;builtinChoice<3;builtinChoice++){
    if((strcmp(builtin[builtinChoice],args[0]))==0){
      break;
    }
  }

  // printf("%d", builtinChoice);
   switch (builtinChoice){
  case 0:

    exit(0);
    return 1;
    break;

  case 1:
    //cd();
    printf("test3");
    //  chdir(..);
    return 1;
    break;
  case 2:

    printPid(pidArray);
    return 1;
    break;

  default:
    return 0;
    break;
  }
}


//Takes in a pointer to a  string from the prompt, parses it into tokens and saves them to an array of char pointers
void parseInput(char* commands, char **myArgv){
  char *token;
  int tokenCounter=0;   //The counter for the # of tokens

  token = strtok(commands," ");
  removeNewLine(token);

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


void printPid(int* pidArray){
  int i;
  for(i=4;i>-1;i--){
    printf("%d\n",pidArray[i]);
  }
}

