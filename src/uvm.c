#include <stdio.h>
#include <stdlib.h>
#include "ins.h"

File readFile(char* fileName) {
  FILE* fileptr;
  char* buffer;
  long filelen;

  fileptr = fopen(fileName, "rb");
  fseek(fileptr, 0, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);

  buffer = (char*) malloc(filelen * sizeof(char));
  fread(buffer, filelen, 1, fileptr);
  fclose(fileptr);
  File file;
  file.length = filelen;
  file.data = buffer;
  return file;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("%s <file>\n", argv[0]);
  }
  else {
    File file = readFile(argv[1]);
    InstructionList instructions = readInstructions(file);

    for (int i = 0; i < instructions.length; i++) {
      Instruction ins = instructions.instructions[i];
      printf("Ins#%x: %08x\n", i, ins.data.whole);
    }
  }
  return 0;
}
