#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Bryce Newton
//OS Project Part 1
//Help from Jerry, Sam, Mike, Ian, Sean, and Ben.
//Using VIM sucks donkey balls

char *PATH;
char **list;

char* pathFinder(char **);
char** getPaths();

int main(int argC, char **argV, char **envP )
{
    printf("Hello, World!"); //for test stuffs

    //find the path
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

}

char* pathFinder(char **envP)
{
    char findPath[] =  "PATH";
    int counterFind=0;
    int x;

    while (envP[counterFind] != NULL)
    {
        for(x = 0; x < 4; x++)
        {
            findPath[x] = envP[counterFind][x]; //looking through enviornment   
        }
        if(strcmp(findPath, "PATH") == 0) //if PATH found in enviorment details
        {
            printf("Find Path \n");
            break;
        }
        counterFind++;
    }

    return envP[counterFind];
}

char** getPaths() {
    
     //first part variables 
     char *path=PATH;
     char **parsed;
     int counterPath = 0;
     path = 5;
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
          if(path[x] == ':' || path[x] == '\0')
	  {
	       counterPath++;
	  }
     }
     counterPath++; //don't understand why. but ben told me to

     path = malloc(counterPath * sizeof(char*)); //allocate memory

     //PART 2 making sure there is enough memory for string
     for(y = 0; y < length; y++)
     {
          if(path[y] ==':' || path[y] == '\0')
          {
               charCounter++;
	       parsed[counterPath] = malloc(charCounter);
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
