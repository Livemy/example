
	#include <dlfcn.h>

	int main(int argc, char *argv[])
	{

		const char *msg;
		int rtn;
		void *handle;
		int (*testdl)(int n, char *str);

		//�򿪶�̬��
		handle = dlopen("./libtest.so", RTLD_LAZY);
		if(!handle) {
			printf("dlopen() error: %s\n", dlerror());
			exit(1);
		}

		//ȡ�÷��Ų�������
		testdl = dlsym(handle, "output");
		msg = dlerror();
		if(msg) {
			printf("Error fetching 'output':%s\n", msg);
			exit(1);
		}

		//ʹ�÷���
		rtn = testdl(3, "Hello World!");
		printf("returned: %d\n", rtn);
		

	}
