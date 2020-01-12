--Employees ���̺��� �μ��� �������� ���� ������� �̸��� �̸��� ������ �˻��غ�����
--NULL�� �˻��� ���� is null�̶�� ǥ���� ���ϴ�.
SELECT * FROM employees;
SELECT Last_name "�̸�", email "�̸���", department_id "�μ���ȣ" FROM employees
WHERE department_id is null;

--�μ���ȣ ������������ ����̸�, �μ���ȣ, �޿����� ǥ���ϵ�
--�μ��� �������� ���� ����� ���� ���� ����Ѵ�.
--ORDERBY~NULL FIRST/LAST ���
SELECT LAST_NAME "�̸�", DEPARTMENT_ID "�μ���ȣ", SALARY "�޿���" FROM employees
ORDER BY DEPARTMENT_ID NULLS FIRST;

--������ ���� �� �ٸ� �÷����� ������ �ϰ� ���� ���� �ڿ� , ���������� �ָ� �ȴ�.
--��, ORDER BY �ڿ� ��ǥ�� ���еǴ� ���� ������ �켱������� �� �� �ִ�.
SELECT LAST_NAME "�̸�", DEPARTMENT_ID "�μ���ȣ", SALARY "�޿���" FROM employees
ORDER BY DEPARTMENT_ID NULLS FIRST, SALARY DESC;

--������� �Ի��� �������� �������� �����ϵ�
--��ȣ, �̸�, �޿��� ǥ���ϰ� �÷����� ��Ī�� ����غ�����.
SELECT EMPLOYEE_ID "�����ȣ", LAST_NAME "�̸�", SALARY "�޿�" FROM employees
ORDER BY HIRE_DATE;

--�� ǥ���� ����ϱ�
SELECT LAST_NAME
FROM EMPLOYEES
WHERE 1!=1;

--�μ���ȣ�� 50�� �ƴϰ� 60�� �ƴ� ��� �߿���
--�Ի����� 03�� ������ �ƴ� ������� �̸�, �μ���ȣ, �Ի����� ǥ���غ�����.
SELECT LAST_NAME "�̸�", DEPARTMENT_ID "�μ���ȣ", HIRE_DATE "�Ի���" FROM employees
WHERE DEPARTMENT_ID !=50 AND DEPARTMENT_ID !=60 
AND NOT HIRE_DATE < (TO_DATE('03/01/01'))
ORDER BY HIRE_DATE;

--BETWEEN ����
-- ���� ���� A�� B ���̿� �ִٸ� TURE�� ��ȯ�Ѵ�.
SELECT * FROM employees
WHERE SALARY NOT BETWEEN 0 AND 3000;

--IN ������
--IN�� �����ǿ� �ٴµ�, �� ���� �ִ�(TURE��) ���� ��� ��ȯ�Ѵ�.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN (40,50);

--������� ����(JOB)�� ST_MAN�� �ƴϰ�, ST_CLERK�� �ƴ�
--������� �̸�, ������ ǥ���غ�����. 
SELECT LAST_NAME "�̸�", JOB_ID "����" FROM employees
WHERE NOT JOB_ID IN ('ST_MAN', 'ST_CLERK')
ORDER BY JOB_ID;

--LIKE ������:���ϰ˻� ( % , _ )
-- %: ���ڰ� �Ѱ��� ���ų�, �Ѱ� �̻��� ����� ���ϵ� ī��
-- _: ���� �Ѱ��� �ǹ��ϴ� ���ϵ� ī��
-- ���ڿ��� �Է��� �� ��ҹ��ڰ� �����ȴ�...
SELECT LAST_NAME FROM employees
WHERE LAST_NAME LIKE 'A%_l';

--LAST_NAME�� 'E'�� ������ ��� ����� LAST_NAME�� ǥ���غ�����
SELECT LAST_NAME FROM employees
WHERE LAST_NAME LIKE '%e'
ORDER BY LAST_NAME ASC;

--CASE (���� 102�� ����)
--10~50�� �μ���ȣ�� ���, �λ���, �����, ������, ���������� 
--�����ϰ� �� ����� �̸�, �μ���ȣ, �μ����� ǥ���غ�����.
SELECT LAST_NAME "�̸�"
, CASE DEPARTMENT_ID
    WHEN 10 THEN '���'
    WHEN 20 THEN '������'
    WHEN 30 THEN '������'
    WHEN 40 THEN '�λ���'
    WHEN 50 THEN '�����'
    ELSE '�μ��̹���'
END AS "�μ���"
FROM employees
WHERE DEPARTMENT_ID BETWEEN 10 AND 50
ORDER BY DEPARTMENT_ID;

