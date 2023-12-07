const mongoose = require('mongoose')

let Schema = mongoose.Schema
const StudentSchema = new Schema(
    {
        name: {
            type: String,
            required: true
        },
        roll: {
            type: Number,
            required: true
        },
        programme: {
            type: String,
            required: true
        },
        courses: {
            type: Array
        }
    },
    { timestamps: true }
)

const Student = mongoose.model('Student', StudentSchema)

module.exports = Student
