#include "client/client.cpp"



int main(int argc, char * argv[]) 
{
  if (argc != 3) {
    printf("Usage: %s hostname port\n",argv[0]);
    return EXIT_FAILURE;
  }
  
  /* argument(s) */
  string hostname = argv[1];
  int port = atoi(argv[2]);
  
  Socket * client = new SocketClientTest(hostname, port);
  client->start();
  
  return EXIT_SUCCESS;
}