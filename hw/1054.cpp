#include <bits/stdc++.h>

using namespace std;

const int CutOff = 14;

void insertion_sort(vector<int>& array, int left, int right) {
    for(int p = left + 1; p <= right; p++) {
        int temp = array[p];
        int j;
        for(j = p; j > left && array[j - 1] > temp; j--) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}

void get_median(vector<int>& array, int left, int right) {
    int mid = (left + right) / 2;

    if(array[left] > array[right]) {
        swap(array[left], array[right]);
    }

    if(array[left] > array[mid]) {
        swap(array[left], array[mid]);
    }

    if(array[mid] > array[right]) {
        swap(array[mid], array[right]);
    }

    swap(array[mid], array[left + 1]);
}

void quick_sort(vector<int>& array, int left, int right) {
    if(right - left <= CutOff) {
        insertion_sort(array, left, right);
    } else {
        get_median(array, left, right);
        int pivot = array[left + 1];

        int i = left + 1;
        int j = right;

        for(;;) {
            while(array[++i] < pivot) {
            } 
            while(array[--j] > pivot) {
            }

            if(i >= j) {
                break;
            }

            swap(array[i], array[j]);
        }
        swap(array[j], array[left + 1]);

        quick_sort(array, left, j - 1);
        quick_sort(array, j + 1, right);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> array(n);
    
    for(int i = 0; i < n; i++) {
        cin >> array[i];
    }

    quick_sort(array, 0, n - 1);

    for(int i = 0; i < n; i++) {
        cout << array[i] << (i == n - 1? "\n" : " ");
    }
}