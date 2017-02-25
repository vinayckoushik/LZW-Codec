#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

 int main(int argc,char *argv[])
{
	int j=0,k1=0,length=0,o;
	unsigned char B,C;
	unsigned int *pattern_length=(unsigned int *)malloc(400000 * sizeof (int));
	unsigned char *P=(unsigned char *)malloc(20);
	unsigned char *X=(unsigned char *)malloc(21);
	unsigned char *Y=(unsigned char *)malloc(21);
	unsigned char *Z=(unsigned char *)malloc(21);
	unsigned short int codeC=0,codeP=0;
	unsigned short int *code=(unsigned short int *)malloc(65536);
	unsigned char **dictionary2=(unsigned char **)malloc(400000*sizeof(unsigned char *));

	for(j=0;j<400000;j++)
	{
		dictionary2[j]=(unsigned char *)malloc(2500);
		
	}

	FILE *fpt;
	FILE *fpo;
	fpt=fopen("compressed.lzw","rb");
	fpo=fopen("decompressed.lzw","wb");

	if((j=fgetc(fpt))==-1)
	{
		exit(0);
	}
	
	for(k1=0;k1<256;k1++)
	{
		pattern_length[k1]=1;
		dictionary2[k1][0]=k1;
	}


	fseek(fpt,0,SEEK_SET);
	fread(code,1,2,fpt);
	codeC=(short int)code[0];

	fwrite(dictionary2[codeC],1,pattern_length[codeC],fpo);
	
	codeP=codeC;
	
	while(fread(code,1,2,fpt)>0)
	{
		codeC=code[0];
		if(codeC<k1 || codeC<256)
		{
			fwrite(dictionary2[codeC],1,pattern_length[codeC],fpo);
			for(o=0;o<pattern_length[codeP];o++)
				X[o]=dictionary2[codeP][o];
			//memcpy(X,dictionary2[codeP],pattern_length[codeP]);
			Y[0]=dictionary2[codeC][0];
			//memcpy(Y,dictionary2[codeC],1);
			length=pattern_length[codeP]+1;
			for(o=0;o<pattern_length[codeP];o++)
				dictionary2[k1][o]=dictionary2[codeP][o];
			dictionary2[k1][o]=Y[0];
			pattern_length[k1]=length;
			k1++;
		}
		else
		{
			for(o=0;o<pattern_length[codeP];o++)
				X[o]=dictionary2[codeP][o];
			//memcpy(X,dictionary2[codeP],pattern_length[codeP]);
			Z[0]=dictionary2[codeP][0];
			//memcpy(Z,dictionary2[codeP],1);
			length=pattern_length[codeP]+1;
			fwrite(dictionary2[codeP],1,pattern_length[codeP],fpo);
			fwrite(dictionary2[codeP],1,1,fpo);
			for(o=0;o<pattern_length[codeP];o++)
				dictionary2[k1][o]=dictionary2[codeP][o];
			dictionary2[k1][o]=Z[0];
			pattern_length[k1]=length;
			k1++;
		}
		codeP=codeC;
	}
	code[0]=0;
	code[1]=0;
	fwrite(code,1,1,fpo);
	fcloseall();
}

