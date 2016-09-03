#include "temp.h"

using namespace std;

TxtTemp::TxtTemp(const string& filename, const string& path) : Temp(filename, path) {

}

TxtTemp::~TxtTemp() {


}

string TxtTemp::lastLine() {

    reader.open((path + filename).c_str(), ios::in);

    string line;

    if (reader.is_open()) {

        while (reader >> std::ws && std::getline(reader, line)) // skip empty lines
            ;

        reader.close();
    }

    return line;
}

void TxtTemp::writeLine(const string& str) {

    writer.open((path + filename).c_str(), ios::out | ios::app | ios::ate);

    if (writer.is_open()) {

        writer << str + "\n";

        writer.close();

    }
}

vector<string> TxtTemp::readLines() {

    vector<string> out;
    string tmp;

    reader.open((path + filename).c_str(), ios::in);

    if (reader.is_open()) {

        while(!getline(reader, tmp).eof()) {

            out.push_back(tmp);
        }

        reader.close();
    }

    return out;
}

void TxtTemp::clear() {

    writer.open((path + filename).c_str(), ios::out | ios::trunc);

    if (writer.is_open()) {

        writer.close();
    }
}

bool TxtTemp::exists() {

    reader.open((path + filename).c_str(), ios::in);

    if (reader.is_open()) {

        reader.close();
        return true;

    } else {

        return false;
    }
}
