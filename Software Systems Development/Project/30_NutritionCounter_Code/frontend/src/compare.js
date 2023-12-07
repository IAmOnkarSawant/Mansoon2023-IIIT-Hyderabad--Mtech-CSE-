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

const recommendedArray = [
  "Include a variety of fruits and vegetables in your diet.",
  "Drink plenty of water throughout the day.",
  "Get regular exercise to maintain a healthy lifestyle.",
];

const notRecommendedArray = [
  "Limit the intake of sugary snacks and beverages.",
  "Avoid excessive consumption of processed foods.",
  "Reduce the intake of saturated fats and cholesterol.",
];

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
        valueLabelComponent={ValueLabelComponent}
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
  { Protein: "Proteins", image: proteinImage },
  { Fats: "Fats", image: fatImage },
  { Fibre: "Fibres", image: fibreImage },
  { Carbohydrates: "Carbohydrates", image: carbsImage },
];
const StyledImg = styled("img")({
  width: "100%",
  height: "auto",
  display: "block",
});
function CustomIcon({ src, alt, ...props }) {
  return <StyledImg src={src} alt={alt} {...props} />;
}

export default function Album() {
  const flag = 0;

  return (
    <ThemeProvider theme={defaultTheme}>
      <CssBaseline />
      <AppBar position="relative">
        <Toolbar></Toolbar>
      </AppBar>
      <main>
        <Container sx={{ py: 8 }} maxWidth="md">
          <Grid container spacing={4}>
            {cards.map((card, index) => (
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
                      pt: "56.25%",
                    }}
                    //image="https://source.unsplash.com/random?wallpapers"
                  />
                  <CardContent sx={{ flexGrow: 1 }}>
                    <Typography gutterBottom variant="h5" component="h2">
                      {Object.keys(card)[0]}
                    </Typography>
                    <Typography>{Object.values(card)[0]}</Typography>
                  </CardContent>
                </Card>
              </Grid>
            ))}
          </Grid>
        </Container>

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
                <CustomizedSlider />
              </CardContent>
            </Card>
          ))}
        </Container>
      </main>

      {/* Footer */}
      <Box sx={{ bgcolor: "background.paper", p: 6 }} component="footer">
        <Typography variant="h6" align="center" gutterBottom>
          Footer
        </Typography>
        <Typography
          variant="subtitle1"
          align="center"
          color="text.secondary"
          component="p"
        >
          Something here to give the footer a purpose!
        </Typography>
        <Typography variant="body2" color="text.secondary" align="center">
          {"Copyright © "}
          <Link color="inherit" href="https://mui.com/">
            Your Website
          </Link>{" "}
          {new Date().getFullYear()}
          {"."}
        </Typography>
      </Box>

      {/* Section 1 */}
      <Box
        sx={{ bgcolor: "#f5f5f5", p: 6, transition: "background-color 1s" }}
        component="section"
      >
        <Container maxWidth="md">
          <Grid container spacing={2}>
            <Grid item xs={12} sm={6}>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: flag === 1 ? "green" : "red",
                  fontSize: "35px",
                  padding: "25px",
                  transition: "color 10s, font-size 1s",
                  fontWeight: "bold",
                }}
              >
                {flag === 1 ? "Recommended" : "Not Recommended"}
              </Typography>
              <ul>
                {flag === 1
                  ? recommendedArray.map((item, index) => (
                      <li key={index}>
                        <Typography variant="body1">{item}</Typography>
                      </li>
                    ))
                  : notRecommendedArray.map((item, index) => (
                      <li key={index}>
                        <Typography variant="body1">{item}</Typography>
                      </li>
                    ))}
              </ul>
            </Grid>

            {/* Image on the right */}
            <Grid
              item
              xs={12}
              sm={6}
              sx={{ display: "flex", justifyContent: "flex-end" }}
            >
              <CustomIcon src={pregaNews} alt="Pregnant Lady" />
            </Grid>
          </Grid>
        </Container>
      </Box>

      {/* Section 2 */}
      <Box
        sx={{ bgcolor: "#f5f5f5", p: 6, transition: "background-color 1s" }}
        component="section"
      >
        <Container maxWidth="md">
          <Grid container spacing={2}>
            {/* Image on the right */}
            <Grid
              item
              xs={12}
              sm={6}
              sx={{ display: "flex", justifyContent: "flex-end" }}
            >
              <CustomIcon src={cardiacNews} alt="New Protein Image" />
            </Grid>
            {/* Text on the left */}
            <Grid item xs={12} sm={6}>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "blue",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Recommended
              </Typography>
              <Typography variant="body1">
                Add your recommended text or content here.
              </Typography>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "orange",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Not Recommended
              </Typography>
              <Typography variant="body1">
                Add your not recommended text or content here.
              </Typography>
            </Grid>
          </Grid>
        </Container>
      </Box>

      {/* Section 3 */}
      <Box
        sx={{ bgcolor: "#f5f5f5", p: 6, transition: "background-color 1s" }}
        component="section"
      >
        <Container maxWidth="md">
          <Grid container spacing={2}>
            {/* Text on the left */}
            <Grid item xs={12} sm={6}>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "purple",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Recommended
              </Typography>
              <Typography variant="body1">
                Add your recommended text or content here.
              </Typography>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "brown",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Not Recommended
              </Typography>
              <Typography variant="body1">
                Add your not recommended text or content here.
              </Typography>
            </Grid>

            {/* Image on the right */}
            <Grid
              item
              xs={12}
              sm={6}
              sx={{ display: "flex", justifyContent: "flex-end" }}
            >
              <CustomIcon src={diabetic} alt="Diabetic" />
            </Grid>
          </Grid>
        </Container>
      </Box>

      {/* Section 4 */}
      <Box
        sx={{ bgcolor: "#f5f5f5", p: 6, transition: "background-color 1s" }}
        component="section"
      >
        <Container maxWidth="md">
          <Grid container spacing={2}>
            {/* Image on the right */}
            <Grid
              item
              xs={12}
              sm={6}
              sx={{ display: "flex", justifyContent: "flex-end" }}
            >
              <CustomIcon src={child} alt="Diabetic" />
            </Grid>
            {/* Text on the left */}
            <Grid item xs={12} sm={6}>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "teal",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Recommended
              </Typography>
              <Typography variant="body1">
                Add your recommended text or content here.
              </Typography>
              <Typography
                variant="h5"
                component="h2"
                gutterBottom
                sx={{
                  color: "gray",
                  fontSize: "24px",
                  transition: "color 1s, font-size 1s",
                }}
              >
                Not Recommended
              </Typography>
              <Typography variant="body1">
                Add your not recommended text or content here.
              </Typography>
            </Grid>
          </Grid>
        </Container>
      </Box>
    </ThemeProvider>
  );
}
