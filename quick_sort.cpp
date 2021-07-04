#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <wan/wantest.h>
using namespace std;


void quick_sort_v1(int* arr, int l, int r){
	if(l >= r) return;

	int x = l, y = r, z = arr[l];
	while(x < y){

		while(x < y && arr[y] >= z) --y;
		if(x < y) arr[x++] = arr[y];
		while(x < y && arr[x] <= z) ++x;
		if(x < y) arr[y--] = arr[x];

	}
	arr[x] = z;

	quick_sort_v1(arr, l, x - 1);
	quick_sort_v1(arr, x + 1, r);
	return;
}

/* v2 改进：
	- 单边递归法：减少递归次数，只递归右侧
	- 三点取中法：优化枢轴选取
	- 无监督partition：双指针同时移动，采用交换而不是替换

*/

#define swap(a, b) { \
	__typeof(a) __a = a; \
	a = b, b = __a; \
}

inline int median(int a, int b, int c){
	if(a > b) swap(a, b); // a < b
	if(a > c) swap(a, c); // a < c
	if(b > c) swap(b, c); // b < c => a < b < c
	return b;
}

void quick_sort_v2(int* arr, int l, int r){
	while(l < r){

		int x = l, y = r, z = median(arr[l], arr[(l + r) >> 1], arr[r]);

		do{
			while(arr[x] < z) ++x;
			while(arr[y] > z) --y;
			if(x <= y){
				swap(arr[x], arr[y]);
				++x, --y;
			}

		}while(x <= y);

		quick_sort_v2(arr, x, r);
		r = y;
	}

	return;
}

/* v3 改进：
	- 小于阈值：快速排序
	- 大于阈值：插入排序，收尾
*/
const int threshold = 16;
void __quick_sort_v3(int* arr, int l, int r){
	while(r - l > threshold){

		int x = l, y = r, z = median(arr[l], arr[(l + r) >> 1], arr[r]);

		do{
			while(arr[x] < z) ++x;
			while(arr[y] > z) --y;
			if(x <= y){
				swap(arr[x], arr[y]);
				++x, --y;
			}

		}while(x <= y);

		__quick_sort_v3(arr, x, r);
		r = y;
	}

	return;
}

void insert_sort(int* arr, int l, int r){
	int ind = l;
	for(int i = l + 1; i <= r; ++i){  // 全局最小值
		if(arr[ind] > arr[i]) ind = i;
	}
	swap(arr[ind], arr[l]);

	for(int i = l + 2; i <= r; ++i){
		int j = i;
		while(arr[j] < arr[j - 1]){
			swap(arr[j], arr[j - 1]);
			--j;
		}
	}
	return;
}

void quick_sort_v3(int *arr, int l, int r){
	__quick_sort_v3(arr, l, r);
	insert_sort(arr, l, r);
	return;
}


// 使用自己的测试框架来测试

#define MAX_N 10000000
int *arr;
int* getRandData(int n){
	int *arr = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; ++i) arr[i] = rand() % n;
	return arr;
}

int* copyArray(int* arr, int n){
	int* temp = (int*)malloc(sizeof(int) * n);
	memcpy(temp, arr, sizeof(int) * n);
	return temp;
}

int check(int* arr, int n){
	for(int i = 1; i < n; ++i){
		if(arr[i] < arr[i - 1]) return 0;
	}
	return 1;
}

TEST(test, quick_sort_v1){
	int *temp = copyArray(arr, MAX_N);
	quick_sort_v1(temp, 0, MAX_N - 1);
	EXPECT_EQ(check(temp, MAX_N), 1);
}

TEST(test, quick_sort_v2){
	int *temp = copyArray(arr, MAX_N);
	quick_sort_v2(temp, 0, MAX_N - 1);
	EXPECT_EQ(check(temp, MAX_N), 1);
}

TEST(test, quick_sort_v3){
	int *temp = copyArray(arr, MAX_N);
	quick_sort_v3(temp, 0, MAX_N - 1);
	EXPECT_EQ(check(temp, MAX_N), 1);
}

int main(){
	srand(time(0)); // 设置随机种子
	arr = getRandData(MAX_N);

	return RUN_ALL_TESTS();

}