-- 03�⵵�� �Ի��ڿ� 50�� �μ��� �������� 5% �޿��� �λ��Ͽ� 
-- ����� �̸�, �Ի���, ���� �޿�, �λ�� �޿��� ǥ���غ�����.
SELECT LAST_NAME "�̸�", HIRE_DATE "�Ի���", SALARY "�����޿�"
, CASE  WHEN HIRE_DATE BETWEEN TO_DATE('03/01/01') AND TO_DATE('03/12/31') THEN SALARY*1.05
        WHEN DEPARTMENT_ID = 50 THEN SALARY*1.05
        ELSE 0
END AS "�λ�޿�"
FROM employees
WHERE HIRE_DATE BETWEEN TO_DATE('03/01/01') AND TO_DATE('03/12/31')
OR DEPARTMENT_ID = 50
ORDER BY "�λ�޿�";

--SUB QUERIES
--�Ʒ� ������ DEPARTMENT_ID�� �ϵ��ڵ��ؼ� ���� ���� �־��� ���ε�, �̴� �����ڰ� �� ���� ������ �˰��ִٴ� �����Ͽ� ����ȴ�.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN(20,40,50);
--Ư���� �������� �������� �־��ְ� ���� �� SUBQUERIES�� ���µ�, �̴� �Ʒ�ó�� �� �ٸ� ���� ���������� �ִ� ���� ���Ѵ�.
SELECT * FROM employees
WHERE DEPARTMENT_ID IN(
SELECT DEPARTMENT_ID FROM employees
);

--���������� �̿��Ͽ� �μ��� 50�̰ų� JOB_ID�� IT_PROG��
--��� ����� ������ ǥ���غ�����
SELECT * FROM 
(
    SELECT * FROM EMPLOYEES
    WHERE DEPARTMENT_ID = 50 OR JOB_ID = 'IT_PROG'
); --�ۼ��� ���������� FROM ������ TABLE�� �ǹ̷� ���̰� �ִ�. �̸� IN-LINE VIEW��� �Ѵ�.

--DAVID�� ���� ������� ȭ�鿡 ����غ�����
SELECT FIRST_NAME, DEPARTMENT_ID FROM EMPLOYEES
WHERE DEPARTMENT_ID =
(
SELECT DEPARTMENT_ID FROM EMPLOYEES
WHERE FIRST_NAME='David' AND LAST_NAME='Lee'
);

--Allan �� Peter, Oliver�� ���� �繫�� �������� 
--�̸�, �μ���ȣ, �޿��� ǥ���ϰ� �μ���ȣ ������ �����غ�����.
SELECT FIRST_NAME, DEPARTMENT_ID, SALARY FROM EMPLOYEES
WHERE DEPARTMENT_ID IN --����� �Ѱ� �̻��̴� IN �����ڰ� �����ϰڴ�.
-- �Ѱ��� ����� �̰�ʹٸ�:ANY
-- ��� ��ġ�ϴ� �� ����� �̰�ʹٸ�: ALL
-- �� �� ��� �̰� �ʹٸ�: SOME
(
SELECT DEPARTMENT_ID FROM EMPLOYEES
WHERE FIRST_NAME='David' OR FIRST_NAME= 'Peter' OR FIRST_NAME= 'Oliver'
)
ORDER BY DEPARTMENT_ID;

--����Ŭ�� �����ϴ� �پ��� �Լ�
--���� ��¥ ����ϱ�
SELECT SYSDATE AS "������ ��¥" FROM DUAL;
--����Ŭ�� �����ϴ� �پ��� ���� �Լ�
--���� �ø�(ū ����)/����(���� ����) �� ����ϱ�
SELECT CEIL(1.234), FLOOR(1.234) FROM DUAL;
--���� ���밪 ����ϱ�
SELECT ABS(-10) FROM DUAL;
--���� ��ȣ ����ϱ�
SELECT SIGN(-10), SIGN(0), SIGN(10) FROM DUAL;
--���� ����ϱ�: e^���
SELECT EXP(1) FROM DUAL;
--������ ����ϱ�
SELECT SQRT(9) FROM DUAL;
--�α� ����ϱ� (ù��° ���ڸ� ����� �ؾ� �ι�° ���ڰ� �Ǵ°�)
SELECT LOG(3,9) FROM DUAL;
--�ڿ��α� (���� e���ϴ� �α�: ln 2.718281828) ����ϱ�
SELECT LN(2.718281828) FROM DUAL;
--������ ����ϱ� (modular ������, cpp���� %�� ����)
SELECT MOD(10,3) FROM DUAL;
--�ﰢ�Լ� ������
SELECT SIN(2), COS(3), TAN(4) FROM DUAL;
--���ﰢ�Լ� ������
SELECT ASIN(0.5), ACOS(0.5), ATAN(0.5) FROM DUAL;
--�ְ�Լ� ������
SELECT SINH(3), COSH(3), TANH(3) FROM DUAL;

