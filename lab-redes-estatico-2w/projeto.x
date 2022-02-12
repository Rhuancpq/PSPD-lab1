struct pair {float l; float f; };
struct operand {int n; float v[10];};

program PROG { 
    version VERSAO { 
        pair GET_MAJOR_MINOR(operand) = 1; 
    } = 100;
} = 77777777;