#include <stdio.h>
#include <string.h>

#include "supportingFiles/conversions.h"
#include "supportingFiles/rTypeOperation.h"

//global register array
const char *registerfile[32] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15","R16","R17","R18","R19","R20","R21","R22","R23","R24","R25","R26","R27","R28","R29","R30","R31"};
// int registerfile[32] = { };
const char *register_name[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

int pc = 0; //pc counter to be incremented
int next_pc = 0; //
int jump_target = 0; //used to jump to a target
int alu_zero = 0;   //had to used "_" rather than "-" as it thought a subtraction was being done
int branch_target = 0;

// int alu_op = 0;    //used for the alu operation code within execute
int alu_op;
int dMem[32] = { };
int total_clock_cycles = 0;





int Rtype(int code[]){              //Uriel Montes
/*
add     10 0000 (funct)
addu    10 0001 (funct)
and     10 0100 (funct)
jr      00 1000 (funct)
nor     10 0111 (funct)
or      10 0101 (funct)
slt     10 1010 (funct)
sltu    10 1011 (funct)
sll     00 0000 (funct) also uses shamt
srl     00 0010 (funct) also uses shamt
sub     10 0010 (funct)
subu    10 0011 (funct)
*/
    int opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);
    if (opcode == 0){  // checking if rtype or not
        printf("Instruction type: R\n");

        int funct = SixConvert(code[26], code[27], code[28], code[29], code[30], code[31]);
        operation(funct);

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        int rd = FiveConvert(code[16], code[17], code[18],code[19],code[20]);
        printf("Rd: %s (%s)\n", register_name[rd], registerfile[rd]);

        int shamt = FiveConvert(code[21], code[22], code[23],code[24],code[25]);
        printf("Shamt: %d\n", shamt);
  
        printf("Funct: %d\n", funct);

        execute(funct, alu_op, rs,  rt,  rd,  shamt, 0);
        
        printf("\n");

    } else{
        return 0;
    }
}

int Itype(int code[]){      //John Villalvazo
    /*
    addi    001000  -8
    addui   001001  -9
    andi    001100  -12
    beq     000100  -4
    bne     000101  -5
    lbu     100100  -36
    lhu     100101  -37
    ll      110000  -48
    lui     001111  -15
    lw      100011  -35
    ori     001101  -13
    slti    001010  -10
    sltiu   001011  -11
    sb      101000  -40
    sc      111000  -56
    sh      101001  -41
    sw      101011  -43
    */

   /*
    rs = register source
    rt = 2nd register source
   */

    //00100000100001010000000000000000 <- test machine code
    int opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);

    if (opcode == 8){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): addi\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
            int value = registerfile[rt] + immediate;
            printf("Value of rs is %x\n", value);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
            
            int value = &registerfile[rt] + immediate;
            printf("Value of rs is %d\n", value);
        }


    }else if (opcode == 9){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): addiu");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 12){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): andi\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 4){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): beq\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            // jump_target = (sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]) <<  2) + next_pc;    //(Immediate * 4) + pc

            printf("Immediate: %d\n", immediate);
            
            // printf("Jump Target: %d\n", jump_target);
            execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            // jump_target = (sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]) <<  2) + next_pc;    //(Immediate * 4) + pc

            printf("Immediate: -%d\n", immediate);
            // printf("Jump Target: %d\n", jump_target);
            execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
        }

    }else if(opcode == 5){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): bne\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 36){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lbu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 37){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lhu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 48){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ll\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 15){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lui\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 35){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lw\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);

            Mem(opcode, immediate + rs, rt);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);

            Mem(opcode, immediate + rs, rt);
        }

    }else if(opcode == 13){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ori\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 10){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): slti\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 11){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sltiu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 40){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sb\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 56){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sc\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 41){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sh\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);
        }

    }else if(opcode == 43){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sw\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], registerfile[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], registerfile[rt]);

        if (code[16] == 0) {
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("Immediate: %d\n", immediate);

            Mem(opcode, immediate + rs, rt);
        }
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("Immediate: -%d\n", immediate);

            Mem(opcode, immediate + rs, rt);
        }

    }else {
        return 0;
    }
    return 0;
}

int Jtype(int code[]){  //Uriel Montes
/*
j       000010
jal     000010
*/
    int opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);

    if (opcode == 2){
        printf("Instruction type: J\n");
        printf("Operation: j\n");

        int address = twosixConverter(code[6],code[7],code[8],code[9],code[10],code[11],code[12],code[13],code[14],code[15],code[16],code[17],code[18],code[19],code[20],code[21],code[22],code[23],code[24],code[25],code[26],code[27],code[28],code[29],code[30],code[31]);
        printf("Address: %d\n", address);


    }

    else if (opcode == 3){
        printf("Instruction type: J\n");
        printf("Operation: jal\n");

        int address = twosixConverter(code[6],code[7],code[8],code[9],code[10],code[11],code[12],code[13],code[14],code[15],code[16],code[17],code[18],code[19],code[20],code[21],code[22],code[23],code[24],code[25],code[26],code[27],code[28],code[29],code[30],code[31]);
        printf("Address: %d\n", address);
    }

    else{
        return 0;
    }
    return 0;
}

