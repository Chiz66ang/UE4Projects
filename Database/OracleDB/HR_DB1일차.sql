SELECT tname FROM TAB;
SELECT * FROM employees;
SELECT SALARY FROM employees;
SELECT last_name, salary FROM employees WHERE last_name='Austin';
--�޿��� 5000���� 8000���̿� �ִ� ����� �̸�, �μ�, �����ȣ�� ����Ͻÿ�.
SELECT first_name, last_name, salary, employee_ID, job_id 
FROM employees 
WHERE salary>=5000 AND salary<=8000 
ORDER BY salary DESC;

--�μ���ȣ�� 50�̰ų� 80�� ��� �߿��� �޿��� 8000 �̻��� ����� �̸�, �μ���ȣ, �޿��� ����Ͻÿ�
SELECT first_name, last_name, department_id, salary 
FROM employees 
WHERE (department_id=50 OR department_id=80) 
AND salary>=8000
ORDER BY salary;

--������� ����̸�, �μ���, �޿����� �ۼ��Ͻÿ�.
SELECT last_name "����̸�", department_ID "�μ���", salary "�޿���" FROM employees;

--������� �޿��� 2.5% �÷��� �� �� �ݾװ� �ø� �ݾ��� ������ ����Ͻÿ�.
--�������� ���̱� ���� AS�� ����Ͽ���, ��Ī�� ���Ⱑ ���ٸ� �ݵ�� ""�� �����־�� �Ѵ�.
SELECT last_name AS "����̸�", department_ID AS "�μ���", salary AS "���� �޿���", salary * 1.025 AS "�ø� �޿���" FROM employees
ORDER BY department_id, salary;

SELECT SYSDATE FROM DUAL;
SELECT SYSDATE FROM employees;
--���⼭ SYSDATE�� ����Ŭ���� �����ϴ� �ý��� ��¥�� ���ϴ� �Լ��̴�. �Ķ���͸� ���� �ʱ� ������ �Լ��� ���� ()�� ������ �ʴ´�.
--SELECT �������� ���� ������/�����ϴ� ��Ī�� ���� �ȴ�. ��, �÷��� ���� ���� �ƴ϶�� ���̴�.
--SYSDATE �Լ��� ���̺� �����ִ°� �ƴ� ����Ŭ ��ü���� �����ϴ� �Լ��̱� ������ FROM ������ Ư���� ���̺���� ���� �ʾƵ� �ȴ�.
--��� ���̺� �� �� ��ŭ ���� �����ϱ� ������ ���� �ѹ��� ����ϰ� ���� �� DUAL�̶�� �� ��¿� ���̺��� ���ָ� �ȴ�.

--ȸ���� �μ���ȣ�� ��� ����Ͻÿ�.
--�÷��� �տ� DISTINCT�� ����ϸ� �ߺ��� ���� ���� �� �ִ�.
SELECT DISTINCT department_id as "�μ���ȣ"
FROM employees
WHERE department_id IS NOT NULL
ORDER BY "�μ���ȣ";

--���� ������. ||�� ���ڿ� ���տ����ڴ�.
--�Ʒ� ���ô� A���ڿ�, ����, C���ڿ��� �����Ͽ� ǥ���ϴ� ���̴�.
SELECT 'A' || '   ' || 'C' FROM DUAL;

--���ڿ��� ��¥������ ����Ȱ �� ��.
--TO_DATE('19/08/01')�� ''�ȿ� �� ���ڿ��� ��¥�� �ٲٶ�� �Լ��̴�.
--�Ʒ� �ڵ�� ���糯¥ (SYSDATE)���� ���ڿ����� �ٲ� ��¥�� �� ���̴�.
--ROUND�� �ݿø��ϴ� ���̴�. �Լ� ���۷����� �Ҽ� ���°�ڸ����� �ݿø����� �������ָ� �ȴ�.
SELECT ROUND(SYSDATE-TO_DATE('19/08/01'),1) FROM DUAL;
