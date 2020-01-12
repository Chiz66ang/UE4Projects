var http = require('http');
var hostname = '192.168.0.4';
var port = 3000;
http.createServer(function(req,res){
   res.writeHead(200,{'Content-Type': 'text/plain'});
   res.end('HelloWorld\n');
}).listen(port, hostname);
console.log('Server running at http://'+hostname+':'+port);