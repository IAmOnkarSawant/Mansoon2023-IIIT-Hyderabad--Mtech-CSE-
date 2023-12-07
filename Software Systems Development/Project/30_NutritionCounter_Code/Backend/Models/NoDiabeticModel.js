const mongoose = require('mongoose');
const NoDiabeticSchema = new mongoose.Schema({
  itemNo: Number,
  name: String,
});

const NoDiabetic = mongoose.model('NoDiabetic', NoDiabeticSchema);
module.exports = NoDiabetic;
