var user = require('../controllers/user');

module.exports = {
	configure:function(app){
		app.route('/user').get(user.get);
	}
};