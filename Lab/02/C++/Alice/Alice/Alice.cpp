#include <fstream>
#include <iostream>
#include <cpp_httplib/httplib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <iomanip>
using json = nlohmann::json;
using namespace httplib;

void gen_webhook(const Request& req, Response& res) {
    std::string str;
    std::ifstream l("index.html");
    std::getline(l, str, '\0');
    res.set_content(str, "text/html");
}

void posn_webhook(const Request& req, Response& res) {

    std::string webstring = R"(
<div class="form-row align-items-center">
    <div class="col">
      <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
 
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div> 
<!-{webhooks_list}->)";
    std::string webhooks = R"({Webhook URL})";
    std::string webcomment = R"(<!-{webhooks_list}->)";

    std::ifstream dl("config.json");

    if (!dl.is_open()) {
        json j;
        j["webhooks"] = json::array();
        std::ofstream dl("config.json");
        dl << std::setw(4) << j << std::endl;
    }



    std::string str;
    std::ifstream l("index.html");
    std::getline(l, str, '\0');

    if (req.has_param("set")) {

        std::string val = req.get_param_value("set");

        json j;
        std::ifstream dl("config.json");
        dl >> j;
        j["webhooks"].push_back(val);
        std::ofstream o("config.json");
        o << std::setw(4) << j << std::endl;


        str.replace(str.find(webcomment), webcomment.size(), webstring);
        while (str.find(webhooks) != std::string::npos)
            str.replace(str.find(webhooks), webhooks.size(), val);
        std::ofstream od("index.html");
        od << std::setw(4) << str << std::endl;
    }
    if (req.has_param("del")) {

        std::string val = req.get_param_value("del");

        json j;
        std::ifstream dl("config.json");
        dl >> j;
        for (int i = 0; i < j["webhooks"].size(); i++) {
            if (j["webhooks"][i].get<std::string>() == val) {
                j["webhooks"].erase(j["webhooks"].begin() + i);
            }
        }
        std::ofstream o("config.json");
        o << std::setw(4) << j << std::endl;

        std::string empty = "";
        std::string webstringdel = R"(
<div class="form-row align-items-center">
    <div class="col">
      <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
 
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div> 
)";

        while (webstringdel.find(webhooks) != std::string::npos)
            webstringdel.replace(webstringdel.find(webhooks), webhooks.size(), val);
        str.replace(str.find(webstringdel), webstringdel.size(), empty);

        std::ofstream od("index.html");
        od << std::setw(4) << str << std::endl;
    }

}

