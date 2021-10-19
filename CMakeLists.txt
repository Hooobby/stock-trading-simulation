cmake_minimum_required(VERSION 3.0)
project(Stock)

set(CMAKE_CXX_STANDARD 11)

include_directories(C:\\mysql\\include)  #include文件夹位置
link_directories(C:\\mysql\\lib) #lib文件夹位置
link_libraries(libmysql)  #lib下dll文件名

include_directories(C:\\Users\\Hobby\\anaconda3\\include)
link_libraries(C:/Users/Hobby/anaconda3/libs/python38.lib)

add_executable(Stock main.cpp stock10.h stock10.cpp database.h database.cpp client.h client.cpp)

#主要配置第一个参数为项目名
target_link_libraries(Stock libmysql)
#target_link_libraries(Stock C:/Users/Hobby/anaconda3/libs/python38.lib)