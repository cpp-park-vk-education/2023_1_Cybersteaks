#pragma once
#include <string>
#include <fstream>
#include <sstream>

class IDBAccessor
{
public:
    virtual void* std::string execute_request(const std::string& request) = 0;
}

class DatabaseMOCK : public IDBAccessor 
{
public:
    std::string request;
    void* execute_request(const std::string& request) override {
        this->request = request;
    }
};

class IFileAccessor {
public:
    virtual std::basic_ostream& GetOutStream() = 0;
}

class FileMOCK : public IFileAccessor {
public:
    std::stringstream sstream;
    std::string fname;
    std::basic_ostream& GetOutStream(){
        return sstream;
    } 
    FileMOCK(const std::string& fname){
        this->fname = fname;
    }
}

class FileAccessor : public IFileAccessor {
public:
    std::ofstream fout;
    FileAccessor(const std::string fname){
        fout.open(fname);
    }
    std::basic_ostream& GetOutStream(){
        return fout;
    }
}  

