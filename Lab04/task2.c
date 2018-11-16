#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char *readFile (int bytes, char *fname){ 
    char *buffer = malloc(sizeof(char) * bytes);
    FILE *fp1;
    fp1 = fopen(fname, "r");
    int sum=0;
    char *temp = malloc(sizeof(char) * bytes);
    char *sumBuffer = malloc(sizeof(char) * bytes);
    while (fgets(buffer, sizeof(buffer), fp1) != NULL){
        for (int i = 0; i < sizeof(buffer); i++){
            if (isdigit(buffer[i])){
                temp[i] = buffer[i];   
            }
            else{
                strcat(sumBuffer, temp);
                memset(temp, 0, sizeof(temp));
                
            }
        }
       strcat(sumBuffer, " ");
    }
    return sumBuffer;
}

int getSum(char *buffer){
    int sum=0;
    char *token = strtok(buffer, " ");
    while(token) {
        sum = sum + atoi(token);
        token = strtok(NULL, " ");
    }
    return sum;
}


int main(int argc, char *argv[]) {
    // Arguments validation
	if (argc != 3){
		printf("Invalid Arguments...\n");
        printf("Usage\n-----\n./a.out file1.txt file2.txt\n");
		return -1;
	}
    // Getting size of the file.
    struct stat st;
    stat(argv[1], &st);
    int bytes = st.st_size;
    
    int fd[2];    
    char *parentBuff = malloc(sizeof(char) * bytes);
    char *childBuff = malloc(sizeof(char) * bytes);
    int sum = 0;

   

    // Piping Process...
    pipe(fd);
    printf("Reading File Descriptor: %d\n", fd[0]);
    printf("Writing File Descriptor: %d\n", fd[1]);
    
    int res = fork(); // Create new process. 
    
    if (res == 0){        //Child
        close(fd[0]);
        childBuff = readFile(bytes, argv[1]); // readFile function returns integers.
        write(fd[1], childBuff, strlen(childBuff) +1);   // writing to pipe.     
        close(fd[1]);        
    }else{               // Parent  
        close(fd[1]);
        sleep(0); // stoping parent process so, child runs first.
        read(fd[0], parentBuff, bytes); // reading pipe
        printf("Sum of integers: %d\n", getSum(parentBuff));
        close(fd[0]);
    }    
}