--���ڿ��� �ٷ�� �Լ��� ���� P.122����
--���ڿ��� ���̸� ��ȯ
SELECT LENGTH('Hello') FROM DUAL;
--�ƽ�Ű�ڵ� ��ȣ�� ��ȯ
SELECT ASCII('A'), ASCII('a') FROM DUAL;
--�ƽ�Ű�ڵ带 �޾� ���ڸ� ��ȯ
SELECT CHR(65) FROM DUAL;
--���ڿ��� �빮��, �ҹ��ڷ� �ٲٱ�
SELECT UPPER('abc'), LOWER('HELLO') FROM DUAL;

SELECT LTRIM('    HELLO') FROM DUAL;
--���ڿ� ����(L), ������(R)�� ���𰡸� ����� (PAD)
--�� ���ڿ��� �����Ͽ� Ư�� ��(10)�� �� ������ �����.
SELECT LPAD('hello', 10, '-') FROM DUAL;

--��� FIRST_NAME�� '_' 2���� ���ʿ� ��������.
SELECT LPAD(FIRST_NAME, LENGTH(FIRST_NAME)+2, '-')
FROM employees;

--SUBSTRING ���� ���ڿ� �����ϱ�
SELECT SUBSTR(FIRST_NAME, 0,3) FROM EMPLOYEES;
--SUBSTRING �Լ��� �̿��Ͽ� �� ����� �Ի翬���� �����Ͽ� ǥ���غ�����
SELECT SUBSTR(HIRE_DATE, 0,2), FIRST_NAME FROM EMPLOYEES
ORDER BY HIRE_DATE;

--�Ի翬���� 07������ ����� �̸��� �μ���ȣ, �Ի翬������ ǥ���غ�����
SELECT HIRE_DATE "�Ի� ��¥", FIRST_NAME "�̸�", DEPARTMENT_ID "�μ���ȣ" FROM EMPLOYEES
WHERE SUBSTR(HIRE_DATE, 0,2)=07
ORDER BY HIRE_DATE;

--���ڿ� �ȿ��� �˻�: ã�� ��ġ�� �����Ѵ�.
SELECT INSTR('HELLO', 'HE') FROM DUAL;
--���ڿ� ��ü
SELECT REPLACE('hello', 'HELLO') FROM DUAL;
--���ڿ� ���̱�
SELECT CONCAT('Hello', 'World') FROM DUAL;

--FIRST_NAME, LAST_NAME�� �ٿ��� "�̸�"���� ǥ���� ��
--12�ڰ� �Ѵ� ���ڿ��� 13��°�� '...'�� �ٿ��� ǥ���غ�����
SELECT 
CASE 
WHEN LENGTH(CONCAT(FIRST_NAME,LAST_NAME))>12 THEN 
CONCAT(SUBSTR(CONCAT(FIRST_NAME,LAST_NAME),0,12)||'...')
ELSE CONCAT (FIRST_NAME, LAST_NAME)
END AS "��� �̸�"
FROM EMPLOYEES;

--Shanta ���� �޿��� ���� �޴� ������� �̸�, �޿����� ǥ���غ�����.
SELECT FIRST_NAME "�̸�", SALARY "�޿���"
FROM EMPLOYEES
WHERE SALARY > 
    (
    SELECT SALARY FROM EMPLOYEES
    WHERE FIRST_NAME= 'Shanta'
    )
ORDER BY SALARY;

--NVL(x,y) �Լ� : x�� NULL�̶�� y�� �����Ѵ�.
--�ΰ��� �˻��ϴ� �Լ� (NULL VALUE)
SELECT FIRST_NAME "�̸�", NVL(MANAGER_ID, 0) "������ ��ȣ"
FROM EMPLOYEES;

--NVL2 �Լ�: MANAGER_ID�� NULL�̶�� x�� �����ϰ�, NULL�� �ƴ϶�� y�� �����Ѵ�.
SELECT FIRST_NAME "�̸�", NVL2(MANAGER_ID, 'x', 'y') "������ ��ȣ"
FROM EMPLOYEES;

--DECODE(x,a,b,c,d,e,f,......)
--x�� a�� ������ b�� ���ϵǰ�, c�� ������ d�� ���ϵǰ�, e�� ������ f�� ������ �ǰ�...

--10������ 50�� �μ���ȣ�� �μ������� ������ ��
--DECODE �Լ��� Ȱ���϶�.
SELECT FIRST_NAME,
DECODE(DEPARTMENT_ID, 10, '�ѹ���', 20, '�����ú�', 30, '�����', 40, '�λ��', 50, '��۰�����')
AS "�����μ�"
FROM EMPLOYEES
WHERE DEPARTMENT_ID <=50 AND DEPARTMENT_ID >=10
ORDER BY DEPARTMENT_ID;

