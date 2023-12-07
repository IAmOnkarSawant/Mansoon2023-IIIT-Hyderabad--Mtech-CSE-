import "../common.css";
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { Link } from 'react-router-dom';

const BACKEND_URI = "http://localhost:5001/api/";

// functional component
function LoginForm(props) {
    const [roll, setRoll] = useState("");
    const [password, setPassword] = useState("");
    const [role, setRole] = useState("");

    const navigate = useNavigate();

    const navigateToQuery = () => {
        navigate('/student');
    }
    const navigateToResponse = () => {
        navigate('/tas/queries');
    }

    return (
    <div className="center-div">
        <h1 className='text-center'>Login</h1>
        <form className='form-group'>
            <label className='m-2 form-label'>Roll No : </label>
            <br/>
            <input className='m-2 form-control' type="text" name="roll" value={roll} onChange={(e) => setRoll(e.target.value)}/>
            <br/>
            <label className='m-2 form-label'>Password : </label>
            <br/>
            <input className='m-2 form-control' type="password" name="password" value={password} onChange={(e) => setPassword(e.target.value)}/>
            <br/> 
            <select className="form-select" style={{width:"200px",marginLeft:"2%"}} name = "role" onChange={(e) => setRole(e.target.value)}>
                <option value="choose">Choose..</option>
            <option value = "Student" >Student</option>
            
            <option value = "TA">TA</option>
         </select>
        </form>
        <br/>
        <div style={{border:"0px solid green",height:"50px",width:"420px"}}>
        <button className=' btn btn-primary' style={{float:"left",marginLeft:"25%"}} onClick={async (e) =>  {
                // send fetch (POST) request to server
                //const role=document.getElementsByName("role");
                console.log(role);
                const requestOptions = {
                    credentials : 'include',
                    method : 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body : JSON.stringify({ roll : roll, password : password ,role:role})
                };

                var res = await fetch(BACKEND_URI + "login", requestOptions);
                alert((await res.json())["msg"]);
                setRoll("");
                setPassword("");
               // var role=role;
                setRole("");
                if(res.status == 200) {
                    sessionStorage.setItem("roll", roll);
                    if(role!='TA')
                    navigateToQuery();
                    else
                    navigateToResponse();
                }
            }}>Login</button>
            <br/>
            <div>
            <Link to='/signup'>  <button className='btn btn-primary'  style={{float:"left",marginLeft:"2%",marginTop:"-6%"}}>Sign Up</button> </Link>
            </div> </div>
    </div>
    );
}

export default LoginForm;