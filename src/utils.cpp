#include "utils.h"

namespace utils {

    namespace randomizer{

        int randomInt(int min, int max){
            static std::mt19937 engine{};
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(engine);
        }

        void randomIP(std::string& src){
            src.clear();
            src = std::to_string(randomInt(1, 255))
                  + "."
                  + std::to_string(randomInt(1, 255))
                  + "."
                  +  std::to_string(randomInt(1, 255))
                  + "."
                  + std::to_string(randomInt(1, 255));
        }

        int randomPort(){
            static auto init_s_port = 0;
            static int seq = 0;
            if(init_s_port == 0){
                init_s_port = 1024 + (randomInt(0, 2000));
                return init_s_port;
            }
            ++seq;
            return (seq + init_s_port) % 65536;
        }

        void randomstr(std::string& src){
            int string_length = randomInt(1, 30);
            src.clear();
            for(int i = 0; i < string_length; ++i){
                src += (static_cast<char>('0' + randomInt(0, 72)));
            }
        }

        void random_vec(std::vector<std::string> &vec, std::string &str){
            str = vec[randomizer::randomInt(0, static_cast<int>(vec.size()) -1)];
        }
    }


    namespace validator{

        bool valid_host(const std::string &host){
            struct sockaddr_in sa{};
            return static_cast<bool>(inet_pton(AF_INET, host.c_str(), &(sa.sin_addr)));
        }

        bool valid_hostname(const std::string &hostname){
            hostent *record = gethostbyname(hostname.c_str());
            return record != nullptr;
        }

        bool valid_port(const std::string &port){
            int temp = static_cast<int>(strtol(port.c_str(), nullptr, 10));
            return temp < 65535 && temp > 0;
        }
    }


    void pause(timespec time){
        nanosleep(&time, nullptr);
    }

    void set_dly(int dly, timespec *time){
        if(time){
            if((dly - 999999999) > 0){
                time->tv_sec = dly - 999999999;
                time->tv_nsec = abs(1000000000 - dly);
            }else if (dly <= 0){
                fputs("[-] delay cannot be less than 1 ns, setting to default\n", stderr);
                time->tv_nsec = 1;
                time->tv_sec = 0;
            }else{
                time->tv_nsec = dly;
                time->tv_sec = 0;
            }
        }
    }

    int to_int(const std::string& str){
        return static_cast<int>(strtol(str.c_str(), nullptr, 10));
    }

};