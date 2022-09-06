#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *file;
    if(argc>1 && (file = fopen(argv[1],"r"))) {
        printf("File Found\nReading File\n");
    }
    else {
        printf("Argument error\nPlease provide the path to a file as an argument\n");
    }
}