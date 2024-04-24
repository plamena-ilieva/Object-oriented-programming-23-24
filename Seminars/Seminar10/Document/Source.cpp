#include <iostream>
#include "Document.h"

class Viewer {
public:
    void view(const Document& document) {
        document.display();
    }
};

class Commenter : public Viewer {
public:
    void addComment(Document& document, const Comment& comment) {
        document.addComment(comment);
    }
};

class Editor : public Commenter {
public:
    void edit(Document& document, const MyString& newContent) {
        document.setContent(newContent);
    }
};

int main()
{
    Document d;
    Viewer v;
    v.view(d);

    Commenter c;
    Comment comm;
    c.addComment(d, comm);
    c.view(d);

    Editor e;
    e.edit(d, "qwertyuiop");
    e.view(d);
}