import React, { createContext, useContext, useState } from "react";

const ChatContext = createContext();

export function ChatProvider({ children }) {
  const [selectedQuestions, setSelectedQuestions] = useState([]);

  const clearHistory = () => {
    setSelectedQuestions([]);
  };

  return (
    <ChatContext.Provider value={{ selectedQuestions, clearHistory }}>
      {children}
    </ChatContext.Provider>
  );
}

export function useChatContext() {
  return useContext(ChatContext);
}
