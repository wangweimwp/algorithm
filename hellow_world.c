#include <stdio.h>
#include "list.h"
#include "binary_tree.h"
#include "heap.h"
#include "red_black_tree.h"
#include "union_find.h"
#include "graph.h"



static int max(int a, int b)
{
	a > b ? a : b;
}

static int func1(int *a, int left, int right)
{
	int max_left_sum = 0, max_right_sum = 0;
	int i = 0;
	int center = (right + left) / 2;

	
	if(left == right){
		if(a[left] > 0){
			return a[left];
		}else{
			return 0;
		}
	}

	max_left_sum = func1(a, left, center);
	max_right_sum = func1(a, center + 1, right);

	int max_left_sq_sum = 0;
	int max_left_sq_temp_sum = 0;
	
	for(i = center; i >=left; i--){
		max_left_sq_temp_sum += a[i];
		if(max_left_sq_sum < max_left_sq_temp_sum)
			max_left_sq_sum = max_left_sq_temp_sum;
	}

	int max_right_sq_sum = 0;
	int max_right_sq_temp_sum = 0;

	for(i = center + 1; i < right; i++){
		max_right_sq_temp_sum += a[i];
		if(max_right_sq_sum < max_right_sq_temp_sum)
			max_right_sq_sum = max_right_sq_temp_sum;
	}
	
	return max(max(max_left_sum, max_right_sum), max_right_sq_sum + max_left_sq_sum);
}

int as_arry[20] = { 0 };

/*归并排序*/
void fun2(int *a, int left, int right)
{
	if(left >= right)
		return;
	int mid = (left + right) / 2;

	fun2(a, left, mid);
	fun2(a, mid + 1, right);


	int index_1 = left, index_2 = mid + 1;
	int index_3 = left;
	#if 0
	while((index_1 <= mid) && (index_2 <= right)){
		if(a[index_1] < a[index_2]){
			as_arry[index_3 ++] = a[index_1 ++];
		}else{
			as_arry[index_3 ++] = a[index_2 ++];
		}		
	}

	while(index_1 <= mid){
		as_arry[index_3 ++] = a[index_1 ++];
	}

	while(index_2 <= right){
		as_arry[index_3 ++] = a[index_2 ++];
	}

	for(int i = left; i <= right; i++){
		a[i] = as_arry[i];
	}
	#else
	while(index_3 <= right){
		if(a[index_1] < a[index_2]){
			if(index_1 <= mid)
				as_arry[index_3 ++] = a[index_1 ++];
			else 
				as_arry[index_3 ++] = a[index_2 ++];
		}else{
			if(index_2 <= right)
				as_arry[index_3 ++] = a[index_2 ++];
			else
				as_arry[index_3 ++] = a[index_1 ++];
		}		
	}

	for(int i = left; i <= right; i++){
		a[i] = as_arry[i];
	}
	
	#endif
}

/*快速排序*/
void fun3(int *a, int left, int right)
{
	if(left >= right)
		return;
	int left_tmp = left;
	int right_tmp = right + 1;
	int key = a[left];
	int temp;

	while(1){
		while(key < a[--right_tmp])//注意这里必须时--right_tmp 不可以right_tmp--
			if(right_tmp == left_tmp)
				break;

		while(key > a[++left_tmp])//注意这里必须时++left_tmp 不可以left_tmp++
			if(left_tmp == right_tmp)
				break;

		if(left_tmp >= right_tmp)
			break;
		else{
			temp = a[left_tmp];
			a[left_tmp] = a[right_tmp];
			a[right_tmp] = temp;
		}
	
	}
	temp = a[left];
	a[left] = a[right_tmp];
	a[right_tmp] = temp;

	fun3(a, left, right_tmp - 1);
	fun3(a, right_tmp + 1, right);
	
}

int arry[] = {4, -3, 5, -2, -1, 2, 6, -2}; 
int arry1[] = {8, 4, 11, 7, 20, 33, 6, 2, 9, 25};





int main()
{
	int max = 0;

	#if 0
	max = func1(arry, 0, sizeof(arry) / 4);
	printf("max = %d \n", max);

	fun3(arry1, 0, sizeof(arry1) / sizeof(arry1[0]) - 1);
	for(int i = 0; i < sizeof(arry1) / sizeof(arry1[0]); i++){
		printf("%d ", arry1[i]);
	}
	printf("\n");
	list_reverse_test();

	binary_tree_test();
	heap_test();
	red_black_tree_test();
	union_find();
	graph_test();
	#endif
	top_logic_test();
	return 0;
}

























