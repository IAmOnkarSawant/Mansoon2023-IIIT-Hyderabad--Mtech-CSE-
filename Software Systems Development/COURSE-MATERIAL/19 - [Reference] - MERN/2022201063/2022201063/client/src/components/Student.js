import React from "react";
import { useState } from "react";
import { json } from "react-router-dom";

import { Link } from 'react-router-dom';
const BACKEND_URI = "http://localhost:5001/api/";
// import './App.css';


const ReadMore = ({ children }) => {
    const text = children;
    const [isReadMore, setIsReadMore] = useState(true);
    const toggleReadMore = () => {
      setIsReadMore(!isReadMore);
    };
    return (
        <div style={{marginLeft:"4%",border:"1px solid black",height:"fit-content",minHeight: "50px"}}>
      <p className="text" style={{float:"left",textAlign:"left",color:"darkblue"}}>
	 {text!=undefined && text.length>150?(isReadMore? text.slice(0, 150) : text):""}
	 <span onClick={toggleReadMore} className="read-or-hide">
		{text!=undefined ? (text.length>150?(isReadMore ? "...read more" : " show less"):text):""}
	</span>
	</p>
      </div>
    );
  };

class Student extends React.Component {
   
    // Constructor 
    constructor(props) {
        super(props);
   
        this.state = {
            items:[],
            DataisLoaded: false
        };
    }
   
    // ComponentDidMount is used to
    // execute the code 
    componentDidMount() {
        fetch(
BACKEND_URI+"getQuery/"+sessionStorage.roll)
            .then((res) => res.json())
            .then((json) => {
                console.log(json.data);
               // console.log(json.data.ta_comment)
                this.setState({
                    items: json.data,
                    DataisLoaded: true
                });
            })
            

    }
    render() {
        const { DataisLoaded, items } = this.state;
        if (!DataisLoaded) return <div>
            <h1> Pleses wait some time.... </h1> </div> ;
        var ta_comment=items.ta_comment;
        var std_comment=items.std_comment;
        if(!ta_comment)
        ta_comment="";
        if(!std_comment)
        std_comment="";
        return (
        <div id="container">
            <div>
            <h1 id="feed" style={{marginTop:"5%",marginLeft:"30%",color:"white"}}> Feedbacks</h1> 
            </div>
            <div>
            <Link to='/addQuery'><button id="newquery" className="btn btn-success"  href="/query" style={{marginRight:"30%",marginTop:"-3%"}} >Add New Query</button></Link>
           </div>
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
            
        <div className = "App">
        {
                items.map((item) => ( 
                <div key = { item.id } className="center-div" style={{width:"50%"}}>
                    <div>
                    <div style={{width:"25%",marginTop:"-5%"}}>
                    < h3 >Exam Name:</h3>
                    </div>
                    <div style={{width:"25%",marginTop:"-5.5%",marginLeft:"15%"}}> 
                    <h3>{ item.exam_name }</h3>
                    </div>
                    <div style={{width:"25%",marginTop:"-5.5%",marginLeft:"50%"}} >
                    < h3>Course Name:</h3>
                    </div>         
                    <div style={{width:"25%",marginTop:"-5.5%",marginLeft:"68%"}}>
                    <h3>{ item.course_name }</h3>
                    </div>
                    <div>
                    < h3 style={{width:"25%",marginTop:"1%",marginLeft:"1%"}}>Question No:</h3>
                  </div>
                    <div>
                    <h3 style={{width:"25%",marginTop:"-5%",marginLeft:"15%"}}>{ item.question_num }</h3>
                   </div>
                   <div>
                    < h3 style={{width:"25%",marginTop:"-5%",marginLeft:"48%"}}>TA Name:</h3>
                  </div>
                    <div>
                    <h3 style={{width:"25%",marginTop:"-5.5%",marginLeft:"64%"}}>{ item.ta_roll}</h3>
                   </div>
                    </div>
                    
                    <div class="row">
                    
                    < h3 style={{width:"25%",marginTop:"5%",marginLeft:"2%"}}>TA comment:</h3>
                    <ReadMore>{ item.ta_comment }</ReadMore>
                    {/* <textarea style={{marginTop:"5%",marginLeft:"4%"}} readOnly>{ item.ta_comment }</textarea> */}
                    
                    < h3 style={{width:"25%",marginTop:"5%",marginLeft:"2%"}}>Std_comment:</h3>
                    <ReadMore>{ item.std_comment }</ReadMore>
                    {/* <textarea  style={{marginTop:"5%",marginLeft:"4%"}} readOnly>{ item.std_comment }</textarea> */}
                   </div>
                  </div>
                   
                    
   
                ))
            }
        </div>
    
             
    </div>
    )
}
}

   
export default Student;