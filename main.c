#include <stdio.h>
#include <stdlib.h>

void main( int argc, char *argv[])
{
	struct pattern {
		long int magic;
		};
	
	struct pattern pat;
	
	long int real_magic = 0xefbeadde; //little endian of 0xdeadbeef
	long int lSize;
	int i;
	int count = 0;
	long int position = 0;
	long int diff = 0;
	long int position_array[5] = {0,0,0,0,0};
	FILE *fp;
	
	
	if (argc !=2)
		{
		printf("\n Usage: norcheck.exe filename \n");
		printf(" (C) bluemimmosa  2011\n");
		exit(1);
		}
	
	fp = fopen(argv[1], "rb");
	if (fp == NULL)
		{
		printf("\n Cannot open file..... Quits\n");
		exit(1);
		}
		
	fseek (fp , 0 , SEEK_END);
	lSize = ftell (fp);
	rewind (fp);
	
	if (lSize != 16777216)
		{
		printf("\n Dumps doesnt seem to be correct, size doesnt match 16,777,216 bytes....\n");
		exit(1);
		}
		
	while (fread(&pat, sizeof(pat),1,fp) == 1)
	{
		if(pat.magic == real_magic)
		{
			position_array[count] = position;
			count++;
		}
		position = position+4;
		//printf("\n pat.magic = %x", pat.magic);
	}
	
	if (count>1)
		{
			printf("\n The magic header 0xDEADBEEF seems to be repeated %d times", count);
			for(i=0; i<count; i++)
			{
				printf("\n The position header found are 0x%x",position_array[i]);
			}
			diff = position_array[1] - position_array[0];
			printf("\n The difference is %x", diff);
			printf("\n The dumps is probably bad, pls check your progskeet wiring for bad #address lines....\n");
		}
	else
		{
			printf("\n The magic header 0xDEADBEEF seems to be repeated %d times", count);
			for(i=0; i<count; i++)
			{
				printf("\n The position header found are 0x%x",position_array[i]);
			}
			printf("\n The dumps seems to be okay, but pls verify it again with norunpack or flowrebuilder....");
		}
		
	fclose(fp);
	
}

		
		
