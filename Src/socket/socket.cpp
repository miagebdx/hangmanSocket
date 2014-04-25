/* Socket Class */
/* Author(s): A. Esnard */

#include "socket.h"

#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <csignal>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>


#define FATAL(err) { perror((char *)err); exit(EXIT_FAILURE); }

SocketServer * SocketServer::_this = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_barrier_t barr;

void sendmsg(int fdw, std::string msg)
{
  char buffer[MSGMAXSIZE];
  memset(buffer, 0, MSGMAXSIZE);
  if(msg.length() > MSGMAXSIZE) {
    std::cerr << "\E[31;1mERROR: message length must be lower than " << MSGMAXSIZE << " characters!\E[m" << std::endl;
    exit(EXIT_FAILURE);
  }
  memcpy(buffer, msg.data(), msg.length());
  int w = write(fdw, buffer, MSGMAXSIZE);
  if(w != MSGMAXSIZE) {
    std::cerr << "\E[31;1mERROR: invalid message size sent!\E[m" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/* --------------------------------------------------------- */

void recvmsg(int fdw, std::string & msg)
{
  char buffer[MSGMAXSIZE];
  int r = read(fdw, buffer, MSGMAXSIZE);
  if(r != MSGMAXSIZE) {
    std::cerr << "\E[31;1mERROR: invalid message size received!\E[m" << std::endl;
    exit(EXIT_FAILURE);
  }
  msg = buffer;
}

/* --------------------------------------------------------- */

void interruption(int signum)
{
  SocketServer * _this = SocketServer::_this;
  close(_this->_fd);
  printf("\E[31;1mend of server!\n\E[m");
  exit(EXIT_SUCCESS);
}

/* --------------------------------------------------------- */

/* la routine principale du thread dédié à chaque client */
void * start_routine(void * arg)
{
  SocketServer * _this = SocketServer::_this;
  int fdw = (size_t)arg;
  printf("\E[32;1mworking with client (fd = %d)\n\E[m", fdw);
  _this->work(fdw);
  close(fdw);
  printf("\E[31;1mgoodbye client (fd = %d)\E[m\n", fdw);
  return NULL;
}

/* --------------------------------------------------------- */
/*                     SOCKET SERVER                         */
/* --------------------------------------------------------- */

SocketServer::SocketServer(int port)
{
  assert(port > 1024);
  this->_port = port;
  this->_fd = -1;
  this->_nfds = 0;
  SocketServer::_this = this;
  pthread_barrier_init(&barr, NULL, 2);
}

/* --------------------------------------------------------- */

SocketServer::~SocketServer()
{
}

/* --------------------------------------------------------- */

void SocketServer::start()
{
  int err;

  /* interception du signal d'interruption */
  signal(SIGINT,interruption);

  /* initialisation de la socket */
  _fd = socket(AF_INET, SOCK_STREAM, 0);
  if(_fd < 0) FATAL("socket");

  /* configuration avançée de la socket */
  int on = 1;
  err = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)); /* reusable socket address */
  if(err < 0) FATAL("setsockopt");

  /* configuration de la socket serveur */
  struct sockaddr_in addr;
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);       /* toutes les IPs */
  addr.sin_port        = htons(_port);            /* port d'écoute */
  err = bind(_fd, (struct sockaddr*)&addr, sizeof(addr));
  if (err < 0) FATAL("bind");

  err = listen(_fd, 4);
  if (err < 0) FATAL("listen");

  /* serveur à l'écoute */
  printf("\E[33;1mserver listen on port %d (fd = %d)\E[m\n", ntohs(addr.sin_port), _fd);
  printf("\E[33;1mpress ctrl-c to kill server\n\E[m");

  /* gestion des connexions clientes */

  while(1) {
    int fdw = accept(_fd, NULL, NULL);
    if (fdw < 0) FATAL("accept");
    printf("\E[32;1mnew incoming connection (fd = %d)\n\E[m", fdw);
    _fds[_nfds] = fdw;
    assert(sizeof(void*)==sizeof(size_t));
    pthread_t tid;
    pthread_create(&tid, NULL, start_routine, (void*)_fds[_nfds]);
    _nfds++;
  }

}

/* --------------------------------------------------------- */

void SocketServer::barrier()
{
  pthread_barrier_wait(&barr);
}

/* --------------------------------------------------------- */
/*                     SOCKET CLIENT                         */
/* --------------------------------------------------------- */

SocketClient::SocketClient(std::string hostname, int port)
{
  assert(port > 1024);
  this->_hostname = hostname;
  this->_port = port;
  this->_fd = -1;
}

/* --------------------------------------------------------- */

SocketClient::~SocketClient()
{

}

/* --------------------------------------------------------- */

void SocketClient::start()
{
  int err;

  /* initialisation de la socket */
  _fd = socket(AF_INET ,SOCK_STREAM, 0);
  if(_fd < 0) FATAL("socket");

  /* recherche de l'IP de la machine serveur */
  struct hostent * server = gethostbyname(_hostname.c_str());
  if(server == NULL) FATAL("gethostbyname");

  /* configuration de la socket */
  struct sockaddr_in addr;
  addr.sin_family      = AF_INET;
  addr.sin_port        = htons(_port);                             /* n° port (16 bits) */
  addr.sin_addr.s_addr = *(unsigned long *)server->h_addr_list[0]; /* addr IP (32 bits) */

  /* demande de connexion au serveur */
  err = connect(_fd,(struct sockaddr *)&addr, sizeof(addr));
  if(err < 0) FATAL("connect");

  /* travail avec le serveur*/
  work(_fd);

}

/* --------------------------------------------------------- */
