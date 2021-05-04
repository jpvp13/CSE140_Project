#include <stdio.h>
#include <string.h>

#include "supportingFiles/conversions.h"
#include "supportingFiles/rTypeOperation.h"
#include "supportingFiles/returnALUOp.h"


//global register array
int registerfile[32];
char *register_name[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

// int instructionNum = 0;
int pc = 0; //pc counter to be incremented
int next_pc = 0; //
int jump_target = 0; //used to jump to a target
int alu_zero = 0;   //had to used "_" rather than "-" as it thought a subtraction was being done
int branch_target = 0;

int iBreakNow;
int destination = 0;
// int alu_op = 0;    //used for the alu operation code within execute
int alu_op;
int dMem[32];
int total_clock_cycles = 0;
int newMem = 0;
int nextAddress = 0;
int branchPC = 0;

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

//pipeline arrays
// int if_id[];
// int id_ex[];
// int ex_mem[];
// int mem_wb[];


int opcode;
int rt, rd, rs, immediate, funct, shamt = 0;
int jumpAddress;


void ControlUnit(int opcode, int funct) {
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
        alu_op = returnAluCode(funct, opcode);

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
        alu_op = returnAluCode(funct, opcode);
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
        alu_op = returnAluCode(funct, opcode);
        // printf("The ALU is %d\n", alu_op);
    }
    else if (opcode == 4){  //beq
        jump = 0;
        regWrite = 0;
        regDst = 0;
        branch = 1;
        ALUSrc = 0;
        instType = 1; 
        memWrite = 0;
        memToReg = 0;
        memRead = 0;
        alu_op = returnAluCode(funct, opcode);
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
        alu_op = returnAluCode(funct, opcode);
        // printf("The ALU is %d\n", alu_op);
    }
}


int execute(){
    // int count = 0;

    ControlUnit(opcode, funct);
        if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 2){ //add
            // ControlUnit(opcode, funct);
            registerfile[rd] = registerfile[rs] + registerfile[rt];
            alu_zero = 0;

            return registerfile[rd];
        } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 0){ //and
            // ControlUnit(opcode, funct);

            alu_zero = 0;
            registerfile[rd] = registerfile[rs] & registerfile[rt];
            
            return registerfile[rd];
        } else if(jump ==1 && regWrite == 0 && regDst == 0 && branch == 0 && ALUSrc == 0 && instType == 0 && memWrite == 0 && memToReg == 0 && memRead == 0 && opcode == 2){  //j
   
            // pc = newTarget;
            alu_zero = 0;
   
            return pc;
        } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 12){  //nor
            // ControlUnit(opcode, funct);

            registerfile[rd] = !(registerfile[rs] | registerfile[rt]);
            alu_zero = 0;
            
            return registerfile[rd];
        } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 1){  //or
            // ControlUnit(opcode, funct);

            registerfile[rd] = registerfile[rs] | registerfile[rt];
            alu_zero = 0;

            
            return registerfile[rd];
        } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 7){  //slt
            // ControlUnit(opcode, funct);

            registerfile[rd] = (registerfile[rs] < registerfile[rt])?1:0;
            alu_zero = 0;

            
            return registerfile[rd];
        } else if(jump == 0 && regWrite == 0 && regDst == 0 && branch == 0 && ALUSrc == 1 && instType == 00 && memWrite == 1 && memToReg == 0 && memRead == 0){ //SW
            
            return destination;

        } else if(jump == 0 && regWrite == 1 && regDst == 1 && branch == 0 && ALUSrc == 0 && instType == 10 && memWrite == 0 && memToReg == 0 && memRead == 0 &&  alu_op == 6){  //sub
            // ControlUnit(opcode, funct);

            registerfile[rd] = registerfile[rs] - registerfile[rt];
            alu_zero = 0;
            
            return registerfile[rd];
        } else if(jump == 0 && regWrite == 1 && regDst == 0 && branch == 0 && ALUSrc == 1 && instType == 00 && memWrite == 0 && memToReg == 1 && memRead == 1){ //LW
    
            
            return destination;
        } else if(jump == 0 && regWrite == 0 && regDst == 0 && branch == 1 && ALUSrc == 0 && instType == 1 && memWrite == 0 && memToReg == 0 && memRead == 0 && alu_op == 6){    //for beq (NOTE THIS IS STILL USING OPCODE JUST BEING CALLED funct FOR SIMPLICITY)
    

            int sub = registerfile[rs] - registerfile[rt];
            if(sub == 0){
                alu_zero = 1;
            } else{
                alu_zero = 0;
            }

            //Weird bug that REQUIRES this to be here or else code breaks
            int signExtend = immediate < 4;
            // printf("The value signExtend is 0x%x inside of beq\n", signExtend);

            int result = signExtend * 4;
            // printf("The value result is 0x%x inside of beq\n", result);
            branch_target = result + next_pc + 4;
            // iBreakNow = 1;

            return branch_target;
            // return pc;
        
    }
    return 0;
}


