#include <direct.h>
#include "temp.h"

using namespace std;

Temp::Temp(const string& filename, const string& filepath) {

    this->filename = filename;

    if (filepath.size() == 0) {

        char buffer[2048];
        path = _getcwd(buffer, 2048);
        path += '/';

    } else if (filepath[filepath.size() - 1] == '/') {

        path = filepath;

    } else {

        path = filepath + '/';
    }
}

Temp::~Temp() {

    if (reader.is_open()) {

        reader.close();
    }

    if (writer.is_open()) {

        writer.close();
    }
}

string Temp::getPath() const {

    return path;
}

string Temp::getFileName() const {

    return filename;
}

void Temp::remove() {

    std::remove((path + filename).c_str());
}

