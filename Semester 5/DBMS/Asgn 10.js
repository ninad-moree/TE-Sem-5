db.Student.insertOne({
    name: "Ninad",
    branch: 'CE',
    rollno: 31253,
    scores: [
        { sub: "DBMS", marks: 90},
        { sub: "Lp1", marks: 97 },
        { sub: "CNS", marks: 86}
    ]
});

// AGGREGATION
db.Student.aggregate({
    $match: { branch: "CE" }
});

db.Student.aggregate([
    {
        $unwind: "$scores" 
    },
    {
        $group: {
            _id: "$rollno",
            totalMarks: { $sum: "$scores.marks" } //$avg, $min, $max, $first, $last, $push
        }
    }
]);

db.Student.aggregate([
    {$match: {rollno: 31253}},
    {$unwind: '$sores'},
]);


//INDEXING
db.Student.createIndex({name: 1});
db.Student.getIndexs();
db.Student.dropIndex({name: 1});

db.Student.createIndex({name: 1, rollno:1});

db.Student.distinct("name");

// // ===============================
// // 1) Aggregation
// // ===============================

// // SUM AGGREGATE
// db.website.aggregate({$group: {_id:"$name", "total": {$sum:"$amount"}}});

// // AVG AGGREGATE 
// db.website.aggregate({$group: {_id:"$name", "total": {$avg:"$amount"}}});

// // MIN AGGREGATION 
// db.website.aggregate({$group:{_id:"$name","total":{$min:"$amount"}}});

// // MAX AGGREGATION 
// db.website.aggregate({$group:{_id:"$name","total":{$max:"$amount"}}});

// // FIRST AGGREGATION 
// db.website.aggregate({$group:{_id:"$name","total":{$first:"$amount"}}});

// // LAST AGGREGATION 
// db.website.aggregate({$group:{_id:"$name","total":{$last:"$amount"}}});

// // PUSH AGGREGATION 
// db.website.aggregate({$group:{_id:"$name","total":{$push:"$amount"}}});

// // COUNT AGGREGATION
// db.website.aggregate({$group:{_id:"$name","total": {$sum:1}}});

// // ADDTOSET AGGREGATE 
// db.website.aggregate({$group:{_id:"$name","total": {$addToSet:"$amount"}}});

// // ===============================
// // 2) Indexing
// // ===============================

// db.createCollection('website1')

// db.website1.insert({'r':1,'name':'harsh'}); 

// db.website1.createIndex({'name':1})

// // CREATE INDEXING 
// db.website1.createIndex({'name':-1})

// db.website1.getIndexes()

// // DROP INDEX
// db.website.dropIndex({'name':-1})

// db.website1.dropIndex({'name':1})

// // GET INDEXING
// db.website1.getIndexes()

// db.website1.find().pretty()

// db.website1.createIndex({'name':1})

// db.website1.getIndexes()

// db.website1.dropIndex({'name':1})
