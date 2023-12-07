import * as React from 'react';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import Button from '@mui/material/Button';
import { useLogout } from "../hooks/useLogout";
import { useAuthContext } from "../hooks/useAuthContext";
import { Link } from "react-router-dom";

export default function Navbar_start() {
  const { logout } = useLogout();
  const { user } = useAuthContext();

  const handleClick = (targetId) => {
    logout();
    const element = document.getElementById(targetId);
    if (element) {
      element.scrollIntoView({ behavior: "smooth" });
    }
  };

  return (
    <Box sx={{ flexGrow: 1 }}>
      <AppBar position="static" sx={{ backgroundColor: '#efe5e0' }}>
        <Toolbar>
          <nav style={{ flexGrow: 1, display: 'flex', justifyContent: 'space-between' }}>
            <div>
             
              <Link to="/" style={{ textDecoration: 'none' }}>
                <Button
                  variant="outlined"
                  color="primary"
                  style={{ border: '1px solid #1976D2', borderRadius: '4px' }}
                >
                  Home
                </Button>
              </Link>
              {user && (
                <div>
                 
                </div>
              )}
            </div>
          </nav>
        </Toolbar>
      </AppBar>
    </Box>
  );
}
