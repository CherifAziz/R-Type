/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#ifndef CLIENTSERVER_HPP_
    #define CLIENTSERVER_HPP_

    #include <ctime>
    #include <iostream>
    #include <string>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>
    #include <boost/asio.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/serialization.hpp>

    using boost::asio::ip::tcp;
    using namespace boost::placeholders;

    struct Data_t {
        int s_id;
        std::string test;
        template<typename Ar> void serialize(Ar& ar, unsigned) { ar & s_id & test; }
    };

    class ClientServer : public std::enable_shared_from_this<ClientServer> {
        public:
            ClientServer(boost::asio::io_context& io_context);
            tcp::socket &getSocket();
            void start();
            void start_read();
            ~ClientServer();

        protected:
        private:
            void onRead(const boost::system::error_code& err, size_t size);
            void onWrite(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);
            tcp::socket _socket;
            std::array<char, 1024> data_;
};

#endif /* !CLIENTSERVER_HPP_ */
