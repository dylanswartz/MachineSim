// Dylan Swartz
// CS331 Fall 2010
// Machine Simulator

#include <cstdio>      
#define DEBUG 0 
#define MEM_BOTTOM 65535
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
    unsigned int mem[MEM_BOTTOM + 1];//smaller memory that address size
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
    pc = inst;
    sp = MEM_BOTTOM; //bottom of memory
    printf("Execution will start in location: %x\n",inst);
    // Your machine simulator starts here.
    while ((mem[pc] & 0xff000000 )!= 0) { //end if halt op code
        #if DEBUG
            printf("Debug-> Program Counter: %x\n", pc);
        #endif
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
                printf("%x\n",mem[address]);// write in hex
                //printf("%d\n",mem[address]);  // write in decimal
                #if DEBUG
                    printf("Debug-> WRITE acc: %d  address: %x\n",acc,address);
                #endif
                pc++;
                break;
            case 0x04000000 : // read
                address = mem[pc] & 0x00ffffff;
                scanf("%x", &mem[address]);
                #if DEBUG
                    printf("Debug-> READ address: %x value: %x\n",address,
                                                                  mem[address]);
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
            case 0x07000000 : // goto
                address = mem[pc] & 0x00ffffff;
                pc = address;   // move pc to address
                #if DEBUG
                    printf("Debug-> PC moved to %x\n",pc);
                #endif
                break;
            case 0x08000000 : // bp (branch if positive)
                #if DEBUG
                    printf("Debug-> PC before branch: %x\n",pc);
                #endif
                if (acc > 0) {
                    address = mem[pc] & 0x00ffffff;
                    pc = address;   // move pc to address
                } else {
                    pc++;
                }
                #if DEBUG
                    printf("Debug-> PC after branch: %x\n",pc);
                #endif
                break;
           case 0x09000000 : // bn (branch if negitive)
                #if DEBUG
                    printf("Debug-> PC before branch: %x\n",pc);
                #endif
                if (acc < 0) {
                    address = mem[pc] & 0x00ffffff;
                    pc = address;   // move pc to address
                } else {
                    pc++;
                }
                #if DEBUG
                    printf("Debug-> PC after branch: %x\n",pc);
                #endif
                break;
            case 0x0a000000 : // bz (branch if zero)
                #if DEBUG
                    printf("Debug-> PC before branch: %x\n",pc);
                #endif
                if (acc == 0) {
                    address = mem[pc] & 0x00ffffff;
                    pc = address;   // move pc to address
                } else {
                    pc++;
                }
                #if DEBUG
                    printf("Debug-> PC after branch: %x\n",pc);
                #endif
                break;
                
                /* STACK COMMANDS HERE */
            case 0x0b000000 : // gosub (push address of next instruction onto
                              // the stack)
                sp--; // remember we are working from the bottom up
                mem[sp] = pc + 1; // address of next instruction
                #if DEBUG
                    printf("Debug-> GOSUB top: %x\n", mem[sp]);
                #endif
                pc++;
                break;

            case 0x0c000000 : // retsub (set pc to top of stack)
                pc = mem[sp];
                if (sp < MEM_BOTTOM) {
                    sp++;
                    #if DEBUG
                        printf("Debug-> GOSUB pc:%x\n", sp-1, sp);
                    #endif
                } else {
                    printf("Nothing to pop.");
                    pc++;
                }
                break;

            case 0x0d000000 : //push
                sp--; // remember we are working from the bottom up
                address = mem[pc] & 0x00ffffff;
                mem[sp] = mem[address];
                #if DEBUG
                    printf("Debug-> PUSH top: %x address: %x\n", mem[sp],
                                                                 address);
                #endif
                pc++;
                break;

            case 0x0e000000 : //pop
                if (sp < MEM_BOTTOM) {
                    sp++;
                    #if DEBUG
                        printf("Debug-> POP sp was:%d sp is:%d\n", sp-1, sp);
                    #endif
                } else {
                    printf("Nothing to pop.\n");
                }
                pc++;
                break;

            case 0x0f000000 : //top
                address = mem[pc] & 0x00ffffff;
                mem[address] = mem[sp];
                #if DEBUG
                    printf("Debug-> TOP: top: %x address: %x\n", mem[sp],
                                                                 address);
                #endif
                pc++;
                break;

            case 0x10000000 : // mult (multiply)
                address = mem[pc] & 0x00ffffff;
                acc = acc * mem[address];
                #if DEBUG
                    printf("Debug-> MULT acc: %d  address: %x\n",acc,address);
                #endif
                pc++;
                break;

            case 0x11000000 : // div (divide)
                address = mem[pc] & 0x00ffffff;
                #if DEBUG
                    printf("Debug-> divide %d by %d\n",acc,mem[address]);
                #endif
                acc = acc / mem[address];
                #if DEBUG
                    printf("Debug-> DIV acc: %d  address: %x\n",acc,address);
                #endif
                pc++;
                break;

            case 0x12000000 : // rem (modulus)
                address = mem[pc] & 0x00ffffff;
                acc = acc % mem[address];
                #if DEBUG
                    printf("Debug-> DIV acc: %d  address: %x\n",acc,address);
                #endif
                pc++;
                break;

            // EXTRA CREDIT COMMADS

            case 0x13000000 : // inc (increment ACC)
                acc++;
                #if DEBUG
                    printf("Debug-> INC acc: %d\n",acc);
                #endif
                pc++;
                break;

            case 0x14000000 : // dec (decrement ACC)
                acc--;
                #if DEBUG
                    printf("Debug-> DEC acc: %d\n",acc);
                #endif
                pc++;
                break;

            case 0x15000000 : // STKEMP (empty stack)
                sp = MEM_BOTTOM;
                #if DEBUG
                    printf("Debug-> STKEMP sp: %d\n", sp);
                #endif
                pc++;
                break;
                
            default:
                printf("Not a valid instruction.\n");
                pc++;
        }
    }
    return 0;
}
