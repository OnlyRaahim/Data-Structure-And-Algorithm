https://leetcode.com/problems/sqrtx/submissions/1836557849/


int mySqrt(int x) {
    long long i = 0;

    while (i * i <= x) {
        i++;
    }

    return i - 1;
}
