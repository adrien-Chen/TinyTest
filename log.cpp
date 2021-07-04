#include <stdio.h>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <getopt.h>
using namespace std;

// 默认参数非空，若空会报错！运算连接符优化
#define LOG(frm, args...){\
	printf("[%s : %d]", __FILE__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}

int main(){
    int a = 1, b = 2;
    printf("a = %d, b = %d\n", a, b);
    LOG("a = %d, b = %d", a, b);
    return 0;
}
