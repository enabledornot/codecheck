#include <stdio.h>
#include <stdlib.h>
void checkFile(FILE *file) {
    char currentChar = fgetc(file);
    int lineCount = 0;
    int charCount = 0;
    while(currentChar != EOF) {
        if(currentChar=='\n') {
            printf("Line %d Count %d\n",lineCount,charCount);
            lineCount+=1;
            charCount = 0;
        }
        else {
            charCount+=1;
        }
        currentChar = fgetc(file);
    }
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