int Mem(int opcode, int destination){
    // int changedMem = -1;    //default do not change memory

    if (opcode == 35){  //load word

        // return dMem[(registerfile[rs_regFile] - 0x00000000) >> 2];
        dMem[destination] = rt;
        // printf("The value of dMem[%d] inside of memory for lw is %d\n", destination, dMem[destination]);
        return dMem[destination];
    }
    else if (opcode == 43){ //store word

        // changedMem = value;
        dMem[destination] = rt;
        // printf("The value of dMem[%d] inside of memory for sw is %d\n", destination, dMem[destination]);
        return dMem[destination];
    }

    return 0;
}

int Writeback(int opcode, int funct, int alu_op){
    

    // changedRegister = -1;

    if(funct == 32 && opcode == 0){   //!add
    


        // printf("The value of destination is %d\n", destination);

        total_clock_cycles = total_clock_cycles + 1;
        // return registerfile[rd];
        return registerfile[destination];
    } else if(funct == 34 && opcode == 0){    //!sub
    

        // printf("The value of destination is %d\n", destination);
        total_clock_cycles = total_clock_cycles + 1;
        return registerfile[rd];
    } else if (funct == 36 && opcode == 0){   //!and
        

        // printf("The value of destination is %d\n", destination);
        total_clock_cycles = total_clock_cycles + 1;
        return registerfile[rd];
    } else if (funct == 37 && opcode == 0){   //!or
    

        // printf("The value of destination is %d\n", destination);
        total_clock_cycles = total_clock_cycles + 1;
        return registerfile[rd];
    } else if (funct == 39 && opcode == 0){   //!nor
    

        // printf("The value of destination is %d\n", destination);
        return registerfile[rd];
        total_clock_cycles = total_clock_cycles + 1;
    } else if (funct == 42 && opcode == 0){   //!slt
    

        // printf("The value of destination is %d\n", destination);
        total_clock_cycles = total_clock_cycles + 1;

        return registerfile[rd];
    } 
    
    if(opcode == 43 ){   //!SW
    // printf("I am inside of sw in writeback\n");

        // printf("The value of destination is %d\n", destination);
        
        total_clock_cycles = total_clock_cycles + 1;
        
        return registerfile[rt];
    } else if(opcode == 35 ){  //!LW
    // printf("I am inside of lw in writeback\n");


        // printf("The value of destination is %d\n", destination);
        total_clock_cycles = total_clock_cycles + 1;
        return registerfile[rt];
    } else  if(opcode == 4 && alu_op == 6){ //!beq
    // printf("I am inside of beq in writeback\n");

        // iBreakNow = 1;
        branchPC = pc;
        // printf("The value of iBreakNow inside of writeback is %d\n", iBreakNow);
        total_clock_cycles = total_clock_cycles + 1;
        return branch_target;
    } else if (opcode == 2){    //!jump
        // printf("I am inside of sw\n");

        total_clock_cycles = total_clock_cycles + 1;
        // printf("The value of jump_target inside of writeback is %d\n", jump_target);
        // return 0;
        return jump_target;
    
    }
    return 0;
}



