#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void replace(char *buffer, char *substr, char *string, int bytesRead)
{
}

int main()
{
    // Declaring file descriptors
    int fd, fd1;

    // Using stat function to get size of the files (bytes = characters)
    struct stat st;
    stat("Input.txt", &st);
    int bytesRead = st.st_size;

    // Initiating character array to read the file.

    char buffer[bytesRead - 1];

    // Handling file I/O
    fd = open("Input.txt", O_RDONLY);
    fd1 = open("Dante.txt", O_WRONLY | O_CREAT, 0600);

    // Error in reading Input.txt file
    if (fd == -1)
    {
        perror("Unable to open Input.txt");
        return -1;
    }
    read(fd, buffer, bytesRead - 1);
    replace(buffer, "Inferno", "Paradisio", bytesRead);
}
