//Md Nabil Ahsan
//ID: 1508388
//Programming Assignment 2: Socket Porgramming

//Input file consists of major names that contain spaces
//e.g. Cognitive Science
//After which there is a tab to separate the names from the salaries.
//Both salaries are sepated by tabs.
//Cognitive Science [tab] 54000 [tab] 121900.

//Input CAN be read char by char, where it reads
//in the spaces and stops reading when it enconters a tab.
//Then the early career and mid-career pay are read
//char by char as well and stored as strings, NOT int.

/*********************************************/

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <netdb.h>

using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int portNumber;
    int sockfd;
    bool isExit = false;
    int buffsize = 1024;
    char buffer[buffsize];
    string hostname;

    struct sockaddr_in serv_addr;
    struct hostent *server;

//Checking for hostname.

returntoHost:
    cout << "Enter Hostname: ";
    cin >> hostname;
    server = gethostbyname(hostname.c_str());


    if (server == NULL) {
      cout << "ERRO: No such host. Try Again." << endl;
      goto returntoHost;
    }
//Checking port number
//According to socket tutorial,
//any number between 2000 and 65535 can be used for the port number.

returnToPort:

    cout << "Enter port number: ";
    cin >> portNumber;

    if (portNumber <= 2000 || portNumber >= 65535) {
      cout << "ERROR: Port number must be between 2000 and 65535" << endl;
      goto returnToPort;
    }

      sockfd = socket(AF_INET, SOCK_STREAM, 0);

      if (sockfd < 0){
        cout << "ERROR opening socket" << endl;
      }

      cout << "Socket created." << endl;
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(portNumber);

      if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == 0){
          cout << "Connection to port number on server: ";
    }

    while (sockfd > 0) {

      cout << "Enter desired major: ";
      cin >> buffer;

      send(sockfd, buffer, buffsize, 0);
      recv(sockfd, buffer, buffsize, 0);

      cout << "The early career pay = " << buffer << " and mid career pay = " << buffer << endl;
    }

    cout << " Terminating..." << endl;
    close(sockfd);

    return 0;
}

// // int main(int argc, char const *argv[]) {
// //
// //   ifstream infile;
// //   infile.open("Salaries.txt");
// //
// //   if(infile.fail()){
// //     std::cout << "FAIL" << '\n';
// //   }
// //   else{
// //     string s;
// //     while (getline(infile,s)) {
// //       /* code */
// //       std::cout << s << endl;
// //     }
// //   }
// //
//
//
//
//     printf("Please enter the message: ");
//     bzero(buffer,256);
//     fgets(buffer,255,stdin);
//     n = write(sockfd,buffer,strlen(buffer));
//
//     if (n < 0)
//          error("ERROR writing to socket");
//     bzero(buffer,256);
//     n = read(sockfd,buffer,255);
//     if (n < 0)
//          error("ERROR reading from socket");
//     printf("%s\n",buffer);
//     return 0;
//
// //   return 0;
// // }
