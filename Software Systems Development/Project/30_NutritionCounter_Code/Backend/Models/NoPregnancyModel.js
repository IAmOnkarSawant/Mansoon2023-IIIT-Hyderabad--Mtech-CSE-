const mongoose = require('mongoose');
const NoPregnancySchema = new mongoose.Schema({
  itemNo: Number,
  name: String,
});

const NoPregnancy = mongoose.model('NoPregnancy', NoPregnancySchema);
module.exports = NoPregnancy;
