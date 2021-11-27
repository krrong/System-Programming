### Overview

- 입력 파일에서 좌표 정보들을 읽어 요구사항을 만족하는 정적 라이브러리를 만들고 이를 링킹하여 프로그램을 작성하시오.

- 입력 파일 예시

  input.txt

  (1265836E, 373252N) (1265949E, 373252N)

  (1042311W, 324522N) (1044700W, 322107N)

  (1042410W, 325018N) (1045001W, 323905N)

  (1040324W, 324707N) (1040127W, 323935N)

  (1041133W, 323039N) (1042920W, 320711N)

  (1041312W, 324758N) (1044543W, 323228N)

  (1042301W, 325032N) (1044349W, 321516N) 

  (1041007W, 322104N) (1043954W, 320824N) 

  (1041841W, 321604N) (1041342W, 322514N) 

  (1041408W, 320737N) (1035852W, 320721N)



### DMS Format

- 위치 좌표를 표기하기 위한 Latitude(위도)와 Longitude(경도)는 dms 형식으로 나타낼 수 있다.
  - d는 degree(도), m은 minute(분), s는 second(초)를 의미한다.
  - 1m은 60s, 1d는 3600s 이다. dms 표기의 마지막 문자 ‘E’, ‘W’, ‘S’, ‘N’ 은 방향을 나타내며, 각각 동, 서 남, 북을 의미한다.
  - Latitude의 범위: (90d 00m 00s S) ~ (90d 00m 00s N) 
  - Longitude의 범위: (180d 00d 00s W) ~ (180d 00d 00s E)
- 효율성을 위하여 dms표기의 문자 ‘d’, ‘m’, ‘s’는 생략하여 표현할 수 있다.
- 위도와 경도를 나타내기 위해 dms 표기 외에 total second로도 표기가 가능하다. total second는 dms를 second로 변환한 것으로 방향에 따라 부호가 결정된다.



### Taxi-cab geometry(Manhattan distance)

- 위도와 경도로 나타낸 두 좌표가 주어졌을 때, 두 지점 사이의 거리는 Taxi-cab geometry(Manhattan distance)를 이용하여 표현하기로 하자. Taxi-cab geometry는 직교 좌표계에 두 점을 나타냈을 때, 가로와 세로 길이의 합이다.



### 요구사항

- Input

  - N개의 줄 (최대 32개) 로 이루어진 입력 파일에 대하여, 각 줄에는 두 좌표 쌍이 주어진다.

  - 좌표는 ‘(Longitude, Latitude)’ 로 주어지며, Longitude와 Latitude 좌표는 DMS 형식이다.

  - Longitude와 Latitude의 DMS 형식은 degree, minute, second로 구분되지 않고 주어진다.

    

- Output

  - N개의 줄 에 대하여, 각 줄에는 두 좌표 쌍의 좌표, 두 좌표 쌍의 거리를 출력한다.

  - 각 좌표는 ‘(Longitude, Latitude)’ 형태로 출력하며, Longitude와 Latitude 좌표는 DMS 형식이며, Longitude와 Latitude의 DMS 형식은 degree, minute, second로 구분하여 변환 출력한다.

  - 두 좌표 쌍의 거리는 Taxi-cab geometry 를 이용하여 구하고, 두 좌표 쌍의 거리는 total second와 DMS 형식으로 출력한다.

  - 출력 예시

    ![image](https://user-images.githubusercontent.com/84285337/143672758-708c05ae-f23d-48d0-927d-556c74dcc5b6.png)

  

### 설계

- object.h

  - gisinfo, coordinate 두 구조체를 정의하고 있는 헤더파일이다. 헤더파일을 여러번 include하게 되면 구조체가 중복정의 될 수 있는 문제가 있기 때문에 #ifndef...#endif를 활용하여 한번만 정의되도록 한다.

    - gisinfo 구조체 : DMS 방식으로 저장하기 위한 도(degree), 분(minute), 초(second), total second를 저장하기 위한 totalSec, 방향을 저장하기 위한 direction, 입력받을 dms변수를 갖고 있는 구조체다.

    - coordinate 구조체 : gisinfo객체로 경도와 위도를 갖는 구조체다.

      ![image](https://user-images.githubusercontent.com/84285337/143672857-7c878051-5452-4ab2-a479-0a9fc2c2fcd8.png)	

  

- system.h
  - 함수의 원형을 담고있는 파일이다. (각 함수에 대한 상세설명은 아래에 나온다.)

​			![image](https://user-images.githubusercontent.com/84285337/143672974-e0ee88be-c20a-477b-addc-fda8d27fc0dc.png)



- getGIS.c
  - int getGIS(char* filename, struct coordinate* a, struct coordinate* b)
    - 파일의 이름(filename), coordinate 배열 2개(a, b)를 인자로 받는다.
    - 파일을 열어 파일의 끝까지 각 라인에 대한 입력을 a와 b에 저장하고 개수를 리턴한다.



- print.c

  - int* calculate(struct coordinate* a, struct coordinate* b, int cnt)

    - coordinate배열 2개(a, b)와 원소의 개수(cnt)를 인자로 받는다. 
    - 원소의 길이와 같은 배열을 동적으로 할당받고 같은 위치에 있는 두 배열의 원소에 대해 거리차를 구하여 저장한다. (total second형식)

    

  - void print(struct coordinate* start, struct coordinate* dest, int cnt)

    - coordinate배열 2개(start, dest)와 원소의 개수(cnt)를 인자로 받는다. 
    - calculate함수를 사용하여 start와 dest의 거리차를 저장한 배열(dist)을 리턴받는다.
    - 리턴받은 거리차는 total second 형식이기 때문에 DMS format으로 바꿔주고 저장하기 위해 cnt만큼의 배열 3개(degree, minute, second)를 동적할당한다.
    - 거리차를 저장한 배열을 이용하여 배열 3개를 채워준다.
    - start, dest, dist, degree, minute, second 배열을 이용하여 출력 형식에 맞게 출력한다.



- changeDMS.c
  - void changeDMS(struct coordinate* a, int cnt)
    - coordinate배열(a)과 원소의 개수(cnt)를 인자로 받는다. 
    - dms에 저장되어 있는 값을 이용하여 degree, minute, second로 분리하여 각 멤버변수에 알맞는 값을 넣어준다.
    - degree, minute, second를 이용하여 total second를 구한다. 이 때 음수인 경우(latitude의 direction이 N이 아닌 경우, longitude의 direction이 E가 아닌 경우)에는 -1을 곱하여 저장한다.



- main.c

  - 입력이 최대 32줄이기 때문에 크기가 32인 coordinate배열 2개를 선언한다. (start, destination)

  - getGIS함수를 이용하여 start와 destination에 파일의 입력 값을 저장하고 개수를 리턴한다.

  - start배열에 대해 changeDMS함수를 이용하여 각 멤버변수에 알맞는 값을 넣어준다.

  - destination배열에 대해 changeDMS함수를 이용하여 각 멤버변수에 알맞는 값을 넣어준다.

  - print함수를 이용하여 형식에 맞게 출력한다.

    ![image-20211127170057381](C:\Users\Lab02\AppData\Roaming\Typora\typora-user-images\image-20211127170057381.png)	
