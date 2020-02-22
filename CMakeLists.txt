cmake_minimum_required(VERSION 3.2)
project(F_CITY)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/")

add_executable(F_CITY main.cpp
        User.cpp User.h
        Payment/Bank.cpp Payment/Bank.h
        auxiliary-lib/Database.cpp auxiliary-lib/Database.h
        auxiliary-lib/TimeInfo.cpp auxiliary-lib/TimeInfo.h
        Transport/Ticket.cpp Transport/Ticket.h
        Payment/Shop.cpp Payment/Shop.h
        Payment/Item.cpp Payment/Item.h
        Hardware/Hardware.cpp Hardware/Hardware.h
        Hardware/wiringPi.h)

include_directories(/usr/local/include/mysql-connector-cpp/include) #using cpp compiler so the path is for mysql connector in the WSL
target_link_libraries(F_CITY mysqlcppconn)
target_link_libraries(F_CITY stdc++)
target_link_libraries(F_CITY wiringPiDev)
target_link_libraries(F_CITY wiringPi)





