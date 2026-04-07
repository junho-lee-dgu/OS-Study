# Assets Guide

이 폴더는 `operations-on-processes` 실습의 실행 캡처 이미지를 저장하는 공간이다.

## 파일 목록

- `01_fork_demo.png`
  - `./fork_demo` 실행 결과
  - 부모/자식 PID, PPID, fork 반환값 확인
  - 같은 코드가 부모와 자식에서 각각 실행되는 모습 확인

- `02_fork_exec_ls.png`
  - `./fork_exec_wait_demo` 기본 실행 결과
  - 자식이 `ls -l`로 바뀌는 흐름 확인
  - 부모가 `waitpid()`로 자식 종료를 기다리는 모습 확인

- `03_fork_exec_echo_whoami.png`
  - `./fork_exec_wait_demo /bin/echo hello world`
  - `./fork_exec_wait_demo /usr/bin/whoami`
  - 같은 자식 생성 구조에서 exec 대상만 바뀔 수 있음을 확인

- `04_proc_tree_demo.png`
  - `./proc_tree_demo` 실행 결과
  - root, child 1, child 2, child 3, grandchild 생성 및 회수 과정 확인

- `05_pstree_proc_tree.png`
  - `pstree -p` 실행 결과
  - `proc_tree_demo`가 실제 tree 형태로 연결된 모습 확인

- `06_zombie_demo.png`
  - `./zombie_demo` 실행 결과
  - 부모가 wait를 늦게 호출하는 zombie window 생성 확인

- `07_zombie_ps_Z.png`
  - `ps -el | grep Z` 실행 결과
  - 자식 프로세스 state가 `Z`로 표시되는 모습 확인

## 정리 원칙

- 파일명 앞에 번호를 붙여 실습 순서가 보이도록 정리
- report.md의 첨부 자료 목록과 동일한 이름 사용
- 가능하면 실행 결과 전체가 보이도록 캡처
- PID, PPID, state(Z), waitpid 결과가 잘 보이도록 저장