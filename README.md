# ChattingMFC

C++ MFC 기반으로 통신하는 서버-클라이언트 구조 채팅 프로그램입니다.
카카오톡을 흉내내어 구성되어있습니다

https://www.youtube.com/watch?v=wSfluL_AFx0

크게, 서버 - RabbitMQ 브로커 - 클라이언트 구조를 갖고 있습니다.
RabbitMQ 브로커는 rabbitmq 3.8.17 을 다운로드 받았고, RabbitMQ client 라이브러리는 SimpleAMQPclient 를 이용했습니다.
서버와 클라이언트는 RabbitMQ 를 이용해 메세지를 주고받는 형태입니다. 현재는 1-N 구조로 연결되어있습니다. 서버간 동기화 기능을 구현한다면, 서버의 개수를 늘릴 수 있을거라고 생각합니다.



# 구현

서버와 클라이언트는 계층화되어있습니다.
  1. Tranmission 부분: 실질적인 연결만을 담당합니다. 특정 노드 (사용자)에 따라, 연결되었는지, 연결안되었는지, 통신가능한지 여부 등을 판별하고 실질적인 메세지를 전달합니다.
  2. Application 부분: Transmission 을 통해 메세지를 수신받아 작업을 처리하고, 상황에 따라 Transmission 을 거쳐 메세지를 전송합니다.

###
서버는 브로커에서 수신받은 메세지를 decoding 하여 작업을 처리하는 역할을 합니다. 작업 내용은 메세지 수신 내용에 따라 다릅니다.
서버 모듈 구성요소는 크게 Transmission, Core, Processor, Data, Display 로 구분됩니다.

  1. Transmission: 서버용 통신 모듈입니다. 브로커에 "server" 메세지 큐를 할당받아 해당 메세지큐에 도착한 메세지를 접속 요청 / 해제 요청 / 일반 메세지로 구별해 작업을 처리합니다. 접속 요청은 노드에 고유 번호를 할당해 해당 번호와 메세지 큐 이름을 mapping 합니다. 반면, 해제 요청은 해당 mapping 을 비활성합니다. 나머지는 일반 메세지로 판별해 상위 계층으로 전송합니다.
  2. Core: 모든 모듈을 총괄하고, 실질적으로 처음 메세지를 전달받는 부분입니다. 작업을 처리하는 하위 모듈로 Processor 를 여러개 두어, non-busy state 의 Processor 에게 작업을 처리하도록 전달합니다. (현재는 Process 의 개수가 단일입니다.)
  3. Processor: Core 에 소속되어 메세지를 전달받아 실질적을 작업을 처리하는 모듈입니다. Core 가 갖고있는 Data, Display 등 보조 모듈을 접근해 작업을 처리합니다. (각 모듈은 thread-safe 하게 구현되어야 한다.)
  4. Data: Server 가 갖는 모든 정보를 관리, 저장하는 모듈입니다. 현재는 서버에 접속한 Client 와, Room 정보를 저장하고 관리하고 있습니다. (추후에, DB와 연결해, 저장을 효율적이고, long-lasting 하게 변환할 예정입니다.)
  5. Display: Server 가 받은 메세지 등을 표현하는 모듈입니다. 화면 출력 & 로그 저장 등의 기능을 담당하고 있습니다.

  변경 예정 목록
  - Server 는 현재 MFC 의존적입니다. (Display & Data 모듈, MFC) 이후에, 서버 측을 MFC 에서 분리하고 console 기반으로 변형할 예정입니다.
  - Command 모듈을 작성할 예정입니다. 해당 모듈은 접속한 Client & Room 에 명령을 내리거나, 공지사항을 독자적으로 생성해 전달 할 수 있도록 구현될 예정입니다.

###
클라이언트는 이용자가 입력한 정보에 따라 해당하는 작업을 처리합니다.
클라이언트 모듈 구성요소는 크게 Transmission, Application, Processor, View 로 구성되어 있습니다.

  1. Transmission: 클라이언트용 통신 모듈입니다. Exclusive 한 메세지 큐를 생성하고, Server Message큐에 해당 사실을 알려 통신을 연결합니다.
  2. Application: 모든 모듈을 담당하는 모듈입니다. Processor 에게 Transmission 에서 온 메세지를 전달하는 역할과 유저가 입력한 기능에 따른 작업을 전달하는 역할을 담당합니다.
  3. Processor: Application 이 담당해야하는 모든 작업을 처리하는 모듈입니다. 이 작업은 client 내 에서 처리될 수도 있고, server 로 메세지를 전송해야할 수도 있습니다.
  4. Display: 유저가 보고 Interact 하는 모듈입니다. 내용을 화면에 띄우고, 유저 입력 데이터 등을 보관합니다.
  5. Data: 클라이언트가 처리해야할 정보를 관리하는 모듈입니다. 방의 개수나, 클라이언트 목록 등의 정보를 보관합니다.

  변경 예정 목록
  - 여러 Dialog 가 지금 기본 MFC 디자인을 이용하고 있습니다. 디자인 개선이 필요합니다.
  - 로직이 깔끔하지 않습니다. 로직을 다듬어야합니다.
  
  개선 목록
  - Server 에 비해 기능 분할이 완벽하게 이루어져 있지 않습니다. Refactoring 을 거쳐 보다 깔끔한 구성을 갖도록 개편할 예정입니다. (완료)
  - Double Buffering 기능이 View Module 에 구현되어있지 않습니다. flickering 이 발생하고 있습니다. (완료)
