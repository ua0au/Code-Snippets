//获取树莓派CPU温度，核心是查看文件/sys/class/thermal/thermal_zone0/temp


#include <stdio.h>  
#include <stdlib.h>   

#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>


int main()   
{  
    int fc;  
    double tempc;  
    char buf1[8]; 
	
      
    // 以只读方式打开/sys/class/thermal/thermal_zone0/temp  
    fc = open( "/sys/class/thermal/thermal_zone0/temp" , O_RDONLY); 
	
	
    //判断文件是否正常被打开 
    if (fc < 0)
	{  
        fprintf(stderr, "failed to open Ctemp\n");  
        return -1;  
    }  
	
	 
      
    // 读取内容  
    if ((read(fc, buf1, 8) < 0))
	{  
        fprintf(stderr, "failed to read Ctemp\n");  
        return -1;  
    }  
	
	
      
    // 转换为浮点数打印  
    tempc = atoi(buf1) / 1000.0; 
    printf("temp: %.3f\n", tempc);
	
	
      
    // 关闭文件  
    close(fc);
	return 0;
} 

//*******************************************************************************


int get_CPU_temp(){

    int fc,;
	int tempc;  
    char cpubuf[8]; 
	
      
    // 以只读方式打开/sys/class/thermal/thermal_zone0/temp  
    fc = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY); 
	
	
    //判断文件是否正常被打开 
    if (fc < 0)
	{  
        fprintf(stderr, "failed to open Ctemp\n");  
        return -1;  
    }  
	
	   
    // 读取内容  
    if ((read(fc, cpubuf, 8) < 0))
	{  
        fprintf(stderr, "failed to read Ctemp\n");  
        return -1;  
    }  
	
 
    // 转换为浮点数打印  
    //tempc = atoi(cpubuf) / 1000.0; 
	
	//四舍五入保留两位小数
	//tempc=( (double)( (int)( (sp+0.005)*100 ) ) )/100;
	
	sscanf(cpubuf, "%2d", tempc);	//ssacnf，很强大，但是效率很低
	
    return(tempc);
	
	
    // 关闭文件  
    close(fc);
	
} 
