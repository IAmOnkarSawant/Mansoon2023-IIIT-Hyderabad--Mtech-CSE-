const Users = require('../models/user')
const Query = require('../models/query')
const bcrypt = require('bcrypt')
const express = require('express')
const router = express.Router()


router.post('/register', async (req, res) => {
    const { roll, password, role } = req.body;
    console.log(req.body);

    if (!roll || !password || !role)
        return res.status(400).json({ msg: 'Missing details' })

    const user = await Users.findOne({ roll, role: role }) // finding user in db
    if (user) return res.status(400).json({ msg: 'User already exists' })

    const newUser = new Users({ roll, password, role })
    // hasing the password
    bcrypt.hash(password, 7, async (err, hash) => {
        if (err)
            return res.status(400).json({ msg: 'error while saving the password' })

        newUser.password = hash
        const savedUserRes = await newUser.save()

        if (savedUserRes)
            return res.status(200).json({ msg: 'user is successfully saved' })
    })
})
// respond with "hello world" when a GET request is made to the homepage
router.get('/hello', (req, res) => {
    res.send('hello world')
  })

router.get('/getQuery/:id', async (req, res) => {
    var id=req.params.id;
    console.log(typeof(id));
    try{
    const query=await Query.find({std_roll:id}).sort({"ta_comment":-1});
    if(query){
    console.log(query);
    res.status(200).json({data:query,msg:"success"})
    }
    else
    res.status(200).json({data:"",msg:"no queries"})
    
    }
    catch(err){
        console.log(err);
    }
})
router.get('/getConcern/:id', async (req, res) => {
    var id=req.params.id;
    console.log(typeof(id));
    try{
    const concern=await Query.find({ta_roll:'ashish'}).sort({"ta_comment":-1});
    if(concern){
    console.log(concern);
    res.status(200).json({data:concern,msg:"success"})
    }
    else
    res.status(200).json({data:"",msg:"no queries"})
    
    }
    catch(err){
        console.log(err);
    }
})

router.post('/query', async (req, res) => {
    console.log(req.body);
    const { exam_name,
        course_name,
        ta_roll,
        question_num,
        std_roll,
        std_comment,
        ta_comment

    } = req.body;
    try {
        const q = new Query({ exam_name, course_name, ta_roll, question_num, std_roll, std_comment,ta_comment })
        console.log(q);
        //console.log();
       const saved=await q.save();
       if(saved)
        res.status(200).json({ msg: "query created successfully" })
    }
    catch (err) {
        console.log(err);
    }
})

router.post('/postResponse', async (req, res) => {
    console.log(req.body);
    const { _id,
        ta_comment,
        ta_name,
        std_roll

    } = req.body;
    try {
        const concern={_id:_id,std_roll:std_roll,ta_roll:ta_name};
        console.log("concern",concern);
        var newvalues = { $set: {ta_comment:'hello answer updated'} };
        const q =await Query.updateOne(concern,newvalues);
        console.log(q);
       if(q)
        res.status(200).json({ msg: "query responded successfully" })
    }
    catch (err) {
        console.log(err);
    }
})
router.post('/login', async (req, res) => {
    console.log(req.body);
    const { roll, password, role } = req.body

    if (!roll || !password || !role) {
        res.status(400).json({ msg: 'Something missing' })
    }

    const user = await Users.findOne({ roll: roll,role:role }) // finding user in db
    if (!user) {
        return res.status(400).json({ msg: 'User not found' })
    }
console.log(user);
    // comparing the password with the saved hash-password
    const matchPassword = await bcrypt.compare(password, user.password)
    console.log(matchPassword);
    if (matchPassword) {
        const userSession = { roll: user.roll } // creating user session to keep user loggedin also on refresh
        req.session.user = userSession // attach user session to session object from express-session
        req.session.save();
         res
            .status(200)
            .json({ msg: 'You have logged in successfully', userSession }) // attach user session id to the response. It will be transfer in the cookies
    } else {
         res.status(400).json({ msg: 'Invalid credential' })
    }
})

router.get('/logout', async (req, res) => {
    console.log("present");
    if (req.session.user) {
        
        req.session.destroy(err => {
            if (err)
                return res.status(500).send("Unable to Logout!");
            else
                return res.status(200).json({ "msg": "Logout Successfull..." });
        })
    }
})


router.get('/isAuth', async (req, res) => {
    if (req.session.user) {
        return res.json(req.session.user)
    } else {
        return res.status(401).json('unauthorize')
    }
})


module.exports = router
