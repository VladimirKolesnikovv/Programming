#include <fstream>
#include <iostream>
#include <cpp_httplib/httplib.h>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace httplib;
json jax;
void gen_response(const Request& req, Response& ress) {
    std::string str;
    int unixtime = 0, mix = 0, dan = 0, uno = 0;
    json j, j2;
    std::ifstream l("weathernow.html");
    Client cli2("http://worldtimeapi.org");
    auto res2 = cli2.Get("/api/timezone/Europe/Simferopol");
    if (res2) {
        if (res2->status == 200) {
            j2 = json::parse(res2->body);
            unixtime = j2["unixtime"].get<int>();

        }
        else {
            std::cout << "Status code: " << res2->status << std::endl;
        }
    }
    else {
        auto err2 = res2.error();
        std::cout << "Error code: " << err2 << std::endl;
    }
    Client cli("http://api.openweathermap.org");
    auto res = cli.Get("/data/2.5/onecall?lat=44.57&lon=34.6&lang=ru&exclude=daily&units=metric&appid=0d58c50a9d9b684efce1459b5c0481b8");
    if (res) {
        if (res->status == 200) {
            j = json::parse(res->body);
            mix = j["hourly"][j["hourly"].size() - 1]["dt"].get<int>();
            for (int i = j["hourly"].size(); i > 0; --i) {

                for (int p = 0; p < j["hourly"].size(); p++) {
                    if (mix > unixtime and j["hourly"][p]["dt"] <= mix) {
                        dan = j["hourly"][p]["dt"];
                        mix = dan;
                        uno = p;
                    }
                }

            }

        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }
    jax["description"] = j["hourly"][uno]["weather"][0]["description"];
    jax["temp"] = std::to_string(j["hourly"][uno]["temp"].get<int>());
    std::getline(l, str, '\0');
    while (str.find("{hourly[i].temp}") != std::string::npos)
        str.replace(str.find("{hourly[i].temp}"), 16, std::to_string(j["hourly"][uno]["temp"].get<int>()));
    str.replace(str.find("{hourly[i].weather[0].description}"), 34, j["hourly"][uno]["weather"][0]["description"]);
    str.replace(str.find("{hourly[i].weather[0].icon}"), 27, j["hourly"][uno]["weather"][0]["icon"]);
    ress.set_content(str, "text/html");
}
void gen_raw(const Request& req, Response& ress) {
    Client("http://localhost:3000").Get("/");
    ress.set_content(jax.dump(4), "text/json");
}
int main() {
    Server svr;
    svr.Get("/raw", gen_raw);
    svr.Get("/", gen_response);
    std::cout << "Start server... OK\n";
    svr.listen("localhost", 3000);
}