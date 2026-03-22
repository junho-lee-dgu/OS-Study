# Lab 04 - API, System Call, User-Kernel Boundary

## What I observed
- `man 2 write` showed: write belongs to the system call manual section and writes bytes to a file descriptor.
- `man 3 printf` showed: printf belongs to the library function manual section and provides formatted output.
- `printf_demo` output: Hello from printf!
- `write_demo` output: Hello from write!
- `grep write printf_trace.txt` result: write(1, "Hello from printf!\n", 19)    = 19
- `grep write write_trace.txt` result: write(1, "Hello from write!\n", 18)     = 18
- `cat` traced with open/read/write/close: a normal user program uses system calls such as openat, read, write, and close.
- The target file was opened with openat(..., O_RDONLY), returned file descriptor 3, read with read(3, ...), printed with write(1, ...), and then closed.
- 'read(...)=0' indicated end-of-file.

## What I learned
- API is: Application Programming Interface; OS service에 접근하기 위한 프로그래머용 창구
- A library function is: 이미 만들어져 있는 함수
- A system call is: 유저 프로그램이 커널에게 운영체제 서비스를 요청하기 위한 공식적인 진입점
- User mode is: 일반 프로그램이 도는 제한된 실행 모드
- Kernel mode is: '항상' 실행 중인 프로그램
- Why `printf()` is not the same as `write()`: printf()는 고수준 라이브러리 함수, write()은 시스템 호출에 아주 가까운 저수준 인터페이스

