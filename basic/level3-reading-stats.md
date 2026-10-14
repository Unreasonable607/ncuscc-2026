# 第 3 关 读数统计

这关不一样，是要写代码，不是敲命令。

任务：读入 n 和 n 个整数，输出 count / sum / min / max 四行。

工作区里给了两个模板二选一，C++17 的 main.cpp 和 C11 的 c/main.c。我用的 C++ 那个。

## 两个坑

一个是模板里特意写了的：min 和 max **不能用 0 初始化**。一开始没懂为什么要专门强调，想了一下才明白——如果输入的数是全正数，min 从 0 开始的话，最后输出的最小值就变成 0 了，可实际上 3 才是最小的。

绕过去的办法是拿第一个读进来的数当初始值：

    if (count == 1) {   // 第一个数直接当初始值
        minv = x;
        maxv = x;
    } else {
        if (x < minv) minv = x;
        if (x > maxv) maxv = x;
    }

另一个是提示 2 说的：根目录只能留一个入口文件。工作区里同时有 main.cpp 和 c/main.c，所以要把不用的那个删掉：

    rm -r c

## 跑样例

编译：

    g++ -std=c++17 -Wall -Wextra -o main main.cpp

编译成功一点输出都没有，一开始还以为是没反应。

跑第一个样例：

    ./main < samples/01-mixed.in

    count=5
    sum=10
    min=-1
    max=5

跟期望输出对比：

    diff <(./main < samples/01-mixed.in) samples/01-mixed.out

diff 没有输出，说明一模一样。02 和 03 也跑了，都通过。

## 记一个新符号

`./main < samples/01-mixed.in` 里的 `<` 是输入重定向，把文件的内容当成程序的输入喂进去。之前学的 `>` 是把输出写进文件，`<` 正好反过来。

## 补充

02 和 03 两个样例也跑了：

    diff <(./main < samples/02-single.in) samples/02-single.out
    diff <(./main < samples/03-alternating.in) samples/03-alternating.out

两个都没有输出，也就是全部通过。
