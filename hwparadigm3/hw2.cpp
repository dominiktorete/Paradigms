#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
    virtual ~Observer() = default;
};

class Warning : public Observer{
    void onWarning(const std::string& message) {
        std::cout << message << std::endl;
    }
    public:
    Warning() = default;

};
class Error : public Observer{
    std::string way_file{};
    void onError(const std::string& message) {
        std::ofstream file(way_file);
        if(file.is_open()){
            file << message;
        }
        else{
            std::cout << "Error open file" << std::endl;
        }
    }
    public:
    Error(std::string way): way_file(way){};

};
class FatalError : public Observer{
    std::string way_file{};
    void onFatalError(const std::string& message) {
        std::ofstream file(way_file);
        std::cout << message << std::endl;
        if(file.is_open()){
            file << message;
        }
        else{
            std::cout << "Error open file" << std::endl;
        }
    }
public:
    FatalError(std::string way): way_file(way){};

};

class Log {
    std::vector<std::weak_ptr<Observer>>observers{};
    public:
    void push(std::weak_ptr<Observer> obs){
        observers.push_back(obs);
    }
    void warning(const std::string& message) const{
        for(auto& curr : observers){
            curr.lock()->onWarning(message);
        }
    }
    void error(const std::string& message) const{
        for(auto& curr : observers){
            curr.lock()->onError(message);
        }
    }
    void fatalError(const std::string& message) const{
        for(auto& curr : observers){
            curr.lock()->onFatalError(message);
        }
    }

};


int main()
{
    std::shared_ptr<Observer> Fatal = std::make_shared<FatalError>("FatalError.txt");
    std::shared_ptr<Observer> Warningerr = std::make_shared<Warning>();
    std::shared_ptr<Observer> Errorerr = std::make_shared<Error>("Error.txt");


    Log log;
    log.push(Fatal);
    log.push(Warningerr);
    log.push(Errorerr);
    log.error("Error message");
    log.fatalError("Fatal Error message");
    log.warning("Warning message");

    return 0;
}
