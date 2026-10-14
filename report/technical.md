# 技术报告

## 一、环境搭建

### 1.1 为什么需要 Linux

考核的三个进阶方向都提到 Linux 或 WSL。真正的超算集群也是 Linux 环境，所以这一步绕不过去。

### 1.2 遇到的第一个问题：官方安装方式卡住

按官方文档执行：

    wsl --install -d Ubuntu-22.04

等了二十多分钟没有明显进展。检查 Windows 功能状态，发现仍然是 Disabled —— 这二十分钟里它连第一步（启用功能）都没完成。

判断原因是：这条命令把「启用 Windows 功能」和「从微软服务器下载组件」绑在一次操作里。国内访问微软下载源速度很差，下载卡住之后，前面已经完成的部分也无法体现出来。

### 1.3 解决：拆成三步手动做

**第一步**，用系统自带的 DISM 工具在本地启用两个功能。这一步不涉及下载，几秒钟就完成：

    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

返回值 3010 表示「操作成功，需要重启」。

**第二步**，重启电脑。Windows 功能只有重启后才真正加载。

**第三步**，分别下载两个组件：

- WSL 组件：从 GitHub Releases 下载官方 MSI 包，实测约 5.8 MB/s
- Ubuntu 发行版：从国内镜像下载 rootfs 包，实测约 13 MB/s

导入发行版：

    wsl --import Ubuntu-22.04 D:\WSL\Ubuntu-22.04 ubuntu-jammy-rootfs.tar.gz

整个过程约 4 分钟完成。

### 1.4 系统配置

- 安装位置放在 D 盘，避免占用 C 盘空间
- 软件源换成国内镜像，否则 `apt install` 同样很慢
- 装了 build-essential、python3-pip、git、curl、wget、vim、htop 等常用工具
- 终端原本每次打开都落在 Windows 的 C 盘目录，在主目录的 shell 配置文件里加了一行，让它自动回到 Linux 家目录

## 二、基础关卡

### 2.1 第 1 关：找到入口

**任务**：在离线工作区里，用提供的 `exam` 程序处理材料，产出 `/workspace/flag`。

先看工作区里有什么：

    ls -la /workspace

    cabinet/   exam   input.bin   logs/

`exam` 的权限是 `-rwxr-xr-x`，有 `x`，说明可以直接运行。

不知道怎么用，就查它的帮助信息：

    /workspace/exam --help

输出说明它读取 `/workspace/input`，把结果写入 `/workspace/output`。

**这里遇到第一个坑**：程序要读的是 `input`，但目录里只有 `input.bin`，名字多了一个后缀。程序只认写死的名字，所以要自己建立对应关系：

    cp /workspace/input.bin /workspace/input

密钥在子目录 `cabinet/` 里（`logs/` 是空的，属于干扰项）：

    cat /workspace/cabinet/key.txt

运行程序：

    /workspace/exam -e <密钥>
    echo $?

`echo $?` 显示上一条命令的退出码，0 表示成功。程序成功时没有任何输出，一开始容易误以为失败。

**第二个坑**：程序产出的是 `output`，而通关要求的是 `flag`，名字又对不上：

    cp /workspace/output /workspace/flag

这一关的设计是两次「名字不一致」，需要主动建立映射，而不是期待程序适应现成的文件名。

### 2.2 第 2 关：两段信号

**任务**：找出两份信号文件，用清单里的密钥分别处理，结果按 A 段在前、B 段在后拼成 `/workspace/flag`。

    find /workspace -type f

    /workspace/inbox/signal-B.bin
    /workspace/archive/2026/signal-A.bin
    /workspace/archive/2026/notes-A.txt
    /workspace/catalog/words.txt

两份信号分布在不同的目录层级里。

找密钥：

    grep -r "ACCESS_KEY=" /workspace

    /workspace/catalog/words.txt:ACCESS_KEY=STAR

密钥是 `STAR` 这一部分，不是整行。程序参数需要的是等号后面的值。

**核心难点**：`exam` 永远只写 `/workspace/output` 一个位置。处理完 A 段再处理 B 段，A 段的结果会被覆盖。

解决办法是每处理完一段就立刻另存：

    cp /workspace/archive/2026/signal-A.bin /workspace/input
    /workspace/exam -e STAR
    cp /workspace/output /workspace/partA

    cp /workspace/inbox/signal-B.bin /workspace/input
    /workspace/exam -e STAR
    cp /workspace/output /workspace/partB

最后按顺序拼接：

    cat /workspace/partA /workspace/partB > /workspace/flag

验证字节数，`wc -c /workspace/flag` 得到 32，等于 A 段 16 字节加 B 段 16 字节。

### 2.3 第 3 关：读数统计

**任务**：修复一个统计程序，读入 n 个整数，输出 count / sum / min / max。

模板给了框架，但提示里特意强调：**min 不要用 0 初始化**。

原因是如果输入全是正数，`min` 从 0 开始就永远不会被更新，最后输出的最小值会错误地变成 0。

解决办法是让第一个读入的数直接作为 min 和 max 的初始值：

    if (count == 1) {
        minv = x;
        maxv = x;
    } else {
        if (x < minv) minv = x;
        if (x > maxv) maxv = x;
    }

另一个要求是根目录只能保留一个入口文件。工作区里同时有 `main.cpp` 和 `c/main.c`，所以删掉不用的：

    rm -r c

编译和自测：

    g++ -std=c++17 -Wall -Wextra -o main main.cpp
    diff <(./main < samples/01-mixed.in) samples/01-mixed.out

`diff` 没有任何输出，说明完全一致。三个样例都通过。

## 三、Git 与 GitHub

考核要求提交 GitHub 仓库链接，所以这部分是必须的。

### 3.1 配置

    git config --global user.name "Unreasonable607"
    git config --global user.email "1708573139@qq.com"

### 3.2 遇到的问题：SSH 连接被拒绝

生成 SSH 密钥并添加到 GitHub 之后，测试连接报错：

    ssh: connect to host github.com port 22: Connection refused

22 端口被网络阻断。

### 3.3 解决：改用 443 端口

GitHub 官方支持通过 443 端口走 SSH 连接。在 `~/.ssh/config` 里加上：

    Host github.com
      Hostname ssh.github.com
      Port 443
      User git

再测试：

    ssh -T git@github.com

    Hi Unreasonable607! You've successfully authenticated

### 3.4 日常使用

    cd ~/ncuscc-2026
    git add .
    git commit -m "说明"
    git push

## 四、体会

（待补：这一节写自己的感受——哪些地方真懂了，哪些还是照着做）
