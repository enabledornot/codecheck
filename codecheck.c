#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 80
static int currentLineCount;
static int currentCharCount;
void handleChar(char currentChar) {
    if(currentChar=='\n') {
        if(currentCharCount>MAX_LINE_LENGTH) {
            printf("LINE LENGTH ERROR ON LINE %d\n",currentLineCount);
        }
        currentLineCount+=1;
        currentCharCount = 0;
    }
    else {
        currentCharCount+=1;
    }
}
void checkFile(FILE *file) {
    char currentChar = fgetc(file);
    currentLineCount = 1;
    currentCharCount = 0;
    while(currentChar != EOF) {
        handleChar(currentChar);
        currentChar = fgetc(file);
    }
    handleChar('\n');
    printf("\n");
}
int main(int argc, char *argv[]) {
    FILE *file;
    if(argc>1 && (file = fopen(argv[1],"r"))) {
        printf("File Found\nReading File\n");
        checkFile(file);
    }
    else {
        printf("Argument error\nPlease provide the path to a file as an argument\n");
    }
}