#include <stdio.h>
#include <string.h>

#include "supportingFiles/conversions.h"
#include "supportingFiles/rTypeOperation.h"
#include "supportingFiles/returnALUOp.h"


//global register array
int registerfile[32];
const char *register_name[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

int instructionNum = 0;
int pc = 0; //pc counter to be incremented
int next_pc = 0; //
int jump_target = 0; //used to jump to a target
int alu_zero = 0;   //had to used "_" rather than "-" as it thought a subtraction was being done
int branch_target = 0;
// int sw = 0;
// int lw = 0;

// int alu_op = 0;    //used for the alu operation code within execute
int alu_op;
int dMem[32];
int total_clock_cycles = 0;

//Control Signals
int jump = 0;
int regWrite = 0;
int regDst = 0;
int branch = 0;
int ALUSrc = 0;
int instType = 0;
int memWrite = 0;
int memToReg = 0;
int memRead = 0;

int opcode;
int rt, rd, rs, immediate, funct, shamt = 0;
int rt_regFile, rd_regFile, rs_regFile = 0;
int jumpAddress;
int val;
int changedMem = -1;
int changedRegister = -1;


int decode(int code[]){
    Rtype(code);    //these is the decode() functions that are embedded within fetch()
    Itype(code);    //these is the decode() functions that are embedded within fetch()
    Jtype(code);    //these is the decode() functions that are embedded within fetch()
}

// int updatePC(int alu_op, int val, int opcode, int funct){
//     // printf("Incoming value of funct is %d\n", funct);
//     if(funct == 32 || funct == 34 || funct == 36 || funct == 37 || funct == 39 || funct == 42){ //R-types
//         pc = pc + 4;
//         // printf("pc is modified to 0x$x", pc);
//         // printf("Within updatePC r-type. The value of pc is %d\n", pc);
//         return;
//     }

//     if(opcode == 35 || opcode == 43){  //I-Types
//         pc = pc + 4;
//         // printf("Within updatePC i-type The value of pc is %d\n", pc);
//         // printf("pc is modified to 0x$x", pc);
//         return;
//     } else if(opcode == 4){
//         pc = pc + 4;
//         branch_target = pc + immediate * 4;
//         pc = branch_target;
//         // printf("Wuthin updatePC beq, The value of pc is %d\n", pc);
//         return;
//         // printf("pc is modified to 0x$x", pc);
//     }

//     if(opcode == 2){
//         //jump goes here
//         pc = pc + (jumpAddress << 2);
//         // printf("Within updatePC j, The value of pc is %d\n", pc);
//         return;
//         //!
//     }
// }


// int execute(int opcode, int funct, int alu_op, int rs, int rt, int rd, int shamt, int immediate){
int execute(){

    ControlUnit(opcode, funct);
    // printf("Jump %d, regWrite %d, regDst %d, branch %d, ALUSrc %d, instType %d, memWrite %d, memToReg %d, memRead %d\n", jump, regWrite, regDst, branch, ALUSrc, instType, memWrite, memToReg, memRead);


    if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 2){ //add
        // ControlUnit(opcode, funct);
        registerfile[rd_regFile] = rs_regFile + rt_regFile;
        alu_zero = 0;
        // int destination = *registerfile[rs] + *registerfile[rt];
        // printf("The value of destination is %d\n", destination);
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 2){ //addu
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = rs_regFile + rt_regFile;
        alu_zero = 0;
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 0){ //and
        // ControlUnit(opcode, funct);

        alu_zero = 0;
        registerfile[rd_regFile] = rs_regFile & rt_regFile;
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);
    } else if(jump ==1 && regWrite == 0 && regDst == 0 && branch == 0 && ALUSrc == 0 && instType == 0 && memWrite == 0 && memToReg == 0 && memRead == 0 && opcode == 2){  //j
        // ControlUnit(opcode, funct);

        pc = jump_target;
        alu_zero = 0;
        // printf("pc value inside of j execute is %d\n", jumpAddress);
        // printf("pc is modified to 0x%x\n",pc);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 12){  //nor
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = !(rs_regFile | rt_regFile);
        alu_zero = 0;
        // printf("nor\n");
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 1){  //or
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = rs_regFile | rt_regFile;
        alu_zero = 0;
        // printf("or\n");
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x",pc);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 7){  //slt
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = (rs_regFile < rt_regFile)?1:0;
        alu_zero = 0;
        // printf("The value of destination %d\n", destination);
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);

        /*this is going to need the (immediate *4) + offset since that what a offset is*/
    } else if(jump == 0 && regWrite == 0 && regDst == 0 && branch == 0 && ALUSrc == 1 && instType == 00 && memWrite == 1 && memToReg == 0 && memRead == 0){ //SW
        //SW
        // ControlUnit(opcode, funct);

        int signExtend = immediate * 4;
        int destination = rs_regFile + signExtend;
        dMem[rt_regFile] = destination;
        // int destination = 1000;
        // printf("destination value is: %d", destination);
        // printf("%s is modified to 0x%x\n", register_name[rt],destination);
        // printf("pc is modified to 0x%x\n", pc);

        // int destination = Mem(opcode, )
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 &&  alu_op == 6){  //sub
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = rs_regFile - rt_regFile;
        alu_zero = 0;
        // printf("The value of destination %d\n", destination);
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);
    // }else if(funct == 35 && lw == 1){    //LW
    } else if(jump == 0 && regWrite == 1 && regDst == 0 && branch == 0 && ALUSrc == 1 && instType == 00 && memWrite == 0 && memToReg == 1 && memRead == 1){
        // ControlUnit(opcode, funct);

        int signExtend = immediate * 4;
        // printf("lw\n");
        int destination = rd_regFile + signExtend;

        registerfile[rt_regFile] = rs_regFile + rt_regFile;
        // int destination = 1000;

        // printf("Jump %d, regWrite %d, regDst %d, branch %d, ALUSrc %d, instType %d, memWrite %d, memToReg %d, memRead %d\n", jump, regWrite, regDst, branch, ALUSrc, instType, memWrite, memToReg, memRead);
        // printf("destination value is: %d", destination);
        // printf("%s is modified to 0x%x\n", register_name[rt],destination);
        // printf("pc is modified to 0x%x\n", pc);
    } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 &&  alu_op == 6){  //subu
        // ControlUnit(opcode, funct);

        registerfile[rd_regFile] = rs_regFile - rt_regFile;
        alu_zero = 0;
        // printf("The value of destination %d\n", destination);
        // printf("%s is modified to 0x%x\n", register_name[rd],destination);
        // printf("pc is modified to 0x%x", pc);
    } 

    if(jump == 0 && regWrite == 0 && regDst == 0 && branch == 1 && ALUSrc == 0 && instType == 01 && memWrite == 0 && memToReg == 0 && memRead == 0){    //for beq (NOTE THIS IS STILL USING OPCODE JUST BEING CALLED funct FOR SIMPLICITY)
        // int signExtend = immediate * 2;
        // printf("Value of sign extension is %d\n", signExtend);
        // int shiftLeft = immediate << 1;
        // printf("Value of shift left is %d\n", shiftLeft);
        // branch_target = pc + immediate * 4;

        int sub = rs_regFile - rt_regFile;
        if(sub == 0){
            alu_zero = 1;
        } else{
            alu_zero = 0;
        }

        int shiftleft = immediate << 2;
        
        // printf("the value of branch target %d\n", branch_target);
        // printf("pc is modified to 0x%x\n", branch_target);
        branch_target = shiftleft + next_pc;
    }

    // printf("The alu_op is: %d\n", alu_op);

    return 0;
}

