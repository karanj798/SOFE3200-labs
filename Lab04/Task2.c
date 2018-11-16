#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{

    int fdread, fdwrite;
    int pipefd[2]; // read & write end descriptor of pipe
    int pid;       //process id
    int readTransfer, writeTransfer;
    int bytes;
    int sizeCounter = 0;
    pipe(pipefd); //create pipe using

    pid = fork(); // create child process

    /* Are src and dest file name arguments missing */
    if (argc != 3)
    {
        printf("Usage: cp file1 file2");
        return 1;
    }


    // Child process : find & replace the words, and also write to file.
    if (pid == 0)
    {
        close(pipefd[READ]);                      //closing read end of pipe
        fdread = open(argv[1], O_RDONLY);         // Open file as read only and return it to file descriptor fd

        printf("Read descriptor -> %i\n", fdread);
        if (fdread == -1) // check if the file exist in file descripter
        {
            perror("could not open input.txt");
            return -1;
        }

        struct stat fileStats;               // declearing stat structure as fileStats
        int err = fstat(fdread, &fileStats); // obtains information about the file in the file descripter
        bytes = fileStats.st_size;

        char data[bytes]; // create a char array of size equivalent to file size of file descripter fd
        for (int i = 0; i < sizeof(data); i++)
        {
            data[i] = '\0';
        }

        //int *aPtr = malloc(sizeof(int)); // Start with 1 string

        // dynamic char array
        char **aPtr;
        int len = 1;                         // Start with 1 string
        aPtr = malloc(sizeof(char *) * len); // Do not cast malloc in C
        aPtr[0] = malloc(100);
        // Do not cast malloc in C
        //aPtr[0] = "This is a test";
        //aPtr[1] = "This is a test 2";
        //printf("asdsads%s\n", aPtr[1]); // This should work now.

        int k = 0;
        
        int input[123];
        read(fdread, data, sizeof(data)); // Read from file and set each character to data array

        int total_n = 0;
        int n;
        int i;

        int numListsizeCounter = 0;
        while (1 == sscanf(data + total_n, "%*[^0123456789]%d%n", &i, &n) && data != '\0')
        {
            total_n += n;
            printf("Extracted > %d\n", i);
            char sNum[40];
            sprintf(sNum, "%d", i); // int to string

            aPtr[sizeCounter] = malloc(100);
            strcpy(aPtr[sizeCounter], sNum);
            sizeCounter++;
        }

        printf("Length of array is : %d\n", sizeCounter);

        char *sCombine = malloc(sizeof(char));
        for (int i = 0; i < sizeCounter; i++)
        {
            strcat(sCombine, aPtr[i]);
            if (i != sizeCounter - 1)
            {
                strcat(sCombine, "/");
            }
        }

        printf("String to be Passed : %s ;; String size: %ld\n", sCombine, strlen(sCombine));

        //printf("size, length: %ld, %ld\n", sizeof(num), strlen(num));
        //write(pipefd[WRITE], (int)strlen(sCombine),5); // write to pipe
        write(pipefd[WRITE], sCombine, strlen(sCombine)); // write to pipe
        close(WRITE);                                     // close read file descriptor
    }
    else
    {                         // Parent process
        close(pipefd[WRITE]); //closing write end of pipe
        int numset[10];

        printf("Size of NUM parent: %ld\n", sizeof(numset));

        fdwrite = open(argv[2], O_WRONLY | O_CREAT, 0644); // Open/create file as write only and return to file descriptor fdWrite
        printf("Write descriptor -> %i\n", fdwrite);

        write(fdwrite, numset, sizeof(numset)); // write modified data to file fdWrite file descripter

        sleep(0); // wait for the child process to finish and return a char of numbers
        char *num = malloc(sizeof(char));
        int bufSize;

        //read(pipefd[READ], bufSize, 5);
        readTransfer = read(pipefd[READ], num, 1000);
        //printf("transfered to parent: %s\n", num);
        printf("\nWhat is passed >>: %s\n", num);
        printf("Passed Size >>: %d\n", readTransfer);

        //SPLIT num sting by "/" and convert it into int and stor in NumIntList
        int NumIntList[100];

        const char splitter[2] = "/";
        int i = 0;

        char *end;
        long number = 0; // There is no point in making "number" a pointer
        char *token = strtok(num, splitter);
        while (token != NULL)
        {
            NumIntList[i] = atoi(token);
            i++;
            number += strtol(token, &end, 0);
            token = strtok(NULL, splitter);
        }

        printf("\n\nAfter Split: \n");
        int sum = 0;
        for (int j = 0; j < i; j++)
        {
            printf("%d\n", NumIntList[j]);
            sum += NumIntList[j];
        }

        printf("\nSum: %d\n", sum);

        // Print to file from argument
        char *printStringToFile = malloc(sizeof(char));
        //char printStringToFile[200] = {0};
        sprintf(printStringToFile, "%s%s%s %d\n", "The sum of the numbers from the file: '", argv[1], "' is : ", sum); // creating a formated string to output
        printf("%s", printStringToFile);
        write(fdwrite, printStringToFile, strlen(printStringToFile));

        /*strcpy(printStringToFile, "The sum of the numbers from the file: ");
        strcat(printStringToFile, argv[1]);
        strcat(printStringToFile, "is : ");
        char sSum[10];
        sprintf(sSum, "%d", sum); // int to string
        strcat(printStringToFile, sSum);

        printf("%s", printStringToFile);
         */

        close(fdwrite); // close write file descriptor
        close(pipefd[READ]);
    }
}