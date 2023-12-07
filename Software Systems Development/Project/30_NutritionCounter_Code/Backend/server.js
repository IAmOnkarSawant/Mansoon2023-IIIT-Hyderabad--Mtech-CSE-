require("dotenv").config();

const express = require("express");
const mongoose = require("mongoose");
const homeRoutes = require("./Routes/home");
const userRoutes = require("./Routes/userControl");

// express app
const app = express();

// middleware
app.use(express.json());

app.use((req, res, next) => {
  console.log(req.path, req.method);
  next();
});

// routes
app.use("/api/home", homeRoutes);
app.use("/api/user", userRoutes);

//mongoose connection
mongoose
  .connect("mongodb://127.0.0.1:27017/SSD_PROJECT", {
    useUnifiedTopology: true,
    useNewUrlParser: true,
  })
  .then(() => {
    // listen to port
    app.listen(process.env.PORT, () => {
      console.log("listening for requests on port", process.env.PORT);
    });
  })
  .catch((err) => {
    console.log(err);
  });
