/* A simple server in the internet domain using TCP
   The port nu1mber is passed as an argument */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

using namespace std;
     struct paymentInfo {
       string major;
       string earlyPay;
       string midPay;
     };

     vector <paymentInfo> dataBank;

int main()
{
     int sockfd, newsockfd, portNumber;
     bool doExit = false;
     int buffsize = 1024;
     char buffer[buffsize];

     paymentInfo p;
     ifstream inputFile;
     string filename;
     string line;

     cout << "Enter filename: ";
     cin >> filename;

     inputFile.open(filename.c_str());

     if(inputFile.fail()){
       cout << "Error opening file" << endl;
       exit(1);
     }

     //Biggest HEADACHE
     while (getline(inputFile, line, '\t' )) {
       istringstream iss(line);
       getline(iss, p.major, '\t');
       getline(iss, p.earlyPay, '\t');
       getline(iss, p.midPay, '\t');

       iss >> p.major;
       iss >> p.earlyPay;
       iss >> p.midPay;

       dataBank.push_back(p);
     }

     inputFile.close();

     cout << "Enter the port number: ";
     cin >> portNumber;


     struct sockaddr_in serv_addr;
     socklen_t size;

     //Creating sockets
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){
       cout << "ERROR opening socket" << endl;
       exit(1);
     }
     cout << "Socket created" << endl;

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portNumber);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
       cout << "Error on binding" << endl;
     }

returnToListen:
     //Listens for client trying to connect.
     listen(sockfd,1);

     //Accepts client with correct port and address.
     newsockfd = accept(sockfd, (struct sockaddr *) &serv_addr, &size);

     if (newsockfd < 0){
      cout << "Error on accept" << endl;
     }

     recv (newsockfd, buffer, buffsize,0);
     string strBuffer(buffer);

     if (strBuffer == " ") {
       /* code */
       cout << "Server terminated..." << endl;
       close(newsockfd);
       exit(1);
     }

     //String parsing and table lookup

     for (int i = 0; i < dataBank.size(); i++) {
       /* code */
       if (dataBank[i].major == strBuffer) {
         /* code */
         strBuffer = dataBank[i].earlyPay;
         strBuffer = dataBank[i].midPay;
         break;
       } else if (i+2 == dataBank.size()) {
         /* code */
         strBuffer = "Not Found...";
         break;
       }
     }

     //Send message back to client
     send(newsockfd, strBuffer.c_str(), buffsize, 0);
goto returnToListen;

     return 0;
}
