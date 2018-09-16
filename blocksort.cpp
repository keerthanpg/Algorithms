#include <iostream>
using namespace std;
/*
Recursively, we find the max element and send it to 
the last unsorted position at right end
then we sort the array from 0 to i excluding 
the elements at the end which are already sorted
in each case, it takes at most 4 block swaps to send an 
element to its correct place
Assuming we run the algorithm for n elements, number of swaps is at most 4n
*/

void arrayswap(int A[], int i, int k){
	int temp;
	cout << i << " " << k << endl;
	for(int j = i; j < i+k; j++){
		temp = A[j];
		A[j] = A[j+k];
		A[j+k] = temp;
	}
	/*	

	for ( i = 0; i < 10 ; i++)
		cout << A[i] <<" ";
	cout<<endl;*/

}

void blockswap(int A[], int n){
	int maxpos, i, j;
	for(i=n-1; i>=0; i--){		
		// i+1 is the number of unsorted elements at any given time
		//cout << " i = " << i << endl;				
		for (j=0; j<=i; j++){
			if (i == A[j]){				
				maxpos = j;
				//cout << " i = " << i <<" maxpos=" << maxpos << endl;
			}
		}
		// now we know where maximum element is located and we just need
		// to send it to ith position
		if (maxpos == i){
			//cout << "already in place" << endl;
			continue;
		}
		else if ((i+1)%2 == 0){
			// if even number of unsorted positions			
			if (maxpos<(i+1)/2){				
				arrayswap(A, 0, (i+1)/2);
				if(A[i] != i){
					arrayswap(A,(i+1)/2 -(maxpos+1), (maxpos+1));
					arrayswap(A, 0, (i+1)/2);
				}
			}
			else{
				arrayswap(A, (i+1)-(maxpos+1), (maxpos+1) - (i+1)/2);
				arrayswap(A, 0, (i+1)/2);
			}
		}
		else{
			if (maxpos == 0){
				// if its the first element, make it the second element
				arrayswap(A, 0, 1);
				maxpos = 1;
			}
			if (maxpos<=i/2){				
				arrayswap(A, 1, i/2);
				if(A[i] != i){
					arrayswap(A, i/2 + 1 - maxpos, maxpos);
					arrayswap(A, 1, i/2);
				}
			}
			else{
				arrayswap(A, i - maxpos + 1, maxpos - i/2);
				arrayswap(A, 1, i/2);
			}

		}
	}
	cout << 0 << " " << 0 << endl;
	/*
	for ( i = 0; i < n ; i++)
		cout << A[i] <<" ";*/

}


int main(){
	int n, A[30001];
	cin >> n;
	for (int i=0; i<n; i++){
		cin >> A[i];
	}
	blockswap(A, n);
	return 0;
}