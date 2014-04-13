#include <stdio.h>
//#include <stdlib.h>

long NetIpChecksum(long ipHeader[], int nWords) {
long  sum = 0;// it should be uint32_t i guess
/*      * IP headers always contain an even number of bytes.      */
 while (nWords-- > 0)     { sum += *(ipHeader++);}

 /*      * Use carries to compute 1's complement sum.      */
sum = (sum >> 16) + (sum & 0xFFFF);     sum += sum >> 16;
 /*      * Return the inverted 16-bit result.      */
return (~sum&0xFFFF);

}

int main()
{
   //char str[30] = "c";
   //char *ptr;
   //long ret;

   //ret = strtoul(str, &ptr, 2);
   //printf("The number(unsigned long integer) is %\n", ret);
   //printf("String part is |%s|", ptr);

   char ipHeader[10][5]={"4500", "003c", "1c46", "4000", "4006", "0000", "ac10", "0a63", "ac10", "0a0c"};
   long ret[10];
   char *ptr;
   int i=0;
   for(i=0;i<10;i++)
   {

      ret[i]= strtoul(ipHeader[i], &ptr, 16);
      //printf("The number(unsigned long integer) is %x\n", ret[i]);
   }
   long checksumval=NetIpChecksum(ret,10);
   ret[5]=checksumval;
   printf("checksum value:%x\n",checksumval);
   long checksum=NetIpChecksum(ret,10);
   printf("checksum test:%x\n",checksum);

   return(0);
}
