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



// db.website.aggregate({$group: {_id:"$name", "total": {$sum:"$amount"}}});

// db.website.aggregate({$group: {_id:"$name", "total": {$avg:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total":{$min:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total":{$max:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total":{$first:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total":{$last:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total":{$push:"$amount"}}});

// db.website.aggregate({$group:{_id:"$name","total": {$sum:1}}});

// db.website.aggregate({$group:{_id:"$name","total": {$addToSet:"$amount"}}});


// db.createCollection('website1')

// db.website1.insert({'r':1,'name':'harsh'}); 

// db.website1.createIndex({'name':1})

// db.website1.createIndex({'name':-1})

// db.website.dropIndex({'name':-1})

// db.website1.dropIndex({'name':1})

// db.website1.getIndexes()

// db.website1.find().pretty()

// db.website1.createIndex({'name':1})

// db.website1.getIndexes()

// db.website1.dropIndex({'name':1})
