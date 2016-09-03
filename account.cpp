#include "account.h"

using namespace std;

Account::Account(const string& username, TxtTemp * file) {

    this->username = username;
    this->uuid = "null";
    this->file = file;
}

Account::~Account() {


}

string Account::getUserName() const {

    return username;
}

string Account::getUuid() const {

    return uuid;
}

void Account::writeData() {

    file->writeLine("User: \"" + username + "\" , id: \"" + uuid + "\"");
}

void Account::setUserName(const string& username) {

    this->username = username;
}

void Account::setUuid(const string& uuid) {

    this->uuid = uuid;
}

Account * Account::readLastData(TxtTemp * file) {

    string s = file->lastLine();

    if (s.empty())
        return 0;

    int pos0 = s.find_first_of('\"') + 1;

    int pos = s.find_first_of('\"', pos0);

    string username = s.substr(pos0, pos - pos0);

    Account * out = new Account(username, file);

    pos0 = s.find_first_of('\"', pos + 1) + 1;

    pos = s.find_first_of('\"', pos0);

    string uuid = s.substr(pos0, pos - pos0);

    out->setUuid(uuid);

    return out;
}
