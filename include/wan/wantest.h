#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

#ifndef _WANTEST_H
#define _WANTEST_H

// LOG 封装
// 默认参数非空，若空会报错！运算连接符优化
#define LOG(frm, args...){\
	printf("[%s : %s : %d] ", __FILE__, __func__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}

// COLOR 封装
#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

// EXPECT 系列
/*
	- 保存参数 a，b：打印错误信息时，将其参数转化为字符串，要先将数值保存
	- 更新错误标记
*/
#define EXPECT(a, cmp, b){\
	__typeof(a) __a = (a), __b = (b); \
	if(!((__a) cmp (__b))){ \
		func_flag = 0; \
		printf(YELLOW("  %s:%d: Failure\n"), __FILE__, __LINE__); \
		printf(YELLOW("    Expected: (%s) %s (%s), actual:%d vs %d\n"),\
			#a, #cmp, #b, __a, __b \
		);\
	}\
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)

// TEST 封装
/*
	调用TEST(a, b){...} 
		=> 声明函数 FUNC_NAME(a, b)
		=> 注册函数设置
		=> 生成函数头 FUNC_NAME(a, b)()

	=> void FUNC_NAME(a, b)(){...} 相当于用宏写了一个样例函数，且注册到了存储区
*/
#define FUNC_NAME(a, b) wan_##a##_##b // wan_test1_add
#define TEST(a, b) \
void FUNC_NAME(a, b)();\
__attribute__((constructor)) \
void reg_##wan_##a##_##b(){ \
	add_test_function(FUNC_NAME(a, b), #a "." #b); \
} \
void FUNC_NAME(a, b)() 


struct FuncDate
{	
	void (*func)();
	const char* func_name;
} func_arr[100]; 
int func_arr_cnt = 0; 
int func_flag; // 全局变量，标记运行结果

void add_test_function(void (*func)(), const char *str){
	func_arr[func_arr_cnt].func = func;
	func_arr[func_arr_cnt].func_name = str;
	func_arr_cnt += 1;
	return;
}

// 设置颜色
const char *RUN    = YELLOW("[  RUN     ]");
const char *OK     = YELLOW("[      OK  ]");
const char *FAILED =    RED("[  FAILED  ]");

// RUN_ALL_TESTS 封装
int RUN_ALL_TESTS(){
	for(int i = 0; i < func_arr_cnt; ++i){ // 运行每个测试用例
		printf("%s %s\n", RUN, func_arr[i].func_name);
		func_flag = 1; // 标记运行结果

		long long start = clock(); // 记录运行时间
		func_arr[i].func();
		long long end = clock();

		if(func_flag){
			printf("%s %s " BLUE("(%lld ms)") "\n", 
				OK, 
				func_arr[i].func_name, 
				(end - start) * 1000 / CLOCKS_PER_SEC
			);
		}else{
			printf("%s %s " BLUE("(%lld ms)") "\n", 
				FAILED, 
				func_arr[i].func_name,
				(end - start) * 1000 / CLOCKS_PER_SEC
			);
		}

	}
	return 0;
} 

#endif
