# Part 4-1 Report: Process Concept & Observation

## 1. 목표
프로그램과 프로세스의 차이를 이해하고, 실행 중 프로세스의 메모리 구조와 상태를 직접 관찰

## 2. 이론 요약
- 프로세스는 실행 중인 프로그램이다.
- 프로세스는 code, data, heap, stack으로 구성된 주소 공간을 가진다.
- 프로세스는 new, ready, running, waiting, terminated 상태를 오간다.
- OS는 PCB를 통해 프로세스 상태를 관리한다.
- context switch는 필요한 동작이지만 오버헤드가 발생한다.

## 3. 실습 내용
### 3-1. ps / /proc 관찰
실행한 명령어:
- `ps -o pid,ppid,stat,ni,pri,comm -p $$`
- `cat /proc/self/status | head -30`
- `cat /proc/self/maps | head -20`

관찰한 내용:
- 현재 셸도 하나의 프로세스였다.
- PID와 PPID를 확인할 수 있었다.
- /proc을 통해 상태와 주소 공간 일부를 확인할 수 있었다.

### 3-2. mem_layout.c 실행
출력 결과에서 함수, 전역 변수, 지역 변수, malloc 메모리의 주소가 '서로 다른 영역'에 배치되는 것을 확인했다.

## 4. 해석
- 프로그램 파일 자체는 정적이지만, 실행되면 프로세스가 되어 상태를 가진다.
- 지역 변수는 스택에, 동적 할당 메모리는 힙에 존재한다.
- OS가 프로세스를 다시 실행하려면 PC, 레지스터, 메모리 상태 등의 정보가 필요하다.
- 따라서 PCB와 context switch 개념이 필수적이다.

## 5. 실무 연결
- PID/PPID는 서버 프로세스 추적에 중요하다.
- ps, /proc 같은 도구는 실제 운영 환경에서도 자주 사용된다.
- 프로세스 관찰은 장애 분석과 성능 분석의 출발점이다.

## 6. 궁금한 점
- make ./mem_layout 실행 시 프로그램이 멈추게 됨 -> 이 녀석(멈춘 놈)은 어떻게 처리 되는건가?