#include "server/server.cpp"
int main(int argc, char * argv[]) 
{
  
  if (argc != 2) {
    printf("usage: %s port\n",argv[0]);
    return EXIT_FAILURE;
  }
  
  /* argument(s) */
  int port = atoi(argv[1]);
  
  Socket * server = new SocketServerTest(port);
  server->start();
  
  return EXIT_SUCCESS;
}
