const fs = require('fs');
const https = require('https');
const WebSocket = require('ws');

// Reading SSL certificates
const serverOptions = {
  key: fs.readFileSync('localhost.key'), // Your private key
  cert: fs.readFileSync('localhost.cert') // Your certificate
};

// Create an HTTPS server
const server = https.createServer(serverOptions);

// Create a WebSocket server attached to the HTTPS server
const wss = new WebSocket.Server({ server });

// Set up WebSocket connection event
wss.on('connection', (ws) => {
  console.log('Client connected');

  // Send a welcome message to the client
  ws.send('Welcome to the WSS WebSocket server!');

  // Handle incoming messages from the client
  ws.on('message', (message) => {
    console.log('Received message:', message);
    ws.send('Server received: ' + message);
  });

  // Handle closing connection
  ws.on('close', () => {
    console.log('Client disconnected');
  });
});

// Start the server on port 8080
server.listen(8080, () => {
  console.log('Server is running on wss://localhost:8080');
});
