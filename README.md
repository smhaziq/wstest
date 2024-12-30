# WebSocket Tester

A simple tool for testing WebSocket connections.

## Requirements

- **Qt 6** (with `QtWebSockets` module)
- **CMake 3.16+**
- **Ninja**
- A **C++ compiler** (e.g., GCC, Clang, MSVC)

## Building the Project

1. **Clone the repository**:
   ```bash
   git clone https://github.com/smhaziq/wstest.git
   cd wstest
   ```

2. **Install Qt 6**:

    Follow the [Qt installation](https://doc.qt.io/qt-6/get-and-install-qt.html) guide for your platform.

3. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```
4. **Configure the project using CMake**:
   ```bash
   cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
   ```
   if it failed with error:
   
   `Could not find a package configuration file provided by "Qt6"...`  
   
   pass Qt6 path as recommended. e.g.
   ```bash
   cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=C:\Qt\6.5.7\msvc2019_64 ..
   ```

5. **Build the project**:
   ```bash
   ninja
   ```
6. **Run the program**: After building, the executable wstest will be available in the build directory. After placing all required Qt's runtime dependencies in same directory, you can run it with the following command:
   ```bash
   ./wstest -s <server_url> -n <num_connections> [--ignore-ssl-errors]
   ```
   Replace <server_url> with the WebSocket server URL and <num_connections> with the number of WebSocket connections you want to create.
   - The --ignore-ssl-errors option can be used if you want the tool to ignore SSL errors while connecting to the server.

## Usage

### Command-line options:

- `-s, --server <server_url>`  
WebSocket server URL to connect to.

- `-n, --connections <num_connections>`  
Number of WebSocket connections to create.

- `-i, --ignore-ssl-errors`  
Ignore SSL errors when connecting to the WebSocket server (useful if the server has an invalid certificate).

### Example:
   ```bash
   ./wstest -s wss://example.com/socket -n 10 -i
   ```
   This command will:
   - Connect to the WebSocket server at wss://example.com/socket.
   - Open 10 WebSocket connections.
   - Ignore SSL errors if the server certificate is invalid.

### Output:

The program will output a summary of the WebSocket connections as they connect and disconnect:

   ```bash
   Summary: Connected: 5 Disconnected: 5 Waiting: 0
   ```

It tracks the number of connected and disconnected WebSockets, as well as the remaining "waiting" connections.

# License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.