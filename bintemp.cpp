#include "temp.h"

using namespace std;

BinTemp::BinTemp(const string &filename, const string &path) : Temp(filename, path) {


}

BinTemp::~BinTemp() {


}

unsigned long BinTemp::readAllData(unsigned char buffer[]) {

    reader.open((filename + path).c_str(), ios::in | ios::binary);

    if (!reader.is_open() || buffer == 0) {

        return 0;
    }

    int n = sizeof(unsigned long);

    char * buf = new char[n];

    reader.read(buf, n);

    unsigned long size = parse<unsigned long>(buf);

    delete buf;

    reader.seekg(n, ios::beg);

    reader.read((char*)&buffer[0], size);

    reader.close();

    return size;
}

unsigned char * BinTemp::readData(const unsigned long& size) {

    reader.open((filename + path).c_str(), ios::in | ios::binary);

    if (!reader.is_open()) {

        return 0;
    }

    unsigned char * out = new unsigned char[size];

    reader.read((char*)out, size);

    reader.close();

    return out;
}

void BinTemp::writeData(unsigned char data[], const unsigned long& size) {

    writer.open((path + filename).c_str(), ios::out | ios::binary | ios::trunc);

    if (!writer.is_open()) {

        return;
    }

    int n = sizeof(unsigned long);

    writer.write((char*)toUchar(size), n);

    writer.seekp(n, ios::beg);

    writer.write((char*)data, size);

    writer.close();
}

int BinTemp::dataSize() {

    reader.open((path + filename).c_str(), ios::out | ios::binary);

    if (!reader.is_open())
        return 0;

    const int n = sizeof(unsigned long);

    unsigned char buf[n];

    reader.read((char*) &buf[0], n);

    return parse<unsigned long>(buf);
}

bool BinTemp::exists() {

    reader.open((path + filename).c_str(), ios::in | ios::binary);

    if (reader.is_open()) {

        reader.close();
        return true;

    } else {

        return false;
    }
}

void BinTemp::clear() {

    writer.open((path + filename).c_str(), ios::out | ios::binary | ios::trunc);

    if (writer.is_open()) {

        const int n = sizeof(unsigned long);

        char size[n] = {0};

        writer.write(size, n);

        writer.close();
    }
}
