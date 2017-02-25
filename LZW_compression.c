#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

int main(int argc,char *argv[])
{
		int j=0,k1=0,m=0,n,length=0,o;
		unsigned char C;
		unsigned int *pattern_length=(unsigned int *)malloc(400000 * sizeof (int));
		unsigned char *P=(unsigned char *)malloc(2000);
		unsigned char *Q=(unsigned char *)malloc(2000);
		unsigned short int code=0;
		unsigned char **dictionary=(unsigned char **)malloc(400000 * sizeof(unsigned char *));

		for(j=0;j<400000;j++)
		{
				dictionary[j]=(unsigned char *)malloc(2000);
		}

		FILE *fpt, *fpo;
		fpt = fopen(argv[1],"rb");
		fpo = fopen("compressed.lzw","wb");

		for(k1=0;k1<256;k1++)
		{
				pattern_length[k1]=1;
				dictionary[k1][0]=k1;
		}

		fseek(fpt,0,SEEK_SET);

		length = 0;
		while (fread(&C,1,1,fpt) > 0)
		{
			for(o=0;o<length;o++)
				Q[o]=P[o];

			P[length]=C;
			length++;

			for(n=0;n<k1;n++)
			{
				if (pattern_length[n] == length)
				{
					if(memcmp(P,dictionary[n],length)==0)
					{
						m=1;
						code=(short int)n;
						break;
					}
				}
			}

				//PC is present 
			if(m == 1)
			{
				m=0;
				continue;
			}

				//PC not present
			else
			{
				length--;

				for(n=0; n<k1; n++)
				{
					if (pattern_length[n] == length)
					{
						if(memcmp(Q, dictionary[n], length) == 0)
						{
							code = (short int)n;
							break;
						}
					}
				}

				fwrite(&code,2,1,fpo);

				for(o=0;o<length+1;o++)
					dictionary[k1][o]=P[o];

				pattern_length[k1] = length + 1;
				k1++;
				P[0]=C;
				length=1;
			}
		}
		
	for(n=0;n<k1;n++)
	{
		if(memcmp(P,dictionary[n],length) == 0)
		{
			code=(short int)n;
			break;
		}
	}

	fwrite(&code,2,1,fpo);
	fcloseall();
}
