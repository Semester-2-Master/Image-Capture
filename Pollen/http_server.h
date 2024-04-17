#include <WebServer.h>

class PollenServer {
  public:
    void init();
    WebServer* getServer();
    void printDirectory();
    void printMessage();
};