/*for beq subtract $1 and $2 which will be used to "jump to branch", be used on every intruction and only "triggered" with beq*/

int Mem(int opcode){
    // int changedMem = -1;    //default do not change memory

    if (opcode == 35){  //load word

        return dMem[(registerfile[rs_regFile] - 0x00000000) >> 2];
        // if (address == 0){
        //     Writeback(dMem[0], value);
        //     printf("The value of writeback is %d\n", Writeback(dMem[0], value));
        // }
        // else if (address > 0){
        //     Writeback(dMem[address/4], value);
        //     printf("The value of writeback is %d\n", Writeback(dMem[address/4], value));
        // }
    }
    else if (opcode == 43){ //store word

        // changedMem = value;
        return dMem[(registerfile[rt_regFile] - 0) >> 2];
        // if (address == 0){
        //     dMem[0] = value;
        // }
        // else if (address > 0){
        //     dMem[address/4] = value;
        // }
    }
}

int Writeback(int opcode, int alu_op){

    // changedRegister = -1;

    if(opcode == 32 || opcode == 34 || opcode == 36 || opcode == 37 || opcode == 39 || opcode == 42){ //add
        // changedRegister = rd;
        printf("Inside Writeback, value of changedRegister is %d\n", changedRegister);
        // register_name[rd] = value;
        return total_clock_cycles = total_clock_cycles + 1;
    }else {
        
       return total_clock_cycles = total_clock_cycles + 1;
    }

    if(opcode == 35 || opcode == 43 || opcode == 4){
        // changedRegister = rt;
        // register_name[rt] = value;
        return;total_clock_cycles = total_clock_cycles + 1;
        
    } else {
        
        return total_clock_cycles = total_clock_cycles + 1;
    }

    

    printf("##End writeback##\n");
}

