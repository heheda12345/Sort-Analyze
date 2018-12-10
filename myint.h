#ifndef MYINT_H
#define MYINT_H

struct MyInt {
    int x;
    static int cmpCnt;
    bool operator < (const MyInt &b) {
        MyInt::cmpCnt++;
        return x < b.x;
    }
};



#endif // MYINT_H
