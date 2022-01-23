#include "types.h"
#include "stat.h"
#include "user.h"


int main(void) {
    for(int i=0; i < 10; i++){
        fork();
    }
    for(int i=0; i<1000; i++){
        printf(1, "PID: %d\n", i);
    }
    exit();

}