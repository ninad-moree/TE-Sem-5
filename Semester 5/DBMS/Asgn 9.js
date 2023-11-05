//INSERTION
db.Student.insertOne({
    rollno: 31253,
    name: "Ninad",
    marks: 93,
    address: [
        {
            city: "Pune",
            pin: 411046,
        }
    ]
});

// SEARCHING
db.Student.find();

db.Student.find({name:"Ninad"});

db.Student.find({name:"Ninad", marks: {$gt: 90}});

db.Student.find({name:"Ninad"}).limit(1);

db.Student.find({name:"Ninad"}).sort({marks: 1});

db.Student.find({name:"Ninad"}).skip(1);

db.Student.find({name:"Ninad"}).count();

db.Student.find({marks: {$in: [80,90]}}); //$in , $nin

//$gt, $lt, $gte, $lte, $ne
db.Student.find({
    //$not,$and
    $or: [
        {name: "Ninad"},
        {marks: {$gt: 80}}
    ]
});

db.Student.find(
    {"address.city": "Pune"}
);

//DELETION
db.Student.deleteOne({name: "Ninad"});

//UPDATION
db.Student.updateOne(
    {name: "Ninad"},
    {$set: {"address.city": "mumbai"}}
);

db.Student.updateOne(
    {name: "Ninad"},
    {$set: {marks: 95}}
);

db.Student.insertOne({
    name: "Vinit",
    rollno: 31254,
    branch: "CE",
    marks: [90,87,91,98],
});

db.Student.find(
    {name: "Vinit"},
    {"marks": {$slice: 2}},
);

db.Student.find({
        name: "Vinit",
        marks: {$size: 4},
});

db.Student.updateOne(
    {name: "Vinit"},
    {$push: {marks: 78}}
);