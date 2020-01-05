//调用执行Linux命令


#include <stdlib.h>  
#include <stdio.h>

int main(int argc, char *argv[]){
	

	FILE *fgpu;

	char buffer[15];

	fgpu=popen("vcgencmd measure_temp","r");	//temp=36.5'C

	/*
	//从文件结构体指针stream中读取数据，每次读取一行。超过一行，仅读完当前行，随后指向文件的指针会自动偏移至下一行，循环调用即可解决

		while(fgets(buffer,sizeof(buffer),fgpu)!=NULL){
			
				printf("%s",buffer);
		}
	*/


	fgets(buffer,sizeof(buffer),fgpu);
	
	float a;
	
	sscanf(buffer,"%*5c%f",&a);
		
	printf("%g\n",a);	//float不再末尾补0


	pclose(fgpu);
	return 0;
}


int get_GPU_temp(){
	
	FILE *fgpu;

	char buffer[15];

	fgpu=popen("vcgencmd measure_temp","r");	//temp=36.5'C

	fgets(buffer,sizeof(buffer),fgpu);
	
	int a;
	
	sscanf(buffer,"%*5c%d",&a);

	return a;

	pclose(fgpu);	
	
}

