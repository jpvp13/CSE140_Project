#ifndef RETURNALU
#define RETURNALU

#include "conversions.h"

int alu_op = 0;
int returnAluCode(int funct, int opcode){
    if(funct == 32){    //ADD
        int four = 0;   
        int three = 0;
        int two = 1;
        int one = 0;
        return alu_op = fourConvert(four,three, two, one);
    } else  if(funct == 36){ //AND
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 0;
        return alu_op = fourConvert(four,three, two, one);
    } else if(funct == 39){ //NOR
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        return alu_op = fourConvert(four,three, two, one);
    } else if(funct == 37){ //OR
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        return alu_op = fourConvert(four,three, two, one);
    } else if(funct == 0 && opcode == 0){  //SLL
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 1;
        return alu_op = fourConvert(four,three, two, one);
    } else if(funct == 34){ //SUB
        int four = 0;
        int three = 1;
        int two = 1;
        int one = 0;
        return alu_op = fourConvert(four,three, two, one);
    }else if(opcode == 4){
        return 6;
    }
    return 0;
}

#endif