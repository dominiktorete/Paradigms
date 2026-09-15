#include <algorithm>
#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Paragraph: public DecoratedText {
    public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";

    }
};
class Reversed: public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::string temp = data;
        std::reverse(temp.begin(), temp.end());
        text_->render(temp);

    }
};
class Link: public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& ref, const std::string& data)  const {
        std::cout << "<a href=";
        text_->render(ref);
        std::cout << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};
int main() {
    Paragraph* text_block = new Paragraph(new Text());
    text_block->render("Hello world");
    std::cout << std::endl;
    Reversed* text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << std::endl;
    Link* text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
}