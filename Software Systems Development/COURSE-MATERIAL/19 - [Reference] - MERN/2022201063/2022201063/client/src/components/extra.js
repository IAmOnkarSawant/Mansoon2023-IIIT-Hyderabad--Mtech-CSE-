<div className="container" style={{border:"1px solid green",marginTop:"3%"}}>
  <div className="row">
    <div className="col" style={{border:"1px sollid green"}}><h3 style={{marginLeft:"8%"}}>Exam Name:</h3></div>
    <div className="col"><h3 style={{marginLeft:"-35%"}}>{item.exam_name}</h3></div>
    <div className="col"><h3 style={{marginLeft:"-10%"}}>Course Name:</h3></div>
    <div className="col"><h3 style={{marginLeft:"-45%"}}>{item.course_name}</h3></div>
    <div className="w-100"></div>
    <div className="col"><h3 style={{marginLeft:"8%"}}>Question Number:</h3></div>
    <div className="col"><h3 style={{marginLeft:"-5%"}}>{item.question_num}</h3></div>
    <div className="col"><h3 style={{marginLeft:"-10%"}}>Question Number:</h3></div>
    <div className="col"><h3 style={{marginLeft:"-25%"}}>{item.question_num}</h3></div>
  </div>
  <div style={{marginLeft:"2%"}}>
  <h3 style={{marginLeft:"1%",marginTop:"3%"}}>TA Comments:</h3>

  <textarea id="std_comment" readOnly>
		{item.ta_comment}
		</textarea>
    
</div>
<div style={{marginLeft:"2%"}}>
  <h3 style={{marginLeft:"1%",marginTop:"3%"}}>Student Comments:</h3>
      <textarea id="std_comment" readOnly>
		{item.std_comment}
		</textarea>
</div>
</div>