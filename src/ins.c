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

Instruction* readInstructions(char* buffer) {
  int length = sizeof(*buffer) / sizeof(buffer[0]);
  // amount of instructions in the buffer
  // this removes any excess bits at the end
  // 32 -> 1, 33 -> 1, 64 -> 2, 65 -> 2, etc.
  int ins_amount = (length - (length % INS_LENGTH)) / INS_LENGTH;
  printf("Ins amount: %d, Buffer length: %d\n", ins_amount, length);
  Instruction* instructions = (Instruction*) malloc(ins_amount * sizeof(Instruction));

  Instruction ins;
  ins_i32 ins_parts;
  for (int i = 0; i < ins_amount * INS_LENGTH; i++) {
    int j = i % 4;
    switch (j) {
      case 0: {
        ins_parts.bits.a = buffer[i];
      } break;
      case 1: {
        ins_parts.bits.b = buffer[i];
      } break;
      case 2: {
          ins_parts.bits.c = buffer[i];
      } break;
      case 3: {
        ins_parts.bits.d = buffer[i];
        ins.data.whole = ins_parts.whole;
        instructions[i] = ins;
      } break;
      default: break;
    }
  }

  return instructions;
}
