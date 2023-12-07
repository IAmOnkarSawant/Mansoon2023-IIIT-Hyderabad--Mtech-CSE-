// History.js

import React, { useEffect, useState } from "react";
import ChatSpace from "../components/ChatSpace";
import { useAuthContext } from "../hooks/useAuthContext";

const History = () => {
  const [historyItems, setHistoryItems] = useState([]);
  const { user } = useAuthContext();

  useEffect(() => {
    const fetchHistory = async () => {
      try {
        const response = await fetch("/api/chat/history", {
          headers: { Authorization: `Bearer ${user.token}` },
        });

        if (!response.ok) {
          throw new Error(`Request failed with status: ${response.status}`);
        }

        const contentType = response.headers.get("content-type");

        if (contentType && contentType.includes("application/json")) {
          const json = await response.json();
          setHistoryItems(json);
        } else {
          console.error("Response is not valid JSON.");
        }
      } catch (error) {
        console.error("Error fetching history data:", error.message);
      }
    };

    if (user) fetchHistory();
  }, [user]);

  const clearHistory = () => {
    setHistoryItems([]);
  };

  return (
    <div className="page-content">
      <button className="clear-history-button" onClick={clearHistory}>
        Clear History
      </button>
      <div className="chat-space">
        {historyItems &&
          historyItems.map((historyItem) => (
            <ChatSpace
              chatItem={historyItem}
              key={historyItem._id} 
            />
          ))}
      </div>
    </div>
  );
};

export default History;
