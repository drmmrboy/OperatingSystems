#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

//Bryce Newton
//OS Project Part 1
//Help from Sam, Mike, Ian, Jerry, Sean, and Ben. and the linux book...kinda
//Couldn't have made it without my best friend Google. Thanks, babe.
//and stack overflow and some other random site
//VIM sucks

//Part One:
//Get and Execute command

//Part Two:
//Implement pipe

//CLEAN THIS UP LATER

char *PATH;
char **list;

char* pathFinder(char **);
char** getPaths();
char** parseInput(char inputLine[]);
void execute(char**);
char** pipeGet(char *inputLine);
void pipeExecute(char**);

int main(int argC, char **argV, char **envP )
{
    printf("Hello, World!\n"); //for test stuffs

    //find PATH
    PATH = pathFinder(envP);
    printf("%s\n", PATH);

    //list the paths
    list = getPaths();
    printf("Address %p\n", &list);
    int listCount = 0;
    while(list[listCount] != NULL)
        {
            printf("Base[%d] Address %p Pointer Value %p String=%s\n", listCount, &list[listCount], list[listCount], list[listCount]);
            listCount++;
        }
    printf("mama, we made it!");

    //process and forking
    //notes:
    //  use fgets to read line
    char inputLine[200];
    __pid_t proccess;

    char **command;
    int status; //thanks mike
    printf("%s", "\nPrompt:");
    bool pipe = false;
    while(fgets(inputLine, 200, stdin) !=NULL) //stdin = standard input
    {
        //bool pipe = false;
        for(int x = 0; x <sizeof(inputLine); x++)
        {
            if(inputLine[x] == '|')
            {
                pipe = true;
                puts("i see a pipe");
                break;
            }
        }
        if(pipe == false)
        {

            command = parseInput(inputLine);
            proccess = fork();

            if(proccess == -1)
            {
                puts("Error with fork. plz buy new ones");
            }
            else if(proccess == 0)
            {
                //EXECUTE! EXECUTE! EXECUTE!!!
                execute(command);
            }
            else
            {
                wait(&status);

            }
        }
        else
        {
            puts("made it to pipe");
            command = pipeGet(inputLine);
            puts("made it to pipe2");
            proccess = fork();

            if(proccess == -1)
            {
                puts("Error with for. plz buy new one");
            }
            else if(proccess == 0)
            {
                puts("pipeExecute");
                pipeExecute(command);
            }
            else
            {
                puts("wait");
                wait(&status);
            }
        }

        printf("%s", "Prompt:");


    }

    free(list);
    free(command);

    return 0;
}

char* pathFinder(char **envP)
{
    char findPath[] =  "PATH";
    int counterFind=0;
    int x;

    while (envP[counterFind] != NULL) {
        for (x = 0; x < 4; x++) {
            findPath[x] = envP[counterFind][x]; //looking through enviornment   
        }
        if (strcmp(findPath, "PATH") == 0) //if PATH found in enviorment details
        {
            puts("Path Found!\n");
            break;
        }
        counterFind++;
    }

    return envP[counterFind];
}

char** getPaths() {

    //printf("getPaths\n");

    //first part variables
    char *path = PATH;
    char **parsed;
    int counterPath = 0;
    path += 5;
    int length = strlen(path)+1;
    int x;

    //second part variables
    int charCounter = 0;
    int arrayCounter = 0;
    int y;

    //third part variables
    int stringCounter = 0;
    int arrayCounter2 = 0;
    int z;

    //PART 1
    for(x = 0; x<length; x++)
    {
        //printf("part1 ");
        if(path[x] == ':' || path[x] == '\0')
        {
            counterPath++;
        }
    }
    counterPath++; //don't understand why. but ben told me to

    parsed = malloc(counterPath * sizeof(char*)); //allocate memory

    //PART 2 making sure there is enough memory for string
    for(y = 0; y < length; y++)
    {
        if(path[y] ==':' || path[y] == '\0')
        {
            charCounter++;
            parsed[arrayCounter] = malloc(charCounter);
            charCounter = 0;
            arrayCounter++;
        }
        else
        {
            charCounter++;
        }

    }
    //PART 3 put strings in the array
    for(z = 0; z < length; z++)
    {
        if(path[z] == ':' || path[z] == '\0')
        {
            stringCounter++;
            parsed[arrayCounter2][stringCounter] = '\0';
            arrayCounter2++;
            stringCounter=0;
        }
        else
        {
            parsed[arrayCounter2][stringCounter] = path[z];
            stringCounter++;
        }

    }

    parsed[counterPath] = NULL;
    return parsed;
    
}

