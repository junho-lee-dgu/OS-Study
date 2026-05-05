# Report: Cooperating Processes & IPC

## 1. 실습 목표
이번 실습의 목표는 cooperating process가 실제로 어떻게 데이터를 주고받고 협력하는지 확인하는 것이다. 이를 위해 pipe를 이용한 message passing, mmap을 이용한 shared memory, socket을 이용한 client-server communication을 각각 실험하였다.

## 2. 관련 개념
- cooperating process는 다른 프로세스의 실행에 영향을 주거나 영향을 받는 프로세스이다.
- message passing은 shared variable 없이 데이터를 주고받는 방식이다.
- shared memory는 같은 메모리 영역을 함께 참조하는 방식이다.
- socket은 IP address와 port로 정의되는 communication endpoint이다.

## 3. 실습 내용
### 3-1. pipe_demo
부모가 pipe에 문자열을 쓰고 자식이 읽도록 구성하였다. 이를 통해 shared variable 없이도 parent-child 간 통신이 가능함을 확인하였다. 또한 child가 먼저 read를 수행하면 blocking이 발생할 수 있음을 관찰하였다.

### 3-2. mmap_shared_demo
mmap(MAP_SHARED)을 사용하여 부모와 자식이 같은 메모리 영역을 공유하도록 하였다. 부모가 쓴 값을 자식이 읽고, 자식이 수정한 값을 부모가 다시 확인할 수 있었다. 이를 통해 shared memory 방식의 직접성을 확인하였다.

### 3-3. tcp_echo_server / tcp_echo_client
server는 127.0.0.1:9090에서 listen하고, client는 해당 endpoint에 접속하여 문자열을 보낸 뒤 echo 응답을 받도록 하였다. 이를 통해 socket 기반의 client-server communication을 로컬 환경에서 재현하였다.

## 4. 결과 해석
pipe는 message passing 구조를 가장 단순하게 보여주었다. mmap은 같은 데이터를 함께 보는 shared memory 구조를 보여주었고, 이는 빠를 수 있지만 synchronization 없이는 위험할 수 있음을 시사한다. socket은 IPC 개념이 네트워크 endpoint 기반 통신으로 확장된 형태라고 이해할 수 있었다.

## 5. 느낀 점
이번 실습을 통해 프로세스 협력은 단순히 여러 프로세스가 동시에 존재하는 것이 아니라, 실제로 데이터를 교환하고 역할을 나누는 구조라는 점을 이해할 수 있었다. 특히 pipe와 mmap의 차이를 직접 비교해보니 message passing과 shared memory의 개념 차이가 더 명확해졌다.