const mongoose = require('mongoose')

let Schema = mongoose.Schema
const UserSchema = new Schema(
    {
        email: {
            type: String,
            required: true,
        },
        password: {
            type: String,
            required: true,
        },
        date: {
            type: Date,
            default: Date.now,
        },
    },
    {
        timestamps: true
    }
)

const User = mongoose.model('User', UserSchema)

module.exports = User
