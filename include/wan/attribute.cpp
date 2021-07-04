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


void (*FuncArr[3])() = {0};

void test1(){
	printf("hello function test1\n");
	return;
}

void test2(){
	printf("hello function test2\n");
	return;
}

void test3(){
	printf("hello function test3\n");
	return;
}

__attribute__((constructor))
void reg1(){
	FuncArr[0] = test1;
	return;
}

__attribute__((constructor))
void reg2(){
	FuncArr[1] = test2;
	return;
}

__attribute__((constructor))
void reg3(){
	FuncArr[2] = test3;
	return;
}

int main(){
	
	// 随机调用
	srand(time(0));
	
	FuncArr[rand() % 3](); 
	return 0;
}
