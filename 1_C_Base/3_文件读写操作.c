
/************************************************************************
* 功能：打开文件，并向文件中写入数据


************************************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	file * pfile;
	int buffer[8190] = { 0x01010101 };
	if ((pfile = fopen("myfile.txt", "wb")) == null)   //打开文件
	{ 
		printf("cant open the file");
		exit(0);
	}
	buffer[0] = 0x00000001;
	buffer[1] = 21665;

	buffer[3] = 0x00000001;
	buffer[4] = 21665;


	buffer[8100] = 0x00000001;
	buffer[8101] = 21667;
	//可以写多个连续的数据(这里一次写4个)
	fwrite(buffer, sizeof(int), 2500, pfile);
	fclose(pfile);                                 //最后的时候记得关闭文件
	return 0;
}


/************************************************************************
* 功能：打开文件，并向文件中写入数据，写入的是二进制格式
* SEEK_SET: 文件开始的位置
* SEEK_CUR: 当前文件指针位置
* SEEK_END: 文件结束的位置
************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
	file * fp;
	int buffer[4];
	if ((fp = fopen("myfile.mp4", "rb")) == null)        打开文件
	{
		printf("cant open the file");
		exit(0);
	}

	fseek(fp, 0, SEEK_END);    //将fp指针指向文件结束位置
	unsigned int  file_size;
	file_size = ftell(fp);    //这三行是为了读取文件大小
	
	fseek(fp, 0, SEEK_SET);   //将指针指向文件开头，这样下面可以从文件开头开始读数据

	printf("file size is %d", file_size);


	if (fread(buffer, sizeof(int), 4, fp) != 4)   //可以一次读取
	{
		printf("file read error\n");
		exit(0);
	}

	for (int i = 0; i<4; i++)
		printf("%d\n", buffer[i]);
	return 0;
}



/************************************************************************
* 功能：打开文件，并向文件中写入数据格式化数据

fprintf(fp, "%d", buffer); 是将格式化的数据写入文件
fprintf(文件指针,格式字符串,输出表列);

fwrite(&buffer, sizeof(int), 1, fp);是以二进位方式写入文件
fwrite(数据，数据类型大小（字节数），写入数据的最大数量，文件指针);
--------------------- 
作者：godenlove007 
来源：CSDN 
原文：https://blog.csdn.net/godenlove007/article/details/7721647 
版权声明：本文为博主原创文章，转载请附上博文链接！
************************************************************************/
//...
#include <cstdio>
int main(void) {
    FILE *FSPOINTER;
    char STRBUFF[16] = "Hello World.";
    //...
    FSPOINTER = fopen("HELLO.TXT", "w+");
    //...
    fprintf(FSPOINTER, "%s", STRBUFF);
    //...
    return 0;
}
// 输出至文件hello.txt：
// hello world