/*
 * This file is part of the Gryphon distribution (https://github.com/zlToxicNetherlz/gryphon).
 * Copyright (c) 2020 Abraham M. Lora (Toxic#2381).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _WEBSOCKETPP_CPP11_THREAD_

#include "splash.hpp"

#include "yaml-cpp/yaml.h"
#include "sleepy_discord/websocketpp_websocket.h"

#include "spdlog/spdlog.h"
#include "deps/simpleson/json.h"

using namespace std;
YAML::Node config;

class GryphonBot : public SleepyDiscord::DiscordClient {
public:

    using SleepyDiscord::DiscordClient::DiscordClient;

    void onReady(std::string* jsonMessage) override {
        spdlog::info("Gryphon has been summoned! Information:");
        json::jobject result = json::jobject::parse(*jsonMessage);
        std::string gdata = (std::string) result.get("v");
        spdlog::info("Data Version: " + gdata);
    }

    void onMessage(SleepyDiscord::Message message) override {

        // validate devid
        if(!(message.author.ID.string() == config["devid"].as<std::string>())) {
            return;
        }

        // help command
        if (message.startsWith("~help")) {
            sendMessage(message.channelID, "**Gryphon Commands:**");
            sendMessage(message.channelID, "**$** `~help` - Show all commands.");
            sendMessage(message.channelID, "**$** `~shutdown` - Shutdown gryphon.");
            sendMessage(message.channelID, "**$** `~say` - Say something.");
            sendMessage(message.channelID, "**$** `~id` - Shows the dev id.");
            sendMessage(message.channelID, "**$** `~test` - Test purpose command.");
            sendMessage(message.channelID, "**$** `~pyrun` - Python runner.");
        }

        // help command
        if (message.startsWith("~id")) {
            sendMessage(message.channelID, "**Your dev ID:** " + config["devid"].as<std::string>());
        }

        // say command
        if (message.startsWith("~say")) {
            string original = message.content;
            string tosay = original.substr(4, original.size());
            sendMessage(message.channelID, tosay);
        }

        // pyrun command
        if (message.startsWith("~pyrun")) {
            sendMessage(message.channelID, "Soon! (WIP)");
        }

        // test command
        if (message.startsWith("~test")) {
            sendMessage(message.channelID, "Pong!");
        }

        // shutdown command (kill gryphon)
        if (message.startsWith("~shutdown")) {
            quit();
        }

    }

};

void launch_splash() {
    spdlog::info("");
    spdlog::info("                                      ______");
    spdlog::info("                           ______,---'__,---'");
    spdlog::info("                       _,-'---_---__,---'");
    spdlog::info("                /_    (,  ---____',");
    spdlog::info("               /  ',,   `, ,-'");
    spdlog::info("              ;/)   ,',,_/,'");
    spdlog::info("              | /\\   ,.'//\\");
    spdlog::info("              `-` \\ ,,'    `.");
    spdlog::info("                   `',   ,-- `.");
    spdlog::info("                   '/ / |      `,         _");
    spdlog::info("                   //'',.\\_    .\\\\      ,{==>-");
    spdlog::info("                __//   __;_`-  \\ `;.__,;'");
    spdlog::info("              ((,--,) (((,------;  `--' jv");
    spdlog::info("              ```  '   ```");
    spdlog::info("");
    spdlog::info("       GRYPHON DEV BOT - v1.05 - AUTHOR: Toxic#2381");
    spdlog::info("");
}

int main() {

    launch_splash();

    config = YAML::LoadFile("../config.yaml");

    if (!config["token"]) {
        spdlog::error("Please enter a token in the config.yaml");
        return -1;
    }

    spdlog::info("Token loaded!");

    // The token was loaded
    // so lets start the client.

    GryphonBot client(config["token"].as<std::string>(), 2);
    client.run(); // run the client

    spdlog::info("Gryphon-Bot loaded!");

}

