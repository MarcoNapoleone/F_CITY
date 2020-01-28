cmake_minimum_required(VERSION 3.10)
project(F_CITY)

set(CMAKE_CXX_STANDARD 14)
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/")

add_executable(F_CITY main.cpp
        User.cpp User.h
        Bank.cpp Bank.h
        Database.cpp Database.h
        TimeInfo.cpp TimeInfo.h
        Ticket.cpp Ticket.h)

include_directories(/usr/local/include/mysql-connector-cpp/include) #using cpp compiler so the path is for mysql connector in the WSL
target_link_libraries(F_CITY mysqlcppconn)
