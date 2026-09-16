#include <iostream>
#include <fstream>
#include <vector>
class Printable{
public:
    virtual ~Printable(){};
    virtual std::string print() const = 0;
};

class PrintHTML
{
public:
    virtual ~PrintHTML() = default;
    virtual std::string printAsHTML() const = 0;
};

class PrintText
{
public:
    virtual ~PrintText() = default;
    virtual std::string printAsText() const = 0;
};

class PrintJSON
{
public:
    virtual ~PrintJSON() = default;
    virtual std::string printAsJSON() const = 0;
};

class Data : public PrintJSON, public PrintText, public PrintHTML, public Printable
{
public:
    Data(std::string data)
        : data_(std::move(data)) {}
    std::string get_data()const{
        return data_;
    }
    std::string printAsHTML() const override
    {
        return "<html>" + get_data() + "<html/>";
    }
    std::string printAsText() const override
    {
        return get_data();
    }
    std::string printAsJSON() const override
    {
        return "{ \"data\": \"" + get_data() + "\"}";
    }
private:
    std::string data_;
};

class Data_HTML : public Data{
    std::string print() const override {
        return printAsHTML();
    }
public:
    Data_HTML(std::string data)
        : Data(data){}
};

class Data_Text : public Data{
    std::string print() const override {
        return printAsText();
    }

public:
    Data_Text(std::string data)
        : Data(data){}
};

class Data_JSON : public Data{
    std::string print() const override {
        return printAsJSON();
    }

public:
    Data_JSON(std::string data)
        : Data(data){}
};

void saveTo(std::ostream &ostream, const std::vector<Data*> printable)
{
    for(auto print : printable){
        ostream << print->print();
    }
}

int main(){
    const std::vector<Data*> p{new Data_JSON("hekkk"), new Data_HTML("asd")};
    saveTo(std::cout,p );



}