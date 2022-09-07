#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 80
#define MAX_FUNCTION_LENGTH 20
static int currentLineCount;
static int currentCharCount;
static int mistakeCount;
static int indentSpaceCount;
static int indentDetectedLength;
static bool isInIndent;
void codingMistake(char *formattedPrint, int lineNumber) {
    printf(formattedPrint,lineNumber);
    mistakeCount+=1;
}
void handleNewLineChar(int* recLineCount) {
    if(currentCharCount>MAX_LINE_LENGTH) {
        codingMistake("LINE LENGTH ERROR ON LINE %d\n",currentLineCount);
    }
    if(indentDetectedLength==0) {
        if(indentSpaceCount!=0) {
            indentDetectedLength = indentSpaceCount;
            printf("detected index length of %d\n",indentDetectedLength);
        }
    }
    else {
        if(indentSpaceCount%indentDetectedLength!=0 && !isInIndent) {
            codingMistake("INDENT ERROR ON LINE %d\n",currentLineCount);
        }
    }
    currentLineCount+=1;
    *recLineCount+=1;
    currentCharCount = 0;
    indentSpaceCount = 0;
    isInIndent = true;
}
void handleChar(char currentChar,int* recLineCount) {
    if(currentChar=='\n') {
        handleNewLineChar(recLineCount);
    }
    else if(currentChar==' ') {
        if(isInIndent) {
            indentSpaceCount+=1;
        }
    }
    else if(isInIndent && currentChar=='	') {
        codingMistake("TABS LOCATED ON LINE %d\n",currentLineCount);
    }
    else {
        isInIndent = false;
        currentCharCount+=1;
    }
}
int checkFileRec(FILE *file, int dept) {
    char currentChar = fgetc(file);
    int recLineCount = 0;
    int startLine = currentLineCount;
    while(currentChar != EOF && currentChar!='}') {
        if(currentChar=='{') {
            recLineCount+=checkFileRec(file,dept+1);
        }
        handleChar(currentChar,&recLineCount);
        currentChar = fgetc(file);
    }
    if(dept != 0 && MAX_FUNCTION_LENGTH < recLineCount) {
        codingMistake("MAX FUNCTION LENGTH DETECTED ON FUNCTION THAT STARTS"
        "ON LINE %d\n",startLine);
    }
    return recLineCount;
}
int main(int argc, char *argv[]) {
    FILE *file;
    if(argc>1 && (file = fopen(argv[1],"r"))) {
        printf("File Found\nReading File\n");
        mistakeCount = 0;
        currentLineCount = 1;
        currentCharCount = 0;
        isInIndent = true;
        checkFileRec(file,0);
        if(mistakeCount==0) {
            printf("great job, no issues found\n");
        }
        else {
            printf("%d problems found with your program\n",mistakeCount);
        }
    }
    else {
        printf("Argument error\nPlease provide the path to a file as an"
        "argument\n");
    }
}