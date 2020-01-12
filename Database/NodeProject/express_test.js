//express_test.js
var express = require('express');
var app = express(); //express의 Top Level 함수
//express를 쓰려면 반드시 위 두줄을 해줘야한다.

/*app.get('/', function (req, res) {
    res.send('HelloWorld!');
});
*/
//클라이언트에게 파라미터를 받아와 서버 로그로 띄워본다.
//서버를 수정했으면 기존 서버를 닫아줘야 하기 때문에 컨트롤 창에서 ctrl +c를 눌러주고 다시 실행해준다.
app.get('/app/:num1/:num2', function (req, res) {
    console.log('num1 = %d, num2 = %d', req.params.num1, req.params.num2);
    var num1 = parseInt(req.params.num1);
    var num2 = parseInt(req.params.num2);
    var msg = '';
    msg = num1 + "+" + num2 + "=" + (num1+num2);
    //msg 꾸미기. (html로 코드한 것)
    //writeHead:데이터의 헤더, 즉 표식을 남겨 데이터가 클라이언트로 넘어갈 때 잘 처리되도록 한다.
    //즉 아래 코드에 붉은색 코드는 클라이언트에서 돌아가는 코드이다.
    //이런 것을 프론트앤드 코드라고 한다.
    var html = '<div style="color:red;">'+msg+'</div>';
    res.writeHead(200, {'Content-Type':'text/html'});
    //res.writeHead(200, {'Content-Type':'application/json'});
    res.write('<h1>Web Calculation</h1>');

    var jsonObj = {};
    jsonObj.num1=num1;
    jsonObj.num2=num2;
    res.end(JSON.stringify(jsonObj));
    //res.send(((req.query.num1*1)+(req.query.num2*1))+"");
    //res.send('HelloWorld!');
});

/* Pass방식의 데이터 전달. 요즘 선호한다.
http://localhost:3000/app/3/5
이것을 get에서 받으려면 app.get('/app/:num1/:num2', function...)
이렇게 명시해주면 된다.
또한 req.query.num1 이 아닌 req.params.num1으로 바꿔줘야한다.
*/

//위에서 앱을 정의해주고 (요청을 받으면 어떤 결과를 반환한다)
//아래의 코드에서 그 앱이 요청을 대기할 수 있도록 정의해준다. (listen)
app.listen(3000, function() {
    console.log('Example app listening on port 3000!');
});

/*http프로토콜 요청방식
get: 클라이언트가 서버에게 데이터를 요청하는 것
post: " 데이터를 주는 것
put: " 데이터를 고치거나 수정하는 것
delete: " 데이터를 지우는 것
head: " 헤드 데이터가 필요하다고 요청하는 것
*/

/*quary string = get 함수로 데이터를 넘겨주는 명령어
quary string이란 주소창에서 .com뒤에 ?를 붙여 값을 전달해주는 것이다.
이때 서버에서는 get이 돌아간다.
app.get('/', function (req, res) {
    console.log('num1=%d, num2=%d', req.query.num1, req.query.num2);
    res.send('HelloWorld!');
});
*/

/*
자바의 경우 자료형이 변수를 선언할 때 지정되는 것이 아니라(cpp), 값이 사용 될 때 알아서 지정되기 때문에
따로 자료형을 써주기보단 var이라는 (variable) 자료형으로 뭉뚱그려 지정해준다.
parseInt: Pass as int (정수로 읽어라)
cpp에서는 "문자", '문자열'이었지만 자바에서는 구분이 없다.
var msg = ''; 에서는 msg변수의 자료형을 '문자/문자열'로 지정해준 것이다.
(num1+num2)를 괄호로 묶어준 것은 문자열 취급이 아닌 이전에 pass as int(정수)로 돌아가기 위해 
이렇게 해준 것이다.
*/

/*
연산은 서버에서 하고 띄우는 것은 클라이언트(프론트앤드)에서 실행한다.
즉, 출력되는 내용을 꾸미고 싶을 때 (폰트, 크기, 디자인, 애니메이션)는
클라이언트 측에서 돌려줘야한다.
이 때 쓰는 언어가 HTML, 자바 스크립트 등등이다. 
*/