
#include <sys/vfs.h>


	
void freedisk_is_ok(){
	
		struct statfs diskInfo;
		statfs("/root", &diskInfo);
		
		unsigned long long totalBlocks = diskInfo.f_bsize;
		unsigned long long totalSize = totalBlocks * diskInfo.f_blocks;
		
		size_t mbTotalsize = totalSize>>20;
		unsigned long long freeDisk = diskInfo.f_bfree*totalBlocks;
		size_t mbFreedisk = freeDisk>>20;
		
		//printf ("/  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);
		

		if(mbFreedisk<1024){
			printf("���̿ռ�С��1G��δ����������е��г��ִ���\n��������������������̿ռ�֮�����������ó���лл��\n");
			exit(0);
		}

}


