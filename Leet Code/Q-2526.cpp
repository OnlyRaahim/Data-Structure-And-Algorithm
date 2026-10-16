//https://leetcode.com/problems/find-consecutive-integers-from-a-data-stream/submissions/2174166256/


class DataStream {
private:
    int value;
    int k;
    int count;

public:
    DataStream(int value, int k) {
        this->value = value;
        this->k = k;
        count = 0;
    }

    bool consec(int num) {
        if (num == value) {
            count++;
        } else {
            count = 0;
        }

        return count >= k;
    }
};
