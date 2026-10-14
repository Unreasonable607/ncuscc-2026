# 第 1 关：找到入口

## 任务

在一个离线 Linux 工作区中，为一份待处理材料生成结果文件 `/workspace/flag`。

- 材料位于 `/workspace/`，包括输入文件和密钥文本
- 处理程序为 `/workspace/exam`，接口以程序帮助信息为准
- 通关条件：`/workspace/flag` 必须是普通文件（≤ 1 MiB），内容与处理结果逐字节相同

## 解题过程

### 1. 查看工作区内容

```bash
ls -la /workspace
```

看到：

```
drwxr-xr-x cabinet
-rwxr-xr-x exam
-rw-r--r-- input.bin
drwxr-xr-x logs
```

### 2. 查看程序用法

```bash
/workspace/exam --help
```

输出说明：程序读取 `/workspace/input`，将结果写入 `/workspace/output`。

### 3. 关键发现：名字对不上

程序要读的是 `input`，但实际文件名是 **`input.bin`** —— 多了一个后缀。

### 4. 制造程序需要的文件名

```bash
cp /workspace/input.bin /workspace/input
```

### 5. 在子目录里找到密钥

```bash
ls -la /workspace/cabinet /workspace/logs
cat /workspace/cabinet/key.txt
```

`logs/` 是空目录（干扰项），密钥在 `cabinet/key.txt` 中。

### 6. 运行处理程序

```bash
/workspace/exam -e <密钥>
echo $?          # 退出码 0 表示成功
```

### 7. 把产出复制成要求提交的文件

程序的产出叫 `output`，但通关要求的是 `flag`：

```bash
cp /workspace/output /workspace/flag
```

## 小结

这一关的两个考点：

1. **发现名字不匹配**，并主动建立正确的文件名
2. **区分「程序产出的文件」和「要求提交的文件」**，用 `cp` 保持二进制内容不变
