#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getRandom(int min, int max){	
	return rand() % max;
}

void createSentence(char *adjective[], char *noun[]){
	printf("The %s %s %s jumped over the %s %s.\n",adjective[getRandom(0, 5)], adjective[getRandom(0, 5)], noun[getRandom(0, 5)], adjective[getRandom(0, 5)], noun[getRandom(0, 5)]);
}

int main (){
	srand(getpid()); 
	char *noun[5] = { "boy", "girl", "dog", "town", "car"};
	char *adjective[5] = { "aggressive","ambitious", "calm", "eager", "faithful"}; 
	createSentence(adjective, noun);
}