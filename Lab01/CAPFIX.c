#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 This function scans the text file and returns the total number of lines.
*/
int ReadData (FILE *fpt, char first[20][30], char last [20][30]){
    int total = 0;
    while (1) {
        // Scanning the file, and storing the last and first names into arrays.
		if (fscanf(fpt,"%s %s",last[total],first[total]) != 2)
			break;
		total++;
	}
    return total;
}

/*
 This function fixes the upper and lower case of word array.
*/
void CapFix (char word [30]){
    int j;
    // Compare the ascii number with first character in the array.
    if (word[0] >= 'a' && word[0] <= 'z'){
	// Converting character to uppercase.
        word[0]=word[0]-'a'+'A';
    }
    // Iterating through every character after the first character.
    for (j=1; j<strlen(word); j++){
	// Converting character to lowercase.
	if (word[j] >= 'A' && word[j] <= 'Z'){
		word[j]=word[j]-'A'+'a';
        }
    }
}

int main(int argc, char *argv[]) {
	FILE *fpt;
	char first[20][30],last[20][30];
	int i,j;

	if (argc != 2) {
		printf("Usage: CAPFIX [filename]\n");
		exit(0);
	}

	if ((fpt=fopen(argv[1],"r")) == NULL) {
		printf("Unable to open %s for reading\n",argv[1]);
		exit(0);
	}
    int total = ReadData(&*fpt, first, last);
	for (i=0; i<total; i++) {
	    CapFix(first[i]);
            CapFix(last[i]);
    }
	for (i=0; i<total; i++)
		printf("%s %s\n",first[i],last[i]);

	fclose(fpt);
}

