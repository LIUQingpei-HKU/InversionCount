#include <iostream>
#include "TestHelper.h"

using namespace std;

// 计算逆序数对的结果以long long返回
// 对于一个大小为N的数组, 其最大的逆序数对个数为 N*(N-1)/2, 非常容易产生整型溢出

// merge函数求出在arr[l...mid]和arr[mid+1...r]有序的基础上, arr[l...r]的逆序数对个数
long long __merge(int arr[], int l, int mid, int r){
    int *aux = new int[r-l+1];
    for(int i=l;i<=r;i++)
        aux[i-l] = arr[i];
    //initialize
    long long res = 0;
    int j=l,k=mid+1;
    for(int i=l;i<=r;i++){
        if(j>mid){
            arr[i] = aux[k-l];
            k++;
        }else if(k>r){
            arr[i] = aux[j-l];
            j++;
        }else if(aux[j-l]<=aux[k-l]){
            arr[i] = aux[j-l];
            j++;
        }else{//aux[j-l]>aux[k-l]
            arr[i] = aux[k-l];
            k++;
            res +=(long long)(mid-j+1);
        }
    }

    delete[] aux;
    return res;
}


long long __inversionCount(int arr[], int l, int r){
    if(l>=r)
        return 0;
    int mid = l + (r-l)/2;//l+r may cause memory overflow

    //inversion count for arr[l...mid]
    long long res1 = __inversionCount(arr,l, mid);
    //inversion count for arr[mid+1...r]
    long long res2 = __inversionCount(arr,mid+1,r);

    return res1 + res2 + __merge(arr,l,mid,r);
}

long long inversionCount(int arr[], int n){
    return __inversionCount(arr,0,n-1);
}

int main() {

    int n = 1000000;

    // 测试1: 测试随机数组
    cout<<"Test Inversion Count for Random Array, n = "<<n<<" :"<<endl;
    int* arr = TestHelper::generateRandomArray(n, 0, n);
    cout<<inversionCount(arr, n)<<endl<<endl;
    delete[] arr;

    // 测试2: 测试完全有序的数组
    // 结果应该为0
    cout<<"Test Inversion Count for Ordered Array, n = "<<n<<" :"<<endl;
    arr = TestHelper::generateOrderedArray(n);
    cout<<inversionCount(arr, n)<<endl<<endl;
    delete[] arr;

    // 测试3: 测试完全逆序的数组
    // 结果应改为 N*(N-1)/2
    cout<<"Test Inversion Count for Inversed Array, n = "<<n<<" :"<<endl;
    arr = TestHelper::generateInversedArray(n);
    cout<<inversionCount(arr, n)<<endl;
    delete[] arr;

    return 0;
}