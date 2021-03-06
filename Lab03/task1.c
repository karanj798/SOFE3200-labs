#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main()
{
    // Declaring file descriptors
    int fd, fd1;

    // Using stat function to get size of the files (bytes = characters)
    struct stat st;
    stat("Input.txt", &st);
    int bytesRead = st.st_size;

    // Initiating character array to read the file.
    char buffer[bytesRead];

    // Handling file I/O
    fd = open("Input.txt", O_RDONLY);
    fd1 = open("Heaven.txt", O_WRONLY | O_CREAT, 0600);

    // Error in reading Input.txt file
    if (fd == -1)
    {
        perror("Unable to open Input.txt");
        return -1;
    }
    else
    {
        // Reading characters and changing a's to b's.
        read(fd, buffer, sizeof(buffer) - 1);
        for (int i = 0; i < bytesRead; i++)
        {
            if (buffer[i] == 'a')
            {
                buffer[i] = 'b';
            }
            if (buffer[i] == 'A')
            {
                buffer[i] = 'B';
            }
        }
        // Writing modified characters.
        write(fd1, buffer, bytesRead - 1);
    }
}
