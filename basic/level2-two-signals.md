# 第 2 关：两段信号

## 任务

一批材料中夹杂无关文件，需要找出两段有效信号并生成一份完整结果。

- 两份输入由文件名中的 `signal-A`、`signal-B` 标识
- 密钥来自清单中唯一的 `ACCESS_KEY=` 记录
- 处理程序为 `/workspace/exam`
- 最终结果须保持 **A 段在前、B 段在后**

通关条件：`/workspace/flag` 的字节内容严格等于 A 段处理结果与 B 段处理结果的有序拼接。

## 解题过程

### 1. 递归查找所有文件

```bash
find /workspace -type f
```

结果：

```
/workspace/inbox/signal-B.bin
/workspace/exam
/workspace/archive/2026/signal-A.bin
/workspace/archive/2026/notes-A.txt
/workspace/catalog/words.txt
```

两个信号文件在不同的目录层级里。

### 2. 找出密钥

```bash
grep -r "ACCESS_KEY=" /workspace
```

输出：

```
/workspace/catalog/words.txt:ACCESS_KEY=STAR
```

注意：`-e` 参数需要的是 `STAR`，不是整行 `ACCESS_KEY=STAR`。

### 3. 处理 A 段

```bash
cp /workspace/archive/2026/signal-A.bin /workspace/input
/workspace/exam -e STAR
cp /workspace/output /workspace/partA
```

最后一步是关键：程序永远只写 `/workspace/output`，处理 B 时会把它覆盖，所以必须先把 A 的结果另存。

### 4. 处理 B 段

```bash
cp /workspace/inbox/signal-B.bin /workspace/input
/workspace/exam -e STAR
cp /workspace/output /workspace/partB
```

### 5. 按顺序拼接

```bash
cat /workspace/partA /workspace/partB > /workspace/flag
```

`cat` 后跟多个文件时按顺序连接输出；`>` 一次性写出，避免了覆盖问题。

### 6. 验证

```bash
wc -c /workspace/flag
```

结果 32 字节 = A 段 16 字节 + B 段 16 字节。

## 小结

三个提示分别对应三个坑：

| 提示 | 对应操作 |
|---|---|
| 目录可能嵌套多层 | `find` 递归查找 + 管道筛选 |
| 清单含干扰记录，整行不都是密钥 | `grep` 定位后再取出密钥部分 |
| 覆盖 vs 追加、输出位置固定 | 先另存 A 的结果，最后用 `cat` 有序拼接 |
