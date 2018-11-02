#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    int bytesRead;
    int fd[2]; //fd[0] = read, fd[1] = write

    pipe(fd);

    struct stat st;
    stat("AliceInWonderland.txt", &st);
    int bytes = st.st_size;
    char buffer[bytes];
    if (fork() != 0) // parent
    {
        close(fd[1]);
        fd[0] = open("AliceInWonderland.txt", O_RDONLY);
        bytesRead = read(fd[0], buffer, bytes);
        printf("%s", buffer); // Printing Alice.txt
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        fd[1] = open("AliceInWonderland_mod.txt", O_WRONLY | O_CREAT, 0600);
        write(fd[1], "Hello World", strlen("Hello World"));
        close(fd[1]);
    }
}