// Home.js

import React, { useEffect, useState } from "react";
import QueCard from "../components/QueCard";
import ChatSpace from "../components/ChatSpace";
import { useAuthContext } from "../hooks/useAuthContext";
import { v4 as uuidv4 } from "uuid";

const Home = () => {
  const [questions, setQuestions] = useState(null);
  const [selectedQuestions, setSelectedQuestions] = useState([]);
  const { user } = useAuthContext();

  useEffect(() => {
    const fetchQuestions = async () => {
      try {
        const response = await fetch("/api/chat", {
          headers: { Authorization: `Bearer ${user.token}` },
        });

        if (!response.ok) {
          throw new Error(`Request failed with status: ${response.status}`);
        }

        const contentType = response.headers.get("content-type");

        if (contentType && contentType.includes("application/json")) {
          const json = await response.json();
          setQuestions(json);
        } else {
          console.error("Response is not valid JSON.");
        }
      } catch (error) {
        console.error("Error fetching data:", error.message);
      }
    };
    if (user) fetchQuestions();
  }, [user]);

  const handleQuestionClick = async (questionNumber) => {
    try {
      const response = await fetch(`/api/chat/${questionNumber}`, {
        headers: { Authorization: `Bearer ${user.token}` },
      });
      //console.log(response);
      if (!response.ok) {
        throw new Error(`Request failed with status: ${response.status}`);
      }
      const data = await response.json();
      console.log(data);
      const chatItem = { ...data, key: uuidv4() };
      setSelectedQuestions((prevSelectedQuestions) => [
        ...prevSelectedQuestions,
        chatItem,
      ]);
    } catch (error) {
      console.error("Error fetching chat data:", error.message);
    }
  };

  return (
    <div className="page-content">
      <div className="chat-space">
        { selectedQuestions && 
          selectedQuestions.map((chat) => (
            <ChatSpace 
              chatItem={chat}
              key={chat.key}
            />
        ))}
        { !selectedQuestions &&
          (
            <div> 
              No chat Itemx    yet!
            </div>
          )
        }
      </div>
      <div className="question-area">
        {questions &&
          questions.map((que) => (
            <QueCard
              question={que}
              key={que._id}
              onClick={handleQuestionClick}
            />
          ))}
      </div>
    </div>
  );
};

export default Home;
