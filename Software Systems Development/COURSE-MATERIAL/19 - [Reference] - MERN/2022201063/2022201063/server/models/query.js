const mongoose=require('mongoose');
const Query=new mongoose.Schema({
    exam_name:{
        type:String,
        required:true
    },
    course_name:{
        type:String,
        required:true
    },
    ta_roll:{
        type:String,
        required:true
    },
    question_num:{
        type:Number,
        required:true
    },
    std_roll:{
        type:String,
        required:true
    },
    ta_comment:{
        type:String,
        // required:true
    },
    std_comment:{
        type:String,
        required:true
    },
    IsActive:{
        type:Boolean,
        // required:true
    }


})

const query=mongoose.model('Query',Query);
module.exports=query;