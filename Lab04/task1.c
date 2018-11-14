#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getRandom(int min, int max){	
	return rand() % max;
}

// Random function returns same number for every run....

void createSentence(char *adjective[], char *noun[]){
	char *sentence = malloc(sizeof(char) * 100);
	strcat(sentence, "The ");
	strcat(sentence, adjective[getRandom(0, 5)]);
	strcat(sentence, " ");
	strcat(sentence, adjective[getRandom(0, 5)]);
	strcat(sentence, " ");
	strcat(sentence, noun[getRandom(0, 5)]);
	strcat(sentence, " "); 
	strcat(sentence, "jumped over the "); 
	strcat(sentence, adjective[getRandom(0, 5)]); 
	strcat(sentence, " ");
	strcat(sentence, noun[getRandom(0, 5)]);
	strcat(sentence, ".");	
	printf("%s\n", sentence);
	free(sentence);
}

int main (){
	srand(getpid()); 
	char *noun[5] = { "boy", "girl", "dog", "town", "car"};
	char *adjective[5] = { "aggressive","ambitious", "calm", "eager", "faithful"}; 
	createSentence(adjective, noun);
}