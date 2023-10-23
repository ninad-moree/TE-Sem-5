// 1) Insert Operations
db.product.insertOne({pid: 4, pname: "ABC", size: "S"});

db.product.insertMany([
{pid: 2, pname: "DEF", size: "M"}, 
{pid: 3, pname: "GHK", size: "L", brand: {company: "Nike", material: "Cotton"}}
]);

// 2) Read Operation
db.product.find().pretty();
// {
//     "_id" : ObjectId("652e008be0708de849b8c7db"),
//     "pid" : 4,
//     "pname" : "ABC",
//     "size" : "S"
// }
// {
//     "_id" : ObjectId("652e01afe0708de849b8c7dc"),
//     "pid" : 2,
//     "pname" : "DEF",
//     "size" : "M"
// }
// {
//     "_id" : ObjectId("652e01afe0708de849b8c7dd"),
//     "pid" : 3,
//     "pname" : "GHK",
//     "size" : "L",
//     "brand" : {
//    	 "company" : "Nike",
//    	 "material" : "Cotton"
//     }
// }

// 3) Delete Operation
db.product.deleteOne({ pname: "DEF" })

// 4) Update Operation
db.product.updateOne( {pid: 4}, { $set: {pname: "XYZ"} } )

// 5) Save Operation
db.product.save( {pid: 1, pname: "ABC", size: "S"} )
