/* Decoder - HW/Lab3 - Spring2021 - CSE140 Computer Architecture 
Authors:
    Uriel Montes
    John Villalvazo

"Decode.c" - Oringal name
*/

#include <stdio.h>
#include <string.h>

const char *register_number[32] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15","R16","R17","R18","R19","R20","R21","R22","R23","R24","R25","R26","R27","R28","R29","R30","R31"};
const char *register_name[32] = {"zero","at","v0","v1","a0","a1","a2","a3","t0","t1","t2","t3","t4","t5","t6","t7","s0","s1","s2","s3","s4","s5","s6","s7","t8","t9","k0","k1","gp","sp","fp","ra"};

int FiveConvert(int five, int four, int three, int two, int one){
    int decimal = 0;

    if (five == 1){
        decimal = decimal + 16;
    }
    if (four == 1){
        decimal = decimal + 8;
    }
    if (three == 1){
        decimal = decimal + 4;
    }
    if (two == 1){
        decimal = decimal + 2;
    }
    if (one == 1){
        decimal = decimal + 1;
    }
    else{
        decimal = decimal;
    }
    return decimal;
}

int SixConvert(int six, int five, int four, int three, int two, int one){
    int decimal = 0;

    if (six == 1){
        decimal = decimal + 32;
    }
    if (five == 1){
        decimal = decimal + 16;
    }
    if (four == 1){
        decimal = decimal + 8;
    }
    if (three == 1){
        decimal = decimal + 4;
    }
    if (two == 1){
        decimal = decimal + 2;
    }
    if (one == 1){
        decimal = decimal + 1;
    }
    else{
        decimal = decimal;
    }

    return decimal;
}

int sixteenConverter(int sixteen, int fifthteen, int fourteen, int thirteen, int twelve, int eleven, int ten, int nine, int eight, int seven, int six, int five, int four, int three, int two, int one){
    int decimal = 0;

    if (sixteen == 1){
        decimal = decimal + 32768;
    }
    if (fifthteen == 1){
        decimal = decimal + 16384;
    }
    if (fourteen == 1){
        decimal = decimal + 8192;
    }
    if (thirteen == 1){
        decimal = decimal + 4096;
    }
    if (twelve == 1){
        decimal = decimal + 2048;
    }
    if (eleven == 1){
        decimal = decimal + 1024;
    }
    if (ten == 1){
        decimal = decimal + 512;
    }
    if (nine == 1){
        decimal = decimal + 256;
    }
    if (eight == 1){
        decimal = decimal + 128;
    }
    if (seven == 1){
        decimal = decimal + 64;
    }
    if (six == 1){
        decimal = decimal + 32;
    }
    if (five == 1){
        decimal = decimal + 16;
    }
    if (four == 1){
        decimal = decimal + 8;
    }
    if (three == 1){
        decimal = decimal + 4;
    }
    if (two == 1){
        decimal = decimal + 2;
    }
    if (one == 1){
        decimal = decimal + 1;
    }
    else{
        decimal = decimal;
    }

    return decimal;
}
int twosixConverter(int twentysix, int twentyfive, int twentyfour, int twentythree, int twentytwo, int twentyone, int twenty, int nineteen, int eightteen, int seventeen, int sixteen, int fifthteen, int fourteen, int thirteen, int twelve, int eleven, int ten, int nine, int eight, int seven, int six, int five, int four, int three, int two, int one){
    
    int decimal = 0;

    if (twentysix == 1){
        decimal = decimal + 33554432;
    }
    if (twentyfive == 1){
        decimal = decimal + 16777216;
    } 
    if (twentyfour == 1){
        decimal = decimal + 8388608;
    } 
    if (twentythree == 1){
        decimal = decimal + 4194304;
    } 
    if (twentytwo == 1){
        decimal = decimal + 2097152;
    } 
    if (twentyone == 1){
        decimal = decimal + 1048576;
    } 
    if (twenty == 1){
        decimal = decimal + 524288;
    } 
    if (nineteen == 1){
        decimal = decimal + 262144;
    } 
    if (eightteen == 1){
        decimal = decimal + 131072;
    } 
    if (seventeen == 1){
        decimal = decimal + 65536;
    } 
    if (sixteen == 1){
        decimal = decimal + 32768;
    } 
    if (fifthteen == 1){
        decimal = decimal + 16384;
    } 
    if (fourteen == 1){
        decimal = decimal + 8192;
    } 
    if (thirteen == 1){
        decimal = decimal + 4096;
    } 
    if (twelve == 1){
        decimal = decimal + 2048;
    } 
    if (eleven == 1){
        decimal = decimal + 1024;
    } 
    if (ten == 1){
        decimal = decimal + 512;
    } 
    if (nine == 1){
        decimal = decimal + 256;
    } 
    if (eight == 1){
        decimal = decimal + 128;
    } 
    if (seven == 1){
        decimal = decimal + 64;
    } 
    if (six == 1){
        decimal = decimal + 32;
    } 
    if (five == 1){
        decimal = decimal + 16;
    } 
    if (four == 1){
        decimal = decimal + 8;
    } 
    if (three == 1){
        decimal = decimal + 4;
    } 
    if (two == 1){
        decimal = decimal + 2;
    } 
    if (one == 1){
        decimal = decimal + 1;
    }
    else{
        decimal = decimal;
    }
    return decimal;
}

