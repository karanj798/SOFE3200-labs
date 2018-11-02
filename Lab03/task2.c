#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

char *replace_str(char *str, char *orig, char *rep)
{
    static char buffer[729];
    char *p = strstr(str, orig); //Finds the index at which orig is at in str pointer.
    if (p == NULL)
    {
        return str;
    }
    int index = p - str;         // Basic Pointer subtraction.
    strncpy(buffer, str, index); // Copy characters from str start to buffer
    buffer[index] = '\0';        // Create more null character for bigger word to replace with.
    sprintf(buffer + index, "%s%s", rep, p + strlen(orig));

    strcpy(str, buffer);
    return buffer;
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
    replace_str(buffer, "Inferno", "Paradisio");
    replace_str(buffer, "In dark woods", "using Windows 8.1");
    replace_str(buffer, "those woods", "Windows 8.1");
    replace_str(buffer, "to enter", "to use 8.1");
    replace_str(buffer, "crest", "screen");
    replace_str(buffer, "Below a hill", "Before a monitor");
    replace_str(buffer, "shoulders", "GUI");
    replace_str(buffer, "planet", "UNIX");
    replace_str(buffer, "dante", "Shakespeare");

    write(fd1, buffer, 734);
}
