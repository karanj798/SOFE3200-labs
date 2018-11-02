#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *replace(char *str, char *orig, char *rep)
{
    char *tempBuf = 0;             //unknown length
    tempBuf = malloc(strlen(str)); //set to current length of buffer

    int runSentinal = 1; // run until all instances of word has been found
    while (runSentinal == 1)
    {
        char *p = strstr(str, orig); //Find end of first occurance
        if (p == NULL)               //If DNE, then don't continue running
        {
            runSentinal = 0;
            return str;
        }
        int diff = strlen(rep) - strlen(orig); //Find out if the target char is larger/smaller

        tempBuf = malloc(strlen(str) + diff - 1); //change size of buffer accordingly
        int index = p - str;
        strncpy(tempBuf, str, index); // Copy characters from str up to the start of
        sprintf(tempBuf + index, "%s%s", rep, p + strlen(orig));
        strcpy(str, tempBuf); //copy buffer to original string
    }
    return tempBuf;
}

int main()
{
    int bytesRead;
    int fd[2], fd1, fd2; //fd[0] = read, fd[1] = write
    fd1 = open("AliceInWonderland.txt", O_RDONLY);
    fd2 = open("Dante.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    pipe(fd);

    struct stat st;
    stat("AliceInWonderland.txt", &st);
    int bytes = st.st_size;
    char parentBuffer[bytes];
    char childBuffer[bytes];
    clock_t start = clock();

    if (fork() != 0) // parent
    {
        close(fd[0]); // Close read end
        bytesRead = read(fd1, parentBuffer, bytes);
        write(fd[1], parentBuffer, bytesRead); //Writing to pipe
        close(fd[1]);                          // Close write end
    }
    else
    {                 // child
        close(fd[1]); // Close write end
        read(fd[0], childBuffer, sizeof(childBuffer));
        close(fd[0]); // Close read end
        replace(childBuffer, "Inferno", "Paradisio");
        replace(childBuffer, "In dark woods", "using Windows 8.1");
        replace(childBuffer, "those woods", "Windows 8.1");
        replace(childBuffer, "to enter", "to use 8.1");
        replace(childBuffer, "crest", "screen");
        replace(childBuffer, "Below a hill", "Before a monitor");
        replace(childBuffer, "shoulders", "GUI");
        replace(childBuffer, "planet", "UNIX");

        write(fd2, childBuffer, sizeof(childBuffer));
        close(fd[0]);
    }
    clock_t end = clock();
    float sec = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %fs ", sec);
}