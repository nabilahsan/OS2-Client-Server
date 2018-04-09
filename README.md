# OS2-Client-Server

STEPS TO RUN THE PROGRAM:
1. cd /Directory of program.
2. Compile using g++ (e.g g++ server.cpp, g++ client.cpp -o client).
3. ./(server executable name) Note: server must be executed and set up first.
4. User will be prompted first by server for input file name (must be in same directory) e.g Salaries.txt
5. Will be prompted again to enter a port number, which will used by the server to connect to the server.
6. Server should be up and looking for any connecting clients.
7. ./(client executable filename) execute the client file you compiled.
8. User will be prompted for a hostname. Note: use localhost if running locally on your own machine.
9. User will be prompted for a Port # to connect to, which must match the Port number you entered for your server.
10. Once successfully connected, you will be prompted for a username. Client will send the server a message containing your input.
11. Server will check to see if there is a match and will return the corresponding key, else it will tell you ‘Not found’ if not.
12. Client will close and the Server will keep running.
