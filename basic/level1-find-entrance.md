# 第 1 关 找到入口

在平台的网页终端里做的，不是我自己电脑上的 Ubuntu。

先翻工作区：

    ls -la /workspace

出来四个东西：

    cabinet/   exam   input.bin   logs/

`exam` 的权限是 `-rwxr-xr-x`，有 x，能跑。前几天刚学的权限，这里派上用场了。

不知道怎么用，就敲了 --help：

    用法：exam [-h] -e 密钥
    使用密钥处理 /workspace/input，将结果写入 /workspace/output

到这里我不太懂：程序要读 /workspace/input，可我看到的是 input.bin，多个后缀。当时没反应过来这是什么意思，是问了才知道——**要在同目录下自己造一个叫 input 的文件**。

    cp /workspace/input.bin /workspace/input

密钥在 cabinet 里：

    cat /workspace/cabinet/key.txt

出来是 MOON。logs 目录是空的，估计是干扰项。

然后跑程序：

    /workspace/exam -e MOON
    echo $?

`echo $?` 是看上一条命令的退出码。敲完 exam 屏幕上什么都没有，我还以为没跑成功，结果是退出码没有报错，是 0。后来才知道 Linux 里很多程序成功的时候就是不吭声。

程序产出的文件叫 output，但要求交的是 flag，名字又不一样：

    cp /workspace/output /workspace/flag

这一关做下来，两次"名字不一样"（input.bin vs input，output vs flag）都是我自己没看出来的，是有人指了才知道。
