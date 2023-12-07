const mongoose = require('mongoose');
const NoChildSchema = new mongoose.Schema({
  itemNo: Number,
  name: String,
});

const NoChild = mongoose.model('NoChild', NoChildSchema);
module.exports = NoChild;