int ControlUnit(int opcode, int funct) {
    if (opcode == 0) {  //r-type
        jump = 0;
        regWrite = 1;
        regDst = 1;
        branch = 0;
        ALUSrc = 0;
        instType = 10; 
        memWrite = 0;
        memToReg = 0;
        memRead = 0;
        alu_op = returnAluCode(funct);

        // printf("The ALU is %d\n", alu_op);
        // printf("The ALU code is %d\n", returnAluCode(funct));
    }
    else if (opcode == 35) {    //lw
        jump = 0;
        regWrite = 1;
        regDst = 0;
        branch = 0;
        ALUSrc = 1;
        instType = 00; 
        memWrite = 0;
        memToReg = 1;
        memRead = 1;
        alu_op = returnAluCode(funct);
        // printf("The ALU is %d\n", alu_op);
    }
    else if (opcode == 43){ //sw
        jump = 0;
        regWrite = 0;
        regDst = 0;
        branch = 0;
        ALUSrc = 1;
        instType = 00; 
        memWrite = 1;
        memToReg = 0;
        memRead = 0;
        alu_op = returnAluCode(funct);
        // printf("The ALU is %d\n", alu_op);
    }
    else if (opcode == 4){  //beq
        jump = 0;
        regWrite = 0;
        regDst = 0;
        branch = 1;
        ALUSrc = 0;
        instType = 01; 
        memWrite = 0;
        memToReg = 0;
        memRead = 0;
        alu_op = returnAluCode(funct);
        // printf("The ALU is %d\n", alu_op);
    }
    else if (opcode == 2){  //j
        jump = 1;
        regWrite = 0;
        regDst = 0;
        branch = 0;
        ALUSrc = 0;
        instType = 00; 
        memWrite = 0;
        memToReg = 0;
        memRead = 0;
        alu_op = returnAluCode(funct);
        // printf("The ALU is %d\n", alu_op);
    }


}

