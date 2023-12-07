const express = require('express')
const router = express.Router()
const UserDet = require('../Models/userModel')
const jwt = require('jsonwebtoken')


const createToken = (_id) => {
  return jwt.sign({_id}, process.env.SECRET, { expiresIn: '3d' })
}

router.post('/login', async (req, res) => {
    const {email, password} = req.body

    try {
      const user = await UserDet.login(email, password)
  
      // create a token
      const token = createToken(user._id)
      
      res.status(200).json({email, token})
    } catch (error) {
      res.status(400).json({error: error.message})
    }
  });

router.post('/signup', async (req, res) => {
        const {email, password, admin, name} = req.body
        try {
          const user = await UserDet.signup(email, password, admin, name)
          const token = createToken(user._id)
          res.status(200).json({email, token})
        } catch (error) {
          res.status(400).json({error: error.message})
        }
  });

module.exports = router

