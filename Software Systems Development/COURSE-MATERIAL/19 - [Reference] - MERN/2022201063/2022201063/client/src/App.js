import './App.css';
import SignUpForm from './components/SignUpForm';
import LoginForm from './components/LoginForm';
import Query from './components/Query';
import Student from './components/Student';
import Content from './components/Content';
import Tasqueries from './components/Tasqueries';
import { BrowserRouter, Route, Routes } from 'react-router-dom';

function App() {
  return (
  <BrowserRouter>
    <Routes>
        <Route path="/" element={<LoginForm />}/>
        <Route path="signup" element={<SignUpForm />}/>
        <Route path="login" element={<LoginForm />}/>
        <Route path="addQuery" element={<Query />}/>
        <Route exact path="student" element={<Student />}/>
        <Route exact path="content" element={<Content />}/>
        <Route exact path="/tas/queries" element={<Tasqueries />}/>
    </Routes>
  </BrowserRouter>);
}

export default App;
