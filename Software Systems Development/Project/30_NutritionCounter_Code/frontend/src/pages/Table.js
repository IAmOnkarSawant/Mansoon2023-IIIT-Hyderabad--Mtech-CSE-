import React, { useState, useEffect, useRef } from "react";
import AppBar from "@mui/material/AppBar";
import CssBaseline from "@mui/material/CssBaseline";
import Toolbar from "@mui/material/Toolbar";
import Container from "@mui/material/Container";
import { createTheme, ThemeProvider } from "@mui/material/styles";
import Typography from "@mui/material/Typography";
import Box from "@mui/material/Box";
import CircularProgress from "@mui/material/CircularProgress";
import MenuItem from "@mui/material/MenuItem";
import Select from "@mui/material/Select";
import ExpandMoreIcon from "@mui/icons-material/ExpandMore";

import Card from "@mui/material/Card";
import CardContent from "@mui/material/CardContent";
import Grid from "@mui/material/Grid";
import { styled } from "@mui/system";

import Slider from "@mui/material/Slider";

import Dialog from "@mui/material/Dialog";
import DialogTitle from "@mui/material/DialogTitle";
import DialogContent from "@mui/material/DialogContent";
import DialogActions from "@mui/material/DialogActions";
import Button from "@mui/material/Button";
import TextField from "@mui/material/TextField";

import { CircularProgressbar, buildStyles } from "react-circular-progressbar";
import "react-circular-progressbar/dist/styles.css";
import { green } from "@mui/material/colors";

import Navbar from "../components/Navbar";

const defaultTheme = createTheme();

const data = {
  Calorie: 10.5,
  Fats: 10,
  Protein: 19.5,
  Sodium: 15,
  Carbohydrate: 45,
};

const Calorie_lessThan_1200 = {
  Breakfast: "All-bran cereal (125),Milk (50),Banana (90)",
  "Early Snack": "Cucumber (30),Avocado dip (50)",
  Lunch: "Grilled cheese with tomato (300),Salad (50)",
  "Evening Snack": "Walnuts",
  Dinner: "Grilled Chicken (200),Brussel sprouts (100),Quinoa (105)",
  Total: 1200,
};

const Calorie_lessThan_1500 = {
  Breakfast: "Granola (120),Greek yogurt (120),Blueberries (40)",
  "Early Snack": "Orange (70)",
  Lunch: "Chicken and vegetable soup (300),Bread (100)",
  "Evening Snack": "Apple (75),Peanut butter (75)",
  Dinner: "Steak (375),Mashed potatoes (150),Asparagus (75)",
  Total: 1500,
};

const Calorie_lessThan_2000 = {
  Breakfast: "Buttered toast (150),Egg (80),Banana (90),Almonds (170)",
  "Early Snack": "Greek yogurt (120),Blueberries (40)",
  Lunch: "Grilled chicken (225),Grilled vegetables (125),Pasta (185)",
  "Evening Snack": "Hummus (50),Baby carrots (35),Crackers (65)",
  Dinner:
    "Grilled salmon (225),Brown rice (175),Green beans (100),Walnuts (165)",
  Total: 2000,
};

const PrettoSlider = styled(Slider)(({ theme }) => ({
  color: "#52af77",
  height: 8,
}));