char** parseInput(char inputLine[])
{
    int inputLength = strlen(inputLine) +1;
    int numArg = 1;
    int x;
    char ** argument;

    //var for da loops
    int count1 = 0;
    int count2 = 0;
    int y;

    int count3 = 0;
    int count4 = 0;
    int z;

    for(x = 0; x < inputLength; x++)
    {
        if(inputLine[x] == ' ' || inputLine[x] == '\0')
        {
            numArg++;
        }
    }
    argument = malloc(numArg * sizeof(char*));

    for(y = 0; y < inputLength; y++)
    {
        if(inputLine[y] ==' ' || inputLine[y] == '\0')
        {
            count1++;//must go  before!!1!11
            argument[count2] = malloc(count1 * sizeof(char*));
            count2++;

            count1 = 0; //reset
        }
    }

    for(z = 0; z < inputLength; z++)
    {
        if(inputLine[z] == ' ' || inputLine[z] == '\0')
        {
            count3++;
            argument[count4][count3] = '\0';
            count4++;
            count3 = 0; //reset


        }
        else if(inputLine[z] == '\n')
        {
            continue; //i guessthis is necessary
        }
        else{
            argument[count4][count3] = inputLine[z];
            count3++;
        }
    }

    return argument;
}

void execute(char **command)
{
    int count = 0;
    char search[200];
    while(list[count] != NULL)
    {
        strcpy(search, list[count]);
        strcat(search, "/");
        strcat(search, command[0]);
        printf("Searching %s\n", search);


        if (access(search, F_OK) != -1)
        {
            //puts("test");
            execv(search, command);
            break;
        }
        count++;
    }
}

char** pipeGet(char *inputLine) //this is almost identical to ParseInput
{
    //Variables used for whole method
    int inputLength = strlen(inputLine);
    char **arguments;

    //PART 1 Variables
    int numOfComm = 1;
    int x;

    //PART 2 Variables
    int y;
    int count1 =0;
    int count2 =0;

    //PART 3 Variables
    int z;
    int count3 =0;
    int count4 =0;

    //PART 1 How many pipes are there?
    puts("part1");
    for(x=0; x<inputLength; x++)
    {
        if(inputLine[x] == '|')
        {
            numOfComm +=1;
        }
    }
    //PART 2
    puts("part2");
    arguments = malloc(numOfComm * sizeof(char*)); //allocate memory
    for(y =0; y<inputLength; y++)
    {
        if(inputLine[y] =='|' || inputLine[y] =='\0')
        {
            count1++;
            arguments[count2] =malloc(count1 * sizeof(char*));
            count2++;
            count1 =0;
        }
        else if(inputLine[y] == '\n')
        {
            continue;
        }
        else
        {
            count1++;
        }
    }

    //PART 3
    puts("part3");

    for(z =0; z<inputLength; z++)
    {
        if(inputLine[z] == '|' || inputLine[z] == '\0')
        {
            count3++;
            arguments[count4][count3] = '\0';
            count4++;
            count3 =0;
        }
        else if(inputLine[z] == '\n')
        {
            continue;
        }
        else
        {
            arguments[count4][count3] = inputLine[z];
            count3++;
        }
    }
    printf("%s", arguments);
    return arguments;
}

void pipeExecute(char **command)
{
    puts("pipeExecute");
    char** first = parseInput(command[0]);
    char** second = parseInput(command[1]);
    int pipeCommand[2];
    pipe(pipeCommand);

    int proccess = fork();

    if(proccess == -1)
    {
        puts("Error with fork, plz buy new ones");
    }
    else if(proccess == 0)
    {
        close(STDIN_FILENO);
        dup2(pipeCommand[0], STDIN_FILENO); //for dup2 you need an extra argument
        close(pipeCommand[1]);

        execute(first);

    }
    else
    {
        close(STDOUT_FILENO);
        dup2(pipeCommand[1],STDOUT_FILENO);
        close(pipeCommand[0]);

        execute(second);
    }




}