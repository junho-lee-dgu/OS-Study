# command.md

## 1. 빌드

```bash
make
```

## 2. 개별 실행

### 2-1. fork 기본 실습

```bash
./fork_demo
```

### 2-2. fork-exec-wait 실습

기본 실행 (`ls -l` 실행):

```bash
./fork_exec_wait_demo
```

또는

```bash
make run-exec
```

다른 프로그램 실행 예시:

```bash
./fork_exec_wait_demo /bin/echo hello world
./fork_exec_wait_demo /usr/bin/whoami
```

### 2-3. process tree 관찰 실습

터미널 1:

```bash
./proc_tree_demo
```

터미널 2:

```bash
pstree -p
```

또는 특정 PID 기준:

```bash
pstree -p <parent_pid>
```

추가 확인:

```bash
ps -f --forest
```

### 2-4. zombie 관찰 실습

터미널 1:

```bash
./zombie_demo
```

터미널 2:

```bash
ps -o pid,ppid,state,cmd | grep zombie_demo
ps -el | grep Z
```

## 3. 정리

```bash
make clean
```