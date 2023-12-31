const mongoose = require('mongoose');

const foodSchema = new mongoose.Schema({
  
  itemNo: Number,
  name: [String], 
  serving_size: String,
  calories: Number,
  total_fat: String,
  saturated_fat: String,
  cholesterol: String,
  sodium: String,
  choline: String,
  folate: String,
  folic_acid: String,
  niacin: String,
  pantothenic_acid: String,
  riboflavin: String,
  thiamin: String,
  vitamin_a: String,
  vitamin_a_rae: String,
  carotene_alpha: String,
  carotene_beta: String,
  cryptoxanthin_beta: String,
  lutein_zeaxanthin: String,
  lucopene: String,
  vitamin_b12: String,
  vitamin_b6: String,
  vitamin_c: String,
  vitamin_d: String,
  vitamin_e: String,
  tocopherol_alpha: String,
  vitamin_k: String,
  calcium: String,
  copper: String,
  iron: String,
  magnesium: String,
  manganese: String,
  phosphorus: String,
  potassium: String,
  selenium: String,
  zinc: String,
  protein: String,
  alanine: String,
  arginine: String,
  aspartic_acid: String,
  cystine: String,
  glutamic_acid: String,
  glycine: String,
  histidine: String,
  hydroxyproline: String,
  isoleucine: String,
  leucine: String,
  lysine: String,
  methionine: String,
  phenylalanine: String,
  proline: String,
  serine: String,
  threonine: String,
  tryptophan: String,
  tyrosine: String,
  valine: String,
  carbohydrate: String,
  fiber: String,
  sugars: String,
  fructose: String,
  galactose: String,
  glucose: String,
  lactose: String,
  maltose: String,
  sucrose: String,
  fat: String,
  saturated_fatty_acids: String,
  monounsaturated_fatty_acids: String,
  polyunsaturated_fatty_acids: String,
  fatty_acids_total_trans: String,
  alcohol: String,
  ash: String,
  caffeine: String,
  theobromine: String,
  water: String,
});

const Food = mongoose.model('Food', foodSchema);

module.exports = Food;
