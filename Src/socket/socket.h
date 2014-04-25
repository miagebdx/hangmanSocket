/* Socket Class */
/* Author(s): A. Esnard */

#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#define MAXCLTS 200  // max nb of client connections allowed
#define MSGMAXSIZE 255

/* --------------------------------------------------------- */

void sendmsg(int fdw, std::string msg);
void recvmsg(int fdw, std::string & msg);

/* --------------------------------------------------------- */

class Socket {
  
 public:
  virtual void work(int fdw) = 0; // to be implemented by end-user...
  virtual void start() = 0;       // to start...
};

/* --------------------------------------------------------- */
/*                     SOCKET SERVER                         */
/* --------------------------------------------------------- */

// server socket 
class SocketServer : public Socket {

  friend void interruption(int signum);
  friend void * start_routine(void * arg);

 public:
  SocketServer(int port);      
  virtual ~SocketServer();    
  virtual void start();
  static SocketServer* _this;
  static void barrier();  // synchronization barrier between 2 threads

 protected:
  int _port;                 // server port
  int _fd;                   // server socket (file descriptor) 
  size_t _fds[MAXCLTS];      // client file descriptors 
  int _nfds;                 // total nb of clients
};

/* --------------------------------------------------------- */
/*                     SOCKET CLIENT                         */
/* --------------------------------------------------------- */

// client socket
class SocketClient : public Socket {
  
 public:
  SocketClient(std::string hostname, int port);      
  virtual ~SocketClient();    
  virtual void start();
  
 protected:
  std::string _hostname;    // server hostname
  int _port;                // server port
  int _fd;                  // client socket (file descriptor) 
  
};

/* --------------------------------------------------------- */


#endif
