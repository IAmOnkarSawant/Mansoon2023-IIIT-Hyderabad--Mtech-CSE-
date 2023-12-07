const mongoose = require('mongoose');
const NoCardiacSchema = new mongoose.Schema({
  itemNo: Number,
  name: String,
});

const NoCardiac = mongoose.model('NoCardiac', NoCardiacSchema);
module.exports = NoCardiac;
