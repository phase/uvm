typedef struct {
  int length;
  char* data;
} File;

#define INS_LENGTH 32 // Instructions are 32 bits long

typedef struct {
  unsigned char type:2;
  unsigned char opcode:6;
  union {
    struct {
      unsigned char rs:5;
      unsigned char rt:5;
      unsigned char rd:5;
      unsigned char shamt:6;
      unsigned char func:6;
    } r;
    struct {
      unsigned char rs:5;
      unsigned char rt:5;
      unsigned int immediate:16;
    } i;
    struct {
      unsigned int address:26;
    } j;
    unsigned int whole:INS_LENGTH;
  } data;
} Instruction;

typedef struct {
  int length;
  Instruction* instructions;
} InstructionList;

InstructionList readInstructions(File file);