--��ȯ�Լ�
--TO_CHAR(number), TO_CHAR(date), TO_NUMBER(t), TO_DATE(t)
SELECT TO_CHAR(TO_DATE('19/08/06'), 'yy-mm-dd') "������ ��¥" 
FROM DUAL;

--�� ����� �Ի����� �����Ͽ� �̹��� (8����)�� �Ի� ������� ����ִ� 
--����� �̸��� �Ի� ��/���� ǥ���Ͻÿ�.

SELECT FIRST_NAME "��� �̸�", TO_CHAR(HIRE_DATE, 'mm/dd') "�Ի� ��/��"
FROM EMPLOYEES
WHERE SUBSTR(HIRE_DATE,3,4)= SUBSTR(SYSDATE,3,4)
ORDER BY "�Ի� ��/��";

--2���� ���̺��� ��ģ��
--�ٸ� ���̺��� ������ ��������� �ڵ�
DESC DEPARTMENTS;
SELECT FIRST_NAME, E.DEPARTMENT_ID, DEPARTMENT_NAME
FROM EMPLOYEES "E", DEPARTMENTS "D"
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
ORDER BY E.DEPARTMENT_ID;

SELECT FIRST_NAME, E.DEPARTMENT_ID, DEPARTMENT_NAME
FROM EMPLOYEES "E" INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
ORDER BY E.DEPARTMENT_ID;

--�� ����� �̸�, ������, �μ���, �ִ� �޿���
SELECT FIRST_NAME "�̸�", JOB_TITLE "������", DEPARTMENT_NAME "�μ���", SALARY "�޿���", MAX_SALARY "�ִ� �޿���"
FROM EMPLOYEES "E" 
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
INNER JOIN JOBS "J"
ON E.JOB_ID = J.JOB_ID
ORDER BY E.FIRST_NAME;

-- 50�� �μ��� �̸�, ������, �ٹ��� �ּ�
SELECT FIRST_NAME "�̸�", DEPARTMENT_NAME "������", STREET_ADDRESS "�ٹ��� �ּ�"
FROM EMPLOYEES "E"
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID AND E.DEPARTMENT_ID = 50
INNER JOIN LOCATIONS "L"
ON D.LOCATION_ID = L.LOCATION_ID
ORDER BY E.FIRST_NAME;

--Alana�� �ٹ��� �ּ�?
SELECT FIRST_NAME "�̸�" ,STREET_ADDRESS "�ٹ��� �ּ�"
FROM EMPLOYEES "E"
INNER JOIN DEPARTMENTS "D"
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
INNER JOIN LOCATIONS "L"
ON D.LOCATION_ID = L.LOCATION_ID
WHERE E.FIRST_NAME = 'Alana';

--���̺� ����
CREATE TABLE PLAYERS (
    pid VARCHAR2(10) PRIMARY KEY,
    phone VARCHAR2(15),
    email VARCHAR2(15),
    regdate DATE,
    score NUMBER(4)
);

--���̺� �� �ֱ� (�÷��� ���� �ִ´�)
INSERT INTO PLAYERS (pid, phone, email, regdate, score)
VALUES (100, '010-0392-4969', 'p1@gmail.com', '2019/02/12', 0);

INSERT INTO PLAYERS (pid, phone, email, regdate, score)
VALUES (101, '010-3959-3819', 'p2@gmail.com', '2019/02/17', 0);

SELECT * FROM PLAYERS;

--�� ���� ������Ʈ�ϱ�
UPDATE PLAYERS SET score=10+score
WHERE pid = 101;

DELETE FROM PLAYERS --�̷��� �ϸ� �����Ͱ� �� ��������.
WHERE pid=101;

--GameHistory ���̺� ���� �� Ű ����
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

--�� �߰��ϱ�

--�� �����ϱ�

--COMMIT
--ROLLBACK�� �ݴ밳������, �޸𸮿� ����ִ� �����͸� DB�� �����Ų��.

--�������� �̸� �ٲٱ�
--SYS_C007587
ALTER TABLE PLAYERS RENAME CONSTRAINT SYS_C007587 TO Player_ID_PK;
COMMIT;

--SYS_C007589
ALTER TABLE GAMEHISTORY RENAME CONSTRAINT 
GH_PLAYER_ID_FK TO GameHistoryPID_FK;

COMMIT;

--TRANSACTION
--���ÿ� ����Ǿ�� �� SQL �۾���/ �� �۾������� ��� �Բ� ����Ǿ�� �� ��