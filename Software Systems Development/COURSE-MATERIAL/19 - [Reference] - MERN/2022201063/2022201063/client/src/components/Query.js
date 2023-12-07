import "../common.css";
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { Link } from 'react-router-dom';

const BACKEND_URI = "http://localhost:5001/api/";

// functional component
function Query(props) {
    const [Examname, setExamname] = useState("");
    const [CourseName, setCourseName] = useState("");
    const [QuestionNo, setQuestionNo] = useState("");
    const [TAname, setTAname] = useState("");
    const [Comments, setComments] = useState("");
   // const [TaComments,setTAcomments]=useState("");
   

    const navigate = useNavigate();

    const navigateToStudent = () => {
        navigate('/student');
    }

    return (<div>
         <div>
           <Link to='/'><button id="newquery" className="btn btn-success"  href="/query" style={{marginRight:"20%",marginTop:"-3%"}} onClick={async (e) =>  {
                const requestOptions = {
                    credentials : 'include',
                    method : 'GET',
                    headers: {'Content-Type': 'application/json' }
                };
            var res = await fetch(BACKEND_URI + "logout",requestOptions);
            console.log(res);
            alert((await res.json())["msg"]);
            // navigateToHome();
            }}>Logout
            </button></Link> 
           </div>
    <div className="center-div">
        <h1 className='text-center'>Query</h1>
        <form className='form-group'>
            <label className='m-2 form-label'>Exam Name: </label>
            <br/>
            <input className='m-2 form-control' type="text" name="examname" value={Examname} onChange={(e) => setExamname(e.target.value)}/>
            
            <br/>
            <label className='m-2 form-label'>Course Name: </label>
            <br/>
            <input className='m-2 form-control' type="text" name="coursename" value={CourseName} onChange={(e) => setCourseName(e.target.value)}/>
            <br/>
            <label className='m-2 form-label'>Question No: </label>
            <br/>
            <input className='m-2 form-control' type="text" name="questionno" value={QuestionNo} onChange={(e) => setQuestionNo(e.target.value)}/>
            <br/>
            <label className='m-2 form-label'>TA's Name: </label>
            <br/>
            <select class="form-select" style={{width:"200px",marginLeft:"2%"}} name = "role" onChange={(e) => setTAname(e.target.value)}>
                <option value="choose">Choose..</option>
            <option value = "Student">Ashish</option>
            
            <option value = "TA">Shaon</option>
         </select> <br/>
            <label className='m-2 form-label'>Comments: </label>
            <br/>
            <textarea id="comments" name="comments" rows="4" cols="50" value={Comments} onChange={(e) => setComments(e.target.value)}></textarea>
            {/* <input className='m-2 form-control' type="text" name="comments" value={Comments} onChange={(e) => setComments(e.target.value)}/> */}
            <br/>
        </form>
        <br/>
        <div>
        <button className='btn btn-primary' onClick={async (e) =>  {
                // send fetch (POST) request to server
                //const role=document.getElementsByName("role");
                //console.log(role);
                const requestOptions = {
                    credentials : 'include',
                    method : 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body : JSON.stringify({ exam_name:Examname  ,
                    course_name:CourseName,
                    ta_roll:TAname,
                    question_num:QuestionNo,
                    std_roll:sessionStorage.getItem("roll"),
                    ta_comment:"",
                    std_comment:Comments,
                    IsActive:""
                })
            }
                var res = await fetch(BACKEND_URI + "query", requestOptions);
                alert((await res.json())["msg"]);
                setExamname("");
                setQuestionNo("");
                setCourseName("");
                setTAname("");
                setComments("");
                if(res.status == 200) {
                    navigateToStudent();
                }
            }}>Post</button>
            <br/>
             </div>
    </div>
    </div>
    );
}

export default Query;