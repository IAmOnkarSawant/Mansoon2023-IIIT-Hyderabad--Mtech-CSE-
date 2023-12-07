
function start(){
var pcontent=document.getElementById("demo_p");
pcontent.innerHTML="Ready to Start!!"
}
function mess(){
    var username=document.getElementsByName("name");
    console.log(username)
    var favmess=document.getElementsByName("mess")[0].value;
    var comment=document.getElementsByClassName("input_data")[0];
    console.log(username,favmess);
    if(username!="" && favmess!="")
    comment.innerHTML="Myself "+username[0].value+", favourite mess: "+favmess;
    else
    comment.innerHTML="Fill details please"
    comment.style.color="Red"
    comment.style.fontSize="20px"
}
function create(){
var div3=document.getElementById("div3");
var p=document.createElement("p");
p.id="newp"
p.innerHTML="Element created";
p.style.marginTop="-15%"
p.style.marginLeft="5%"
div3.appendChild(p);
}
function hide(){
    const element = document.getElementById("newp");
    element.remove();
}
function mouseEnter(){
var p=document.getElementById("img4");
p.style.height="250";
p.style.width="250";
// p.innerHTML=str.italics();
}
function mouseLeave(){
    var p=document.getElementById("img4");
    p.style.height="150";
    p.style.width="150";
    // p.innerHTML=str.italics();
}
function dragStart(event) {
    event.dataTransfer.setData("Text", event.target.id);
  }
  
  function dragging(event) {
    document.getElementById("demo").innerHTML = "The p element is being dragged";
  }
  
  function allowDrop(event) {
    event.preventDefault();
  }
  
  function drop(event) {
    event.preventDefault();
    const data = event.dataTransfer.getData("Text");
    event.target.appendChild(document.getElementById(data));
    document.getElementById("demo").innerHTML = "The p element was dropped";
  }

  function getinput(){
    let text = document.getElementById("getInput").value;
  document.getElementById("showinput").innerHTML = "You wrote: " + text;
  }
  function finish(){
    // alert("See you on Lab , Thankyou!!")
    
    swal({
        title: "Good job!",
        text: "See you on Lab , Thankyou!!",
        icon: "success",
        button: "Aww yiss!",
      });
  }
