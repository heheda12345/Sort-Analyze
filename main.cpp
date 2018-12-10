#include <iostream>
#include <algorithm>
#include <fstream>
#include "timer.h"
#include "sorter.h"
#include "myint.h"
using namespace std;


int rd() {
    int x = 0;
    for (int i = 0; i < 10; i++)
        x = x*233333+rand();
    return x < 0 ? -x : x;
}

template<class T>
void my_random_shuffle(T *a, T *b) {
    int n = b - a;
    for (int i=1; i<n; i++)
        swap(a[i], a[rd()%(i+1)]);
}

void test_quick_insert_1_11() {
    const int mxn = 11;
    int a[mxn], b[mxn];
    MyTimer t;
    for (int n=1; n<=mxn; n++) {
        // test quickSort
        for (int i=0; i<n; i++)
            a[i] = i;
        t.start();
        do {
            memcpy(b, a, sizeof(int)*n);
            Sorter::quickSort(b, b+n);
        } while (next_permutation(a, a+n));
        t.end();
        printf("quick sort %d : %lf\n", n, t.used());
        t.reset();
        // test insertSort
        for (int i=0; i<n; i++)
            a[i] = i;
        t.start();
        do {
            memcpy(b, a, sizeof(int)*n);
            Sorter::insertSort(b, b+n);
        } while (next_permutation(a, a+n));
        t.end();
        printf("insert sort %d : %lf\n", n, t.used());
        t.reset();
    }
}

void test_quick_insert_larger() {
    int *a = new int[100000000];
    int m = 1e6;
    int b[150];
    for (int n=1; n<=100; n++) {
        for (int i=0; i<n; i++)
            b[i] = i;
        int mn = m*n;
        for (int x=0; x<mn; x+=n) {
            random_shuffle(b, b+n);
            memcpy(a+x, b, sizeof(int)*n);
        }
        MyTimer t;

        t.start();
        for (int x=0; x<mn; x+=n) {
            memcpy(b, a+x, sizeof(int)*n);
            Sorter::quickSort(b, b+n);
        }
        t.end();
        printf("quick sort %d : %lf", n, t.used()); cout << endl;
        t.reset();

        t.start();
        for (int x=0; x<mn; x+=n) {
            memcpy(b, a+x, sizeof(int)*n);
            Sorter::insertSort(b, b+n);
        }
        t.end();
        printf("insert sort %d : %lf", n, t.used()); cout << endl;
        t.reset();
    }
    delete a;
}

void test_quick_middle3_cmp() {
    int *a = new int[5000000];
    MyInt* b = new MyInt[5000000];
    for (int n=1; n<=(1<<20); n<<=1) {
        int cntRaw = 0, cntMid = 0;
        for (int t=0; t<10; t++) {
            for (int i=0; i<n; i++)
                a[i] = i;
            random_shuffle(a+1, a+n+1);

            for (int i=0; i<n; i++)
                b[i].x = a[i];
            MyInt::cmpCnt = 0;
            Sorter::quickSort(b, b+n);
            cntRaw += MyInt::cmpCnt;

            for (int i=0; i<n; i++)
                b[i].x = a[i];
            MyInt::cmpCnt = 0;
            Sorter::quickSort3(b, b+n);
            cntMid += MyInt::cmpCnt;
        }
        printf("%d : raw %.1lf mid %.1lf", n, cntRaw/10.0, cntMid/10.0); cout<<endl;
    }
    delete a;
    delete b;
}

void test_quick_middle3_time() {
    int **a = new int*[10];
    for (int i=0; i<10; i++) a[i] = new int[1500000];
    int* b = new int[1500000];
    for (int n=1; n<=(1<<20); n<<=1) {
        for (int t=0; t<10; t++) {
            for (int i=0; i<n; i++)
                a[t][i] = i;
            random_shuffle(a[t]+1, a[t]+n+1);
        }
        MyTimer t;

        t.start();
        for (int j=0; j<10; j++) {
            for (int i=0; i<n; i++)
                b[i] = a[j][i];
            Sorter::quickSort(b, b+n);
        }
        t.end();
        double raw = t.used();

        t.start();
        for (int j=0; j<10; j++) {
            for (int i=0; i<n; i++)
                b[i] = a[j][i];
            Sorter::quickSort3(b, b+n);
        }
        t.end();
        double mid = t.used();
        printf("%d : raw %lf mid %lf", n, raw, mid); cout<<endl;
    }
    for (int i=0; i<10; i++) delete a[i];
    delete a;
    delete b;
}

void test_quick_middle3_insert_cmp() {
    int *a = new int[5000000];
    MyInt* b = new MyInt[5000000];
    for (int n=1; n<=(1<<20); n<<=1) {
        int cntRaw = 0, cntMid = 0;
        for (int t=0; t<10; t++) {
            for (int i=0; i<n; i++)
                a[i] = i;
            random_shuffle(a+1, a+n+1);

            for (int i=0; i<n; i++)
                b[i].x = a[i];
            MyInt::cmpCnt = 0;
            Sorter::quickSortInsert(b, b+n);
            cntRaw += MyInt::cmpCnt;

            for (int i=0; i<n; i++)
                b[i].x = a[i];
            MyInt::cmpCnt = 0;
            Sorter::quickSortInsert3(b, b+n);
            cntMid += MyInt::cmpCnt;
        }
        printf("%d : quick_insert %.1lf quick_insert_3 %.1lf", n, cntRaw/10.0, cntMid/10.0); cout<<endl;
    }
    delete a;
    delete b;
}

void test_quick_middle3_insert_time() {
    int **a = new int*[10];
    for (int i=0; i<10; i++) a[i] = new int[1500000];
    int* b = new int[1500000];
    for (int n=1; n<=(1<<20); n<<=1) {
        for (int t=0; t<10; t++) {
            for (int i=0; i<n; i++)
                a[t][i] = i;
            random_shuffle(a[t]+1, a[t]+n+1);
        }
        MyTimer t;

        t.start();
        for (int j=0; j<10; j++) {
            for (int i=0; i<n; i++)
                b[i] = a[j][i];
            Sorter::quickSortInsert(b, b+n);
        }
        t.end();
        double raw = t.used();

        t.start();
        for (int j=0; j<10; j++) {
            for (int i=0; i<n; i++)
                b[i] = a[j][i];
            Sorter::quickSortInsert3(b, b+n);
        }
        t.end();
        double mid = t.used();
        printf("%d : quick_insert %lf quick_insert_3 %lf", n, raw, mid); cout<<endl;
    }
    for (int i=0; i<10; i++) delete a[i];
    delete a;
    delete b;
}

void sort_of_100_times() {
    /*
    对n=1,2,...2^20,分别运行100次随机快速排序，记录比较次数
    */
    ofstream out;
    out.open("100_times_log.csv");
    int mxn = 20;
    const int tm = 100;
    MyInt *a = new MyInt[2000010];
    out << "n,";
    for (int i=0; i<tm; i++) out << i << ',';
    out << endl;
    for (int i=0; i<=mxn; i++) {
        printf("exec %d\n", i);
        int n = 1 << i;
        out << n << ",";
        for (int j=0; j<tm; j++) {
            for (int k=0; k<n; k++)
                a[k].x = k;
            my_random_shuffle(a, a+n);
            MyInt::cmpCnt = 0;
            Sorter::quickSort(a, a+n);
            out << MyInt::cmpCnt << ',';
        }
        out << endl;
    }
    delete a;

}

int main()
{
    // sort_of_100_times();
    return 0;
}
