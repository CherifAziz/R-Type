/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#include "UdpServerSystem.hpp"

namespace rtype {

    //UDPCLIENT SIDE

    UdpClient::UdpClient(udp::endpoint endpoint, udp::socket &socket) : _endpoint(endpoint), _serverSocket(socket)
    {
        std::cout << "UdpClient Added" << std::endl;
    }

    UdpClient::~UdpClient() 
    {
        std::cout << "UdpClient removed" << std::endl;
    }

    void UdpClient::sendDataToClient(Serialize::Data data)
    {
        std::cout << "Sending data to client" << std::endl;
        data.printData();
        std::string data_to_send = Serialize::serialize<Serialize::Data>(data);
        this->_serverSocket.async_send_to(boost::asio::buffer(data_to_send), this->_endpoint,
                            boost::bind(&UdpClient::handler_send, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    udp::endpoint &UdpClient::getEndpoint()
    {
        return this->_endpoint;
    }

    boost::uuids::uuid &UdpClient::getUuid() 
    {
        return this->_uuid;
    }

    void UdpClient::setUuid(boost::uuids::uuid uuid) {
        this->_uuid = uuid;
    }

    entity_t &UdpClient::getEntity() {
        return this->_entity;
    }

    void UdpClient::setEntity(entity_t entity) {
        this->_entity = entity;
    }

    void UdpClient::handler_send(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (error) {
            std::cout << "Error: " << error.message() << std::endl;
        } else {
            std::cout << "Sent data" << std::endl;
        }
    }

    void UdpClient::addToListOfCommands(Serialize::Data &data) 
    {
        this->_listOfCommands.push(data);
    }

    std::optional<Serialize::Data> UdpClient::getCommand() 
    {
        try {
            if (this->_listOfCommands.empty())
                return std::nullopt;
            Serialize::Data data = this->_listOfCommands.front();
            this->_listOfCommands.pop();
            return data;
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    //CLIENT MANAGER SIDE

    ClientManager::ClientManager()
    {
    }
    
    ClientManager::~ClientManager()
    {
    }

    void ClientManager::addClient(udp::endpoint endpoint,  udp::socket &socket) 
    {
        this->_clients[endpoint] = std::make_unique<UdpClient>(endpoint, socket);
    }

    void ClientManager::removeClient(udp::endpoint endpoint) 
    {
        if (this->_clients.find(endpoint) != this->_clients.end())
            this->_clients.erase(endpoint);
    }

    std::optional<UdpClient * const> ClientManager::getClient(udp::endpoint endpoint) 
    {
        if (this->_clients.find(endpoint) == this->_clients.end())
            return std::nullopt;
        else
            return this->_clients[endpoint].get();
    }

    void ClientManager::sendToEachClient(Serialize::Data data) 
    {
        for (auto &client : this->_clients) {
            client.second->sendDataToClient(data);
        }
    }

    std::map<udp::endpoint, std::unique_ptr<UdpClient>> &ClientManager::getClients()
    {
        return this->_clients;
    }

    //UDP SERVER SYSTEM SIDE


    UdpServerSystem::UdpServerSystem(boost::asio::io_service &io_service, int port, std::shared_ptr<Services::IService> services) : AUdpServerSystem("UdpServer"), _service(services), _socker(io_service, udp::endpoint(boost::asio::ip::udp::v4(), port)), _nullscene(0), _nullstring("") 
    {
        std::cout << "UdpServer Created" << std::endl;
        this->start_receive();
    }

    UdpServerSystem::~UdpServerSystem()
    {
    }

    void UdpServerSystem::start_receive()
    {
        this->_socker.async_receive_from(boost::asio::buffer(this->_data),
                            this->_remote_endpoint,
                            boost::bind(&UdpServerSystem::handler_received, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
    }

    void UdpServerSystem::send_data(int s_id, std::string text, boost::asio::ip::udp::endpoint endpoint)
    {
        Serialize::Data info = Serialize::createData<Serialize::Data>(s_id, text);
        if (this->_clients.getClient(endpoint) != std::nullopt)
            this->_clients.getClient(endpoint).value()->sendDataToClient(info);
    }

    const std::string &UdpServerSystem::getName() const
    { 
        return this->_nullstring; 
    }

    bool UdpServerSystem::isGameStillPlaying() 
    { 
        return true; 
    }

    const size_t &UdpServerSystem::getCurrentScene() const 
    { 
        return this->_nullscene; 
    }

    void UdpServerSystem::update(std::shared_ptr<IScene> &scene) 
    {
        for (auto &client : this->_clients.getClients()) {
            std::optional<Serialize::Data> data = client.second->getCommand();
            if (data != std::nullopt) {
                this->_service->callService(client.second->getEndpoint(), this->_clients, data.value(), *scene);
                if (data.value().s_id == Services::Command::DISCONNECTED)
                    return;
            }
        }
    }

    std::pair<size_t, size_t> UdpServerSystem::getWindowWSize() const
    {
        return std::make_pair(0, 0);
    }

    void UdpServerSystem::handler_received(const boost::system::error_code &error, std::size_t size) 
    {
        std::cout << "On Received" << std::endl;
        if (!error && error != boost::asio::error::eof && size > 0) {
            if (this->_clients.getClient(this->_remote_endpoint) == std::nullopt)
                this->_clients.addClient(this->_remote_endpoint, this->_socker);
            if (size >= sizeof(Serialize::Data)) {
                std::cout << "Received data" << std::endl;
                Serialize::Data info = Serialize::deserialize<Serialize::Data>(std::string(this->_data.data(), size), size);
                if (this->_clients.getClient(this->_remote_endpoint) != std::nullopt)
                    this->_clients.getClient(this->_remote_endpoint).value()->addToListOfCommands(info);
                else
                    std::cout << "Client not found" << std::endl;
            }
        }
        if (error == boost::asio::error::eof) {
            std::cout << "Client disconnected: " << this->_remote_endpoint << std::endl;
            this->_clients.removeClient(this->_remote_endpoint);
        }
        if (error) {
            std::cout << "Handler_recieved -> Error: " << error.message() << std::endl;
        }
        this->_socker.async_receive_from(boost::asio::buffer(this->_data),
                                        this->_remote_endpoint,
                                        boost::bind(&UdpServerSystem::handler_received, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
    }

    void UdpServerSystem::handler_send(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/)
    {
        std::cout << "sent to client" << std::endl;
    }

}