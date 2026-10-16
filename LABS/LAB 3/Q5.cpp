
#include <iostream>
#include <string>
using namespace std;

class Page {
public:
    string url;
    Page* prev;
    Page* next;

    Page(string url) {
        this->url = url;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Page* current;

public:
    BrowserHistory(string homePage) {
        current = new Page(homePage);
    }

    void visit(string url) {
        
        Page* temp = current->next;

        while (temp != NULL) {
            Page* nextPage = temp->next;
            delete temp;
            temp = nextPage;
        }

        
        Page* newPage = new Page(url);

        current->next = newPage;
        newPage->prev = current;

        current = newPage;
    }

    string back(int steps) {
        while (steps > 0 && current->prev != NULL) {
            current = current->prev;
            steps--;
        }

        return current->url;
    }

    string forward(int steps) {
        while (steps > 0 && current->next != NULL) {
            current = current->next;
            steps--;
        }

        return current->url;
    }

    ~BrowserHistory() {
        while (current->prev != NULL) {
            current = current->prev;
        }

        while (current != NULL) {
            Page* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    BrowserHistory* browserHistory =
        new BrowserHistory("leetcode.com");

    browserHistory->visit("google.com");
    browserHistory->visit("facebook.com");
    browserHistory->visit("youtube.com");

    cout << browserHistory->back(1) << endl;
    cout << browserHistory->back(1) << endl;
    cout << browserHistory->forward(1) << endl;

    browserHistory->visit("linkedin.com");

    cout << browserHistory->forward(2) << endl;
    cout << browserHistory->back(2) << endl;
    cout << browserHistory->back(7) << endl;

    delete browserHistory;

    return 0;
}