export default function Table() {
  const recommendationRef = useRef(null);
  const [tableInfo, setTableInfo] = useState(true);
  const [loading, setLoading] = useState(true);
  const [initialLoad, setInitialLoad] = useState(true);
  const [userInfo, setUserInfo] = useState({
    age: "",
    weight: "",
    height: "",
    gender: "",
    goal: "",
  });
  const [openDialog, setOpenDialog] = useState(true);
  const [bmi, setBMI] = useState(null);
  const [showInfoCards, setShowInfoCards] = useState(false);
  const [prevCards, setPrevCards] = useState([]);
  const [bmr, setBMR] = useState(null);
  const [showRecommendation, setShowRecommendation] = useState(false);
  const [calorieRecommendation, setCalorieRecommendation] = useState(null);
  const [bmiCategory, setBmiCategory] = useState("");
  const [activeSection, setActiveSection] = useState("");

  useEffect(() => {
    const handleScroll = () => {
      const scrollPosition = window.scrollY;

      const analyzeSection = 0;
      const ocrDetectionSection =
        document.getElementById("OCRSection")?.offsetTop;
      const suggestionSection =
        document.getElementById("SuggestionSection")?.offsetTop;
      const dietPlanSection =
        document.getElementById("DietPlanSection")?.offsetTop;

      if (
        scrollPosition >= analyzeSection &&
        scrollPosition < ocrDetectionSection
      ) {
        setActiveSection("analyze");
      } else if (
        scrollPosition >= ocrDetectionSection &&
        scrollPosition < suggestionSection
      ) {
        setActiveSection("ocrDetection");
      } else if (
        scrollPosition >= suggestionSection &&
        scrollPosition < dietPlanSection
      ) {
        setActiveSection("suggestion");
      } else if (scrollPosition >= dietPlanSection) {
        setActiveSection("dietPlan");
      }
    };

    window.addEventListener("scroll", handleScroll);

    return () => {
      window.removeEventListener("scroll", handleScroll);
    };
  }, []);

  useEffect(() => {
    setOpenDialog(true);
    const delay = setTimeout(() => {
      setInitialLoad(false);
    }, 8000);
    return () => clearTimeout(delay);
  }, []);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const scriptResponse = await fetch("/api/home/run-python-script-table");
        const tableData = await scriptResponse.json();
        setTableInfo(tableData);
        setLoading(false);
      } catch (error) {
        console.error("Error fetching data:", error);
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  useEffect(() => {
    if (showRecommendation) {
      const recommendationElement = document.getElementById("Recid");
      if (recommendationElement) {
        recommendationElement.scrollIntoView({ behavior: "smooth" });
      }
    }
  }, [showRecommendation]);

  if (loading) {
    return (
      <Box
        sx={{
          display: "flex",
          justifyContent: "center",
          alignItems: "center",
          height: "100vh",
        }}
      >
        <CircularProgress />
      </Box>
    );
  }

  let calculatedBmiCategory;
  const handleDialogSubmit = () => {
    if (
      userInfo.age !== "" &&
      userInfo.weight !== "" &&
      userInfo.height !== "" &&
      userInfo.gender !== "" &&
      userInfo.goal !== ""
    ) {
      const calculatedBMI = calculateBMI(userInfo.weight, userInfo.height);
      setBMI(calculatedBMI);
    

      if (calculatedBMI < 18.5) {
        calculatedBmiCategory = "Underweight";
      } else if (calculatedBMI >= 18.5 && calculatedBMI <= 24.9) {
        calculatedBmiCategory = "Healthy Weight";
      } else if (calculatedBMI >= 25 && calculatedBMI <= 29.9) {
        calculatedBmiCategory = "Overweight";
      } else if (calculatedBMI >= 30 && calculatedBMI <= 34.9) {
        calculatedBmiCategory = "Obese";
      } else if (calculatedBMI >= 35 && calculatedBMI <= 39.9) {
        calculatedBmiCategory = "Severely Obese";
      } else {
        calculatedBmiCategory = "Morbidly Obese";
      }

      setBmiCategory(calculatedBmiCategory);

   
      const calculatedBMR =
        userInfo.gender === "male"
          ? calculateBMRForMen(userInfo.weight, userInfo.height, userInfo.age)
          : calculateBMRForWomen(
              userInfo.weight,
              userInfo.height,
              userInfo.age
            );

      setBMR(calculatedBMR);

      sendBMItoBackend(userInfo, calculatedBMI);
      //
      // setUserInfo({
      //   age: '',
      //   weight: '',
      //   height: '',
      //   gender: '',
      //   goal: '',
      // });
      setOpenDialog(false);

      let calorieRecommendation;
      if (calculatedBMR < 1200) {
        calorieRecommendation =
          userInfo.goal === "Weight Gain"
            ? Calorie_lessThan_1200
            : Calorie_lessThan_1500;
      } else if (calculatedBMR < 1500 && calculatedBMR >= 1200) {
        calorieRecommendation =
          userInfo.goal === "Weight Gain"
            ? Calorie_lessThan_1500
            : Calorie_lessThan_1200;
      } else if (calculatedBMR <= 2000 && calculatedBMR >= 1500) {
        calorieRecommendation =
          userInfo.goal === "Weight Gain"
            ? Calorie_lessThan_2000
            : Calorie_lessThan_1500;
      } else {
        calorieRecommendation = Calorie_lessThan_2000;
      }

      setPrevCards(["Calorie"]);
      const nutrients = ["Calorie", "Protein", "Fats"];
      setPrevCards(nutrients);
      setShowInfoCards(true);
      // Display new cards one after the other with a delay
      //const recommendationDelay = 4000; // 4 seconds
      // setTimeout(() => {
      //   setShowRecommendation(true);
      //   scrollToRecommendation();
      // }, recommendationDelay);
      setCalorieRecommendation(calorieRecommendation);
      const delay = 2000; // 2 seconds

      nutrients.forEach((nutrient, index) => {
        setTimeout(() => {
          setShowInfoCards(true);
        }, delay * index);
      });
    }
  };

  const calculateBMI = (weight, height) => {
    const weightInKg = parseFloat(weight);
    const heightInM = parseFloat(height) / 100;
    return weightInKg / (heightInM * heightInM);
  };

  const calculateBMRForMen = (weight, height, age) => {
    return 13.397 * weight + 4.799 * height - 5.677 * age + 88.362;
  };

  const calculateBMRForWomen = (weight, height, age) => {
    return 9.247 * weight + 3.098 * height - 4.33 * age + 447.593;
  };

  const sendBMItoBackend = async (userInfo, bmi) => {
    console.log("Sending BMI to the backend:", bmi);
    console.log("User Info:", userInfo);
    console.log("BMR:", bmr);
  };

  const handleChange = (key, value) => {
    console.log(`Setting ${key} to ${value}`);
  };

  // const handleRecommendationClick = () => {
  //   setShowRecommendation(true);
  //   scrollToRecommendation(); // Call the function to scroll to the recommendation section
  // };
  const handleRecommendationClick = () => {
    window.scrollTo({ top: 0, behavior: "smooth" });
    setShowRecommendation(true);
  };

  return (
    <ThemeProvider theme={defaultTheme}>
      <Navbar />
      <br />
      <br />
      <br />
      <CssBaseline />
      <AppBar position="relative" id="AnalyzeSection">
        <Toolbar sx={{ display: "flex", justifyContent: "center" }}>
          <Typography variant="h4" color="inherit">
            LETS ANALYSE!
          </Typography>
        </Toolbar>
      </AppBar>
      <main>
        <Container
          id="mainContent"
          sx={{ py: 8, background: "none" }}
          maxWidth="md"
        >
          {bmi !== null && (
            <Box
              sx={{
                display: "flex",
                flexDirection: "column",
                alignItems: "center",
                mb: 4,
              }}
            >
              {bmi !== undefined && (
                <div style={{ display: "flex", justifyContent: "center" }}>
                  <div
                    style={{ width: "400px", height: "400px", margin: "auto" }}
                  >
                    <CircularProgressbar
                      value={bmi}
                      text={`Your BMI is ${bmi.toFixed(2)}`}
                      styles={buildStyles({
                        rotation: 0.25,
                        strokeLinecap: "butt",
                        textSize: "8px",
                        pathTransitionDuration: 0.5,
                        pathColor: `rgba(30, 140, 100, ${bmi / 100})`,
                        textColor: "#f88",
                        trailColor: "orange",
                        backgroundColor: "orange",
                        strokeWidth: 2,
                        pathRadius: 1,
                      })}
                    />
                  </div>

                  <div
                    style={{
                      width: "500px",
                      height: "400px",
                      margin: "auto",
                      position: "relative",
                      display: "flex",
                      justifyContent: "center",
                    }}
                  >
                    <Card
                      sx={{
                        background: "#f5f5f5",
                        borderRadius: "10px",
                        boxShadow: "0px 0px 10px 0px rgba(0,0,0,0.1)",
                      }}
                    >
                      <CardContent>
                        <Typography variant="h5" sx={{ marginBottom: "1rem" }}>
                          User Information
                        </Typography>
                        <Typography
                          variant="body1"
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          Age: {userInfo.age}
                        </Typography>
                        <Typography
                          variant="body1"
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          Weight: {userInfo.weight} kg
                        </Typography>
                        <Typography
                          variant="body1"
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          Height: {userInfo.height} cm
                        </Typography>
                        <Typography
                          variant="body1"
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          BMI: {bmi.toFixed(2)}
                        </Typography>
                        <Typography
                          variant="body1"
                          color={
                            bmiCategory !== "Healthy Weight" ? "red" : "green"
                          }
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          Category: {bmiCategory}
                        </Typography>
                        <Typography
                          variant="body1"
                          sx={{ marginBottom: "0.5rem" }}
                        >
                          Basal Metabolic Rate: {bmr.toFixed(2)} calories/day
                        </Typography>
                      </CardContent>
                    </Card>
                  </div>
                </div>
              )}
            </Box>
          )}

          <AppBar
            position="relative"
            id="OCRSection"
            style={{ marginTop: "20px" }}
          >
            <Toolbar sx={{ display: "flex", justifyContent: "center" }}>
              <Typography variant="h4" color="inherit" sx={{ marginBottom: 2 }}>
                OCR DETECTION MODULE
              </Typography>
            </Toolbar>
          </AppBar>

          {!openDialog && (
            <div
              style={{
                background: "white",
                padding: "16px",
                borderRadius: "5px",
                boxShadow: "0px 0px 10px 0px rgba(0,0,0,0.1)",
              }}
            >
              <Grid container spacing={0}>
                {tableInfo.noutput ? (
                  tableInfo.noutput.map((nutrient) => (
                    <React.Fragment key={nutrient.Nutrients}>
                      <Grid item xs={12} sm={4}>
                        <Typography variant="h6" component="div">
                          {nutrient.Nutrients +
                            (nutrient.weight
                              ? " (" + nutrient.weight + ") "
                              : "")}
                        </Typography>
                      </Grid>
                      <Grid
                        item
                        xs={12}
                        sm={8}
                        style={{
                          display: "flex",
                          alignItems: "center",
                          paddingRight: "10px",
                        }}
                      >
                        <PrettoSliderCard
                          value={
                            nutrient.percentage && nutrient.percentage != "0"
                              ? nutrient.percentage
                              : null
                          }
                          onChange={(newValue) =>
                            handleChange(nutrient.Nutrients, newValue)
                          }
                          initialLoad={initialLoad}
                        />
                      </Grid>
                    </React.Fragment>
                  ))
                ) : (
                  <div style={{ textAlign: "center", maxWidth: "100%" }}>
                    <h3>Table Not found</h3>
                  </div>
                )}
              </Grid>
            </div>
          )}

          <AppBar
            position="relative"
            id="SuggestionSection"
            style={{ marginTop: "20px" }}
          >
            <Toolbar sx={{ display: "flex", justifyContent: "center" }}>
              <div
                style={{
                  marginTop: "20px",
                  marginBottom: "20px",
                  borderRadius: "10px",
                  background: "#1976D2",
                  textAlign: "center",
                }}
              >
                <Typography variant="h4" sx={{ color: "white" }}>
                  OUR SUGGESTIONS
                </Typography>
              </div>
            </Toolbar>
          </AppBar>

          {showInfoCards && (
            <Grid container spacing={2} sx={{ marginTop: "20px" }}>
              {prevCards.map((nutrient, index) => (
                <Grid key={index} item xs={12}>
                  <InfoCard
                    nutrient={nutrient}
                    value={
                      tableInfo.noutput ? tableInfo.noutput.percentage : null
                    }
                  />
                </Grid>
              ))}
            </Grid>
          )}

          {showRecommendation && (
            <div
              id="DietPlanSection"
              ref={recommendationRef}
              style={{ marginTop: "20px" }}
            >
              <div
                style={{
                  background: "#1976D2",
                  padding: "8px",
                  textAlign: "center",
                  marginBottom: "20px",
                }}
              >
                <Typography
                  variant="h4"
                  sx={{ marginTop: 1, padding: 2, color: "white" }}
                >
                  PERSONAL DIET PLAN
                </Typography>
              </div>
              <table
                style={{
                  width: "100%",
                  borderCollapse: "collapse",
                  marginTop: 4,
                }}
              >
                <thead>
                  <tr>
                    <th style={{ border: "1px solid #dddddd", padding: "8px" }}>
                      Meal
                    </th>
                    <th style={{ border: "1px solid #dddddd", padding: "8px" }}>
                      Calorie Plan
                    </th>
                  </tr>
                </thead>
                <tbody>
                  {Object.entries(calorieRecommendation).map(
                    ([meal, caloriePlan]) => (
                      <tr key={meal}>
                        <td
                          style={{
                            border: "1px solid #dddddd",
                            padding: "8px",
                          }}
                        >
                          {meal}
                        </td>
                        <td
                          style={{
                            border: "1px solid #dddddd",
                            padding: "8px",
                          }}
                        >
                          {caloriePlan}
                        </td>
                      </tr>
                    )
                  )}
                </tbody>
              </table>
            </div>
          )}
        </Container>
      </main>

      <Dialog open={openDialog} fullWidth maxWidth="xs">
        <DialogTitle>Enter User Information</DialogTitle>
        <DialogContent>
          <TextField
            label="Age"
            type="number"
            value={userInfo.age}
            onChange={(e) => setUserInfo({ ...userInfo, age: e.target.value })}
            fullWidth
            margin="normal"
          />
          <TextField
            label="Weight (kg)"
            type="number"
            value={userInfo.weight}
            onChange={(e) =>
              setUserInfo({ ...userInfo, weight: e.target.value })
            }
            fullWidth
            margin="normal"
          />
          <TextField
            label="Height (cm)"
            type="number"
            value={userInfo.height}
            onChange={(e) =>
              setUserInfo({ ...userInfo, height: e.target.value })
            }
            fullWidth
            margin="normal"
          />
          <TextField
            label="Goal"
            fullWidth
            margin="normal"
            select
            value={userInfo.goal}
            onChange={(e) => setUserInfo({ ...userInfo, goal: e.target.value })}
          >
            <MenuItem value="">Select Your Goal</MenuItem>
            <MenuItem value="Weight Gain">Weight Gain</MenuItem>
            <MenuItem value="Weight Loss">Weight Loss</MenuItem>
          </TextField>

          <TextField
            label="Gender"
            fullWidth
            margin="normal"
            select
            value={userInfo.gender}
            onChange={(e) =>
              setUserInfo({ ...userInfo, gender: e.target.value })
            }
          >
            <MenuItem value="">Select Gender</MenuItem>
            <MenuItem value="male">Male</MenuItem>
            <MenuItem value="female">Female</MenuItem>
          </TextField>
        </DialogContent>
        <DialogActions>
          <Button
            onClick={handleDialogSubmit}
            color="primary"
            disabled={
              !(
                userInfo.age !== "" &&
                userInfo.weight !== "" &&
                userInfo.height !== "" &&
                userInfo.gender !== "" &&
                userInfo.goal !== ""
              )
            }
          >
            Submit
          </Button>
        </DialogActions>
      </Dialog>
      <Box sx={{ position: "fixed", bottom: "20px", right: "20px" }}>
        <Button
          variant="contained"
          style={{ backgroundColor: "green", color: "white" }}
          onClick={handleRecommendationClick}
          disabled={!bmi || showRecommendation}
          endIcon={<ExpandMoreIcon />}
        >
          PERSONALISED DIET !!!
        </Button>
      </Box>
    </ThemeProvider>
  );
}

