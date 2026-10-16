#include <bits/stdc++.h>
using namespace std;

class Call {
public:
    int callID;
    int arrivalTime;
    string customerName;
    int processingTime;

    Call(int id, int time, string name, int duration) {
        callID = id;
        arrivalTime = time;
        customerName = name;
        processingTime = duration;
    }
};

class CallCenter {
private:
    queue<Call> calls;
    int CSR;
    vector<bool> available;
    vector<int> busyUntil;

public:
    CallCenter(int numberOfCSR) {
        CSR = numberOfCSR;
        available.resize(CSR, true);
        busyUntil.resize(CSR, 0);
    }

     void addCall(Call c) {
        calls.push(c);

        cout << "Call " << c.callID << " from " << c.customerName
             << " added to queue at time "
             << c.arrivalTime << endl;
    }

    void processCalls(int currentTime) {
        
        for (int i = 0; i < CSR; i++) {
            if (!available[i] && busyUntil[i] <= currentTime) {
                available[i] = true;
                cout << "CSR " << i + 1
                     << " completed the call at time "
                     << currentTime << endl;
            }
        }

        for (int i = 0; i < CSR; i++) {
            if (available[i] && !calls.empty()) {
                Call c = calls.front();
                calls.pop();

                available[i] = false;
                busyUntil[i] = currentTime + c.processingTime;

                cout << "CSR " << i + 1
                     << " is handling Call " << c.callID
                     << " (" << c.customerName << ")"
                     << " from time " << currentTime
                     << " to " << busyUntil[i] << endl;
            }
        }
    }
};

int main() {
    CallCenter center(2); 

    center.addCall(Call(101, 0, "Ali", 3));
    center.addCall(Call(102, 0, "Ahmed", 2));
    center.processCalls(0);

    center.addCall(Call(103, 1, "Sara", 2));
    center.processCalls(1);

    center.addCall(Call(104, 2, "Zain", 1));
    center.processCalls(2);

    center.processCalls(3);
    center.processCalls(4);

    return 0;
}