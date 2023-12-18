db.createCollection('Journal');

db.Journal.insert({'book_id':1,'book_name':'JavacdOOP','amt':500,'status':'Available'});
db.Journal.insert({'book_id':1,'book_name':'JavaOOP','amt':400,'status':'NotAvailable'});
db.Journal.insert({'book_id':1,'book_name':'Java','amt':300,'status':'NotAvailable'});
db.Journal.insert({'book_id':2,'book_name':'Java','amt':300,'status':'Available'});
db.Journal.insert({'book_id':2,'book_name':'OPP','amt':200,'status':'Available'});
db.Journal.insert({'book_id':2,'book_name':'C+','amt':200,'status':'Available'});
db.Journal.insert({'book_id':3,'book_name':'C+','amt':150,'status':'Available'});
db.Journal.insert({'book_id':3,'book_name':'C++','amt':200,'status':'NotAvailable'});
db.Journal.insert({'book_id':4,'book_name':'OPP C++','amt':300,'status':'Not Available'});
db.Journal.insert({'book_id':5,'book_name':'OPPC++','amt':400,'status':'Available'});
db.Journal.insert({'book_id':5,'book_name':'C++','amt':400,'status':'Available'});
db.Journal.insert({'book_id':5,'book_name':'C++Java','amt':400,'status':'NotAvailable'});


var mapfunction=function(){ emit(this.book_id,this.amt)};

var reducefunction=function(key,value){return Array.sum(value);};

db.Journal.mapReduce(mapfunction,reducefunction, {'out':'new'});
// {
//     "result" : "new",
//     "timeMillis" : 49,
//     "counts" : {
//         "input" : 12,
//         "emit" : 12,
//         "reduce" : 4,
//         "output" : 5
//     }
//     "ok" : 1
// } 



db.Journal.mapReduce(mapfunction,reducefunction,{'out':'new'}).find().pretty();
// { "_id" : 1, "value" : 1200}
// { "_id" : 2, "value" : 700 }
// { "_id" : 3, "value" : 350 }
// { "_id" : 4, "value" : 300 }
// { "_id" : 5, "value" : 1200}


db.new.find().pretty();
// { "_id" : 1, "value" : 1200 }
// { "_id" : 2, "value" : 700 }
// { "_id" : 3, "value" : 350 }
// { "_id" : 4, "value" : 300 }
// { "_id" : 5, "value" : 1200 }
