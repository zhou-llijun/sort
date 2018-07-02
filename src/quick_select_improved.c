#include <stdio.h>

// フェルマー素数
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
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
	int pivot, l, r, i;

// issue #2に従って、A[0]とA[n/2]をスワップ 
	swap(A, 0, n/2);
// 先頭の要素をピボットとする
	pivot = A[0];
	l = 0;	// １つ目のpivotのインデックス
	r = n;	// pivot列の後にくる１つ目の他の要素のインデックス
	for(i = 1; i < r; i++){
		if(A[i] < pivot) swap(A, i, l++);
		else if(A[i] > pivot) swap(A, i--, --r);
	}
	if(l <= k && k < r) return pivot;
	else if(k >= r) return quick_select(A+r, n-r, k-r);
	else return quick_select(A, l, k);
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
	for(i=0;i<N;i++) {
		if(quick_select(I, N, i) != 0) printf("ERROR %d %d\n", i, quick_select(I, N, i));
	}

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
