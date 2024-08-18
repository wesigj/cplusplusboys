#include "stdio.h"
#include <string.h>

#define ADDRESS_USER 0x1000000
#define ADDRESS_LENGTH 100

unsigned char buffer1[ADDRESS_LENGTH];
unsigned char buffer2[ADDRESS_LENGTH];
unsigned char buffer3[ADDRESS_LENGTH];
unsigned char buffer4[ADDRESS_LENGTH];

typedef struct buffer
{
    unsigned int address;
    unsigned int address_length;
    unsigned char *pbuffer;
} Buffer;

// const Buffer test1 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer1[0]};
// const Buffer test2 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer2[0]};
// const Buffer test3 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer3[0]};
// const Buffer test4 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer4[0]};

const Buffer test[4] = {
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer1[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer2[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer3[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer4[0]}};

const Buffer *pstructbuffers[4] = {
    &test[0],
    &test[1],
    &test[2],
    &test[3]};

const Buffer **get_buffer()
{
    return pstructbuffers;
}

int main()
{

    // Buffer **tests = (Buffer **)pstructbuffers;
    const Buffer **tests;

    tests = get_buffer();

    for (int i = 0; i < 4; i++)
    {
        memcpy(tests[i]->pbuffer, "testestes", i + 1);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("buffer = %s\r\n", tests[i]->pbuffer);
    }

    return 0;
}