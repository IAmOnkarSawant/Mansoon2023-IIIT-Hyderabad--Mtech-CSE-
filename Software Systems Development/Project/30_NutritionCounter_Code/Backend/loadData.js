const fs = require('fs');
const csv = require('csv-parser');
const mongoose = require('mongoose');
const Food = require('./Models/foodModel'); // Import your Mongoose model

mongoose.connect('mongodb://127.0.0.1:27017/SSD_PROJECT', { useNewUrlParser: true, useUnifiedTopology: true });

const results = [];

fs.createReadStream('nutrition.csv')
  .pipe(csv())
  .on('data', (data) => {
    const names = data.name.split(',').map((name) => name.trim());
    data.name = names;

    results.push(data);
  })
  .on('end', async () => {
    try {
      // Insert the parsed data into the MongoDB collection using async/await
      await Food.insertMany(results, { maxTimeMS: 60000 });
      console.log('Data inserted successfully.');
    } catch (err) {
      console.error(err);
    } finally {
      mongoose.connection.close(); // Close the database connection
    }
  });
