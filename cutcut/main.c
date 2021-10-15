#include <stdio.h>
#include "cut.h"

int main(){
    int oo[4][4] = {
        {23, 0, 23, 0},
        {14, 5, 144, 2},
        {24, 21, 24, 24},
        {1, 42, 1, 52}
    };

    apply_cut(oo, 4, 4);    
}