#ifndef TEMP_H
#define TEMP_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Temp {

public:

    Temp(const string& filename, const string& filepath = "");
    ~Temp();

    //virtual void clear();
    //virtual bool exists();

    string getPath() const;
    string getFileName() const;

    void remove();

protected:

    ifstream reader;
    ofstream writer;
    string path;
    string filename;

};

class TxtTemp : public Temp {

public:

    TxtTemp(const string& filename, const string& path);
    ~TxtTemp();

    string lastLine();
    void writeLine(const string& str);
    vector<string> readLines();

    void logcmd(const string& cmd);

    void clear();
    bool exists();
};

class BinTemp : public Temp {

public:

    BinTemp(const string& filename, const string& path);
    ~BinTemp();

    unsigned long readAllData(unsigned char buffer[] = 0);  // returns size
    unsigned char * readData(const unsigned long& size);
    void writeData(unsigned char data[], const unsigned long& size);
    void appendData(unsigned char data[], const unsigned long& size);
    int dataSize();

    void clear();
    bool exists();
};

template <class X, class C>
X parse(const C arg[]) {

    return * (X*) arg;
}

template <class T>
unsigned char * toUchar(const T& arg) {

    return (unsigned char*) &arg;
}

#endif // TEMP_H
