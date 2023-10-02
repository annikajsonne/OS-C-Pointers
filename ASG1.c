/*

COMP3361: Operating Systems
Homework 1 

Name: Annika Sonne

*/

#include <stdio.h>
#include <stdlib.h>

//TODO: Question 1
/* Split the character array inp into words, and return the number of words. 
A sequence of non-blank characters ending in one or more blank spaces is a word. 
In addition, argc should be set to the number of words, argv[0] should point to the first character of the first word, 
argv[1] to the first character of the second word, and so on. 
Note: You should be able to print each word using theargvpointers, for example using the following function. */
int parse_command(char *inp, int *argc, char *argv[]) {
    //argv at 0
    argv[0] = inp;
    //index at 1 since we already have it at 0
    int i = 1;
    //make a new char pointer and point to inp
    char* p = inp;
    //while pointer isnt the termination
    while(*p != '\0') {
    //if it isnt a space increase pointner         
        if(*p != ' ') {
            p++;
        } else {
            //else increase the count and do a while to cover the double space and then set argv at i to pointer
            (*argc)++;
            while(*p != ' ') {
                p++;
            }
            argv[i] = p;
        }
        i++;
    }
    //after then increase the count to count for the last word and then return it
    (*argc)++;
    return *argc;
}
//test function
void print_cmd_line(char *argv[], int *argc) { 
        int i;
        for (i=0; i<*argc; i++) {
            printf('%s\n',argv[i]);
        }
}

//TODO: Question 2
/* Convert value into a null-terminated string using the specified base (2, 8, 10 or 16) 
and store the result in the str array (pre-allocated). 
For example, value=512 should result in the string 1000000000 for base=2, 1000 for base=8, 512 for base=10, 
and 200 for base=16. If base is 10 and value is negative, the string should be preceded with a minus (-) sign. 
For all other base, treat value as an unsigned number. 
The return value is a pointer to the generated string, i.e. same as str.
*/
char *itoa(int value, char *str, int base) {
    //make the variables needed
    int i = 0;
    int result;
    int rem;
    int neg;

    //if its negative fix it and note that for if its base 10
    if(value < 0) {
        neg = 1;
        value = -value;
    }
    
    //do the calc
    while(value != 0) {
        result = value/base;
        rem = value % base;
        value = result;

        //checking remainder for each division
        if(rem < 10) {
            rem = rem + 48;
        } else {
            rem = rem + 55;
        }
        //add this to the string
        str[i] = rem;

        //increment i
        i++;
    }

    //flip the bits/digits/etc to be in big endian
    for(int j = 0; j < (i/2); j++) {
        char t = str[j];
        str[j] = str[i-j-1];
        str[i-j-i] = t;
    }
   
    //add termination character
    str[i + 1] = '\0';
    i++;

    //if its negative and base 10 add the negative
    if((neg == 1) && (base == 10)) {
        //move the characters one up
        for(int j = i + 1; j > 0; j--) {
            str[j] = str[j-1];
        }
        str[0] = '-';
    }

    return str;
}

//TODO: Question 3
/* Write a C function called printany that can print any primitive C data type (char, int, unsigned, long, and float) 
You can have up to two arguments to the function and no global variables should be used in the function.
*/
void printany(char p, void* data) {
    //if char
    if(p == 'c') {
        char* charData = (char*) data;
        printf("%c\n", *charData);
    //if int
    } else if(p == 'i') {
        int* intData = (int*) data;
        printf("%d\n", *intData);
    //if unsigned int
    } else if(p == 'u') {
        unsigned int* uIntData = (unsigned int*) data;
        printf("%u\n", *uIntData);
    //if long
    } else if(p == 'l') {
        long* longData = (long*) data;
        printf("%lu\n", *longData);
    //if float
    } else if(p == 'f') {
        float* floatData = (float*) data;
        printf("%f\n", *floatData);
    }
}

//TODO: Question 4
typedef struct {
    unsigned short limit_0_15; // bits 0 (lowest order) to 15 of limit; 
    unsigned short base_0_15; // bits 0 to 15 of base
    unsigned char base_16_23; // bits 16 to 23 of base
    unsigned char limit_and_flag; // bits 16 to 19 of limit and 0 to 3 of flag
    unsigned char base_24_31; // bits 24 to 31 of base
} DESC;
/* Write a function that takes as input three integers base, limit and flag, and a DESC pointer g. The
function then populates the memory pointed to by g as per the comments given in the struct description.
*/
void populate_desc(int base, int limit, int flag, DESC *g) {

    g->limit_0_15 = 0xFFFF & limit;
    g->base_0_15 = 0xFFFF & base;
    g->base_16_23 = 0xFF0000 & base;
    g->limit_and_flag = ((0x70000 & limit) << 1) + (0b111 & flag);
    g->base_24_31 = 0xFF000000 & base;
}

int main() {

}