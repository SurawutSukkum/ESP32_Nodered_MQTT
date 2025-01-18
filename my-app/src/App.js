import React, { useState, useEffect } from 'react';

function App() {
  const [modelOutput, setModelOutput] = useState(null);

  useEffect(() => {
    const fetchModelOutput = () => {
      fetch('http://127.0.0.1:3001/all')
        .then(response => response.json())
        .then(data => setModelOutput(data))
        .catch(error => console.error('Error fetching model output:', error));
    };

    fetchModelOutput(); // Initial fetch
    const intervalId = setInterval(fetchModelOutput, 1000); // Fetch every 5 seconds

    return () => clearInterval(intervalId); // Cleanup on unmount
  }, []);

    // Extract values
  const temperature = modelOutput.find((item) => item.temp)?.temp || "N/A";
  const humidity = modelOutput.find((item) => item.humi)?.humi || "N/A";

  return (
    <div style={{ textAlign: "center", marginTop: "40px", fontFamily: "Arial, sans-serif" }}>
      <h1>Environmental Data by N'Marc</h1>
      <p style={{ fontSize: "30px" }}>
        Temperature is <strong>{temperature}°C</strong> and Humidity is <strong>{humidity}%</strong>.
      </p>
      <img src="Octocat.png" className="App-logo" alt="logo" />

    </div>
  );
}

export default App;
