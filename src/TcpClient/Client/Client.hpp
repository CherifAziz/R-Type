/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/serialization.hpp>

    using namespace boost::placeholders;
    using boost::asio::ip::tcp;

    class Payload {
        private:
            std::string _test;
            int _id;

        public:
            Payload(std::string test, int id): _test(test), _id(id) {};
            ~Payload() = default;
    };

    struct Data_t {
        int s_id;
        std::string test;
        template<typename Ar> void serialize(Ar& ar, unsigned) { ar & s_id & test; }
    };

    class Client {
        public:
            Client(boost::asio::io_context &ioc, std::string ip, int port);
            void start_receive();
            void sendDataToServer(std::string data);
            ~Client();

        protected:
        private:
            void onReceive(const boost::system::error_code& err, std::size_t size);
            void onSent(const boost::system::error_code& err);
            tcp::socket _socket;
            std::string _message;
            std::array<char, 1024> data_;
    };

#endif /* !CLIENT_HPP_ */
