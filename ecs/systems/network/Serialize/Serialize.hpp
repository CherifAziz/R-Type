/*
** EPITECH PROJECT, 2023
** Serialize.hpp
** File description:
** Serialize
*/

#ifndef SERIALIZE_HPP_
    #define SERIALIZE_HPP_
    #include <iostream>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>
    #include <boost/unordered_map.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/serialization.hpp>

    namespace Serialize {
        struct Data {
            int size;
            std::string _data;
            template<typename Ar> void serialize(Ar& ar, unsigned) {
                ar & size & _data;
            }
        };

        template<typename T>
        std::string serialize(T &data) {
            std::ostringstream os;
            boost::archive::binary_oarchive archive(os);
            archive << data;
            return os.str();
        }

        template<typename T>
        T deserialize(std::string data, size_t size) {
            T received_data;
            std::stringstream archive_stream;
            archive_stream.write(data.data(), size);
            boost::archive::binary_iarchive archive(archive_stream);
            archive >> received_data;
            return received_data;
        }
    };
#endif /* !SERIALIZE_HPP_ */
