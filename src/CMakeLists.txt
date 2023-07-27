cmake_minimum_required(VERSION 3.25)

SET(CMAKE_TOOLCHAIN_FILE "/Users/Serey/.clion-vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
project(ChatServer VERSION 0.1)

find_path(LIB_PATH lib)
link_directories(${LIB_PATH}/lib)
add_executable(ChatServer main.cpp )
target_include_directories(ChatServer PUBLIC ${MY_INCLUDE_DIR})
find_package(libuv CONFIG REQUIRED)
target_link_libraries(ChatServer PRIVATE $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(ChatServer PRIVATE nlohmann_json::nlohmann_json)
find_package(ZLIB REQUIRED)
target_link_libraries(ChatServer PRIVATE ZLIB::ZLIB)
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
target_include_directories(ChatServer PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE uSockets)


