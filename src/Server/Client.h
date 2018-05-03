//
// Created by silvman on 30.04.18.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H

#include <SFML/Network.hpp>
#include <utility>
#include "Entities.h"


namespace mp {
    
    class Client {
    private:
        struct msg {
            static constexpr const char *waiting_connection = "[client:process] connecting to server";
            static constexpr const char *error_sending_events = "[client:fail] server didn't accept events";
            static constexpr const char *error_accepting_events = "[client:fail] can't accept events";
            static constexpr const char *connected = "[client:success] connected to server";
        };

        sf::TcpSocket       socket_;
        sf::SocketSelector  selector_;
        int                 player_id_;
        bool                connected_;

    public:
        explicit Client(const std::string &ip, unsigned short port = 55001);


        /*
         * Эти два метода кидаются исключениями std::logic_error в случаях,
         * когда с соединением что-то не так
         */
        bool askEvents();
        bool sendEvents();

        bool isConnected();

        // эвенты
        std::vector<mp::Event> incoming;
        std::vector<mp::Event> outcoming;

    };

}


#endif //TOWERDEFENSE_CLIENT_H