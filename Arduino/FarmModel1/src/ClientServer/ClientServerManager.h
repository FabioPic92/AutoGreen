#include "Server.h"
#include "Client.h"

class ClientServerManager{
    private:
        UnoR4::Server *server;
        UnoR4::Client *client;

    public:
        ClientServerManager(){
              server = new UnoR4::Server(WL_IDLE_STATUS);
        }

        int Connection(){
            if(server->Connection() == 0){
              server->printWifiStatus();
            } else {
              Serial.println("Error Connection");
              return -1;
            }
            client = new UnoR4::Client(server->getServer());
            client->InitClient();
            return 0;
        }

        bool isWifiConnected() {
            return server && server->isConnected();
        }
        //Aggiungere check Client
        //Funzione da mettere in loop
        void Refresh(){
                client->InitClient();
                client->Connection();
        }

};

