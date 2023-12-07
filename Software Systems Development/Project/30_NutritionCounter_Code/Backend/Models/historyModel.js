const mongoose = require("mongoose");

const Schema = mongoose.Schema;

const historySchema = new Schema(
  {
    question: {
      type: String,
      required: true,
    },
    answer: {
      type: String,
      required: true,
    },
    user_id: {
      type: String,
    }
  },
  { timestamps: true }
);

module.exports = mongoose.model("History", historySchema);
