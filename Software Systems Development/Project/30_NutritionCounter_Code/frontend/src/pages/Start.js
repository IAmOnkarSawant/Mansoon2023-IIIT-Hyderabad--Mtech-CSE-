import React, { useState, useRef } from "react";
import {
  Button,
  Typography,
  Container,
  Card,
  CardActions,
  CardContent,
  CardMedia,
  Input,
  InputLabel,
} from "@mui/material";
import {
  PhotoCamera,
  CloudUpload,
  GetApp,
  Videocam,
} from "@mui/icons-material";
import { useNavigate } from "react-router-dom";
import Navbar_start from "../components/Navbar_start";
import { createTheme, ThemeProvider } from "@mui/material/styles";

const Start = () => {
  const navigate = useNavigate();
  const videoRef = useRef(null);
  const canvasRef = useRef(null);
  const inputRef = useRef(null);
  const [isRecording, setIsRecording] = useState(false);
  const [imageData, setImageData] = useState(null);
  const [mode, setMode] = useState("initial");

  const startRecording = async () => {
    if (imageData) {
      setImageData(null);
    }

    try {
      const stream = await navigator.mediaDevices.getUserMedia({ video: true });
      videoRef.current.srcObject = stream;
      setIsRecording(true);
    } catch (error) {
      console.error("Error accessing the camera:", error);
    }
  };

  const stopRecording = () => {
    const video = videoRef.current;
    const canvas = canvasRef.current;
    const context = canvas.getContext("2d");

    video.pause();
    context.drawImage(video, 0, 0, canvas.width, canvas.height);
    video.srcObject.getVideoTracks()[0].stop();
    setIsRecording(false);

    const imageDataURL = canvas.toDataURL("image/jpeg");
    setImageData(imageDataURL);
  };

  const handleImageUpload = (e) => {
    const file = e.target.files[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = (event) => {
        setImageData(event.target.result);
      };
      reader.readAsDataURL(file);
    }
  };

  const downloadImage = () => {
    if (imageData) {
      const destinationPath = mode === "ingredients" ? "/album" : "/table";
      handleUpload(destinationPath);
    }
  };

  const handleButtonClick = (selectedMode) => {
    setMode(selectedMode);
  };

  const handleUpload = async (destinationPath) => {
    const formData = new FormData();
    const blob = await dataURItoBlob(imageData);
    formData.append("image", blob, "captured-image.jpeg");

    try {
      const response = await fetch("/api/home/upload", {
        method: "POST",
        body: formData,
      });

      if (response.ok) {
        alert("File uploaded successfully.");
        navigate(destinationPath);
      } else {
        alert("Error uploading the file.");
      }
    } catch (error) {
      console.error("Error:", error);
    }
  };

  const dataURItoBlob = async (dataURI) => {
    const response = await fetch(dataURI);
    const blob = await response.blob();
    return blob;
  };
  const defaultTheme = createTheme();

  return (
    <ThemeProvider theme={defaultTheme}>
      <Navbar_start />
      <br />
      <br />
      <Container maxWidth="sm">
        <Typography
          variant="h4"
          align="center"
          gutterBottom
          style={{ marginTop: "20px", fontWeight: "bold", color: "black" }}
        >
          {mode === "initial" && (
            <>
              <span
                role="img"
                aria-label="camera-icon"
                style={{ marginRight: "10px" }}
              >
                📸
              </span>
              Select One
            </>
          )}
          {mode !== "initial" && "Camera App"}
        </Typography>
        {mode === "initial" && (
          <Card>
            <CardContent
              style={{ display: "flex", justifyContent: "space-between" }}
            >
              <Button
                variant="contained"
                color="primary"
                onClick={() => handleButtonClick("ingredients")}
                style={{ width: "48%" }}
              >
                Ingredients
              </Button>
              <Button
                variant="contained"
                color="primary"
                onClick={() => handleButtonClick("table")}
                style={{ width: "48%" }}
              >
                Table
              </Button>
            </CardContent>
          </Card>
        )}
        {(mode === "ingredients" || mode === "table") && (
          <Card>
            <CardContent>
              <CardMedia
                component="video"
                ref={videoRef}
                autoPlay
                height="360"
              />
              <canvas
                ref={canvasRef}
                style={{ display: "none" }}
                width="640"
                height="480"
              />
            </CardContent>
            <CardActions>
              <InputLabel htmlFor="image-upload" style={{ width: "100%" }}>
                <Input
                  accept="image/*"
                  id="image-upload"
                  type="file"
                  inputRef={inputRef}
                  style={{ display: "none" }}
                  onChange={handleImageUpload}
                />
                <Button
                  variant="contained"
                  color="primary"
                  startIcon={<CloudUpload />}
                  component="span"
                  fullWidth
                >
                  Choose Image
                </Button>
              </InputLabel>
              {isRecording ? (
                <Button
                  variant="contained"
                  color="secondary"
                  startIcon={<PhotoCamera />}
                  onClick={stopRecording}
                  fullWidth
                >
                  Capture Image
                </Button>
              ) : (
                <Button
                  variant="contained"
                  color="primary"
                  startIcon={<Videocam />}
                  onClick={startRecording}
                  fullWidth
                >
                  Start Camera
                </Button>
              )}
            </CardActions>
            {imageData && (
              <CardContent>
                <CardMedia
                  component="img"
                  src={imageData}
                  alt="Captured"
                  style={{ width: "100%" }}
                />
              </CardContent>
            )}
            {imageData && (
              <CardActions>
                <Button
                  variant="contained"
                  color="primary"
                  startIcon={<GetApp />}
                  onClick={downloadImage}
                  fullWidth
                >
                  Upload Image
                </Button>
              </CardActions>
            )}
          </Card>
        )}
      </Container>
    </ThemeProvider>
  );
};

export default Start;
