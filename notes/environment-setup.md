# 装环境的过程

考核的几个方向都要求 Linux 或者 WSL，所以第一步是装 WSL2。

第一次是按官方说的敲：

    wsl --install -d Ubuntu-22.04

然后就是等。等了很久，我以为是我网慢。后来发现不是慢，是卡住了——查了一下 Windows 功能状态，还是 Disabled，也就是二十分钟里它其实什么都没干成。它把"启用功能"和"下载组件"绑在一起，下载卡住，前面那步也不动。

最后是分三步做的：

1. 先用命令在本机把两个 Windows 功能打开（这一步是纯本地的，几秒钟就好了）

    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

2. 重启电脑

3. 再装 WSL 组件和 Ubuntu。改成从别的源下载，几分钟就完了。

Ubuntu 装在 D:\WSL\Ubuntu-22.04，用户名叫 bulizhi。

装完之后配置了一下：
- 把软件源换成国内的镜像（不然装软件也很慢）
- 装了常用工具：gcc、python3、git、curl 这些

对了，中间还有个小插曲：终端默认打开的目录是 Windows 的 C 盘，不是 Ubuntu 的家目录，每次都要自己 cd 回来。后来在主目录的配置文件里加了一行，让它每次打开自动回到主目录。