int printINFO(int opcode){
    printf("total_clock_cycles %d\n", total_clock_cycles);
    

    if(funct == 32 || funct == 34 || funct == 36 || funct == 37 || funct == 39 || funct == 42){ //R-types
        printf("%s is modified to 0x%x\n", register_name[rd_regFile], dMem[changedMem]);
        printf("pc is modified to 0x%x\n", pc);
        // printf("Within updatePC r-type. The value of pc is %d\n", pc);
        return;
    }


    //! look into this since its not printing correctly, or any funct tbh
    if(opcode == 35 || opcode == 43){  //I-Types
        printf("%s is modified to 0x%x\n", register_name[rt_regFile], dMem[changedMem]);
        printf("The value of rt_regfile is %d\n", rt_regFile);
        // printf("Within updatePC i-type The value of pc is %d\n", pc);
        printf("pc is modified to 0x%x\n", pc);
        return;
    } else if(opcode == 4){
            //!what to output for BEQ??
        printf("memory 0x%x is modified to 0x%x", registerfile[branch_target], branch_target);
        // printf("Wuthin updatePC beq, The value of pc is %d\n", pc);
        return;
        printf("pc is modified to 0x%x\n", pc);
    }

    if(opcode == 2){
        //! jump goes here
        // printf("%s is modified to 0x%x\n", register_name[changedRegister], dMem[changedMem]);
        // printf("Within updatePC j, The value of pc is %d\n", pc);
        return;
    }


}

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
    opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);

    

    if (opcode == 0){  // checking if rtype or not
        printf("Instruction type: R\n");

        funct = SixConvert(code[26], code[27], code[28], code[29], code[30], code[31]);
        operation(funct);


        ControlUnit(opcode, funct);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rd = FiveConvert(code[16], code[17], code[18],code[19],code[20]);
        printf("Rd: %s\n", register_name[rd]);

        shamt = FiveConvert(code[21], code[22], code[23],code[24],code[25]);
        printf("shamt: %d\n", shamt);
  
        printf("funct: %d\n", funct);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];
        rd_regFile = registerfile[rd];

        printf("Value of rs_regFile is %d\n", rs_regFile);
        printf("Value of rt_regFile is %d\n", rt_regFile);
        printf("Value of rd_regFile is %d\n", rd_regFile);

        execute(alu_op);

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
    opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);

    // ControlUnit(opcode, 0);

    if (opcode == 8){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): addi\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            int value = registerfile[rt] + immediate;
            printf("Value of rs is %x\n", value);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            
            
            rt_regFile = registerfile[rt];
            int value = rt_regFile + immediate;

            execute(alu_op);
            // printf("Value of rs is %d\n", value);
        }


    }else if (opcode == 9){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): addiu");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 12){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): andi\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 4){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): beq\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            // jump_target = (immediate) <<  2) + next_pc;    //(immediate * 4) + pc

            printf("immediate: %d\n", immediate);
            
            // printf("Jump Target: %d\n", jump_target);
            // execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
            execute(alu_op);
        }//! ///////////////////////////////////////////////
        else if (code[16] == 1) {
            for (int i = 16; i <= 31; i++){
                if (code[i] == 1){
                    code[i] = 0;
                }
                else if (code[i] == 0){
                    code[i] = 1;
                }
            }
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            // jump_target = (sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]) <<  2) + next_pc;    //(immediate * 4) + pc

            printf("immediate: -%d\n", immediate);
            // printf("Jump Target: %d\n", jump_target);
            // execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
            execute(alu_op);
        }

    }else if(opcode == 36){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lbu\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 37){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lhu\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 48){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ll\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 15){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lui\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 35){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lw\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);

            // lw = 1;
            // ControlUnit(opcode, 0);
            // int signExtend = immediate << 2;
            // rt = Mem(opcode, signExtend + rs);
            Mem(opcode);
            
            // printf("Jump %d, regWrite %d, regDst %d, branch %d, ALUSrc %d, instType %d, memWrite %d, memToReg %d, memRead %d\n", jump, regWrite, regDst, branch, ALUSrc, instType, memWrite, memToReg, memRead);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            // lw = 1;
            // ControlUnit(opcode, 0);
            Mem(opcode);

            // int signExtend = immediate << 2;
            // rt = Mem(opcode, signExtend + rs_regFile, immediate);
            
            execute(alu_op);
            
        }

    }else if(opcode == 13){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ori\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 10){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): slti\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 11){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sltiu\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 40){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sb\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 56){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sc\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 41){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sh\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
            printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            execute(alu_op);
        }

    }else if(opcode == 43){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sw\n");

        ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s\n", register_name[rt]);

        rs_regFile = registerfile[rs];
        rt_regFile = registerfile[rt];

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            printf("immediate: %d\n", immediate);
            // sw = 1;

            rs_regFile = registerfile[rs];

            Mem(opcode);
            execute(alu_op);
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
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            immediate = immediate + 1;

            printf("immediate: -%d\n", immediate);
            // sw = 1;

            rs_regFile = registerfile[rs];

            Mem(opcode);
            execute(alu_op);
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
    opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);


    if (opcode == 2){
        ControlUnit(opcode, 0);
        printf("Instruction type: J\n");
        printf("Operation: j\n");

        jumpAddress = twosixConverter(code[6],code[7],code[8],code[9],code[10],code[11],code[12],code[13],code[14],code[15],code[16],code[17],code[18],code[19],code[20],code[21],code[22],code[23],code[24],code[25],code[26],code[27],code[28],code[29],code[30],code[31]);
        printf("Address: %d\n", jumpAddress);

        int shiftLeft = jumpAddress << 2;
        jump_target = shiftLeft + next_pc;

        // execute(alu_op);
    } else{
        return 0;
    }
    return 0;
}

