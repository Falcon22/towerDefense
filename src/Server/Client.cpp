//
// Created by silvman on 30.04.18.
//

#include <iostream>
#include "Client.h"
#include "Server.h"

bool mp::ClientMultiplayerFacade::askEvents() {
    if (connection->hasNewData()) try {
            connection->getData(incoming);
        return true;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return false;
}

bool mp::ClientMultiplayerFacade::sendEvents() {
    if (!outcoming.empty()) try {
        connection->sendData(outcoming);
        return true;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return false;
}

void mp::ClientMultiplayerFacade::connect() {
    connection->connect();

}

bool mp::ClientMultiplayerFacade::isConnected() {
    return connection->isConnected();
}

mp::ClientMultiplayerFacade::ClientMultiplayerFacade() {
    connection = std::unique_ptr<AbstractConnectionFacade>(new ClientConnectionFacade);
}




bool mp::ServerConnectionFacade::hasNewData() {
    if (selector_.wait(constants::waitTime()))
        return first_.hasNewData(selector_) || second_.hasNewData(selector_);

    return false;
}

void mp::ServerConnectionFacade::getData(std::vector<mp::Event> &to) {
    if (first_.hasNewData(selector_)) {
        try {
            first_.getEvents();
            to.insert(to.end(), first_.from_client.begin(), first_.from_client.end()); // сращиваем 2 вектора
            first_.from_client.clear(); // очищаем после получения данных
        } catch (const std::exception &e) {
            selector_.remove(first_.getSocket());
        }
    }

    if (second_.hasNewData(selector_)) {
        try {
            second_.getEvents();
            to.insert(to.end(), second_.from_client.begin(), second_.from_client.end()); // сращиваем 2 вектора
            second_.from_client.clear(); // очищаем после получения данных
        } catch (const std::exception &e) {
            selector_.remove(second_.getSocket());
        }
    }
}

void mp::ServerConnectionFacade::sendData(std::vector<mp::Event> &from) {
    for (auto &&event : from) {
        switch (event.id) {
            case 1: {
                second_.to_send.push_back(event);
                break;
            }

            case 2: {
                first_.to_send.push_back(event);
                break;
            }

            case 0: { // broadcasting
                second_.to_send.push_back(event);
                first_.to_send.push_back(event);

                break;
            }

            default:
                break;
        }
    }

    first_.sendEvents();
    second_.sendEvents();

    from.clear(); // TODO нужна проверка на отправленность
}

void mp::ServerConnectionFacade::connect() {
    // does nothing as the connection comes from the master process
}

bool mp::ServerConnectionFacade::isConnected() {
    return first_.isAvailable() && second_.isAvailable(); // грубая проверка подключения с обоими игроками
}



mp::ServerMultiplayerFacade::ServerMultiplayerFacade(mp::player &first, mp::player &second) {
    connection = std::unique_ptr<AbstractConnectionFacade>(new mp::ServerConnectionFacade(first, second));
}

bool mp::ServerMultiplayerFacade::askEvents() {
    if (connection->hasNewData()) try {
            connection->getData(incoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

bool mp::ServerMultiplayerFacade::sendEvents() {
    if (!outcoming.empty()) try {
            connection->sendData(outcoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

void mp::ServerMultiplayerFacade::connect() {
    connection->connect();
}

bool mp::ServerMultiplayerFacade::isConnected() {
    return connection->isConnected();
}

mp::AbstractMultiplayerFacade::~AbstractMultiplayerFacade() { }


