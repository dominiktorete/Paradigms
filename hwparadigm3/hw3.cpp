#include <iostream>
#include <string>
#include <fstream>

enum class Type{
    Fatal, Error, Warning, Uncknown
};
class LogMessage {
    Type type_;
    std::string message_{};
public:
    LogMessage(Type typ, std::string messag) : type_(typ), message_(messag) {}
    Type type() const{
        return type_;
    }
    const std::string& message() const{
        return message_;
    }
};
class Handle{
public:
    Handle() = default;
    virtual ~Handle(){}
    virtual void print(const std::string& message){}
    virtual void give_work(LogMessage& log){}
};

class FatalError : public Handle {
    Handle* child{};
    Type type = Type::Fatal;
public:
    FatalError(Handle* child_) : child(std::move(child_)){}
    void print(const std::string& message) override {
        throw message.c_str();
    }
    void give_work(LogMessage& log) override {
        if(log.type() == type){
            print(log.message());
        }
        else{
            child->give_work(log);
        }
    }
    ~FatalError(){
        delete child;
    }
};


class Error : public Handle {
    Handle* child{};
    Type type = Type::Error;
    std::string file_way{};
public:
    Error(Handle* child_, std::string way) : child(std::move(child_)), file_way(way){}
    void print(const std::string& message) override {
        std::ofstream file(file_way);
        if(file.is_open()){
            file << message;
        }
        else {
            std::cout << "Error open file" << std::endl;
        }
    }
    void give_work(LogMessage& log) override {
        if(log.type() == type){
            print(log.message());
        }
        else{
            child->give_work(log);
        }
    }
    ~Error(){
        delete child;
    }
};

class Warning : public Handle {
    Handle* child{};
    Type type = Type::Warning;
public:
    Warning(Handle* child_) : child(std::move(child_)){}
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
    void give_work(LogMessage& log) override {
        if(log.type() == type){
            print(log.message());
        }
        else{
            child->give_work(log);
        }
    }
    ~Warning(){
        delete child;
    }
};

class Uncknown : public Handle {
    Type type = Type::Uncknown;
public:
    Uncknown() {}
    void print(const std::string& message) override {
        throw "Message not processed";
    }
    void give_work(LogMessage& log) override {

        print(log.message());
    }
};

void processed(Handle* hand, LogMessage& log1){
    try{
        hand->give_work(log1);
    }
    catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
    catch(const char* ch ){
        std::cout << ch << std::endl;
    }
}

int main()
{
    Handle* unk = new Uncknown();
    Handle* wa = new Warning(unk);
    Handle* er = new Error(wa, "error.log");
    Handle* ferror = new FatalError(er);

    LogMessage log1(Type::Fatal, "fat er");
    LogMessage log2(Type::Warning, "war er");
    processed(ferror, log1);
    processed(ferror, log2);
    delete ferror;
    return 0;
}
