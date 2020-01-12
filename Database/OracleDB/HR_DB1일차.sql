SELECT tname FROM TAB;
SELECT * FROM employees;
SELECT SALARY FROM employees;
SELECT last_name, salary FROM employees WHERE last_name='Austin';
--급여가 5000에서 8000사이에 있는 사원의 이름, 부서, 사원번호를 출력하시오.
SELECT first_name, last_name, salary, employee_ID, job_id 
FROM employees 
WHERE salary>=5000 AND salary<=8000 
ORDER BY salary DESC;

--부서번호가 50이거나 80인 사원 중에서 급여가 8000 이상인 사원의 이름, 부서번호, 급여를 출력하시오
SELECT first_name, last_name, department_id, salary 
FROM employees 
WHERE (department_id=50 OR department_id=80) 
AND salary>=8000
ORDER BY salary;

--사원들의 사원이름, 부서명, 급여액을 작성하시오.
SELECT last_name "사원이름", department_ID "부서명", salary "급여액" FROM employees;

--사원들의 급여를 2.5% 올려서 그 전 금액과 올린 금액을 나란히 출력하시오.
--가독성을 높이기 위해 AS를 사용하였고, 별칭에 띄어쓰기가 들어간다면 반드시 ""로 감싸주어야 한다.
SELECT last_name AS "사원이름", department_ID AS "부서명", salary AS "이전 급여액", salary * 1.025 AS "올린 급여액" FROM employees
ORDER BY department_id, salary;

SELECT SYSDATE FROM DUAL;
SELECT SYSDATE FROM employees;
--여기서 SYSDATE는 오라클에서 제공하는 시스템 날짜를 구하는 함수이다. 파라미터를 받지 않기 때문에 함수명 끝에 ()를 붙이지 않는다.
--SELECT 다음에는 값을 가지는/리턴하는 명칭이 오면 된다. 즉, 컬럼명만 오는 것이 아니라는 뜻이다.
--SYSDATE 함수는 테이블에 속해있는게 아닌 오라클 자체에서 제공하는 함수이기 때문에 FROM 다음에 특정한 테이블명이 오지 않아도 된다.
--대신 테이블 행 수 만큼 값을 리턴하기 때문에 값을 한번만 출력하고 싶을 땐 DUAL이라는 값 출력용 테이블을 써주면 된다.

--회사의 부서번호를 모두 출력하시오.
--컬럼명 앞에 DISTINCT를 사용하면 중복된 값을 지울 수 있다.
SELECT DISTINCT department_id as "부서번호"
FROM employees
WHERE department_id IS NOT NULL
ORDER BY "부서번호";

--결합 연산자. ||는 문자열 결합연산자다.
--아래 예시는 A문자열, 공백, C문자열을 결합하여 표현하는 식이다.
SELECT 'A' || '   ' || 'C' FROM DUAL;

--문자열을 날짜형으로 형변활 할 때.
--TO_DATE('19/08/01')은 ''안에 든 문자열을 날짜로 바꾸라는 함수이다.
--아래 코드는 현재날짜 (SYSDATE)에서 문자열에서 바꾼 날짜를 뺀 것이다.
--ROUND는 반올림하는 것이다. 함수 레퍼런스에 소수 몇번째자리까지 반올림할지 지정해주면 된다.
SELECT ROUND(SYSDATE-TO_DATE('19/08/01'),1) FROM DUAL;
