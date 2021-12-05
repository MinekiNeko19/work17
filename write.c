#include "write.h"


int main() {
    // access resources in semaphone
    
    // display last line added to file

    // prompt for next line

    // write to file and shared mem

    // temporary test code
    char input[3];
    fgets(input, 3 , stdin);
    printf("%c\n",input[0]);
    if (input[0]=='n') {
        printf("creating semaphore\n");
        create();
        print_err();
    }
    if (input[0]=='y') {
        printf("removing semaphore\n");
        rem();
        print_err();
    }
    return 0;
}
int write(char * line) {
    return 0;
}