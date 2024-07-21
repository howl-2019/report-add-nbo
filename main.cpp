#include<stdio.h>
#include<stdint.h>
#include<stddef.h>
#include<stdlib.h>


int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("arg error\n");
		return -1;
	}
	FILE* fd1 = fopen(argv[1], "rb");
	if(fd1 == NULL)
	{
		printf("first file fopen error\n");
		return 0;
	}
	FILE* fd2 = fopen(argv[2], "rb");
	if(fd2 == NULL)
	{
		printf("second file fopen error\n");
		return 0;
	}

	unsigned char thousand[5] = {"\0"};
	unsigned char five[5] = {"\0"};

	int result1 = fread(thousand, 1, 4, fd1);
	if(result1 < 4)
	{
		printf("first file is too short\n");
		return 0;
	}
	int result2 = fread(five, 1, 4, fd2);
	if(result2 < 4)
	{
		printf("second file is too short\n");
		return 0;
	}

	uint32_t l = 0;
	uint32_t r = 0;

	for(int i=0; i < 4; i++)
	{
		uint32_t t = thousand[i];
		t = t << 8 * (3 - i);
		l += t;
	}
	for(int i=0; i < 4; i++)
	{
		uint32_t t = five[i];
		t = t << 8 * (3 - i);
		r += t;
	}

	printf("%d(0x%04x) + %d(0x%04x) = %d(0x%04x)\n", l, l, r, r, l + r, l + r);
	fclose(fd1);
	fclose(fd2);
	return 0;
}
