#ifndef __SORTER_H__
#define __SORTER_H__

class Sorter {
public:
    template<class T>
    static void quickSort(T *lo, T *hi) {
        if (lo < hi) {
            T *p = partition(lo, hi);
            quickSort(lo, p);
            quickSort(p+1, hi);
        }
    }

    template<class T>
    static T *partition(T *lo, T *hi) {
        T pivot = *lo;
        while (lo < hi) {
            hi--;
            while (lo < hi && !(*hi<pivot)) hi--; //hi表示第一个<pivot的位置，或hi
            *lo = *hi; //原来*lo所对应的位置的数被覆盖了
            if (lo < hi) lo++;
            while (lo < hi && !(pivot<*lo)) lo++; //lo表示第一个>pivot的位置，或hi
            *hi = *lo; //如果因为相等退出也是对的
        }
        *lo = pivot;
        return lo;
    }

    template<class T>
    static void insertSort(T *lo, T *hi) {
        if (lo == hi) return;
        for (T *i = lo+1; i != hi; ++i) {
            T val = *i;
            if (val < *lo) {
                for (T *j = i; j != lo; --j) {
                    *j = *(j-1);
                }
                *lo = val;
            } else {
                T *last = i, *next = i;
                --next;
                while (val < *next) {
                    *last = *next;
                    last = next;
                    --next;
                }
                *last = val;
            }
        }
    }

    template<class T>
    static void quickSort3(T *lo, T *hi) {
        if (lo < hi) {
            T *p = partition3(lo, hi);
            quickSort3(lo, p);
            quickSort3(p+1, hi);
        }
    }

    template<class T>
    static T *partition3(T *lo, T *hi) {
        T* mid = lo + (hi-lo)/2;
        hi--;
        T* p = median3(lo, mid, hi);
        std::swap(*p, *lo);
        T pivot = *lo;
        while (lo < hi) {
            while (lo < hi && !(*hi<pivot)) hi--;
            *lo = *hi;
            while (lo < hi && !(pivot<*lo)) lo++;
            *hi = *lo;
        }
        *lo = pivot;
        return lo;
    }

    template<class T>
    static T* median3(T* a, T* b, T* c) {
        if (*a < *b) {
            if (*b < *c) return b;
            else if (*a < *c) return c;
            else return a;
        }
        else if (*a < *c) return a;
        else if (*b < *c) return c;
        else return b;
    }

    template<class T>
    static void quickSortInsert(T *lo, T *hi) {
        if (hi - lo > 60) {
            T *p = partition(lo, hi);
            quickSortInsert(lo, p);
            quickSortInsert(p+1, hi);
        } else {
            insertSort(lo, hi);
        }
    }

    template<class T>
    static void quickSortInsert3(T *lo, T *hi) {
        if (hi - lo > 60) {
            T *p = partition3(lo, hi);
            quickSortInsert3(lo, p);
            quickSortInsert3(p+1, hi);
        } else {
            insertSort(lo, hi);
        }
    }

};

#endif
