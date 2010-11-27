#include <cstdio>
#define DEBUG 1
using namespace std;
int main()
{
// The load file for our machine will consist of pairs of
// numbers separated by a space. The first number indicates 
// a memory location. The second number indicates an instruction.
// The load file is terminated by a -1 in the location place
// and the place where execution is to begin in the instruction
// place. All input data will follow the load file termination line.
// So in our simulation the load information and the input data
// are in the same file.
  unsigned int mem[65536];//smaller memory that address size 
  int acc=0;
  unsigned int pc;
  unsigned int sp; 
  unsigned int loc, inst;
  unsigned int address;
  scanf("%x %x", &loc,&inst);
  while(loc!=-1){
     printf("Location: %x     Instruction: %x\n",loc,inst);
     mem[loc]=inst;  // loads the instruction into memory
     scanf("%x %x", &loc,&inst);
  }
  pc=inst;
  sp=65535; //bottom of memory
  printf("Execution will start in location: %x\n",inst);
  // Your machine simulator starts here. 
 while ((mem[pc] & 0xff000000 )!= 0) { //end if halt op code
    // decode instruction
    // switch based on opcode
    switch (mem[pc] & 0xff000000) {
     case 0x01000000 : // add
          address = mem[pc] & 0x00ffffff;
          acc = acc + mem[address]; 
          #if DEBUG 
          printf("Debug-> ADD acc: %d  address: %x\n",acc,address);
          #endif
          pc++; 
          break;
	 case 0x02000000 : // subtract
		  address = mem[pc] & 0x00ffffff;
		  acc = acc - mem[address]; 
	      #if DEBUG 
		  printf("Debug-> SUB acc: %d  address: %x\n",acc,address);
		  #endif
		  pc++; 
		  break;
      case 0x03000000 : // write word
          address = mem[pc] & 0x00ffffff;
          printf("%x\n",mem[address]);
          #if DEBUG
          printf("Debug-> WRITE acc: %d  address: %x\n",acc,address);
          #endif
          pc++;
          break;
      case 0x05000000 : // load
          address = mem[pc] & 0x00ffffff;
          acc = mem[address];
          #if DEBUG
          printf("Debug-> LOAD acc: %d  address: %x\n",acc,address);
          #endif
          pc++;
          break;
      case 0x06000000 : // store
          address = mem[pc] & 0x00ffffff;
          mem[address] = acc;
          #if DEBUG
          printf("Debug-> STORE acc: %d  address: %x\n",acc,address);
          #endif
          pc++;
          break;
      // rest of instructions go here.               
     default:
            printf("Not a valid instruction.\n");
            pc++; 
   }
 }
 return 0;
}
