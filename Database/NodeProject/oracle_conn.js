
//oracle_conn.js
const oracledb = require('oracledb');
var emp_id = 101;
oracledb.getConnection(
{
   user		:"hr",
   password	:"hr",
   connectString:"192.168.0.4/XEPDB1"
},
function(err, connection){
if(err){
   console.error(err.message);


   return;
}
connection.execute(
   'SELECT * FROM employees WHERE employee_id=:bv',
   [emp_id],
   {
   maxRows:1
   },

function(err, result)
{
   if(err){
	console.error(err.message);
	connection.close();
	return;
   }
   //console.log(result.metaData); //Column names etc
   console.log(result.rows); //
   connection.close();
   }
);
}
);