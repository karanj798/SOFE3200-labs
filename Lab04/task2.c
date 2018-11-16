#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char *readFile (int bytes){ 
    char *buffer = malloc(sizeof(char) * bytes);
    FILE *fp1;
    fp1 = fopen("input.txt", "r");
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
	/*if (argc != 3){
		printf("Invalid Arguments...");
		return -1;
	}*/
    struct stat st;
    stat("input.txt", &st);
    int bytes = st.st_size;
    
    int fd[2];
    pipe(fd);
    char *parentBuff = malloc(sizeof(char) * bytes);
    char *childBuff = malloc(sizeof(char) * bytes);
    int sum = 0;
    

    int res = fork();

    if (res == 0){
        close(fd[0]);
        childBuff = readFile(bytes);
        write(fd[1], childBuff, strlen(childBuff) +1);
        //printf("Child: %s\n", childBuff);
        //printf("x : %d => len : %ld\n", x, strlen(childBuff) + 1);
        
        close(fd[1]);        
    }else{
        
        close(fd[1]);
        sleep(0);
        read(fd[0], parentBuff, bytes);
        //printf("%ld\n", sizeof(childBuff));
        //printf("Parent: %s\n", parentBuff);
        printf("%d\n", getSum(parentBuff));
        //printf("%s", parentBuff);
        close(fd[0]);
    }

    
}
/* Original code 
------------------
while (fgets(buffer, sizeof(buffer), fp1) != NULL){
        for (int i = 0; i < sizeof(buffer); i++){
            if (isdigit(buffer[i])){
                temp[i] = buffer[i];   
            }
             if (buffer[i+1] == '\n' || buffer[i+1] == ' '){
                sum = sum + atoi(temp);
                memset(temp, 0, sizeof(temp));
            }            
        }
    }printf("%d", sum);
*/