int operation(int funct){
    if (funct == 32){
        printf("Operation: add\n");
    }

    else if (funct == 33){  //addu operation
        printf("Operation: addu\n");
    }

    else if (funct == 36){    //and operation
        printf("Operation: and\n");
    }

    else if (funct == 8){      //jr operation
        printf("Operation: jr\n");
    }

    else if (funct == 39){      //nor operation
        printf("Operation: nor\n");
    }

    else if (funct == 37){      //or operation
        printf("Operation: or\n"); 
    }

    else if (funct == 42){      //slt operation
        printf("Operation: slt\n"); 
    }

    else if (funct == 43){      //sltu operation
        printf("Operation: sltu\n"); 
    }

    else if (funct == 0){      //sll operation
        printf("Operation: sll\n"); 
    }

    else if (funct == 2){      //srl operation
        printf("Operation: srl\n"); 
    }

    else if (funct == 34){      //sub operation
        printf("Operation: sub\n"); 
    }

    else if (funct == 35){      //subu operation
        printf("Operation: subu\n"); 
    }
    return 0;
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
    int opcode = SixConvert(code[0], code[1], code[2], code[3], code[4], code[5]);

    if (opcode == 0){  // checking if rtype or not
        printf("Instruction type: R\n");

        int funct = SixConvert(code[26], code[27], code[28], code[29], code[30], code[31]);
        operation(funct);

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int rd = FiveConvert(code[16], code[17], code[18],code[19],code[20]);
        printf("Rd: %s (%s)\n", register_name[rd], register_number[rd]);

        int shamt = FiveConvert(code[21], code[22], code[23],code[24],code[25]);
        printf("Shamt: %d\n", shamt);
  
        printf("Funct: %d\n", funct);
    }

    else{
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
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);


    }else if (opcode == 9){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): addiu");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 12){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): andi\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23], code[24], code[25], code[26], code[27], code[28], code[29], code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 4){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): beq\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 5){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): bne\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 36){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lbu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 37){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lhu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 48){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ll\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 15){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lui\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 35){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): lw\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 13){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): ori\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 10){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): slti\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 11){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sltiu\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 40){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sb\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 56){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sc\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 41){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sh\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else if(opcode == 43){
        printf("Instruction Type: I\n");
        printf("Operation (Opcode): sw\n");

        int rs = FiveConvert(code[6], code[7], code[8],code[9],code[10]);
        printf("Rs: %s (%s)\n", register_name[rs], register_number[rs]);

        int rt = FiveConvert(code[11], code[12], code[13],code[14],code[15]);
        printf("Rt: %s (%s)\n", register_name[rt], register_number[rt]);

        int immediate = sixteenConverter(code[16], code[17], code[18],code[19],code[20],code[21], code[22], code[23],code[24],code[25],code[26], code[27], code[28],code[29],code[30], code[31]);
        printf("Immediate: %d\n", immediate);

    }else {
        return 0;
    }
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


int main(int argc, char** argv){

    int code[32];   //making space available
    char var[32];   //taking the instruction as a char then breaking it up into its individual numbers

    // user enters machine code
    printf("Enter an instruction in machine code:\n");
    scanf("%s", var);   //reads number as a "word" then breaks it down to digits

    for (int i = 0; i < 32; i++){
        code[i] = var[i] - '0'; //convert the char into a digit
    }
    printf("\n");
    
    Rtype(code);
    Itype(code);
    Jtype(code);

    return 0;
}

/*  TEST CASE machine code
00000001000010011000100000100000 <- add
00001000001010101010101101000101 <- j
00001100001010101010101101000101 <- jal
00110100001001000000000000000000 <- ori
00100000100001010000000000000000 <- addi
*/