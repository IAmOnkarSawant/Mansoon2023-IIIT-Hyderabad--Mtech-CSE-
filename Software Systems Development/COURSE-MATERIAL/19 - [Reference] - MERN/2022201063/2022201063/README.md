# MERN-expressJs

>## Overview
- This project has been designed to understand the basics of ExpressJs framework.
- This project has made use of MongoDB Cloud platform as a database server.
- It covers basic session based authentication.

>## Execution
- Make sure your present location is inside the **_MERN-server_** folder.
- Create config.env file consisting the MongoDB connection URI and port number.
- The Libraries that are used here, (Make sure you install it using `npm` command) 
    - express 
    - mongoose 
    - dotenv 
    - cors 
    - body-parser 
    - bcrypt 
    - express-session 
    - connect-mongodb-session

- Next, Run the below command:
    ```
        nodemon app.js
    ```

#Client

- client contains components developed in ReactJS
- This frontend client contains 3 main components:
    - LoginForm
    - SignUpForm
    - Student (view the queries raised by logged in student)
    - Query (To add new Query)

- The structure of the code is based on the template provided by *create-react-app*.
- In this project, we have used functional components as well as class components too

### Steps to run the Client App.

- Open a new terminal and navigate to the location client.
- Run the following command to install the dependencies :
    ```
    npm install
    ```
    This will create the node_modules folder and install all the packages in it.
-  Run the following command to start the application:
    ```
    npm start
    ```
    
  ** Use personal internet connecting to mongodb ATLAS **

  ### things completed
1. login
2. signup
3. feedback
4. ta concern page(for now ta_name is kept to ashish whose concerns are displayed on post static comment will get updated as of now but api is written );
