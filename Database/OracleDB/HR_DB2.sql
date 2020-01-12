--Employees 테이블에서 부서를 배정받지 못한 사원들의 이름과 이메일 정보를 검색해보세요
--NULL을 검색할 때는 is null이라는 표현을 씁니다.
SELECT * FROM employees;
SELECT Last_name "이름", email "이메일", department_id "부서번호" FROM employees
WHERE department_id is null;

--부서번호 오름차순으로 사원이름, 부서번호, 급여액을 표시하되
--부서를 배정받지 못한 사원은 가장 먼저 출력한다.
--ORDERBY~NULL FIRST/LAST 사용
SELECT LAST_NAME "이름", DEPARTMENT_ID "부서번호", SALARY "급여액" FROM employees
ORDER BY DEPARTMENT_ID NULLS FIRST;

--동일한 값일 때 다른 컬럼으로 정렬을 하고 싶을 때는 뒤에 , 정렬조건을 주면 된다.
--즉, ORDER BY 뒤에 쉼표로 구분되는 것이 정렬의 우선순위라고 할 수 있다.
SELECT LAST_NAME "이름", DEPARTMENT_ID "부서번호", SALARY "급여액" FROM employees
ORDER BY DEPARTMENT_ID NULLS FIRST, SALARY DESC;

--사원들을 입사일 기준으로 고참부터 정렬하되
--번호, 이름, 급여를 표시하고 컬럼명은 별칭을 사용해보세요.
SELECT EMPLOYEE_ID "사원번호", LAST_NAME "이름", SALARY "급여" FROM employees
ORDER BY HIRE_DATE;

--논리 표현식 사용하기
SELECT LAST_NAME
FROM EMPLOYEES
WHERE 1!=1;

--부서번호가 50도 아니고 60도 아닌 사원 중에서
--입사일이 03년 이전이 아닌 사원들의 이름, 부서번호, 입사일을 표시해보세요.
SELECT LAST_NAME "이름", DEPARTMENT_ID "부서번호", HIRE_DATE "입사일" FROM employees
WHERE DEPARTMENT_ID !=50 AND DEPARTMENT_ID !=60 
AND NOT HIRE_DATE < (TO_DATE('03/01/01'))
ORDER BY HIRE_DATE;

--BETWEEN 구문
-- 열의 값이 A와 B 사이에 있다면 TURE를 반환한다.
SELECT * FROM employees
WHERE SALARY NOT BETWEEN 0 AND 3000;

--IN 연산자
--IN은 행조건에 붙는데, 그 값이 있는(TURE인) 행을 모두 반환한다.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN (40,50);

--사원들의 직무(JOB)에 ST_MAN도 아니고, ST_CLERK도 아닌
--사원들의 이름, 직무를 표시해보세요. 
SELECT LAST_NAME "이름", JOB_ID "직무" FROM employees
WHERE NOT JOB_ID IN ('ST_MAN', 'ST_CLERK')
ORDER BY JOB_ID;

--LIKE 연산자:패턴검색 ( % , _ )
-- %: 문자가 한개도 없거나, 한개 이상인 경우의 와일드 카드
-- _: 문자 한개를 의미하는 와일드 카드
-- 문자열을 입력할 땐 대소문자가 구별된다...
SELECT LAST_NAME FROM employees
WHERE LAST_NAME LIKE 'A%_l';

--LAST_NAME이 'E'로 끝나는 모든 사원의 LAST_NAME을 표시해보세요
SELECT LAST_NAME FROM employees
WHERE LAST_NAME LIKE '%e'
ORDER BY LAST_NAME ASC;

--CASE (교재 102쪽 참고)
--10~50번 부서번호를 운영팀, 인사팀, 배송팀, 생산팀, 마켓팅으로 
--변경하고 각 사원의 이름, 부서번호, 부서명을 표시해보세요.
SELECT LAST_NAME "이름"
, CASE DEPARTMENT_ID
    WHEN 10 THEN '운영팀'
    WHEN 20 THEN '마케팅'
    WHEN 30 THEN '생산팀'
    WHEN 40 THEN '인사팀'
    WHEN 50 THEN '배송팀'
    ELSE '부서미배정'
END AS "부서명"
FROM employees
WHERE DEPARTMENT_ID BETWEEN 10 AND 50
ORDER BY DEPARTMENT_ID;

