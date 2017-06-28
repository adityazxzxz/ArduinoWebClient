var express = require('express');
var logger = require('morgan');
var bodyParser = require('body-parser');
var user = require('./app/routes/user');

var app = express();
user.configure(app);

app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));
console.log('App js loaded');

//export file app.js agal bisa di import oleh js lain
module.exports = app;