#include <iostream>
#include <string>
#include "uwebsockets/App.h"
#include "nlohmann/json.hpp"
#include <map>

using json = nlohmann::json;

void processPublicMsg(json data, auto* ws)
{
    int userId = ws->getUserData()->userId;
    json payload = {
            {"command", data["command"]},
            {"text", data["text"]},
            {"userFrom", ws->getUserData()->userId}
    };
    ws->publish("public", payload.dump());
    std::cout << "User sent Public Message " << userId << "\n";
}

void processPrivateMsg(json data, auto* ws)
{
    int userId = ws->getUserData()->userId;
    json payload = {
            {"command", data["command"]},
            {"text", data["text"]},
            {"userFrom", userId}
    };
    int userTo = data["userTo"];
    ws->publish("user" + std::to_string(userTo), payload.dump());
    std::cout << "User sent Private Message " << userId << "\n";
}

void processSetName(json data, auto* ws)
{
    int userId = ws->getUserData()->userId;
    ws->getUserData()->name = data["name"];
    std::cout << "User set their name " << userId << "\n";
}

std::string processStatus(auto data, bool online)
{
    json payload = {
            {"command", "status"},
            {"userId", data->userId},
            {"name", data->name},
            {"online", online}
    };
    return payload.dump();
}

struct userData {
    int userId;
    std::string name;
};

std::map<int, userData*> onlineUsers;

int main() {
    int latestUserId = 10;
    uWS::App app = uWS::App().ws<userData>("/*", {
            .idleTimeout = 16,
            .open = [&latestUserId](auto *ws) {
                auto *data = ws->getUserData();
                data->userId = latestUserId++;
                data->name = "noname";
                std::cout << "New user connected: " << data->userId << "\n";
                ws->subscribe("public");
                ws->subscribe("user" + std::to_string(data->userId));
                ws->publish("public", processStatus(data, true));
                for (auto entry: onlineUsers) {
                    ws->send(processStatus(entry.second, true), uWS::OpCode::TEXT);
                }
                onlineUsers[data->userId] = data;
            },
            .message = [](auto *ws, std::string_view data,
                          uWS::OpCode opCode) {
                json parsedData = json::parse(data); //ToDo:chec format
                if (parsedData["command"] == "publicMsg") {
                    processPublicMsg(parsedData, ws);
                } else if (parsedData["command"] == "privateMsg") {
                    processPrivateMsg(parsedData, ws);
                } else if (parsedData["command"] == "setName") {
                    processSetName(parsedData, ws);
                    auto *data = ws->getUserData();
                    ws->publish("public", processStatus(data, true));
                }
            },
            .close = [](auto *ws, int /*code*/, std::string_view /*message*/) {
                auto *data = ws->getUserData();
                onlineUsers.erase(data->userId);
                std::cout << "User " << data->userId <<" disconnected\n";
            }
    }).listen(9001, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        } //localhost:9001
    }).run();
}
