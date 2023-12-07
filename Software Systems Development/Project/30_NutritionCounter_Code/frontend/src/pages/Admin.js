import React, { useState } from 'react';
import { useAuthContext } from '../hooks/useAuthContext';

const Admin = () => {
  const [question, setQuestion] = useState('');
  const [answer, setAnswer] = useState('');
  const { user } = useAuthContext();

  const handleSubmit = async (e) => {
    e.preventDefault();

    try {
        let questionNumber = 10;
      const response = await fetch('/api/chat/ques', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          Authorization: `Bearer ${user.token}`,
        },
        body: JSON.stringify({ questionNumber, question, answer }),
      });

      if (!response.ok) {
        throw new Error(`Request failed with status: ${response.status}`);
      }

      setQuestion('');
      setAnswer('');
      alert('Question added successfully!');
    } catch (error) {
      console.error('Error adding question:', error.message);
      alert('Failed to add question. Please try again.');
    }
  };

  return (
    <div className="admin-container">
      <h2 className="admin-title">Add a Question</h2>
      <form className="admin-form" onSubmit={handleSubmit}>
        <div className="admin-form-group">
          <label htmlFor="question" className="admin-label">
            Question:
          </label>
          <textarea
            id="question"
            value={question}
            onChange={(e) => setQuestion(e.target.value)}
            required
            className="admin-textarea"
          ></textarea>
        </div>
        <div className="admin-form-group">
          <label htmlFor="answer" className="admin-label">
            Answer:
          </label>
          <textarea
            id="answer"
            value={answer}
            onChange={(e) => setAnswer(e.target.value)}
            required
            className="admin-textarea"
          ></textarea>
        </div>
        <button type="submit" className="admin-button">
          Submit
        </button>
      </form>
    </div>
  );
};

export default Admin;