void gen_response(const Request& req, Response& res) {
    json j;
    json jxon;
    j = json::parse(req.body.c_str());
    if (j["request"]["original_utterance"].get<std::string>() != "ping" && j["request"]["original_utterance"].get<std::string>() != "пинг") {
        if (true) {
            j["state"]["session"].push_back({ "name","null" });
            j["state"]["session"].push_back({ "thelp","null" });
            j["state"]["session"].push_back({ "value",0 });
        }
        if ((j["state"]["session"]["name"].get<std::string>() == "null") || (j["state"]["session"]["name"].get<std::string>() == "menu") && (j["request"]["command"].get<std::string>() != "помощь")) {
            std::ifstream l("response.json");
            jxon = json::parse(l);
        }
        if ((j["request"]["command"].get<std::string>() == "помощь" || j["state"]["session"]["name"].get<std::string>() == "help") && j["state"]["session"]["thelp"].get<std::string>() != "bin") {
            std::ifstream l1("response1.json");
            jxon = json::parse(l1);
        }
        if (j["state"]["session"]["thelp"].get<std::string>() == "bin") {
            std::ifstream l2("trashb.json");
            jxon = json::parse(l2);
        }
        if (j["session"]["new"].get<bool>()) {
            jxon["session_state"].push_back({ "name","menu" });
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if ((j["request"]["command"].get<std::string>() != "добавить" && j["request"]["nlu"]["tokens"][0].get<std::string>() == "добавить" && j["request"]["nlu"]["tokens"][2].get<std::string>() == "корзину") && j["state"]["session"]["thelp"].get<std::string>() != "bin") {
            jxon["session_state"].push_back({ "name","menu" });
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);
            rev["check"].push_back({ {"item",j["request"]["nlu"]["tokens"][3] },{"price",j["request"]["nlu"]["tokens"][4]} });
            std::ofstream o_1("buy.json");
            o_1 << std::setw(4) << rev << std::endl;
            jxon["response"]["text"] = "ОК";
            jxon["response"]["tts"] = "ОК";
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() != "удалить" && j["request"]["nlu"]["tokens"][0].get<std::string>() == "удалить" && j["request"]["nlu"]["tokens"][2].get<std::string>() == "корзины" && j["state"]["session"]["thelp"].get<std::string>() != "bin" && j["state"]["session"]["name"].get<std::string>() != "help") {
            jxon["session_state"].push_back({ "name","menu" });
            int c = 0;
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);
            for (int i = 0; i < rev["check"].size(); i++) {
                if (rev["check"][i]["item"].get<std::string>() == j["request"]["nlu"]["tokens"][3].get<std::string>()) {
                    rev["check"].erase(rev["check"].begin() + i);
                    c = 1;
                }
            }
            std::ofstream o_1("buy.json");
            o_1 << std::setw(4) << rev << std::endl;
            if (c == 1) {
                jxon["response"]["text"] = "ОК";
                jxon["response"]["tts"] = "ОК";
            }
            else {
                jxon["response"]["text"] = "Данного товара нет";
                jxon["response"]["tts"] = "Данного товара нет";
            }
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() == "что в корзине" && j["state"]["session"]["thelp"].get<std::string>() != "bin" && j["state"]["session"]["name"].get<std::string>() != "help") {
            jxon["session_state"].push_back({ "name","menu" });
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);
            std::string item;
            if (rev["check"][0].contains("item")) {
                for (int i = 0; i < rev["check"].size(); i++) {
                    item += rev["check"][i]["item"];
                    item += " ";
                    item += rev["check"][i]["price"];
                    item += "\n";

                }
                jxon["response"]["text"] = item;
                jxon["response"]["tts"] = item;
            }
            else {
                jxon["response"]["text"] = "Корзина пуста.";
                jxon["response"]["tts"] = "Корзина пуста.";
            }
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() == "очистить корзину" && j["state"]["session"]["thelp"].get<std::string>() != "bin" && j["state"]["session"]["name"].get<std::string>() != "help") {
            jxon["session_state"].push_back({ "name","menu" });
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);

            for (int i = 0; i < rev["check"].size();) {
                rev["check"].erase(rev["check"].begin() + i);
            }

            std::ofstream o_1("buy.json");
            o_1 << std::setw(4) << rev << std::endl;
            jxon["response"]["text"] = "Корзина пуста.";
            jxon["response"]["tts"] = "Корзина пуста.";
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() == "сумма" && j["state"]["session"]["thelp"].get<std::string>() != "bin" && j["state"]["session"]["name"].get<std::string>() != "help") {
            jxon["session_state"].push_back({ "name","menu" });
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);
            int sum = 0;
            if (rev["check"][0].contains("price")) {
                for (int i = 0; i < rev["check"].size(); i++) {
                    sum = sum + std::stoi(rev["check"][i]["price"].get<std::string>());
                }
            }
            jxon["response"]["text"] = sum;
            jxon["response"]["tts"] = sum;
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() == "покупка завершена" && j["state"]["session"]["thelp"].get<std::string>() != "bin" && j["state"]["session"]["name"].get<std::string>() != "help") {
            std::ifstream o_("buy.json");
            json rev = json::parse(o_);
            if (rev["check"][0].contains("item")) {
                if (j["session"]["user"].contains("user_id")) {
                    rev["user_id"] = j["session"]["user"]["user_id"];
                }
                else {
                    rev["user_id"] = "anonymous";
                }
                std::ifstream l("config.json");

                if (l.is_open()) {
                    int dil;
                    std::string str, str2;
                    json j = json::parse(l);
                    std::string mayk = "http://";
                    for (int i = 0; i < j["webhooks"].size(); i++) {
                        str = j["webhooks"][i];
                        if (str.find('/', mayk.size()) != std::string::npos) {
                            dil = str.find('/', mayk.size());
                        }
                        else {
                            str += "/";
                            dil = str.find('/', mayk.size());
                        }
                        str2 = str.substr(0, dil);
                        Client cli(str2.c_str());
                        str2 = str.substr(dil, -1);
                        cli.Post(str2.c_str(), rev.dump(4), "application/json");
                        for (int i = 0; i < rev["check"].size();) {
                            rev["check"].erase(rev["check"].begin() + i);
                        }
                        std::ofstream o_O("buy.json");
                        o_O << std::setw(4) << rev << std::endl;
                    }
                }


            }
            jxon["response"]["text"] = "Заходите ещё";
            jxon["response"]["tts"] = "Заходите ещё";
            jxon["response"]["end_session"] = true;
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"].erase("tts");
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if ((j["request"]["command"].get<std::string>() == "молчать") && (j["state"]["session"]["name"].get<std::string>() == "menu")) {
            jxon["response"]["tts"] = "sil <[500]>";
            jxon["session_state"].push_back({ "value",5 });
            jxon["session_state"].push_back({ "name","menu" });
            jxon["response"]["text"] = "Молчу, молчу";
            jxon["response"]["buttons"][1]["title"] = "Говорить";
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if ((j["request"]["command"].get<std::string>() == "говорить") && (j["state"]["session"]["name"].get<std::string>() == "menu")) {
            jxon["session_state"].push_back({ "value",10 });
            jxon["session_state"].push_back({ "name","menu" });
            jxon["response"]["text"] = "Хорошо";
            jxon["response"]["tts"] = "Хорошо";
            jxon["response"]["buttons"][1]["title"] = "Молчать";
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else if (j["request"]["command"].get<std::string>() == "помощь" || j["state"]["session"]["name"].get<std::string>() == "help") {
            int c = 0;
            jxon["session_state"].push_back({ "name","help" });
            if (j["request"]["command"].get<std::string>() == "говорить" && j["state"]["session"]["thelp"] != "bin") {
                jxon["response"]["text"] = "Эта команда заставляет Алису озвучивать все команды вслух, чтобы включить команду выйдите из справки.\nО чём ещё рассказать?";
                jxon["response"]["tts"] = "Эта команда заставляет Алису озвучивать все команды вслух, сейчас эта команда работает. О чём ещё рассказать?";
                c = 1;
            }
            if (j["request"]["command"].get<std::string>() == "молчать" && j["state"]["session"]["thelp"] != "bin") {
                jxon["response"]["text"] = "Эта команда заставляет Алису замолчать , пока не активирована команда <Говорить>, чтобы включить команду выйдите из справки.\nО чём ещё рассказать?";
                jxon["response"]["tts"] = "Эта команда заставляет Алису замолчать , пока не активирована команда Говорить, чтобы включить команду выйдите из справки. О чём ещё рассказать?";
                c = 1;
            }
            if (j["request"]["command"].get<std::string>() == "корзина" && j["state"]["session"]["thelp"] != "bin") {
                std::ifstream l2("trashb.json");
                jxon = json::parse(l2);
                jxon["session_state"].push_back({ "thelp","bin" });
                jxon["session_state"].push_back({ "name","help" });
                c = 1;
            }
            if (j["state"]["session"]["thelp"].get<std::string>() == "bin") {
                jxon["session_state"].push_back({ "thelp","bin" });
                if (j["request"]["command"].get<std::string>() == "очистить корзину") {
                    jxon["response"]["text"] = "Корзина очищается\nДействие подтверждается фразой : Корзина пуста ";
                    jxon["response"]["tts"] = "Корзина очищается. Действие подтверждается фразой. Корзина пуста ";
                    c = 1;
                }
                if (j["request"]["command"].get<std::string>() == "добавить в корзину") {
                    jxon["response"]["text"] = "В корзину добавляется новый товар\n Действие подтверждается фразой : ОК ";
                    jxon["response"]["tts"] = "Я добавляю в корзину  новый товар. Ваше действие подтверждается фразой.  ОК";
                    c = 1;
                }
                if (j["request"]["command"].get<std::string>() == "удалить из корзины") {
                    jxon["response"]["text"] = "Пользователь должен назвать товар точно так же как и при добавлении. \n Если товара нет в корзине: Сообщает пользователю, что данного товара нет ";
                    jxon["response"]["tts"] = "Пользователь должен назвать товар точно так же как и при добавлении. Если товара нет в корзине, то я сообщаю пользователю, что данного товара нет ";
                    c = 1;
                }
                if (j["request"]["command"].get<std::string>() == "что в корзине") {
                    jxon["response"]["text"] = "Если в корзине нет товаров:\n Сообщает пользователю, что корзина пуста \nЕсли в корзине есть товары :\nПеречисляет все товары в произвольном порядке в формате : Название и цена.";
                    jxon["response"]["tts"] = "Если в корзине нет товаров. Сообщает пользователю, что корзина пуста. Если в корзине есть товары. Перечисляет все товары в произвольном порядке в формате. Название и цена.";
                    c = 1;
                }
                if (j["request"]["command"].get<std::string>() == "сумма") {
                    jxon["response"]["text"] = "Определяет суммарную стоимость товаров в корзине\n.Сообщает стоимость пользователю.";
                    jxon["response"]["tts"] = "Данная команда определяет суммарную стоимость товаров в корзине. Я сообщаю стоимость пользователю.";
                    c = 1;
                }
                if (j["request"]["command"].get<std::string>() == "покупка завершена") {
                    jxon["response"]["text"] = "Если в корзине есть хоть один товар, отправляет всем подписавшимся (всем webhook-ам) post-запрос. \n Действие подтверждается фразой: Заходите ещё \n Сессия завершается";
                    jxon["response"]["tts"] = "Если в корзине есть хоть один товар, отправляю всем подписавшимся (всем webhook-ам) post-запрос. \n Действие подтверждаю фразой: Заходите ещё \n Сессия завершается ";
                    c = 1;
                }
            }
            if (j["request"]["command"].get<std::string>() == "выйти") {
                std::ifstream l("response.json");
                jxon = json::parse(l);
                jxon["response"]["text"] = "Обращайся ещё";
                jxon["response"]["tts"] = "Обращайся ещё";
                jxon["session_state"].push_back({ "name","menu" });
                c = 1;
            }
            if (j["state"]["session"]["value"].get<int>() == 5) {
                if (j["request"]["command"].get<std::string>() == "выйти") {
                    jxon["response"]["buttons"][1]["title"] = "Говорить";
                }
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                jxon["session_state"].push_back({ "value",10 });
            }
            if (c == 0 && j["request"]["command"].get<std::string>() != "помощь") {
                jxon["response"]["text"] = "Неизвестная команда";
                jxon["response"]["tts"] = "Неизвестная команда";
            }
            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
        else {
            jxon["response"]["text"] = "Неизвестная команда.";
            if (j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["tts"] = "sil <[500]>";
                jxon["session_state"].push_back({ "value",5 });
            }
            else {
                if (j["state"]["session"]["name"].get<std::string>() == "menu") {
                    jxon["session_state"].push_back({ "name","menu" });
                }
                jxon["response"]["tts"] = "Неизвестная команда.";
                jxon["session_state"].push_back({ "value",10 });
            }
            if (j["state"]["session"]["name"].get<std::string>() == "menu" && j["state"]["session"]["value"].get<int>() == 5) {
                jxon["response"]["buttons"][1]["title"] = "Говорить";
                jxon["session_state"].push_back({ "name","menu" });
            }

            res.set_content(jxon.dump(4), "text/json; charset=UTF-8");
        }
    }
}


int main() {
    Server svr;
    svr.Get("/webhooks", gen_webhook);
    svr.Post("/webhooks", posn_webhook);
    svr.Post("/", gen_response);
    svr.listen("localhost", 1234);
}