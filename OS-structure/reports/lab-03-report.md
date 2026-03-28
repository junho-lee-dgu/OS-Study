# Lab 03 - OS Services and User View

## What I observed
- My current shell: `/bin/bash`
- `cd` built-in result: cd is a shell builtin
- `ls` external program result: ls is /usr/bin/ls
- Program execution result: `hello_os.c`를 `gcc`로 컴파일한 뒤 `./hello_os`를 실행했고, `Hello, OS services!`가 출력되었으며 종료 상태는 `0`이었다.
- File manipulation result: `practice_dir`를 만들고 `a.txt`를 생성해 내용을 썼다. 이후 `cp`로 `b.txt`를 만들고, `mv`로 `c.txt`로 이름을 바꿨다. 최종적으로 `a.txt`와 `c.txt`가 존재했다.
- Error detection result: 존재하지 않는 `no_such_file.txt`를 `cat`으로 열려고 하자 `No such file or directory`가 출력되었고 종료 상태는 `1`이었다.
- Pipe communication result: `echo "hello operating system" | wc -w` 실행 결과 `3`이 출력되었다.

## What I learned
- The shell is: 사용자가 입력한 명령을 읽고 해석해서 실행으로 연결하는 프로그램이다. 내 환경에서는 `bash`를 사용하고 있다.
- A terminal is: 명령을 입력하고 출력을 확인하는 문자 기반 창/환경이다.
- A system program is: 운영체제 위에서 사용자에게 편리한 실행 환경을 제공하는 프로그램이다. 예를 들어 `ls`, `cp`, `cat`, `gcc` 같은 도구들이 있다.
- The OS service I saw most clearly today was: program execution과 file-system manipulation이었다.

## Questions
- 왜 `cd`는 shell built-in이어야 하고, `ls`는 외부 프로그램이어도 되는가?
- shell과 kernel은 정확히 어디서 경계가 나뉘는가?