void printINFO(int opcode, int funct, int newMem, int check){
    printf("total_clock_cycles %d: \n", total_clock_cycles);
    

    if(funct == 32 && opcode == 0){    //add
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if(funct == 34 && opcode == 0){ //sub
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if (funct == 36 && opcode == 0){    //and
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if (funct == 37 && opcode == 0){    //or
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if (funct == 39 && opcode == 0){    //nor
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if (funct == 42 && opcode == 0){    //slt
        
        printf("%s is modified to 0x%x\n", register_name[rd], newMem);
        printf("pc is modified to 0x%x\n", pc);
    } 

    
    if(opcode == 35) {  //! LW

        printf("%s is modified to 0x%x\n", register_name[rt], newMem);
        printf("pc is modified to 0x%x\n", pc);

    } else if(opcode == 4){ //BEQ
  
        pc = branch_target;
        printf("pc is modified to 0x%x\n", pc);

    } else if(opcode == 43){    //!SW
        // printf("The value of pc is %d\n", pc);
        // pc = branch_target + 4;
        pc = check;
        // printf("The value of pc is %d\n", pc);
        // pc = branch_target;
        printf("memory 0x%x is modified to 0x%x\n", newMem, registerfile[rt] );
        printf("pc is modified to 0x%x\n", pc);
        
    } else  if(opcode == 2){    //Jump
        //! jump goes here
        printf("I am inside of jump\n");

        printf("pc is modified to 0x%x\n", pc);
    }
    // return 0;
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
        // printf("Instruction type: R\n");

        funct = SixConvert(code[26], code[27], code[28], code[29], code[30], code[31]);
        operation(funct);


        // ControlUnit(opcode, funct);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        // printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        // printf("Rt: %s\n", register_name[rt]);

        rd = FiveConvert(code[16], code[17], code[18],code[19],code[20]);
        // printf("Rd: %s\n", register_name[rd]);

        shamt = FiveConvert(code[21], code[22], code[23],code[24],code[25]);
        // printf("shamt: %d\n", shamt);
  
        // printf("funct: %d\n", funct);


        // execute();

    }
    return 0;
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
    ll      110000  -48s
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

    if(opcode == 4){
        // printf("Instruction Type: I\n");
        // printf("Operation (Opcode): beq\n");

        // ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        // printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        // printf("Rt: %s\n", register_name[rt]);



        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            // jump_target = (immediate) <<  2) + next_pc;    //(immediate * 4) + pc

            // printf("immediate: %d\n", immediate);
            
            // printf("Jump Target: %d\n", jump_target);
            // execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
            // execute();
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

            // printf("immediate: -%d\n", immediate);
            // printf("Jump Target: %d\n", jump_target);
            // execute(opcode, alu_op, rs,  rt,  0,  0, immediate);
            // execute();
        }

    }else  if(opcode == 35){
        // printf("Instruction Type: I\n");
        // printf("Operation (Opcode): lw\n");

        // ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        // printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        // printf("Rt: %s\n", register_name[rt]);


        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            // printf("immediate: %d\n", immediate);

            // lw = 1;
            // ControlUnit(opcode, 0);
            int signExtend = immediate * 4;
            destination = registerfile[rd] + signExtend;

            // registerfile[rt] = Mem(35,destination);


            // printf("The value inside of registerfile[rt] is %d inside of lw\n", registerfile[rt_regFile]);
            
            // printf("Jump %d, regWrite %d, regDst %d, branch %d, ALUSrc %d, instType %d, memWrite %d, memToReg %d, memRead %d\n", jump, regWrite, regDst, branch, ALUSrc, instType, memWrite, memToReg, memRead);
            // execute();
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

            // printf("immediate: -%d\n", immediate);
            // lw = 1;
            int signExtend = immediate * 4;
            destination = registerfile[rd] + signExtend;

            // registerfile[rt] = Mem(35,destination);


            // printf("The value inside of registerfile[rt] is %d inside of lw\n", registerfile[rt_regFile]);

            // int signExtend = immediate << 2;
            // rt = Mem(opcode, signExtend + rs_regFile, immediate);
            
            // execute();
            
        }

    }else if(opcode == 43){
        // printf("Instruction Type: I\n");
        // printf("Operation (Opcode): sw\n");

        // ControlUnit(opcode, 0);

        rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        // printf("Rs: %s\n", register_name[rs]);

        rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        // printf("Rt: %s\n", register_name[rt]);

        if (code[16] == 0) {
            immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
            // printf("immediate: %d\n", immediate);
            // sw = 1;


            int signExtend = immediate * 4;
            destination = registerfile[rs] + signExtend;
        
            // execute();

        } else if (code[16] == 1) {
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

            // printf("immediate: -%d\n", immediate);
            // sw = 1;


            int signExtend = immediate * 4;
            destination = registerfile[rs] + signExtend;
        

            // execute();
        }

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
        // ControlUnit(opcode, 0);
        // printf("Instruction type: J\n");
        // printf("Operation: j\n");

        jump_target = twosixConverter(code[6],code[7],code[8],code[9],code[10],code[11],code[12],code[13],code[14],code[15],code[16],code[17],code[18],code[19],code[20],code[21],code[22],code[23],code[24],code[25],code[26],code[27],code[28],code[29],code[30],code[31]);
    }
    return 0;
}


int decode(int code[]){
    Rtype(code);    //these is the decode() functions that are embedded within fetch()
    Itype(code);    //these is the decode() functions that are embedded within fetch()
    Jtype(code);    //these is the decode() functions that are embedded within fetch()
    return 0;
}



int fetch(FILE *ptr, char var[32], int code[32], int k){
    // int i = 0;
     if ( ptr == NULL ){
        printf( "sample_binary.c file failed to open." ) ;
    } else {
        // for(k; k <= 7; k++){
            // while(k < 8){
            if(fgets ( var, 33, ptr) != NULL){
                pc = pc + 4;
                // printf("pc value is: %d\n", pc);    //wanted to see the pc value
                fscanf(ptr, "%[^\n]", var);   //reads number as a "word" then breaks it down to digits

                // printf("%s", var);

                
                //! need to find the sign-extension within the immediate type

                for (int i = 0; i < 32; i++){
                    code[i] = var[i] - '0'; //convert the char into a digit
                }

                

                if(branch == 1){
                    int signExtend = immediate < 4;
                    // printf("The value signExtend is 0x%x inside of beq\n", signExtend);

                    int result = signExtend * 4;
                    // printf("The value result is 0x%x inside of beq\n", result);
                    branch_target = result + next_pc + 4;
                    // printf("The value of branch target is %d\n", branch_target);
                    
                    // branch_target = branch_target + 4 + next_pc;
                } else if (jump == 1){

                    // printf("The value signExtend is 0x%d inside of beq\n", signExtend);
                    pc = jump_target + pc;

                }
                next_pc = pc + 4;
                
                return 0;
            }

            // printf("------------------\n");
            
        // }
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

        // printf("The value of dMem[%d] is %d\n", i, dMem[i]);
        // printf("The value of registerfile[%d] is %d\n", i, registerfile[i]);
    }

    FILE *ptr;

    //!make it so that a user can input name of file

    ptr = fopen("Given_Files/sample_binary.txt", "r");

    int code[32];   //making space available
    char var[32];   //taking the instruction as a char then breaking it up into its individual numbers
    

    for(int instructionNum = 0; instructionNum < 8; instructionNum++){
        // printf("The value of instructionNum is %d\n", instructionNum);
        fetch(ptr, var, code, instructionNum);
    
        decode(code);

        newMem = execute();
     
        // Mem(opcode, destination);
        Mem(opcode, newMem);


        Writeback(opcode,funct, alu_op);
        printINFO(opcode, funct, newMem, 0);
        // printf("The value of branch is %d\n", branch);
        printf("-----------------------------------\n");

        if(branch == 1){
            
            if (pc == branchPC + branch_target){

                int instructionDistance = (branch_target - branchPC)/4;
                // printf("The value of instructionDistance is %d\n", instructionDistance);
                total_clock_cycles = total_clock_cycles - instructionDistance;
                // printf("This is inside of the branch for main\n");
                int check = branch_target + 4;
                // printf("The value of check %d\n", check);
                printINFO(opcode, funct, newMem, check);
                printf("-----------------------------------\n");
                break;

            } else{
                for(instructionNum = instructionNum + 1; instructionNum < 9; instructionNum++){
                    // printf("The value of instructionNum is %d\n", instructionNum);
                    fetch(ptr, var, code, instructionNum);
    
                    decode(code);

                    newMem = execute();
                
                    // Mem(opcode, destination);
                    Mem(opcode, newMem);


                    Writeback(opcode,funct, alu_op);
                    // total_clock_cycles = total_clock_cycles - 1;

                     if (pc == branchPC + branch_target){
                        int instructionDistance = (branch_target - branchPC)/4;
                        // printf("The value of instructionDistance is %d\n", instructionDistance);
                        total_clock_cycles = total_clock_cycles - instructionDistance;
                        // printf("This is inside of the branch for main\n");
                        int check = branch_target + 4;
                        printINFO(opcode, funct, newMem, check);
                        printf("-----------------------------------\n");
                        break;
                    }
                }
            }
        } 
    }

    printf("Program Terminated:\n");
    printf("total execution time is %d cycles\n", total_clock_cycles);
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
