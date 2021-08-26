#include <stdio.h>

void bytePrint(void * numberToPrint, size_t size) {
    /* This function prints size bytes of *numberToPrint in hexadecimal*/
    unsigned char *lowestAddress = (unsigned char *)numberToPrint;
    const char mapp[17] = "0123456789ABCDEF";
    for(size_t i = 0; i < size; ++i) {
        putchar( mapp[*(lowestAddress + i) >> 4] );
        putchar( mapp[*(lowestAddress + i) & 0xF]);
        putchar(' ');
    }
    putchar('\n');
}

void bis(void *operatedNumber, void *maskNumber, size_t size) {
    /*bis is a bit operation in DEC VAX computers.
    bis sets *operatedNumber to 1 at each bit position where that of *maskNumber is 1.
    size indicates how many bytes *operatedNumber and *maskNumber have.*/
    unsigned char *num = (unsigned char *)operatedNumber;
    const unsigned char *mask = (unsigned char *)maskNumber;
    for(size_t i = 0; i < size; ++i)
        *(num + i) |= *(mask + i);
}

void bic(void *operatedNumber, void *maskNumber, size_t size) {
    /*bic is a bit operation in DEC VAX computers.
    bic sets *operatedNumber to 0 at each bit position where that of *maskNumber is 1.
    size indicates how many bytes *operatedNumber and *maskNumber have.*/
    unsigned char *num = (unsigned char *)operatedNumber;
    const unsigned char *mask = (unsigned char *)maskNumber;
    for(size_t i = 0; i < size; ++i)
        *(num + i) &= ~*(mask + i);
}

/*
    bis(&a, &b, sizeof(a)) gives the result of (a | b) kept in a.
    bic(&a, &b, sizeof(a)) gives the result of (a & ~b) kept in a.
    apply the property x ^ y = (x & ~y) | (~x & y) and you can use only
    bis and bic to implement a ^ b
*/
int main() {
    int n = 511, mask = 0x2;
    bic(&n, &mask, sizeof(int));
    bytePrint(&n, sizeof(int));
    return 0;
}