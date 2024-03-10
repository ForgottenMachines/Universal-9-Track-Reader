#include <stdio.h>
#include <stdlib.h>
unsigned int testData[800];

void buildTestData();
void domycrc();
int main()
{
    buildTestData();
    calcCrc(testData, 800);
    return 0;
}

void buildTestData()
{
   unsigned  int i;
    for(i=0; i<800; i++)
    {
        testData[i]=0x40;
    }
}

void calcCrc(unsigned int *idata, unsigned int length)
{
    unsigned int lsb=0;
    unsigned int crc = 0;   // set all 9 CRC bits to 0
    int i;
    //for all characters "ch" in the block (not including CRCC or LRCC) in sequence
    for(i=0;i<length; i++)
    {
        printf("idata %d \n",idata[i]);
        //crc = crc XOR ch  // add without carries, C0...C7, P
        crc=crc^idata[i];

        //if crc AND binary(000000010)
        if(crc&2)
        {      // if P will be 1 after the upcoming rotate right,
            //crc = crc XOR binary(011110000)  // then invert what will become C2, C3, C4, C5
            crc = crc ^ 0xF0;
        }
        // do a 9-bit rotate to the right:
        lsb = crc & 1;    // first make a copy of the rightmost bit
        crc = crc >> 1;  // shift right by one bit, losing the rightmost bit
        if (lsb == 1)
        {    // if the preserved rightmost bit was a one
            //crc = crc OR binary(100000000)  // put it back at the left
            crc=crc | 0x100;
        }
        printf("crc result %d is %x\n",i,crc);

    } // loop until all data characters have been processed
    //crc = crc XOR binary(110101111);  // invert all bits except C2 and C4
    crc=crc ^ 0x1AF;
    printf("crc final result is %x\n",crc);
}
