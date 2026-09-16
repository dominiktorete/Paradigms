#include <iostream>
#include <string>
#include <fstream>
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class CommConsole : public LogCommand {
public:
    virtual ~CommConsole() = default;
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class CommFile : public LogCommand {
    std::string way_file{};
public:
    CommFile(std::string way_f) : way_file(way_f){}
    virtual ~CommFile() = default;
    void print(const std::string& message) override {
        std::ofstream file(way_file);
        if(file.is_open()){
            file << message;
        }
        else {
            throw std::invalid_argument("Error open file");
        }
    }
};

void print(LogCommand& log){
    log.print("Hello World");
}

int main()
{
    LogCommand* log1 = new CommConsole();
    LogCommand* log2 = new CommFile("Result.txt");

    print(*log1);
    try{
        print(*log2);
    }
    catch(std::exception& ex){
        ex.what();
    }
    delete log1;
    delete log2;
    return 0;
}
