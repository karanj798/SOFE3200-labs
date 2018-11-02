#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

char *replace(char*str, char*orig, char*rep)
{
   char *tempBuf = 0; //unknown length
   tempBuf = malloc(strlen(str)); //set to current length of buffer


   int runSentinal = 1; // run until all instances of word has been found
   while (runSentinal == 1) {

      char *p = strstr(str, orig); //Find end of first occurance
      if (p == NULL) //If DNE, then don't continue running
      {
         runSentinal = 0; 
         return str;
      }
      int diff = strlen(rep) - strlen(orig); //Find out if the target char is larger/smaller


      


      tempBuf = malloc(strlen(str) + diff);//change size of buffer accordingly
      int index = p - str;
      strncpy(tempBuf, str, index); // Copy characters from str up to the start of
    
      sprintf(tempBuf + index, "%s%s", rep, p + strlen(orig));
      //printf("NEW REPLACEMENT\n");
      //printf("%s\n", tempBuf);


      strcpy(str, tempBuf); //copy buffer to original string


      
   }

   return tempBuf;
}

int main()
{

    // Declaring file descriptors
    int fd, fd1;
    char* buffer = 0;

    // Using stat function to get size of the files (bytes = characters)
    struct stat st;
    stat("Input.txt", &st);
    int bytesRead = st.st_size;

    // Initiating character array to read the file.

    buffer = malloc(bytesRead);
    // Handling file I/O
    fd = open("Input.txt", O_RDONLY);
    fd1 = open("Dante.txt", O_WRONLY | O_CREAT, 0600);

    // Error in reading Input.txt file
    if (fd == -1)
    {
        perror("Unable to open Input.txt");
        return -1;
    }
    read(fd, buffer, bytesRead - 1); //read file into buffer


    replace(buffer, "Inferno", "Paradisioooooooooooooooooooooooooooooooooooooooo");
    replace(buffer, "In dark woods", "using Windows 8.111111111111111111111");
    replace(buffer, "those woods", "Windows 8.11111111111111111111111");
    replace(buffer, "to enter", "to use 8.1");
    replace(buffer, "crest", "screen");
    replace(buffer, "Below a hill", "Before a monitor");
    replace(buffer, "shoulders", "GUI");
    replace(buffer, "planet", "UNIX");


    write(fd1, buffer, strlen(buffer));


    

}
