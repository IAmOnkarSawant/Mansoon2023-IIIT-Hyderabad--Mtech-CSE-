const mongoose=require('mongoose');
const userSchema=new mongoose.Schema({
    roll:{
        type:String,
        required:true
    },
    password:{
        type:String,
        required:true
    },
    role:{
        type:String
        
    }
})

const User=mongoose.model('User',userSchema);
module.exports=User;