import React, { Fragment } from "react";
import { Link } from "react-router-dom";

import Start from "./Start";

function Landing() {
  return (
    <Fragment>
      <header className="header" id="header">
        <div
          className="container"
          style={{
            display: "flex",
            flexDirection: "column",
            height: "40%",
            justifyContent: "center",
          }}
        >
          <figure className="logo animated fadeInDown delay-07s">
            <a href="#">
              <img src="assets/img/nutrition_icon.png" alt="" />
            </a>
          </figure>
          <h1 className="animated fadeInDown delay-07s">
            Welcome <br /> To <br /> Nutrition Counter App
          </h1>
          <h2 className="we-create animated fadeInUp delay-1s">
            <li>We tell you which nutritions are good for you!</li>
          </h2>

          <Link
            to="/start"
            className="link animated fadeInUp delay-1s servicelink"
          >
            Get Started
          </Link>
        </div>
      </header>
    </Fragment>
  );
}

export default Landing;
