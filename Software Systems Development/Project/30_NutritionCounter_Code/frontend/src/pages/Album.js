import * as React from "react";
import AppBar from "@mui/material/AppBar";
import Button from "@mui/material/Button";
import Card from "@mui/material/Card";
import CardContent from "@mui/material/CardContent";
import CardMedia from "@mui/material/CardMedia";
import CssBaseline from "@mui/material/CssBaseline";
import Grid from "@mui/material/Grid";
import Stack from "@mui/material/Stack";
import Box from "@mui/material/Box";
import Toolbar from "@mui/material/Toolbar";
import Typography from "@mui/material/Typography";
import Container from "@mui/material/Container";
import CircularProgress from "@mui/material/CircularProgress";
import Link from "@mui/material/Link";
import { createTheme, ThemeProvider } from "@mui/material/styles";
import Slider from "@mui/material/Slider";
import Tooltip from "@mui/material/Tooltip";
import PropTypes from "prop-types";
import { styled } from "@mui/system";
import proteinImage from "./protein.jpg";
import fatImage from "./fats.jpg";
import fibreImage from "./fiber.jpg";
import carbsImage from "./carbs.jpg";
import { useEffect, useState } from "react";
import SvgIcon from "@mui/material/SvgIcon";
import pregaNews from "./pregaNews.svg";
import cardiacNews from "./cardiac.svg";
import diabetic from "./Diabetic.svg";
import child from "./child.svg";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
  faCheckCircle,
  faTimesCircle,
  faBaby,
} from "@fortawesome/free-solid-svg-icons";
import { green, red } from "@mui/material/colors";

import Navbar_Album from "../components/Navbar_Album";

const PrettoSlider = styled(Slider)(({ theme }) => ({
  color: "#52af77",
  height: 8,
  "& .MuiSlider-track": {
    border: "none",
  },
  "& .MuiSlider-thumb": {
    height: 24,
    width: 24,
    backgroundColor: "#fff",
    border: "2px solid currentColor",
    "&:focus, &:hover, &.Mui-active, &.Mui-focusVisible": {
      boxShadow: "inherit",
    },
    "&:before": {
      display: "none",
    },
  },
  "& .MuiSlider-valueLabel": {
    lineHeight: 1.2,
    fontSize: 12,
    background: "unset",
    padding: 0,
    width: 32,
    height: 32,
    borderRadius: "50% 50% 50% 0",
    backgroundColor: "#52af77",
    transformOrigin: "bottom left",
    transform: "translate(50%, -100%) rotate(-45deg) scale(0)",
    "&:before": { display: "none" },
    "&.MuiSlider-valueLabelOpen": {
      transform: "translate(50%, -100%) rotate(-45deg) scale(1)",
    },
    "& > *": {
      transform: "rotate(45deg)",
    },
  },
  
  "& .MuiSlider-thumb, & .MuiSlider-track": {
    transition: theme.transitions.create(["left", "transform"], {
      duration: theme.transitions.duration.shortest, 
    }),
  },
}));

function ValueLabelComponent(props) {
  const { children, value } = props;

  return (
    <Tooltip enterTouchDelay={0} placement="top" title={value}>
      {children}
    </Tooltip>
  );
}

ValueLabelComponent.propTypes = {
  children: PropTypes.element.isRequired,
  value: PropTypes.number.isRequired,
};

function CustomizedSlider() {
  const [sliderValue, setSliderValue] = useState(0);

  useEffect(() => {
    const targetValue = 20; 
    const duration = 2000; 

    const startTime = Date.now();
    const updateSlider = () => {
      const currentTime = Date.now();
      const elapsed = currentTime - startTime;

      if (elapsed < duration) {
        const progress = elapsed / duration;
        const easedProgress = 0.5 - 0.5 * Math.cos(progress * Math.PI); 
        const newValue = Math.round(targetValue * easedProgress);
        setSliderValue(newValue);
        requestAnimationFrame(updateSlider);
      } else {
        setSliderValue(targetValue);
      }
    };

    updateSlider();
  }, []); 

  return (
    <Box sx={{ m: 1 }}>
      <Typography gutterBottom></Typography>
      <PrettoSlider
        valueLabelDisplay="auto"
        aria-label="pretto slider"
        value={sliderValue}
        ValueLabelComponent={ValueLabelComponent}
        marks={marks}
      />
    </Box>
  );
}

