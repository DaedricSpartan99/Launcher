#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "temp.h"
#include <string>

using namespace std;

class Account {

public:

    Account(const string& username, TxtTemp * file);
    ~Account();

    string getUserName() const;
    string getUuid() const ;

    void requestUuid();
    void writeData();

    void setUserName(const string& username);
    void setUuid(const string& uuid);

    static Account * readLastData(TxtTemp * file);

private:

    string username;
    string uuid;
    TxtTemp * file;
};

#endif // ACCOUNT_H
