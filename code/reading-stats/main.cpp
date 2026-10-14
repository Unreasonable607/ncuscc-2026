#include <iostream>

// 读数统计：读入 n 和 n 个整数，输出 count/sum/min/max
int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 1;
    }

    int count = 0;
    int sum = 0;
    int minv = 0;
    int maxv = 0;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        count++;
        sum += x;

        if (count == 1) {   // 第一个数直接当 min/max 的初始值，避免用 0 初始化
            minv = x;
            maxv = x;
        } else {
            if (x < minv) minv = x;
            if (x > maxv) maxv = x;
        }
    }

    std::cout << "count=" << count << "\n";
    std::cout << "sum=" << sum << "\n";
    std::cout << "min=" << minv << "\n";
    std::cout << "max=" << maxv << "\n";
    return 0;
}
