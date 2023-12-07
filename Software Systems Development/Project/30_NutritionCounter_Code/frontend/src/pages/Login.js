import { useState } from "react"
import { useNavigate, Link } from "react-router-dom";
import { useLogin } from "../hooks/useLogin"

const Login = () => {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const {login, error, isLoading} = useLogin()
  const navigate  = useNavigate ();

  const handleSubmit = async (e) => {
    e.preventDefault()
    try {
      await login(email, password)
      navigate.push("/");
    } catch (error) {
      console.error("Error fetching history data:", error.message);
    }
  }

  return (
    <form className="login" onSubmit={handleSubmit}>
      <h3>LOG IN</h3>
      
      <label>Email address:</label>
      <input 
        type="email" 
        onChange={(e) => setEmail(e.target.value)} 
        value={email} 
      />
      <label>Password:</label>
      <input 
        type="password" 
        onChange={(e) => setPassword(e.target.value)} 
        value={password} 
      />

      <div className="forgotLink">
        <Link to="/login" className="forgot-password-link">
          Forgot Password?
        </Link>
      </div>

      <button disabled={isLoading}>Log in</button>
      {error && <div className="error">{error}</div>}
    </form>
  )
}

export default Login