#include <stdio.h>
#include <stdlib.h>
#include "ins.h"

char* readFile(char* fileName) {
  FILE* fileptr;
  char* buffer;
  long filelen;

  fileptr = fopen(fileName, "rb");
  fseek(fileptr, 0, SEEK_END);
  filelen = ftell(fileptr);
  printf("File length: %ld", filelen);
  rewind(fileptr);

  buffer = (char*) malloc(filelen * sizeof(char));
  fread(buffer, filelen, 1, fileptr);
  fclose(fileptr);
  return buffer;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("%s <file>\n", argv[0]);
  }
  else {
    char* buffer = readFile(argv[1]);

    Instruction* instructions = readInstructions(buffer);
    int length = sizeof(instructions) / sizeof(instructions[0]);
    free(buffer);

    for (int i = 0; i < length; i++) {
      Instruction ins = instructions[i];
      printf("Ins: %x\n", ins.data.whole);
    }
  }
  return 0;
}