const marks = [
  {
    value: 0,
  },
  {
    value: 20,
  },
  {
    value: 37,
  },
  {
    value: 100,
  },
];


const defaultTheme = createTheme();

const cards = [{ N1: "Nutrient1" }, { N2: "Nutrient2" }, { N3: "Nutrient3" }];
const new_cards = [
  { type: "protein", image: proteinImage },
  { type: "fats", image: fatImage },
  { type: "fiber", image: fibreImage },
  { type: "carbs", image: carbsImage },
];
const StyledImg = styled("img")({
  width: "100%", 
  height: "auto", 
  display: "block",
});
function CustomIcon({ src, alt, ...props }) {
  return <StyledImg src={src} alt={alt} {...props} />;
}

function Album() {
  const [cards, setCards] = useState([]);

  const [loading, setLoading] = useState(true);

  const [loadingTopNutrients, setLoadingTopNutrients] = useState(true);

  const [conditionStatus, setConditionStatus] = useState({
    pregnant: {
      count: 0,
      ingredients: [],
      recommended: true,
    },
    diabetic: {
      count: 0,
      ingredients: [],
      recommended: true,
    },
    child: {
      count: 0,
      ingredients: [],
      recommended: true,
    },
    cardiac: {
      count: 0,
      ingredients: [],
      recommended: true,
    },
  });

  const [topNutrients, setTopNutrients] = useState({
    protein: 0,
    fats: 0,
    fiber: 0,
    carbs: 0,
  });
  const flag = 0;

  // ...

  useEffect(() => {
    const fetchConditionStatus = async () => {
      try {
       
        const responsePregnant = await fetch("/api/home/is-rec-pregnant");
        const dataPregnant = await responsePregnant.json();
        setConditionStatus((prevStatus) => ({
          ...prevStatus,
          pregnant: {
            count: dataPregnant.count,
            ingredients: dataPregnant.ingredients,
            recommended: dataPregnant.count === 0,
          },
        }));

        
        const responseDiabetic = await fetch("/api/home/is-rec-diabetic");
        const dataDiabetic = await responseDiabetic.json();
        setConditionStatus((prevStatus) => ({
          ...prevStatus,
          diabetic: {
            count: dataDiabetic.count,
            ingredients: dataDiabetic.ingredients,
            recommended: dataDiabetic.count === 0,
          },
        }));

        // Fetch Child status
        const responseChild = await fetch("/api/home/is-rec-child");
        const dataChild = await responseChild.json();
        setConditionStatus((prevStatus) => ({
          ...prevStatus,
          child: {
            count: dataChild.count,
            ingredients: dataChild.ingredients,
            recommended: dataChild.count === 0,
          },
        }));

        // Fetch Cardiac status
        const responseCardiac = await fetch("/api/home/is-rec-cardiac");
        const dataCardiac = await responseCardiac.json();
        setConditionStatus((prevStatus) => ({
          ...prevStatus,
          cardiac: {
            count: dataCardiac.count,
            ingredients: dataCardiac.ingredients,
            recommended: dataCardiac.count === 0,
          },
        }));
      } catch (error) {
        console.error("Error checking condition status:", error);
      }
      console.log(conditionStatus);
    };

    fetchConditionStatus();
  }, []);
  // ...

  useEffect(() => {
    const fetchTopNutrients = async () => {
      try {
        const response = await fetch("/api/home/get-top4-nutrients");
        const data = await response.json();
        setTopNutrients(data);
        setLoadingTopNutrients(false);
      } catch (error) {
        console.error("Error fetching top nutrients:", error);
        setLoadingTopNutrients(false);
      }
    };

    fetchTopNutrients();
  }, []);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const scriptResponse = await fetch("/api/home/run-python-script");
        const nutrientResponse = await fetch("/api/home/get-nutrients");
        const nutrientData = await nutrientResponse.json();
        // console.log("Nutrient data:", nutrientData);
        const mergedData = [...nutrientData];

        setCards(mergedData);
        setLoading(false);
      } catch (error) {
        console.error("Error fetching data:", error);
        setLoading(false);
      }
    };

    fetchData();
  }, []);

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
  return (
    <ThemeProvider theme={defaultTheme}>
      <Navbar_Album />
      <br />
      <br />
      <br />
      <CssBaseline />
      <AppBar id="Ing" position="relative">
        {/* <Toolbar></Toolbar> */}
        <Typography variant="h4" sx={{ color: "white" }}>
          INGREDIENTS
        </Typography>
      </AppBar>
      <main>
        <Container sx={{ py: 8 }} maxWidth="md">
          <Grid container spacing={4}>
            {Array.isArray(cards) && cards.length > 0 ? (
              
              cards.map((card, index) => (
                <Grid item key={index} xs={12} sm={6} md={4}>
                  <Card
                    sx={{
                      height: "100%",
                      display: "flex",
                      flexDirection: "column",
                    }}
                  >
                    <CardMedia
                      component="div"
                      sx={{
                        // 16:9
                        pt: "56.25%",
                      }}
                      image="https://source.unsplash.com/random?"
                    />
                    <CardContent sx={{ flexGrow: 1 }}>
                      <Typography variant="h5" component="h2">
                        <strong>
                          {!card ? "Un-identified" : card.name[0]}{" "}
                        </strong>
                       
                      </Typography>
                      <Typography>
                        {generateDescription(card)}{" "}
                        
                      </Typography>
                    </CardContent>
                  </Card>
                </Grid>
              ))
            ) : (
              <Grid item xs={12} sm={6} md={4}>
              
                <Card
                  sx={{
                    height: "100%",
                    display: "flex",
                    flexDirection: "column",
                  }}
                >
                  <CardMedia
                    component="div"
                    sx={{
                      // 16:9
                      pt: "56.25%",
                    }}
                    image="https://source.unsplash.com/random?no-ingredients"
                  />
                  <CardContent sx={{ flexGrow: 1 }}>
                    <Typography variant="h5" component="h2" align="center">
                      No Ingredients
                    </Typography>
                    <Typography align="center">
                      No nutrient data available
                    </Typography>
                  </CardContent>
                </Card>
              </Grid>
            )}
          </Grid>
        </Container>
        <AppBar id="Mac" position="relative" style={{ marginTop: "20px" }}>
          <Toolbar sx={{ display: "flex", justifyContent: "center" }}>
            <div
              style={{
                marginTop: "5px",
                marginBottom: "5px",
                borderRadius: "10px",
                background: "#1976D2",
                padding: "4px",
                textAlign: "center",
              }}
            >
              <Typography variant="h4" sx={{ color: "white" }}>
                MACRO-NUTRIENTS
              </Typography>
            </div>
          </Toolbar>
        </AppBar>
        <Container
          sx={{ py: 8, display: "flex", justifyContent: "space-between" }}
          maxWidth="md"
        >
          {new_cards.map((new_card, index) => (
            <Card
              key={index}
              sx={{
                height: "100%",
                width: "23%",
                display: "flex",
                flexDirection: "column",
              }}
            >
              <CardMedia
                component="div"
                sx={{
                  pt: "50%",
                }}
                image={new_card.image}
              />
              <CardContent sx={{ flexGrow: 1 }}>
                
                <PrettoSlider
                  valueLabelDisplay="auto"
                  aria-label="pretto slider"
                  value={topNutrients[new_card.type]}
                  ValueLabelComponent={ValueLabelComponent}
                />
              </CardContent>
            </Card>
          ))}
        </Container>

        {/* -------------------- Reccomendations---------------------------------------------------------- */}
        {/* -------------------- Reccomendations---------------------------------------------------------- */}
        {/* -------------------- Reccomendations---------------------------------------------------------- */}
        {/* -------------------- Reccomendations---------------------------------------------------------- */}
        {/* -------------------- Reccomendations---------------------------------------------------------- */}
        {/* -------------------- Reccomendations---------------------------------------------------------- */}

        {/* Section for Pregnancy */}
        <AppBar id="Recom" position="relative" style={{ marginTop: "20px" }}>
          <Toolbar sx={{ display: "flex", justifyContent: "center" }}>
            <div
              style={{
                marginTop: "5px",
                marginBottom: "5px",
                borderRadius: "10px",
                background: "#1976D2",
                padding: "4px",
                textAlign: "center",
              }}
            >
              <Typography variant="h4" sx={{ color: "white" }}>
                RECOMMENDATIONS
              </Typography>
            </div>
          </Toolbar>
        </AppBar>
        <Card
          sx={{
            bgcolor: "#ffffff",
            p: 4,
            transition: "background-color 1s",
            margin: "20px 0",
          }}
          component="section"
        >
          <Container maxWidth="md">
            <Grid container spacing={2}>
              
              <Grid item xs={12} sm={6}>
                <div
                  sx={{
                    display: "flex",
                    flexDirection: "column",
                    alignItems: "center",
                    justifyContent: "center",
                    textAlign: "center",
                  }}
                >
                  <Typography
                    variant="h5"
                    component="h2"
                    gutterBottom
                    sx={{
                      color: conditionStatus.pregnant.recommended
                        ? green[500]
                        : red[500],
                      fontSize: "28px",
                      padding: "20px",
                      transition: "color 10s, font-size 1s",
                      fontWeight: "bold",
                      marginBottom: "10px",
                    }}
                  >
                    {conditionStatus.pregnant.recommended ? (
                      <FontAwesomeIcon icon={faCheckCircle} />
                    ) : (
                      <FontAwesomeIcon icon={faTimesCircle} />
                    )}{" "}
                    {conditionStatus.pregnant.recommended
                      ? "Recommended"
                      : "Not Recommended"}{" "}
                    for Pregnancy!
                  </Typography>

                  
                  {conditionStatus.pregnant.count > 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "15px",
                          fontSize: "18px",
                        }}
                      >
                        Reasons:
                      </Typography>
                      <ul
                        sx={{
                          listStyle: "none",
                          padding: 0,
                          margin: 0,
                          textAlign: "center", 
                        }}
                      >
                        {conditionStatus.pregnant.ingredients.map(
                          (ingredient, index) => (
                            <li
                              key={index}
                              sx={{
                                marginBottom: "10px",
                                fontSize: "16px",
                                lineHeight: "1.6",
                              }}
                            >
                              <Typography variant="body1">
                                {ingredient}
                              </Typography>
                            </li>
                          )
                        )}
                      </ul>
                    </div>
                  )}
                  {conditionStatus.pregnant.count <= 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignItems: "center",
                        }}
                      >
                        "We've meticulously curated the ingredients for your
                        food – worry not, as there are no harmful components
                        detected!"
                      </Typography>
                    </div>
                  )}

                  <Container
                    sx={{
                      py: 4,
                      display: "flex",
                      justifyContent: "center",
                    }}
                    maxWidth="md"
                  >
                    {/* https://americanpregnancy.org/healthy-pregnancy/pregnancy-health-wellness/foods-to-avoid-during-pregnancy/ */}
                    <a
                      href="https://americanpregnancy.org/healthy-pregnancy/pregnancy-health-wellness/foods-to-avoid-during-pregnancy/"
                      target="_blank"
                      rel="noopener noreferrer"
                    >
                      <Button variant="contained" color="primary" size="large">
                        Explore More
                      </Button>
                    </a>
                  </Container>
                </div>
              </Grid>

              
              <Grid
                item
                xs={12}
                sm={6}
                sx={{
                  display: "flex",
                  justifyContent: "center",
                  alignItems: "center",
                }}
              >
                <CustomIcon
                  src={pregaNews}
                  alt="Pregnant Lady"
                  sx={{ maxWidth: "100%", height: "auto" }}
                />
              </Grid>
            </Grid>
          </Container>
        </Card>

        
        <Card
          sx={{
            bgcolor: "#ffffff",
            p: 4,
            transition: "background-color 1s",
            margin: "20px 0",
          }}
          component="section"
        >
          <Container maxWidth="md">
            <Grid container spacing={2}>
             
              <Grid
                item
                xs={12}
                sm={6}
                sx={{ display: "flex", justifyContent: "flex-start" }}
              >
                <CustomIcon src={diabetic} alt="Diabetic" />
              </Grid>

              
              <Grid item xs={12} sm={6}>
                <div
                  sx={{
                    display: "flex",
                    flexDirection: "column",
                    alignItems: "center",
                  }}
                >
                  <Typography
                    variant="h5"
                    component="h2"
                    gutterBottom
                    sx={{
                      color: conditionStatus.diabetic.recommended
                        ? "green"
                        : "red",
                      fontSize: "30px",
                      padding: "25px",
                      transition: "color 10s, font-size 1s",
                      fontWeight: "bold",
                      marginBottom: "10px",
                    }}
                  >
                    {conditionStatus.diabetic.recommended ? (
                      <FontAwesomeIcon icon={faCheckCircle} />
                    ) : (
                      <FontAwesomeIcon icon={faTimesCircle} />
                    )}{" "}
                    {conditionStatus.diabetic.recommended
                      ? "Recommended"
                      : "Not Recommended"}{" "}
                    for Diabetic Individuals!
                  </Typography>

                
                  {conditionStatus.diabetic.count > 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignContent: "center",
                        }}
                      >
                        Playing it safe with your health! Here's why we're not
                        recommending:
                      </Typography>
                      <ul sx={{ listStyle: "none", padding: 0, margin: 0 }}>
                        {conditionStatus.diabetic.ingredients.map(
                          (ingredient, index) => (
                            <li key={index} sx={{ marginBottom: "5px" }}>
                              <Typography variant="body1">
                                {ingredient}
                              </Typography>
                            </li>
                          )
                        )}
                      </ul>
                    </div>
                  )}

                  {conditionStatus.diabetic.count <= 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignContent: "center",
                        }}
                      >
                        "We've meticulously curated the ingredients for your
                        food – worry not, as there are no harmful components
                        detected!"
                      </Typography>
                    </div>
                  )}
                  <Container
                    sx={{
                      py: 4,
                      display: "flex",
                      justifyContent: "center",
                    }}
                    maxWidth="md"
                  >                    
                  <a
                      href="https://www.who.int/health-topics/diabetes?gclid=Cj0KCQiA67CrBhC1ARIsACKAa8SXl2WDIngYX_8PZYTkKH3pP9Ta040YxZBDmqUEcoZLtdiSx6SJ3NwaAjoDEALw_wcB#tab=tab_1"
                      target="_blank"
                      rel="noopener noreferrer"
                    >
                      <Button variant="contained" color="primary" size="large">
                        Explore More
                      </Button>
                    </a>
                  </Container>
                </div>
              </Grid>
            </Grid>
          </Container>
        </Card>

        {/* Section for Cardiac */}
        <Card
          sx={{
            bgcolor: "#ffffff",
            p: 4,
            transition: "background-color 1s",
            margin: "20px 0",
          }}
          component="section"
        >
          <Container maxWidth="md">
            <Grid container spacing={2}>
              
              <Grid item xs={12} sm={6}>
                <div
                  sx={{
                    display: "flex",
                    flexDirection: "column",
                    alignItems: "center",
                    justifyContent: "center",
                    textAlign: "center",
                  }}
                >
                  <Typography
                    variant="h5"
                    component="h2"
                    gutterBottom
                    sx={{
                      color: conditionStatus.cardiac.recommended
                        ? "green"
                        : "red",
                      fontSize: "28px",
                      padding: "20px",
                      transition: "color 10s, font-size 1s",
                      fontWeight: "bold",
                      marginBottom: "10px",
                    }}
                  >
                    {conditionStatus.cardiac.recommended ? (
                      <FontAwesomeIcon icon={faCheckCircle} />
                    ) : (
                      <FontAwesomeIcon icon={faTimesCircle} />
                    )}{" "}
                    {conditionStatus.cardiac.recommended
                      ? "Recommended"
                      : "Not Recommended"}{" "}
                    for Cardiac Patients!
                  </Typography>

                 
                  {conditionStatus.cardiac.count > 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "15px",
                          fontSize: "18px",
                          alignContent: "center",
                        }}
                      >
                        Playing it safe with your health! Here's why we're not
                        recommending:
                      </Typography>
                      <ul
                        sx={{
                          listStyle: "none",
                          padding: 0,
                          margin: 0,
                          textAlign: "center", 
                        }}
                      >
                        {conditionStatus.cardiac.ingredients.map(
                          (ingredient, index) => (
                            <li
                              key={index}
                              sx={{
                                marginBottom: "10px",
                                fontSize: "16px",
                                lineHeight: "1.6",
                              }}
                            >
                              <Typography variant="body1">
                                {ingredient}
                              </Typography>
                            </li>
                          )
                        )}
                      </ul>
                    </div>
                  )}
                  {conditionStatus.cardiac.count <= 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignContent: "center",
                        }}
                      >
                        "We've meticulously curated the ingredients for your
                        food – worry not, as there are no harmful components
                        detected!"
                      </Typography>
                    </div>
                  )}
                  <Container
                    sx={{
                      py: 4,
                      display: "flex",
                      justifyContent: "center",
                    }}
                    maxWidth="md"
                  >
                  
                    <a
                      href="https://www.nhlbi.nih.gov/health/heart-healthy-living/healthy-foods#:~:text=Foods%20to%20limit,%2C%20added%20sugars%2C%20and%20alcohol."
                      target="_blank"
                      rel="noopener noreferrer"
                    >
                      <Button variant="contained" color="primary" size="large">
                        Explore More
                      </Button>
                    </a>
                  </Container>
                </div>
              </Grid>

              {/* Image on the right */}
              <Grid
                item
                xs={12}
                sm={6}
                sx={{
                  display: "flex",
                  justifyContent: "center",
                  alignItems: "center",
                }}
              >
                <CustomIcon
                  src={cardiacNews}
                  alt="Cardiac"
                  sx={{ maxWidth: "100%", height: "auto" }}
                />
              </Grid>
            </Grid>
          </Container>
        </Card>

        {/* Section for Child */}
        <Card
          sx={{
            bgcolor: "#ffffff",
            p: 4,
            transition: "background-color 1s",
            margin: "20px 0",
          }}
          component="section"
        >
          <Container maxWidth="md">
            <Grid container spacing={2}>
              
              <Grid
                item
                xs={12}
                sm={6}
                sx={{ display: "flex", justifyContent: "flex-start" }}
              >
                <CustomIcon src={child} alt="Child" />
              </Grid>

              
              <Grid item xs={12} sm={6}>
                <div
                  sx={{
                    display: "flex",
                    flexDirection: "column",
                    alignItems: "center",
                  }}
                >
                  <Typography
                    variant="h5"
                    component="h2"
                    gutterBottom
                    sx={{
                      color: conditionStatus.child.recommended
                        ? "green"
                        : "red",
                      fontSize: "30px",
                      padding: "25px",
                      transition: "color 10s, font-size 1s",
                      fontWeight: "bold",
                      marginBottom: "10px",
                    }}
                  >
                    {conditionStatus.diabetic.recommended ? (
                      <FontAwesomeIcon icon={faCheckCircle} />
                    ) : (
                      <FontAwesomeIcon icon={faTimesCircle} />
                    )}{" "}
                    {conditionStatus.child.recommended
                      ? "Recommended"
                      : "Not Recommended"}{" "}
                    for Children!
                  </Typography>

                  
                  {conditionStatus.child.count > 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignContent: "center",
                        }}
                      >
                        Playing it safe with your health! Here's why we're not
                        recommending:
                      </Typography>
                      <ul sx={{ listStyle: "none", padding: 0, margin: 0 }}>
                        {conditionStatus.child.ingredients.map(
                          (ingredient, index) => (
                            <li key={index} sx={{ marginBottom: "5px" }}>
                              <Typography variant="body1">
                                {ingredient}
                              </Typography>
                            </li>
                          )
                        )}
                      </ul>
                    </div>
                  )}
                  {conditionStatus.child.count <= 0 && (
                    <div>
                      <Typography
                        variant="body1"
                        sx={{
                          fontWeight: "bold",
                          marginBottom: "5px",
                          alignContent: "center",
                        }}
                      >
                        "We've meticulously curated the ingredients for your
                        food – worry not, as there are no harmful components
                        detected!"
                      </Typography>
                    </div>
                  )}
                  <Container
                    sx={{
                      py: 4,
                      display: "flex",
                      justifyContent: "center",
                    }}
                    maxWidth="md"
                  >
                    <a
                      href="https://www.nhs.uk/conditions/baby/weaning-and-feeding/foods-to-avoid-giving-babies-and-young-children/"
                      target="_blank"
                      rel="noopener noreferrer"
                    >
                      <Button variant="contained" color="primary" size="large">
                        Explore More
                      </Button>
                    </a>
                  </Container>
                </div>
              </Grid>
            </Grid>
          </Container>
        </Card>
      </main>
    </ThemeProvider>
  );
}

function generateDescription(nutrient) {
  const sortedKeys = Object.keys(nutrient)
    .filter(
      (key) =>
        key !== "_id" &&
        key !== "name" &&
        key !== "serving_size" &&
        key !== "__v"
    )
    .sort((a, b) => parseFloat(nutrient[b]) - parseFloat(nutrient[a]))
    .slice(0, 5);

  return (
    <div>
      <Typography variant="subtitle1" color="text.secondary" gutterBottom>
        Nutrient Details - per 100g:
      </Typography>
      <ul style={{ listStyleType: "none", padding: 0 }}>
        {sortedKeys.map((key) => (
          <li key={key}>
            <Typography variant="body2" color="text.secondary">
              <strong>{key}:</strong> {nutrient[key]}
            </Typography>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default Album;