-- 03년도에 입사자와 50번 부서의 직원들을 5% 급여를 인상하여 
-- 사원의 이름, 입사일, 원래 급여, 인상된 급여를 표시해보세요.
SELECT LAST_NAME "이름", HIRE_DATE "입사일", SALARY "원래급여"
, CASE  WHEN HIRE_DATE BETWEEN TO_DATE('03/01/01') AND TO_DATE('03/12/31') THEN SALARY*1.05
        WHEN DEPARTMENT_ID = 50 THEN SALARY*1.05
        ELSE 0
END AS "인상급여"
FROM employees
WHERE HIRE_DATE BETWEEN TO_DATE('03/01/01') AND TO_DATE('03/12/31')
OR DEPARTMENT_ID = 50
ORDER BY "인상급여";

--SUB QUERIES
--아래 문장은 DEPARTMENT_ID를 하드코딩해서 개발 전에 넣어준 것인데, 이는 개발자가 그 값의 유무를 알고있다는 전제하에 실행된다.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN(20,40,50);
--특정한 행조건은 동적으로 넣어주고 싶은 때 SUBQUERIES를 쓰는데, 이는 아래처럼 또 다른 식을 행조건으로 넣는 것을 말한다.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN(
SELECT DEPARTMENT_ID FROM employees
);

--서브쿼리를 이용하여 부서가 50이거나 JOB_ID가 IT_PROG인
--모든 사원의 정보를 표시해보세요
SELECT * FROM 
(
    SELECT * FROM EMPLOYEES
    WHERE DEPARTMENT_ID = 50 OR JOB_ID = 'IT_PROG'
); --작성한 서브쿼리는 FROM 다음에 TABLE의 의미로 쓰이고 있다. 이를 IN-LINE VIEW라고 한다.

--DAVID와 그의 동료들을 화면에 출력해보세요
SELECT FIRST_NAME, DEPARTMENT_ID FROM EMPLOYEES
WHERE DEPARTMENT_ID =
(
SELECT DEPARTMENT_ID FROM EMPLOYEES
WHERE FIRST_NAME='David' AND LAST_NAME='Lee'
);

--Allan 과 Peter, Oliver와 같은 사무실 직원들의 
--이름, 부서번호, 급여를 표시하고 부서번호 순으로 정렬해보세요.
SELECT FIRST_NAME, DEPARTMENT_ID, SALARY FROM EMPLOYEES
WHERE DEPARTMENT_ID IN --결과가 한개 이상이니 IN 연산자가 적절하겠다.
-- 한가지 결과를 뽑고싶다면:ANY
-- 모두 일치하는 한 결과를 뽑고싶다면: ALL
-- 그 중 몇개만 뽑고 싶다면: SOME
(
SELECT DEPARTMENT_ID FROM EMPLOYEES
WHERE FIRST_NAME='David' OR FIRST_NAME= 'Peter' OR FIRST_NAME= 'Oliver'
)
ORDER BY DEPARTMENT_ID;

--오라클이 지원하는 다양한 함수
--현재 날짜 출력하기
SELECT SYSDATE AS "오늘의 날짜" FROM DUAL;
--오라클이 지원하는 다양한 수학 함수
--수의 올림(큰 정수)/버림(작은 정수) 수 출력하기
SELECT CEIL(1.234), FLOOR(1.234) FROM DUAL;
--수의 절대값 출력하기
SELECT ABS(-10) FROM DUAL;
--수의 부호 출력하기
SELECT SIGN(-10), SIGN(0), SIGN(10) FROM DUAL;
--지수 출력하기: e^몇승
SELECT EXP(1) FROM DUAL;
--제곱근 출력하기
SELECT SQRT(9) FROM DUAL;
--로그 출력하기 (첫번째 숫자를 몇승을 해야 두번째 숫자가 되는가)
SELECT LOG(3,9) FROM DUAL;
--자연로그 (밑은 e로하는 로그: ln 2.718281828) 출력하기
SELECT LN(2.718281828) FROM DUAL;
--나머지 출력하기 (modular 연산자, cpp에서 %와 같다)
SELECT MOD(10,3) FROM DUAL;
--삼각함수 연산자
SELECT SIN(2), COS(3), TAN(4) FROM DUAL;
--역삼각함수 연산자
SELECT ASIN(0.5), ACOS(0.5), ATAN(0.5) FROM DUAL;
--쌍곡선함수 연산자
SELECT SINH(3), COSH(3), TANH(3) FROM DUAL;

--문자열을 다루는 함수들 교재 P.122참고
--문자열의 길이를 반환
SELECT LENGTH('Hello') FROM DUAL;
--아스키코드 번호를 반환
SELECT ASCII('A'), ASCII('a') FROM DUAL;
--아스키코드를 받아 문자를 반환
SELECT CHR(65) FROM DUAL;
--문자열을 대문자, 소문자로 바꾸기
SELECT UPPER('abc'), LOWER('HELLO') FROM DUAL;

