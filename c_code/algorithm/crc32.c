#include <stdio.h>   
unsigned long int crc32_table[256];   
unsigned long int ulPolynomial=0x04c11db7;  
unsigned long int GenerateCRC32(char* DataBuf,unsigned long int len);
unsigned long int UPDC32(char octet, unsigned long int crc);
unsigned long int crc32_loader(char *sp,unsigned long int len); 


unsigned long int Reflect(unsigned   long   int   ref,   char   ch)   
{ 
	unsigned long int value=0;   
  int i; 
  for(i=1;i<(ch+1);i++)   
  { 
  	if(ref&1)   
  	value|=1<<(ch-i);   
    ref>>=1; 
  }   
  return   value;   
} 
  
init_crc32_table()   
{ 
 	unsigned   long   int   crc,temp;   
  int i,j;
  for( i=0;i<=0xFF;i++)   
  {       
  	temp=Reflect(i,8);   
  	crc32_table[i]=temp<<   24;   
  	for(j=0;j<8;j++)
  	{   
        unsigned   long   int   t1,t2;   
    		unsigned   long   int   flag=crc32_table[i]&0x80000000;   
    		t1=(crc32_table[i]<<1);   
    		if(flag==0)   
        	t2=0;   
    		else   
        	t2=ulPolynomial;   
    		crc32_table[i]   =t1^t2   ; 
    }   
  	crc=crc32_table[i];   
  	crc32_table[i]=Reflect(crc32_table[i],32);   
  }   
} 


int main()
{
		init_crc32_table();
		int i;
		for(i=0;i<256;i++)
		{
			printf("%8x\t",crc32_table[i]);
			if((i+1)%4==0)
				printf("\n");
		}
		char test[114]={
			0x50,
			0x44,
			0x33,
			0x22,
			0x11,
			0xee,
			0x22,
			0x33,
			0x44,
			0x55,
			0x66,
			0xaa,
			0x00,
			0x64,
			0x00,
			0x01,
			0x00,
			0x01,
			0x02,
			0x03,
			0x04,
			0x05,
			0x06,
			0x07,
			0x08,
			0x09,
			0x0a,
			0x0b,
			0x0c,
			0x0d,
			0x0e,
			0x0f,
			0x10,
			0x11,
			0x12,
			0x13,
			0x014,
			0x015,
			0x016,
			0x017,
			0x018,
			0x019,
			0x01a,
			0x01b,
			0x01c,
			0x01d,
			0x01e,
			0x01f,
			0x020,
			0x021,
			0x022,
0x023,
0x024,
0x025,
0x026,
0x027,
0x028,
0x029,
0x02a,
0x02b,
0x02c,
0x02d,
0x02e,
0x02f,
0x030,
0x031,
0x032,
0x033,
0x034,
0x035,
0x036,
0x037,
0x038,
0x039,
0x03a,
0x03b,
0x03c,
0x03d,
0x03e,
0x03f,
0x040,
0x041,
0x042,
0x043,
0x044,
0x045,
0x046,
0x047,
0x048,
0x049,
0x04a,
0x04b,
0x04c,
0x04d,
0x04e,
0x04f,
0x050,
0x051,
0x052,
0x053,
0x054,
0x055,
0x056,
0x057,
0x058,
0x059,
0x05a,
0x05b,
0x05c,
0x05d,
0x05e,
0x05f,
0x060,
0x061};
char test2[96]={0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53};
//char test3[2]={0x01,0x00};
printf("\n******%x******\n",GenerateCRC32(test,114));
printf("\n******%x******\n",GenerateCRC32(test2,96));
printf("\n******%x******\n",crc32_loader(test,114));
printf("\n******%x******\n",crc32_loader(test2,96));
//printf("\n******%x******\n",crc32_loader(test3,2));

}
  
   
unsigned   long int  GenerateCRC32(char*   DataBuf,unsigned   long    int len)   
{   
  unsigned   long   oldcrc32;   
  unsigned   long   crc32;   
  unsigned   long   oldcrc;   
  unsigned     int   charcnt;   
                  char   c,t;   
  oldcrc32=0x00000000;//��ֵΪ0   
  charcnt=0;   
  while(len--)   
  {   
    t=(oldcrc32>>24)&0xFF;       //Ҫ�Ƴ����ֽڵ�ֵ   
  	oldcrc=crc32_table[t];                   //�����Ƴ����ֽڵ�ֵ���   
    c=DataBuf[charcnt];                     //���ƽ������ֽ�ֵ   
    oldcrc32=(oldcrc32<<8)|c;       //�����ƽ������ֽ�ֵ���ڼĴ���ĩ�ֽ���   
    oldcrc32=oldcrc32^oldcrc;           //���Ĵ���������ֵ����xor����   
    charcnt++;   
  }   
  crc32=oldcrc32;   
  return   crc32;   
}  
  
    
unsigned long int UPDC32(char octet,unsigned long int crc) 
{
     return (crc32_table[((crc)^ (octet)) & 0xff] ^ ((crc) >> 8));
}


unsigned long int crc32_loader(char *sp,unsigned long int len) 
{
   	unsigned long int oldcrc32,crc32;
    unsigned long int i;

    oldcrc32=0xFFFFFFFF;
    for(i=0;i<len;i++)
    {
        oldcrc32=UPDC32(*(sp++),oldcrc32);
    }
 
    crc32=~oldcrc32; 
    return crc32; 
} 
 