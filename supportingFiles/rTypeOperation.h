#ifndef RTYPEOPERATION
#define RTYPEOPERATION

#include <stdio.h>

int operation(int funct){   //for R type funcs
    if (funct == 32){
        // printf("Operation: add\n");
    }

    else if (funct == 33){  //addu operation
        // printf("Operation: addu\n");
    }

    else if (funct == 36){    //and operation
        // printf("Operation: and\n");
    }

    else if (funct == 8){      //jr operation
        // printf("Operation: jr\n");
    }

    else if (funct == 39){      //nor operation
        // printf("Operation: nor\n");
    }

    else if (funct == 37){      //or operation
        // printf("Operation: or\n"); 
    }

    else if (funct == 42){      //slt operation
        // printf("Operation: slt\n"); 
    }

    else if (funct == 43){      //sltu operation
        // printf("Operation: sltu\n"); 
    }

    else if (funct == 0){      //sll operation
        // printf("Operation: sll\n"); 
    }

    else if (funct == 2){      //srl operation
        // printf("Operation: srl\n"); 
    }

    else if (funct == 34){      //sub operation
        // printf("Operation: sub\n"); 
    }

    else if (funct == 35){      //subu operation
        // printf("Operation: subu\n"); 
    }
    return 0;
}


#endif