function PrettoSliderCard({ value, onChange, initialLoad }) {
  const [sliderValue, setSliderValue] = useState(value);

  useEffect(() => {
    if (!initialLoad) {
    
      const delay = setTimeout(() => {
        setSliderValue(value);
      }, 1000);

      return () => {
        clearTimeout(delay);
      };
    }
  }, [initialLoad, value]);

  const handleChange = (event, newValue) => {
    setSliderValue(newValue);
    onChange(newValue);
  };

  return (
    <div style={{ width: "150%" }}>
      <PrettoSlider
        value={sliderValue}
        onChange={handleChange}
        aria-labelledby="discrete-slider"
        valueLabelDisplay="auto"
        step={1}
        marks={[
          { value: 0, label: "0" },
          { value: 50, label: "50" },
          { value: 100, label: "100" },
        ]}
        min={0}
        max={100}
        sx={{
          transition: "all 2s ease-in-out",
        }}
      />
    </div>
  );
}

function InfoCard({ nutrient, value }) {
  let additionalContent = "";

  if (nutrient === "Calorie") {
    if (value < 5) {
      additionalContent =
        "The content of Calorie is less than usually recommended.";
    } else if (value > 20) {
      additionalContent =
        "The content of Calorie is higher than usually recommended.";
    } else {
      additionalContent =
        "The content of Calorie is within the range usually recommended. But you must consider other factors too";
    }
  } else if (nutrient === "Protein") {
    if (value < 5) {
      additionalContent =
        "The content of Protein is less than usually recommended.";
    } else if (value > 20) {
      additionalContent =
        "The content of Protein is higher than usually recommended.";
    } else {
      additionalContent =
        "The content of Protein is within the range usually recommended. But you must consider other factors too";
    }
  } else if (nutrient === "Fats") {
    if (value < 5) {
      additionalContent =
        "The content of Fats is less than usually recommended.";
    } else if (value > 20) {
      additionalContent =
        "The content of Fats is higher than usually recommended.";
    } else {
      additionalContent =
        "The content of Fats is within the range usually recommended. However, foods with a higher fat content are usually less recommended, even if it is within the range";
    }
  }

  return (
    <Card>
      <CardContent>
        <Typography variant="h6" style={{ fontWeight: "bold" }}>
          {nutrient}
        </Typography>
        <Typography variant="body1" style={{ fontWeight: "bold" }}>{`Value: ${
          value ? value + "%" : { nutrient } + " percentage not found!"
        }`}</Typography>
        {additionalContent && (
          <Typography
            variant="body2"
            color={value < 5 || value > 20 ? "error" : "textSecondary"}
          >
            <ul>
              <li>{additionalContent}</li>
            </ul>
          </Typography>
        )}
      </CardContent>
    </Card>
  );
}
