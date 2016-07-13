#include <stdio.h>
#include <stdlib.h>

typedef char byte;

byte* readFile(char* fileName) {
    FILE *fileptr;
    byte *buffer;
    long filelen;

    fileptr = fopen(fileName, "rb");
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

    buffer = (byte*)malloc(filelen * sizeof(byte));
    fread(buffer, filelen, 1, fileptr);
    fclose(fileptr);
    return buffer;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("You need to specify the file to run!\n");
    }
    else {
        byte* buffer = readFile(argv[1]);

        for(int i = 0; buffer[i] != 0; i++) {
            printf("%x\n", buffer[i]);
        }
    }
    return 0;
}
