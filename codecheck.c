#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 80

static int currentLineCount;
static int currentCharCount;
static int mistakeCount;
static int indentSpaceCount;
static int indentDetectedLength;
static bool isInIndent;
void handleNewLineChar() {
    if(currentCharCount>MAX_LINE_LENGTH) {
        printf("LINE LENGTH ERROR ON LINE %d\n",currentLineCount);
        mistakeCount+=1;
    }
    if(indentDetectedLength==0) {
        if(indentSpaceCount!=0) {
            indentDetectedLength = indentSpaceCount;
            printf("detected index length of %d\n",indentDetectedLength);
        }
    }
    else {
        if(indentSpaceCount%indentDetectedLength!=0 && isInIndent) {
            printf("INDENT ERROR ON LINE %d\n",currentLineCount);
            mistakeCount+=1;
        }
    }
    currentLineCount+=1;
    currentCharCount = 0;
    indentSpaceCount = 0;
    isInIndent = true;
}
void handleChar(char currentChar) {
    if(currentChar=='\n') {
        handleNewLineChar();
    }
    else if(currentChar==' ') {
        if(isInIndent) {
            indentSpaceCount+=1;
        }
    }
    else if(isInIndent && currentChar=='	') {
        printf("TABS LOCATED ON LINE %d\n",currentLineCount);
        mistakeCount+=1;
    }
    else {
        isInIndent = false;
        currentCharCount+=1;
    }
}
void checkFile(FILE *file) {
    char currentChar = fgetc(file);
    currentLineCount = 1;
    currentCharCount = 0;
    isInIndent = true;
    while(currentChar != EOF) {
        handleChar(currentChar);
        currentChar = fgetc(file);
    }
    handleChar('\n');
    if(mistakeCount==0) {
        printf("great job, no issues found\n");
    }
    else {
        printf("%d problems found with your program\n",mistakeCount);
    }
}
int main(int argc, char *argv[]) {
    FILE *file;
    if(argc>1 && (file = fopen(argv[1],"r"))) {
        printf("File Found\nReading File\n");
        checkFile(file);
    }
    else {
        printf("Argument error\nPlease provide the path to a file as an"
        "argument\n");
    }
}