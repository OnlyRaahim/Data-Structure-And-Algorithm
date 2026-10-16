//https://leetcode.com/problems/product-of-the-last-k-numbers/submissions/2174165035/


class ProductOfNumbers {
private:
    vector<int> prefix;

public:
    ProductOfNumbers() {
        prefix.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            prefix.clear();
            prefix.push_back(1);
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }

    int getProduct(int k) {
        if (k >= prefix.size()) {
            return 0;
        }

        return prefix.back() / prefix[prefix.size() - k - 1];
    }
};
