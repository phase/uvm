#include <stdio.h>
#include <stdlib.h>
#include "ins.h"

typedef union {
  struct {
    unsigned int a:8;
    unsigned int b:8;
    unsigned int c:8;
    unsigned int d:8;
  } bits;
  unsigned int whole:INS_LENGTH;
} ins_i32;

InstructionList readInstructions(File file) {
  // amount of instructions in the buffer
  // this removes any excess bits at the end
  // 32 -> 1, 33 -> 1, 64 -> 2, 65 -> 2, etc.
  int ins_amount = (file.length - (file.length % INS_LENGTH)) / INS_LENGTH;
  printf("Ins amount: %d, Buffer length: %d\n", ins_amount, file.length);
  Instruction* instructions = (Instruction*) malloc(ins_amount * sizeof(Instruction));

  Instruction ins;
  ins_i32 ins_parts;
  int ins_length;
  for (int i = 0; i < ins_amount * INS_LENGTH; i++) {
    int j = i % 4;
    switch (j) {
      case 0: ins_parts.bits.a = file.data[i]; break;
      case 1: ins_parts.bits.b = file.data[i]; break;
      case 2: ins_parts.bits.c = file.data[i]; break;
      case 3:
        ins_parts.bits.d = file.data[i];
        ins.data.whole = ins_parts.whole;
        instructions[ins_length] = ins;
        ins_length++;
        break;
      default: break;
    }
  }

  InstructionList instructionList;
  instructionList.instructions = instructions;
  instructionList.length = ins_length;
  return instructionList;
}
