import React from "react";

function ChatItem({ chatItem }) {
  return (
    <div className="question-card">
      <h3>Question {chatItem.questionNumber}</h3>
      <p className="question-text">{chatItem.question}</p>
      <p className="answer-text">Answer: {chatItem.answer}</p>
    </div>
  );
}

export default ChatItem;
