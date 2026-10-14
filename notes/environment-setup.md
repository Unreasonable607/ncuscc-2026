# 环境搭建记录

## 背景

考核的三个方向都要求 Linux 或 WSL 环境，因此第一步是在 Windows 上装好 WSL2。

## 过程

### 第一次尝试：官方一键安装（失败）

```powershell
wsl --install -d Ubuntu-22.04
```

卡在下载环节，20 分钟后检查发现 Windows 功能状态仍然是 `Disabled` —— 说明它把「启用功能」和「下载组件」绑在一起，下载卡住就全都不动。

### 改用的方案（约 4 分钟完成）

1. **本地启用 Windows 功能**（DISM，秒级完成）
   ```powershell
   dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
   dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
   ```

2. **重启**，让功能生效

3. **从 GitHub 下载 WSL 组件**（约 5.8 MB/s）

4. **从国内镜像导入 Ubuntu**
   ```bash
   wsl --import Ubuntu-22.04 D:\WSL\Ubuntu-22.04 ubuntu-jammy-rootfs.tar.gz
   ```

### 系统配置

- 安装位置：`D:\WSL\Ubuntu-22.04`
- 默认用户：`bulizhi`
- APT 源换成国内镜像（中科大）
- 安装了 build-essential、python3-pip、git、curl、wget、vim、htop 等

## 小结

官方一键安装在国内网络环境下容易卡住，拆成「本地启用功能 → 下载组件 → 导入发行版」三步更可控。
