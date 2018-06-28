#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];
int med[N];

/*
A[foo], A[bar]をスワップする関数
*/
void swap(int A[], int foo, int bar){
	int z = A[foo];
	A[foo] = A[bar];
	A[bar] = z;
}

/*
長さnが5以下の配列Aのk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
挿入ソートが適用
*/
int solve5(int A[], int n, int k){
	int i, j, min, z;
	for(i = 0; i < n; i++){
		min = i;
		for(j = i+1; j < n; j++){
			if(A[j] < A[min]) min = j;			
		}
		swap(A, i, min);
	}
	return A[k];
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
中央値の中央値アルゴリズムが適用
*/
int quick_select(int A[], int n, int k){
	if(n <= 5) return solve5(A, n, k);
	int block;				// 分割数
	int left;				// 分割していない部分の項数
	for(block = 0; (left = n-5*block) > 0; block++){
		if(left >= 5) med[block] = solve5(A+5*block, 5, 2);
		else med[block] = solve5(A+5*block, left, left/2);
	}

	int pivot, i, j;
	pivot = quick_select(med, block, block/2);
	for(i=0; i<n; i++){			// pivotを探し出して先頭に置く
		if(A[i] == pivot){
			swap(A, i, 0);
			break;
		}
	}

  for(i = j = 1; i < n; i++){
    if(A[i] <= pivot){
      int z = A[j];
      A[j] = A[i];
      A[i] = z;
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
