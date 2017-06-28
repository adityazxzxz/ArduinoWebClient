var db = require('../../config/database');

function Todo(){
	this.get = function(req,res,next){
		db.acquire(function(err,con){
			if(err) throw err;
			con.query('select * from pmb',function(err,data){
				con.release();
				if(err)
					return res.json({status:'400',message:'Failed',result:[]});

				return res.json({status:'200',message:'Success',result:data});
			});
		});
	}
}

module.exports = new Todo();