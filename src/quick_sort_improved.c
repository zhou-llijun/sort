#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[foo], A[bar]をスワップする関数
*/
void swap(int A[], int foo, int bar){
	int z = A[foo];
	A[foo] = A[bar];
	A[bar] = z;
}

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
	if(n <= 1) return;
	int pivot, l, r, i;
	pivot = A[0];
	l = 0;	// １つ目のpivotのインデックス
	r = n;	// pivot列の後にくる１つ目の他の要素のインデックス
	for(i = 1; i < r; i++){
		if(A[i] < pivot) swap(A, i, l++);
		if(A[i] > pivot) swap(A, i--, --r);
	}
	quick_sort(A, l);
	quick_sort(A+r, n-r);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する
	int I[N];
	for(i=0;i<N;i++) I[i] = 0;
	quick_sort(I, N);

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