int fetch(FILE *ptr, char var[32], int code[32]){
    // int i = 0;
     if ( ptr == NULL ){
        printf( "sample_binary.c file failed to open." ) ;
    } else {
        for(int k = 1; k < 9; k++){
            // printf("total_clock_cycles %d:\n", total_clock_cycles);
            printf("total_clock_cycle decided by fetch(): %d\n", k);
            // printf("Enter an instruction in machine code:\n");
            if(fgets ( var, 33, ptr) != NULL){
                pc = pc + 4;
                printf("pc value is: %d\n", pc);    //wanted to see the pc value
                fscanf(ptr, "%[^\n]", var);   //reads number as a "word" then breaks it down to digits

                printf("%s", var);

                int next_pc = pc + 4;

                /* ! We will discuss later but the branch target and jump target addresses
                will be updated by the other functions to “branch_target” and “jump_target”. So, add a logic
                in this Fetch() function that copies one of the three possible pc values (next_pc,
                branch_target, and jump_target) to pc variable. This updated pc value will be used for the
                next instruction fetch
                */
               
                //! need to find the sign-extension within the Immediate type

                for (int i = 0; i < 32; i++){
                    code[i] = var[i] - '0'; //convert the char into a digit
                }

                printf("\n");

                Rtype(code);    //these is the decode() functions that are embedded within fetch()
                Itype(code);    //these is the decode() functions that are embedded within fetch()
                Jtype(code);    //these is the decode() functions that are embedded within fetch()
            }

            printf("------------------\n");
            
        }
        // Closing the file using fclose()
        fclose(ptr) ;
    }
    return 0;

}



int execute(int funct, int alu_op, int rs, int rt, int rd, int shamt, int immediate){
    //! what is the purpose of alu_zero??
    //! note that we will shortly transition to "alu_op" code to start choosing which loop to trigger

    if(funct == 32){ //add
        int four = 0;
        int three = 0;
        int two = 1;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        int destination = rs + rt;
        alu_zero = 0;
        // int destination = *registerfile[rs] + *registerfile[rt];
        
        // printf("The value of destination is %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 33){ //addu
        int four = 0;
        int three = 0;
        int two = 1;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        int destination = rs + rt;
        alu_zero = 0;
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 36){ //and
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        alu_zero = 0;
        int destination = rs & rt;
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 8){  //jr 
        int four = 0;
        int three = 0;
        int two = 1;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        pc = rs;
        alu_zero = 0;
        printf("pc is modified to 0x%x\n",pc);
    } else if(funct == 39){  //nor
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = !(rs|rt);
        alu_zero = 0;
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 37){  //or
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = rs|rt;
        alu_zero = 0;
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 42){  //slt
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = (rs < rt);
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);

        /*this is going to need the (immediate *4) + offset since that what a offset is*/
    } else if(funct == 43){  //sltu
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = (rs < rt);
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 0){  //sll
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = rt << shamt;
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 2){  //srl
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        alu_op = fourConvert(four,three, two, one);
        int destination = rt >> shamt;
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 34){  //sub
        int four = 0;
        int three = 1;
        int two = 1;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        int destination = rs-rt;
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(funct == 35){  //subu
        int four = 0;
        int three = 1;
        int two = 1;
        int one = 0;
        alu_op = fourConvert(four,three, two, one);
        int destination = rs-rt;
        alu_zero = 0;
        printf("The value of destination %d\n", destination);
        printf("%s is modified to 0x%x\n", register_name[rd],destination);
    }

    if(funct == 4){    //for beq (NOTE THIS IS STILL USING OPCODE JUST BEING CALLED FUNCT FOR SIMPLICITY)
        int signExtend = immediate * 2;
        int shiftLeft = signExtend << 2;
        branch_target = shiftLeft + pc + 4;

        int sub = rs-rt;
        if(sub == 0){
            alu_zero = 1;
        } else{
            alu_zero = 0;
        }
        
        // printf("the value of branch target %d\n", branch_target);
        printf("pc is modified to 0x%x\n", branch_target);
    }

    // printf("The alu_op is: %d\n", alu_op);

    return 0;
}

/*for beq subtract $1 and $2 which will be used to "jump to branch", be used on every intruction and only "triggered" with beq*/

int Mem(int opcode, int address, int value){
    if (opcode == 35){  //load word
        if (address == 0){
            Writeback(dMem[0], value);
        }
        else if (address > 0){
            Writeback(dMem[address/4], value);
        }
    }
    else if (opcode == 43){ //store word
        if (address == 0){
            dMem[0] = value;
        }
        else if (address > 0){
            dMem[address/4] = value;
        }
    }
}

int Writeback(int value, int rt){
    rt = value;

    total_clock_cycles = total_clock_cycles + 1;
}

int main(int argc, char** argv){

    FILE *ptr;

    ptr = fopen("Given_Files/sample_binary.txt", "r");

    int code[32];   //making space available
    char var[32];   //taking the instruction as a char then breaking it up into its individual numbers

    fetch(ptr, var, code);
    // printf("The value of alu_op via main: %d", alu_op);
    // execute(alu_op);

    return 0;
}


/*  TEST CASE machine code
00000001000010011000100000100000 <- add
00001000001010101010101101000101 <- j
00001100001010101010101101000101 <- jal
00110100001001000000000000000000 <- ori
00100000100001010000000000000000 <- addi
00010010001100100000000000000011 <- beq
*/

