#include <stdio.h>
#include <stdlib.h>

// return 1 if it is leap yaer, 0 not
int isLeapYear(int x)
{
    // leap year if it is divisible by 4 but not by 100 unless it is also divisible by 400
    if ((!(x % 4) && (x % 100)) || !(x % 400)) return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    // argument count
    if (argc < 2) {
        printf("Argument count %s <number>\n", argv[0]);
        return 1;
    }
    // int atoi(const cahr *str)
    // convert string to integer
    int x = atoi(argv[1]);

    if (isLeapYear(x) == 1) printf("{%d} was a leap year\n", x);
    else printf("{%d} was not a leap year\n", x);

    return 0;
}