SELECT LTRIM('    HELLO') FROM DUAL;
--문자열 왼쪽(L), 오른쪽(R)에 무언가를 덧댄다 (PAD)
--단 문자열을 포함하여 특정 수(10)가 될 때까지 덧댄다.
SELECT LPAD('hello', 10, '-') FROM DUAL;

--모든 FIRST_NAME에 '_' 2개를 왼쪽에 덧대어보세요.
SELECT LPAD(FIRST_NAME, LENGTH(FIRST_NAME)+2, '-')
FROM employees;

--SUBSTRING 하위 문자열 추출하기
SELECT SUBSTR(FIRST_NAME, 0,3) FROM EMPLOYEES;
--SUBSTRING 함수를 이용하여 각 사원의 입사연도만 추출하여 표시해보세요
SELECT SUBSTR(HIRE_DATE, 0,2), FIRST_NAME FROM EMPLOYEES
ORDER BY HIRE_DATE;

--입사연도가 07연도인 사원의 이름과 부서번호, 입사연원일을 표시해보세요
SELECT HIRE_DATE "입사 날짜", FIRST_NAME "이름", DEPARTMENT_ID "부서번호" FROM EMPLOYEES
WHERE SUBSTR(HIRE_DATE, 0,2)=07
ORDER BY HIRE_DATE;

--문자열 안에서 검색: 찾은 위치를 리턴한다.
SELECT INSTR('HELLO', 'HE') FROM DUAL;
--문자열 대체
SELECT REPLACE('hello', 'HELLO') FROM DUAL;
--문자열 붙이기
SELECT CONCAT('Hello', 'World') FROM DUAL;

--FIRST_NAME, LAST_NAME을 붙여서 "이름"으로 표시할 때
--12자가 넘는 문자열은 13번째에 '...'을 붙여서 표시해보세요
SELECT 
CASE 
WHEN LENGTH(CONCAT(FIRST_NAME,LAST_NAME))>12 THEN 
CONCAT(SUBSTR(CONCAT(FIRST_NAME,LAST_NAME),0,12)||'...')
ELSE CONCAT (FIRST_NAME, LAST_NAME)
END AS "사원 이름"
FROM EMPLOYEES;

--Shanta 보다 급여를 많이 받는 사원들의 이름, 급여액을 표시해보세요.
SELECT FIRST_NAME "이름", SALARY "급여액"
FROM EMPLOYEES
WHERE SALARY > 
    (
    SELECT SALARY FROM EMPLOYEES
    WHERE FIRST_NAME= 'Shanta'
    )
ORDER BY SALARY;

--NVL(x,y) 함수 : x가 NULL이라면 y를 리턴한다.
--널값을 검사하는 함수 (NULL VALUE)
SELECT FIRST_NAME "이름", NVL(MANAGER_ID, 0) "관리자 번호"
FROM EMPLOYEES;

--NVL2 함수: MANAGER_ID가 NULL이라면 x를 리턴하고, NULL이 아니라면 y를 리턴한다.
SELECT FIRST_NAME "이름", NVL2(MANAGER_ID, 'x', 'y') "관리자 번호"
FROM EMPLOYEES;

--DECODE(x,a,b,c,d,e,f,......)
--x가 a와 같으면 b가 리턴되고, c와 같으면 d가 리턴되고, e와 같으면 f가 리턴이 되고...

--10번부터 50번 부서번호를 부서명으로 변경할 때
--DECODE 함수를 활용하라.
SELECT FIRST_NAME,
DECODE(DEPARTMENT_ID, 10, '총무부', 20, '마케팅부', 30, '사업부', 40, '인사부', 50, '배송관리부')
AS "업무부서"
FROM EMPLOYEES
WHERE DEPARTMENT_ID <=50 AND DEPARTMENT_ID >=10
ORDER BY DEPARTMENT_ID;

--변환함수
--TO_CHAR(number), TO_CHAR(date), TO_NUMBER(t), TO_DATE(t)
SELECT TO_CHAR(TO_DATE('19/08/06'), 'yy-mm-dd') "오늘의 날짜" 
FROM DUAL;

--각 사원의 입사일을 조사하여 이번달 (8월달)에 입사 기념일이 들어있는 
--사원의 이름과 입사 월/일을 표시하시오.

SELECT FIRST_NAME "사원 이름", TO_CHAR(HIRE_DATE, 'mm/dd') "입사 월/일"
FROM EMPLOYEES
WHERE SUBSTR(HIRE_DATE,3,4)= SUBSTR(SYSDATE,3,4)
ORDER BY "입사 월/일";