int fetch(FILE *ptr, char var[32], int code[32], int k){
    // int i = 0;
     if ( ptr == NULL ){
        printf( "sample_binary.c file failed to open." ) ;
    } else {
        // for(k; k <= 7; k++){
            while(k < 9){
            if(fgets ( var, 33, ptr) != NULL){
                pc = pc + 4;
                // printf("pc value is: %d\n", pc);    //wanted to see the pc value
                fscanf(ptr, "%[^\n]", var);   //reads number as a "word" then breaks it down to digits

                // printf("%s", var);

                
                //! need to find the sign-extension within the immediate type

                for (int i = 0; i < 32; i++){
                    code[i] = var[i] - '0'; //convert the char into a digit
                }

                // if(branch_target != 0){
                //     pc = branch_target;
                // } else if( jump_target != 0){
                //     pc = jump_target;
                // } else {
                //     next_pc = pc + 4;
                //     pc = next_pc;
                // }

                // printf("\n");

                // Rtype(code);    //these is the decode() functions that are embedded within fetch()
                // Itype(code);    //these is the decode() functions that are embedded within fetch()
                // Jtype(code);    //these is the decode() functions that are embedded within fetch()
                // printf("Value of k is %d\n", k);
                return;
            }

            // printf("------------------\n");
            
        }
        // printf("program terminated:\n");
        // printf("total execution time is %d cycle\n", total_clock_cycles);
        // k--;
        // printf("total execution time is %d cycles\n", k);
        // Closing the file using fclose()
        fclose(ptr) ;
    }
    return 0;

}


int main(int argc, char** argv){

    for(int i = 0; i < 32; i++){
        //using given initializations for dMem
        if(i == 28){
            dMem[i] = 5;
        } else if(i == 29){
            dMem[i] = 16;
        } else{
            dMem[i] = 0;
        }

        //using given initializations for registerfile
        if(i == 9){
            registerfile[i] = 32;
        } else if(i == 10){
            registerfile[i] = 5;
        } else if(i == 16){
            registerfile[i] = 112;
        }
    }

    FILE *ptr;

    ptr = fopen("Given_Files/sample_binary.txt", "r");

    int code[32];   //making space available
    char var[32];   //taking the instruction as a char then breaking it up into its individual numbers
    
    // // char test = register_name[0];
    // printf("The value of register_name[8] is 0x%x\n", registerfile[28]);
    // printf("The register that is outputted is %s\n", register_name[28]);
    // printf("The value inside of dMem is 0x%x\n", dMem[28]);
    // printf("The value accessed by register_name[0] is %s\n", registerfile[test]);

    for(instructionNum; instructionNum < 9; instructionNum++){
        fetch(ptr, var, code, instructionNum);
        // printf("After fetch\n");
        decode(code);
        // printf("After decode\n");
        execute();
        // printf("After execute\n");
        // printf("The value of funct from global var is %d\n", funct);

        // updatePC(alu_op, val, opcode, funct);
        // printf("The value of pc is %d\n", pc);
        // printf("After new pc\n");

        printf("The value of val is %d\n", val);
        Mem(opcode);
        // printf("After mem\n");

        

        Writeback(opcode, alu_op);
        printf("Current PC value is %d\n", pc);


        // printf("changedeRegister value is %d\n", changedRegister);
        // printf("changedeMem value is %d\n", changedMem);

        printINFO(opcode);
        // printf("After print\n");

        printf("-----------------------------------\n");

    
    }
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

