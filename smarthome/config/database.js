var mysql = require('mysql');

function Connection(){
	this.pool = null;
	var konek = {
		host:'localhost',
		user:'root',
		password:'asshole',
		database:'db_kesosi'
	};

	var pool = mysql.createPool(konek);

	this.acquire = function(callback){
			pool.getConnection(function(err,connection){
			callback(err,connection);
		});
	};
}

module.exports = new Connection();

