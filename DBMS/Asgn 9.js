// 1) INSERT OPERATIONS:
db.Product.insertOne({pid: 4, pname: "ABC", size:"S", price: 29, rating: 4})

db.Product.insertOne({pid: 1, pname: "DEF", size:"S", price: 110, rating: 4.5})

db.Product.insertMany([
    {pid: 2, pname: "GHK", size: "M", price: 199, rating: 3.7},
    {pid: 3, pname: "LKM", size: "L", price: 69, rating: 3.4},
    {pid: 5, pname: "NHK", size: "L", price: 299, rating: 4.9},
    {pid: 6, pname: "TUV", size: "S", price: 100, rating: 3.0}
]);


// 2) READ OPERATIONS
db.Product.find()

db.Product.find({rating: {$gt: 3}})


// 3) DELETE OPERATIONS
db.Product.deleteOne({pname: "GHK"})

// 4) UPDATE OPERATIONS
db.Product.updateOne({pname: "NHK"}, {$set: {price: 169}})

// 5) OPERATORS

// a-AND
db.Product.find({
    price: { $lt: 150},
    rating: {$gt: 3.5}
})

// b-OR
db.Product.find({
    $or: [
      {price: {$gt: 100}},
      {size: "S"}
    ]
})



