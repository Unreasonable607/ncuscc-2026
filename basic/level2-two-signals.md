# 第 2 关 两段信号

这关比第一关麻烦，文件多，还分布在不同的目录里。

先找文件：

    find /workspace -type f

    /workspace/inbox/signal-B.bin
    /workspace/exam
    /workspace/archive/2026/signal-A.bin
    /workspace/archive/2026/notes-A.txt
    /workspace/catalog/words.txt

A 和 B 在不同的地方，一个在 inbox，一个埋在 archive/2026 下面。

找密钥：

    grep -r "ACCESS_KEY=" /workspace

    /workspace/catalog/words.txt:ACCESS_KEY=STAR

这里有个坑，密钥是 STAR，不是整行 ACCESS_KEY=STAR。这个提示里写了，我自己多半会填错。

然后要分别处理 A 和 B。麻烦的地方是：程序永远只写 /workspace/output 这个位置，处理 B 的时候会把 A 的结果盖掉。

所以先处理 A：

    cp /workspace/archive/2026/signal-A.bin /workspace/input
    /workspace/exam -e STAR
    cp /workspace/output /workspace/partA

第三步是关键的，先把 A 的结果另存成 partA。

再处理 B：

    cp /workspace/inbox/signal-B.bin /workspace/input
    /workspace/exam -e STAR
    cp /workspace/output /workspace/partB

最后拼起来，A 在前 B 在后：

    cat /workspace/partA /workspace/partB > /workspace/flag

验证：

    wc -c /workspace/flag

    32 /workspace/flag

A 是 16 字节，B 是 16 字节，加起来 32，对上了。

中间有一步我先点了提交，平台提示"缺少规定的提交文件"。当时有点慌，后来才明白 flag 是最后才生成的，中途点当然说没有。

另外这关我重来过一次，之前那次做到一半工作区被重建了。