--2개의 테이블을 합친다
--다른 테이블의 구조를 가지고오는 코드
DESC DEPARTMENTS;
SELECT FIRST_NAME, E.DEPARTMENT_ID, DEPARTMENT_NAME
FROM EMPLOYEES "E", DEPARTMENTS "D"
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
ORDER BY E.DEPARTMENT_ID;

SELECT FIRST_NAME, E.DEPARTMENT_ID, DEPARTMENT_NAME
FROM EMPLOYEES "E" INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
ORDER BY E.DEPARTMENT_ID;

--각 사원의 이름, 직무명, 부서명, 최대 급여액
SELECT FIRST_NAME "이름", JOB_TITLE "직무명", DEPARTMENT_NAME "부서명", SALARY "급여액", MAX_SALARY "최대 급여액"
FROM EMPLOYEES "E" 
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
INNER JOIN JOBS "J"
ON E.JOB_ID = J.JOB_ID
ORDER BY E.FIRST_NAME;

-- 50번 부서의 이름, 직무명, 근무지 주소
SELECT FIRST_NAME "이름", DEPARTMENT_NAME "직무명", STREET_ADDRESS "근무지 주소"
FROM EMPLOYEES "E"
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID AND E.DEPARTMENT_ID = 50
INNER JOIN LOCATIONS "L"
ON D.LOCATION_ID = L.LOCATION_ID
ORDER BY E.FIRST_NAME;

--Alana의 근무지 주소?
SELECT FIRST_NAME "이름" ,STREET_ADDRESS "근무지 주소"
FROM EMPLOYEES "E"
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
INNER JOIN LOCATIONS "L"
ON D.LOCATION_ID = L.LOCATION_ID
WHERE E.FIRST_NAME = 'Alana';

--테이블 생성
CREATE TABLE PLAYERS (
    pid VARCHAR2(10) PRIMARY KEY,
    phone VARCHAR2(15),
    email VARCHAR2(15),
    regdate DATE,
    score NUMBER(4)
);

--테이블에 값 넣기 (컬럼에 값을 넣는다)
INSERT INTO PLAYERS (pid, phone, email, regdate, score)
VALUES (100, '010-0392-4969', 'p1@gmail.com', '2019/02/12', 0);

INSERT INTO PLAYERS (pid, phone, email, regdate, score)
VALUES (101, '010-3959-3819', 'p2@gmail.com', '2019/02/17', 0);

SELECT * FROM PLAYERS;

--행 정보 업데이트하기
UPDATE PLAYERS SET score=10+score
WHERE pid = 101;

DELETE FROM PLAYERS --이렇게 하면 데이터가 다 지워진다.
WHERE pid=101;

--GameHistory 테이블 생성 및 키 연동
CREATE TABLE GAMEHISTORY (
    PlayerID VARCHAR2 (10) REFERENCES PLAYERS(pid),
    GameDate DATE,
    GameName VARCHAR2 (15),
    GameDuration NUMBER (3,1),
    Team VARCHAR2 (15),
    Score NUMBER (3)
);
    
INSERT INTO GAMEHISTORY
VALUES ('100', '2018/03/15', 'LOL', 3.3, 'MyTeam', 20);

INSERT INTO GAMEHISTORY
VALUES ('101', '2019/05/02', 'OverWatch', 20.6, 'YourTeam', 42);

INSERT INTO GAMEHISTORY
VALUES('100', '2019/02/01', 'OverWatch', 5.1, 'YourTeam', 40);

SELECT * FROM GAMEHISTORY;

SELECT PID, EMAIL, GAMEDATE
FROM PLAYERS "P"
INNER JOIN GAMEHISTORY "GH"
ON P.PID = GH.PLAYERID
ORDER BY PID;

--열 추가하기

--열 삭제하기

--COMMIT
--ROLLBACK의 반대개념으로, 메모리에 들어있는 데이터를 DB에 저장시킨다.

--제약조건 이름 바꾸기
--SYS_C007587
ALTER TABLE PLAYERS RENAME CONSTRAINT SYS_C007587 TO Player_ID_PK;
COMMIT;

--SYS_C007589
ALTER TABLE GAMEHISTORY RENAME CONSTRAINT 
GH_PLAYER_ID_FK TO GameHistoryPID_FK;

COMMIT;

--TRANSACTION
--동시에 실행되어야 할 SQL 작업들/ 한 작업단위로 모두 함께 실행되어야 할 것