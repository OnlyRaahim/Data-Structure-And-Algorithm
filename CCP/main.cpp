// ============================================================================
//  OPERATION BLACKOUT  --  Full-Crew Coordinated Heist Simulation
// ----------------------------------------------------------------------------
//  Every crew member has their own device and their own active problems.
//  Switch between crew members to solve ALL crises personally—or order
//  teammates to auto-resolve on comms when the SWAT clock gets tight.
// ============================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <windows.h>
using namespace std;

// ------------------------------- String Helpers -----------------------------
string toStr(int v) { stringstream ss; ss << v; return ss.str(); }

// ------------------------------- Terminal Colors & Sound FX -----------------
namespace C {
const string R = "\033[0m", RED = "\033[31m", GRN = "\033[32m", YEL = "\033[33m",
             BLU = "\033[34m", MAG = "\033[35m", CYN = "\033[36m", WHT = "\033[37m",
             BOLD = "\033[1m", DIM = "\033[2m";
}
bool FAST = false;

int rnd(int a, int b) { return a + (rand() % (b - a + 1)); }
void sleepMs(int ms) { if (!FAST) Sleep(ms); }
void clearScreen() { if (!FAST) system("cls"); }

void playTone(int freq, int dur) {
    if (!FAST) Beep(freq, dur);
}

void sfxClick()   { playTone(900, 35); }
void sfxAlarm()   { playTone(520, 120); playTone(380, 160); }
void sfxUnlock()  { playTone(660, 80); playTone(880, 80); playTone(1150, 140); }
void sfxPhone()   { playTone(750, 90); playTone(750, 90); }

void typeOut(const string& s, int d = 5) {
    for (size_t i = 0; i < s.size(); i++) { cout << s[i] << flush; sleepMs(d); }
    cout << "\n";
}

void pauseKey(const string& prompt = "Press ENTER to continue") {
    if (FAST) return;
    cout << C::DIM << "\n  [" << prompt << "]" << C::R;
    string t; getline(cin, t); cout << "\n";
}

// ------------------------------- Crew & Device Definitions ------------------
enum Role { LEADER, BREACHER, HANDLER, HACKER };
const char* roleName[]   = {"BOSS", "BREACHER", "WHEELMAN", "GHOST"};
const char* deviceName[] = {
    "Tactical Command Pad",
    "Seismic Thermal & Breach Rig",
    "Police Scanner & Crowd HUD",
    "Kali Quantum Cyberdeck"
};

string col(Role r) {
    switch (r) {
        case LEADER:   return C::YEL;
        case BREACHER: return C::RED;
        case HANDLER:  return C::GRN;
        default:       return C::CYN;
    }
}

void say(Role r, const string& t) {
    cout << "\n  " << col(r) << C::BOLD << roleName[r] << ": " << C::R << col(r);
    typeOut(t);
    cout << C::R;
}

void bootDevice(Role r, const string& moduleTitle) {
    sfxClick();
    cout << "\n  " << col(r) << C::BOLD << ">> ACTIVE PERSPECTIVE: " << roleName[r]
         << "  |  Device: " << deviceName[r] << " (" << moduleTitle << ")" << C::R << "\n\n";
    sleepMs(200);
}

// ------------------------------- Global Story & Mission State ---------------
stack<string> missionLog;
int heat = 0;
int swatMins = 30;
int bagCapacity = 12;

bool managerKeycardObtained = false;
bool guardRadioIntercepted  = false;
bool secretBullionRoomOpen  = false;
bool vaultFirstDigitKnown   = false;
bool empAvailable           = true;
bool negotiatorCalled       = false;

void spendTime(int m, const string& reason) {
    swatMins = max(0, swatMins - m);
    if (m > 0) {
        cout << "  " << C::CYN << "Time -" << m << " min: " << reason
             << " (SWAT arrives in " << swatMins << " min)" << C::R << "\n";
    }
}

void addHeat(int n, const string& why) {
    heat = max(0, min(100, heat + n));
    if (n > 0) {
        sfxAlarm();
        cout << "  " << C::RED << "Police Alert +" << n << "%: " << why << " (Alert Level: " << heat << "%)" << C::R << "\n";
    } else if (n < 0) {
        cout << "  " << C::GRN << "Police Alert " << n << "%: " << why << " (Alert Level: " << heat << "%)" << C::R << "\n";
    }
    missionLog.push(why + (n > 0 ? " (+" + toStr(n) + "% alert)" : ""));
}

void drawHUD(int act, const string& title) {
    string hCol = (heat >= 70) ? C::RED : (heat >= 40 ? C::YEL : C::GRN);
    string tCol = (swatMins <= 8) ? C::RED : (swatMins <= 15 ? C::YEL : C::CYN);

    string intel = "";
    if (managerKeycardObtained) intel += "Tariq's Keycard, ";
    if (guardRadioIntercepted)  intel += "Guard Radio, ";
    if (secretBullionRoomOpen)  intel += "Secret Vault Room, ";
    if (empAvailable)           intel += "EMP Ready";
    else if (!intel.empty())    intel.erase(intel.size() - 2);
    if (intel.empty())          intel = "None";

    cout << "\n\n  " << C::BOLD << C::MAG << "STAGE " << act << "  |  " << title << C::R << "\n"
         << "  " << C::DIM << "Status: " << C::R
         << "Alert " << hCol << heat << "%" << C::R << "   "
         << "SWAT Arrival " << tCol << swatMins << " min" << C::R << "   "
         << "Bag Space " << C::YEL << bagCapacity << " kg" << C::R << "   "
         << "Advantages: " << C::CYN << intel << C::R << "\n\n";
    sleepMs(200);
}

int readChoice(int lo, int hi, int def, Role activeRole = LEADER) {
    if (FAST) return rnd(lo, hi);
    while (true) {
        cout << "\n  " << col(activeRole) << C::BOLD << roleName[activeRole] << ", choose an option ("
             << lo << "-" << hi << "): " << C::R << flush;
        string s;
        if (!getline(cin, s)) return def;
        if (s.empty()) return def;
        stringstream ss(s);
        int v;
        if ((ss >> v) && v >= lo && v <= hi) { sfxClick(); cout << "\n"; return v; }
        cout << C::RED << "  Please enter a number between " << lo << " and " << hi << ".\n" << C::R;
    }
}

string readCodeInput() {
    if (FAST) return "";
    cout << "\n  " << C::YEL << "Enter a 4-digit PIN guess (or press ENTER to let Ghost crack it): " << C::R << flush;
    string s;
    if (!getline(cin, s) || s.size() != 4) { cout << "\n"; return ""; }
    for (int i = 0; i < 4; i++) if (s[i] < '0' || s[i] > '9') { cout << "\n"; return ""; }
    sfxClick();
    cout << "\n";
    return s;
}

// ------------------------------- Decision Tree: SWAT Negotiator Call --------
struct TalkNode {
    string policeLine;
    string opt1Text;
    string opt2Text;
    int next1, next2;
    int timeDelta, heatDelta;
    string outcomeMsg;

    TalkNode() : next1(-1), next2(-1), timeDelta(0), heatDelta(0) {}
};

void runNegotiatorCall() {
    if (negotiatorCalled || rnd(1, 100) > 99) return;
    negotiatorCalled = true;
    sfxPhone();

    cout << "\n  " << C::RED << C::BOLD << "INCOMING CALL ON BANK LANDLINE: DIG South Police Negotiator" << C::R << "\n";
    bootDevice(LEADER, "Encrypted Voice Line");

    vector<TalkNode> tree(6);

    // Node 0: Opening Call
    tree[0].policeLine = "\"This is DIG South. We have the building surrounded. Tell me everyone inside is unharmed.\"";
    tree[0].opt1Text   = "\"Nobody is hurt. Keep your tactical teams back and everyone walks out.\"";
    tree[0].opt2Text   = "\"Pull every patrol car back two blocks right now or things get ugly!\"";
    tree[0].next1      = 1;
    tree[0].next2      = 2;

    // Node 1: Calm Branch
    tree[1].policeLine = "\"Fair enough. What are your terms so we can hold the SWAT breach team?\"";
    tree[1].opt1Text   = "\"We're releasing two elderly clients right now as a sign of good faith.\"";
    tree[1].opt2Text   = "\"Clear Shahrah-e-Faisal and give us 10 minutes with no choppers.\"";
    tree[1].next1      = 3;
    tree[1].next2      = 4;

    // Node 2: Aggressive Branch
    tree[2].policeLine = "\"Threats won't work here. Give me one reason not to send SWAT through the roof.\"";
    tree[2].opt1Text   = "\"Wait—calm down. We have medical staff tending to a fainted guard.\"";
    tree[2].opt2Text   = "\"Send them in and see what happens.\" (Slam phone down)";
    tree[2].next1      = 4;
    tree[2].next2      = 5;

    // Node 3: Best Outcome (Leaf)
    tree[3].policeLine = "\"We see two civilians exiting the front doors. Holding SWAT back for 6 minutes.\"";
    tree[3].timeDelta  = 6;
    tree[3].heatDelta  = -8;
    tree[3].outcomeMsg = "Masterful negotiation! Bought +6 extra minutes and lowered police alert by 8%.";

    // Node 4: Moderate Outcome (Leaf)
    tree[4].policeLine = "\"Alright, I'm holding the breach squad for 3 minutes while we verify your terms.\"";
    tree[4].timeDelta  = 3;
    tree[4].heatDelta  = -3;
    tree[4].outcomeMsg = "Stalled the police command post (+3 extra minutes, -3% alert).";

    // Node 5: Worst Outcome (Leaf)
    tree[5].policeLine = "\"Line dead—all tactical units, green light to advance on the bank!\"";
    tree[5].timeDelta  = -3;
    tree[5].heatDelta  = 12;
    tree[5].outcomeMsg = "Hung up on DIG Negotiator—SWAT moved up (-3 min, +12% alert).";

    int curr = 0;
    while (curr != -1) {
        TalkNode& node = tree[curr];
        cout << "  " << C::YEL << "Police Negotiator: " << C::R << node.policeLine << "\n\n";

        // Leaf node: apply final result and end call
        if (node.next1 == -1 && node.next2 == -1) {
            if (node.timeDelta > 0) {
                swatMins += node.timeDelta;
                cout << "  " << C::GRN << "Time +" << node.timeDelta
                     << " min (SWAT arrives in " << swatMins << " min)" << C::R << "\n";
            } else if (node.timeDelta < 0) {
                spendTime(-node.timeDelta, "Negotiation backfired");
            }
            addHeat(node.heatDelta, node.outcomeMsg);
            break;
        }

        // Decision node: display both clear options
        cout << "    1) " << node.opt1Text << "\n"
             << "    2) " << node.opt2Text << "\n";
        int pick = readChoice(1, 2, 1, LEADER);
        curr = (pick == 1) ? node.next1 : node.next2;
    }
    pauseKey();
}

// ------------------------------- Persistent Leaderboard ---------------------
struct Record {
    string bossTitle;
    int haul;
    int alertLvl;
    int driveMins;
    bool operator<(const Record& o) const { return haul > o.haul; }
};

void showHallOfFame() {
    ifstream fin("heist_records.txt");
    if (!fin) return;
    vector<Record> list;
    Record r;
    while (fin >> r.haul >> r.alertLvl >> r.driveMins) {
        getline(fin, r.bossTitle);
        if (!r.bossTitle.empty() && r.bossTitle[0] == ' ') r.bossTitle.erase(0, 1);
        list.push_back(r);
    }
    fin.close();
    if (list.empty()) return;

    sort(list.begin(), list.end());
    cout << "\n  " << C::BOLD << C::YEL << "Past Syndicate Heist Records (Top Scores):" << C::R << "\n";
    int limit = min(5, (int)list.size());
    for (int i = 0; i < limit; i++) {
        cout << "    " << (i + 1) << ". $" << setw(4) << list[i].haul << "K  |  "
             << left << setw(28) << list[i].bossTitle
             << C::DIM << " (Alert: " << list[i].alertLvl << "%, Escape: " << list[i].driveMins << "m)" << C::R << "\n";
    }
}

void saveRecord(const string& title, int haul, int alertLvl, int driveMins) {
    ofstream fout("heist_records.txt", ios::app);
    if (fout) {
        fout << haul << " " << alertLvl << " " << driveMins << " " << title << "\n";
        fout.close();
    }
}

// ------------------------------- Equipment Checklist (Hash Map) -------------
struct GearCheck {
    static const int SIZE = 13;
    string keys[SIZE];
    bool vals[SIZE];
    bool used[SIZE];

    GearCheck() {
        for (int i = 0; i < SIZE; i++) { used[i] = false; vals[i] = false; }
    }

    int slotFor(const string& k) const {
        unsigned int h = 0;
        for (size_t i = 0; i < k.size(); i++) h = h * 31 + (unsigned char)k[i];
        return (int)(h % SIZE);
    }

    void set(const string& k, bool v) {
        int idx = slotFor(k), start = idx;
        while (used[idx] && keys[idx] != k) { idx = (idx + 1) % SIZE; if (idx == start) break; }
        keys[idx] = k; vals[idx] = v; used[idx] = true;
    }

    void displayChecklist() const {
        cout << "  " << C::BOLD << C::CYN << "Safehouse Rig & Loadout Check:" << C::R << "\n";
        for (int i = 0; i < SIZE; i++) {
            if (!used[i]) continue;
            cout << "    Bay " << setw(2) << (i + 1) << " : " << left << setw(22) << keys[i]
                 << (vals[i] ? C::GRN + "READY" : C::RED + "NEEDS ATTENTION") << C::R << "\n";
        }
    }
};

// ------------------------------- Bank & City Map Network --------------------
struct Edge { int to, w; bool blocked; };

struct MapNetwork {
    vector<string> names;
    vector<vector<Edge> > adj;

    int add(const string& n) { names.push_back(n); adj.push_back(vector<Edge>()); return (int)names.size() - 1; }
    void link(int a, int b, int w) { Edge e1 = {b, w, false}, e2 = {a, w, false}; adj[a].push_back(e1); adj[b].push_back(e2); }

    void setBlocked(int a, int b, bool v) {
        for (size_t i = 0; i < adj[a].size(); i++) if (adj[a][i].to == b) adj[a][i].blocked = v;
        for (size_t i = 0; i < adj[b].size(); i++) if (adj[b][i].to == a) adj[b][i].blocked = v;
    }
    bool isBlocked(int a, int b) const {
        for (size_t i = 0; i < adj[a].size(); i++) if (adj[a][i].to == b) return adj[a][i].blocked;
        return false;
    }
    int getWeight(int a, int b) const {
        for (size_t i = 0; i < adj[a].size(); i++) if (adj[a][i].to == b) return adj[a][i].w;
        return 0;
    }

    enum { INF = 1000000000 };

    vector<int> safestPath(int s, int t, int& totalCost) const {
        int n = (int)names.size();
        vector<int> d(n, INF), p(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        d[s] = 0; pq.push(make_pair(0, s));
        while (!pq.empty()) {
            pair<int, int> top = pq.top(); pq.pop();
            int du = top.first, u = top.second;
            if (du > d[u]) continue;
            for (size_t i = 0; i < adj[u].size(); i++) {
                const Edge& e = adj[u][i];
                if (e.blocked) continue;
                if (d[u] + e.w < d[e.to]) { d[e.to] = d[u] + e.w; p[e.to] = u; pq.push(make_pair(d[e.to], e.to)); }
            }
        }
        totalCost = d[t];
        if (totalCost >= INF) return vector<int>();
        vector<int> r;
        for (int v = t; v != -1; v = p[v]) r.push_back(v);
        reverse(r.begin(), r.end());
        return r;
    }

    vector<int> fewestRoomsPath(int s, int t) const {
        int n = (int)names.size();
        vector<int> p(n, -1); vector<bool> vis(n, false); queue<int> q;
        vis[s] = true; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (size_t i = 0; i < adj[u].size(); i++) {
                const Edge& e = adj[u][i];
                if (!e.blocked && !vis[e.to]) { vis[e.to] = true; p[e.to] = u; q.push(e.to); }
            }
        }
        if (!vis[t]) return vector<int>();
        vector<int> r;
        for (int v = t; v != -1; v = p[v]) r.push_back(v);
        reverse(r.begin(), r.end());
        return r;
    }

    int routeRisk(const vector<int>& r) const {
        int sum = 0;
        for (size_t i = 0; i + 1 < r.size(); i++) sum += getWeight(r[i], r[i + 1]);
        return sum;
    }

    string pathStr(const vector<int>& p) const {
        string s;
        for (size_t i = 0; i < p.size(); i++) s += (i ? " -> " : "") + names[p[i]];
        return s;
    }
};

// ------------------------------- Clean Visual Maps --------------------------
string tagNode(int id, int activeId, const string& label) {
    if (id == activeId) return C::BOLD + C::YEL + "*" + label + "*" + C::R;
    return label;
}

void drawBankMap(const MapNetwork& g, int crewNode) {
    cout << "  " << C::BOLD << C::CYN << "Habib Reserve Bank Floorplan" << C::R
         << C::DIM << "  (Numbers = guard security level | * = crew location)" << C::R << "\n\n"
         << "               " << tagNode(3, crewNode, "Roof Vent") << " ..(" << g.getWeight(3,7) << ").. " << tagNode(7, crewNode, "Server Room") << "\n"
         << "                  :                      :\n"
         << "    " << tagNode(0, crewNode, "Street") << " ..(" << g.getWeight(0,1) << ").. " << tagNode(1, crewNode, "Front Door")
         << " ..(" << g.getWeight(1,5) << ").. " << tagNode(5, crewNode, "Lobby") << " ..(" << g.getWeight(5,9) << ").. " << tagNode(9, crewNode, "Office") << "\n"
         << "       :                                 :                  :\n"
         << "       :..(" << g.getWeight(0,2) << ").. " << tagNode(2, crewNode, "Alley") << " ..(" << g.getWeight(2,6) << ").. " << tagNode(6, crewNode, "Staff Hall")
         << "        " << tagNode(10, crewNode, "Vault Hall") << " ..(1).. " << C::RED << tagNode(11, crewNode, "VAULT") << C::R << "\n"
         << "       :                                                    :\n"
         << "       :..(" << g.getWeight(0,4) << ").. " << tagNode(4, crewNode, "Sewer") << " ..(" << g.getWeight(4,8) << ").. " << tagNode(8, crewNode, "Tunnel") << " ..(" << g.getWeight(8,10) << ")..'\n\n";
}

string roadEdge(const MapNetwork& g, int a, int b) {
    if (g.isBlocked(a, b)) return C::RED + " [POLICE BLOCKADE] " + C::R;
    return " ..(" + toStr(g.getWeight(a, b)) + "m).. ";
}

void drawCityMap(const MapNetwork& g, int vanNode) {
    cout << "  " << C::BOLD << C::CYN << "Karachi Getaway Radar" << C::R
         << C::DIM << "  (Drive time in minutes | * = getaway van)" << C::R << "\n\n"
         << "            " << tagNode(2, vanNode, "Tower") << roadEdge(g,2,5) << tagNode(5, vanNode, "Lyari Exp") << roadEdge(g,5,7) << tagNode(7, vanNode, "N. Bypass") << "\n"
         << "            /     \\                                     \\\n"
         << "    " << tagNode(0, vanNode, "Bank") << "          " << tagNode(4, vanNode, "Shahrah-e-Faisal") << roadEdge(g,4,6) << tagNode(6, vanNode, "Korangi") << " ..(" << g.getWeight(6,8) << "m).. " << C::GRN << tagNode(8, vanNode, "SAFEHOUSE") << C::R << "\n"
         << "            \\     /                                     /\n"
         << "            " << tagNode(1, vanNode, "Saddar") << roadEdge(g,1,3) << tagNode(3, vanNode, "Clifton Bridge") << " .......'\n\n";
}

// ------------------------------- Structs & Vault Solver ---------------------
struct Hostage {
    string name, role, observation, checkPrompt, calmPrompt;
    int panic;
    bool operator<(const Hostage& o) const { return panic < o.panic; }
};

struct SecurityNode { string name; int threat; };
struct Loot { string name; int w, v; };

bool ratioOrder(const pair<int, Loot>& a, const pair<int, Loot>& b) {
    return a.second.v * b.second.w > b.second.v * a.second.w;
}

void findValidPins(string cur, const vector<int>& digits, vector<bool>& used,
                   vector<string>& out, bool showLog) {
    int pos = (int)cur.size();
    if (pos == 4) {
        out.push_back(cur);
        if (showLog) cout << "    " << string(pos * 2, ' ') << C::GRN << cur << " (Matches all clues)\n" << C::R;
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (used[i]) continue;
        int d = digits[i];
        string nextStr = cur + char('0' + d);
        if (pos == 0 && d % 2 != 0) {
            if (showLog) cout << "    " << C::DIM << nextStr << "... skipped (1st digit must be even)\n" << C::R;
            continue;
        }
        if (pos == 1 && d % 2 == 0) {
            if (showLog) cout << "      " << C::DIM << nextStr << ".. skipped (2nd digit must be odd)\n" << C::R;
            continue;
        }
        if (pos == 3 && d <= cur[0] - '0') {
            if (showLog) cout << "          " << C::DIM << nextStr << " skipped (4th digit must be larger than 1st)\n" << C::R;
            continue;
        }
        used[i] = true;
        findValidPins(nextStr, digits, used, out, showLog);
        used[i] = false;
    }
}

bool codeOK(const string& s) {
    return (s[0] - '0') % 2 == 0 && (s[1] - '0') % 2 == 1 && s[3] > s[0];
}

// ============================================================================
void banner() {
    cout << C::RED << C::BOLD
         << "\n   ___  ____  _____ ____      _  _____ ___ ___  _   _\n"
         << "  / _ \\|  _ \\| ____|  _ \\    / \\|_   _|_ _/ _ \\| \\ | |\n"
         << " | | | | |_) |  _| | |_) |  / _ \\ | |  | | | | |  \\| |\n"
         << " | |_| |  __/| |___|  _ <  / ___ \\| |  | | |_| | |\\  |\n"
         << "  \\___/|_|   |_____|_| \\_\\/_/   \\_\\_| |___\\___/|_| \\_|\n"
         << "        ____  _        _    ____ _  _____  _   _ _____\n"
         << "       | __ )| |      / \\  / ___| |/ / _ \\| | | |_   _|\n"
         << "       |  _ \\| |     / _ \\| |   | ' / | | | | | | | |\n"
         << "       | |_) | |___ / ___ \\ |___| . \\ |_| | |_| | | |\n"
         << "       |____/|_____/_/   \\_\\____|_|\\_\\___/ \\___/  |_|\n"
         << C::R << C::YEL << "\n            Tactical Command Edition  |  Karachi Heist\n" << C::R;
}

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));
    for (int i = 1; i < argc; i++) if (string(argv[i]) == "--fast") FAST = true;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) SetConsoleMode(hOut, dwMode | 0x0004);

    clearScreen();
    banner();
    cout << "\n  " << C::BOLD << "Your Syndicate & Specialized Devices:" << C::R << "\n\n"
         << "    1. " << C::YEL << "BOSS     " << C::R << "(" << deviceName[0] << ")  Command decisions, SWAT calls, Loot planning\n"
         << "    2. " << C::RED << "BREACHER " << C::R << "(" << deviceName[1] << ")  Thermal drills, blast walls, vault locks\n"
         << "    3. " << C::GRN << "WHEELMAN " << C::R << "(" << deviceName[2] << ")  Crowd control, radio intercepts, getaway driving\n"
         << "    4. " << C::CYN << "GHOST    " << C::R << "(" << deviceName[3] << ")  Route planning, security override, keypad cracking\n";

    showHallOfFame();
    pauseKey("Press ENTER to enter the safehouse");

    // ===================== STAGE 1: COORDINATED CREW PREP ===================
    GearCheck kit;
    kit.set("Fake FIA Badges", true);
    kit.set("Vault Blueprints", true);
    kit.set("Thermite Fuel Cell", false);
    kit.set("Hydraulic Jack", true);
    kit.set("Police Scanner", false);
    kit.set("Armored Vigo Van", true);
    kit.set("Door Bypass Token", false);
    kit.set("EMP Charge", true);

    bool ghostPrepDone = false, breacherPrepDone = false, wheelmanPrepDone = false;

    while (!ghostPrepDone || !breacherPrepDone || !wheelmanPrepDone) {
        drawHUD(1, "Safehouse Readiness (Coordinate Your Crew)");
        kit.displayChecklist();

        cout << "\n  " << C::BOLD << "Active Crew Problems — Select a member to take control (or order auto-fix):" << C::R << "\n"
             << "    1) " << (ghostPrepDone ? C::GRN + "[RESOLVED] GHOST    " : C::CYN + "[PENDING]  GHOST    ") << C::R
             << "-> Bank pushed a firmware update locking out our door badges\n"
             << "    2) " << (breacherPrepDone ? C::GRN + "[RESOLVED] BREACHER " : C::RED + "[PENDING]  BREACHER ") << C::R
             << "-> Thermite fuel cell is leaking & duffel bags need steel frames\n"
             << "    3) " << (wheelmanPrepDone ? C::GRN + "[RESOLVED] WHEELMAN " : C::GRN + "[PENDING]  WHEELMAN ") << C::R
             << "-> Rangers patrol van parked across from the bank's side alley\n"
             << "    0) " << C::YEL << "Order remaining crew to rush & auto-resolve on comms" << C::R << " (Saves time, +6% Alert per rushed task)\n";

        int pick = readChoice(0, 3, 1, LEADER);
        if (pick == 0) {
            if (!ghostPrepDone) {
                ghostPrepDone = true; kit.set("Door Bypass Token", true);
                addHeat(6, "Ghost rushed a noisy badge bypass on comms");
            }
            if (!breacherPrepDone) {
                breacherPrepDone = true; kit.set("Thermite Fuel Cell", true);
                addHeat(6, "Breacher patched leaky thermite cell in a hurry");
            }
            if (!wheelmanPrepDone) {
                wheelmanPrepDone = true; kit.set("Police Scanner", true);
                addHeat(6, "Wheelman skipped radio scan to roll out immediately");
            }
            break;
        } else if (pick == 1 && !ghostPrepDone) {
            ghostPrepDone = true;
            bootDevice(HACKER, "Network Patch Analyzer");
            cout << "  " << C::CYN << "Ghost's Problem: " << C::R << "Habib Reserve Bank just updated its electronic door firmware:\n\n"
                 << "    1) " << C::CYN << "Recompile our access tokens to match the new firmware" << C::R << " (Clean entry, -2 min, 0% Alert)\n"
                 << "    2) " << C::YEL << "Piggyback on an IT technician's active login" << C::R << " (0 min lost, +4% Alert)\n";
            if (readChoice(1, 2, 1, HACKER) == 1) {
                say(HACKER, "Tokens recompiled. Door readers will treat us like head-office staff.");
                spendTime(2, "Ghost recompiled door tokens");
                missionLog.push("Ghost cleanly bypassed new bank firmware");
            } else {
                say(HACKER, "Cloned a technician session—fast, though IT logs might flag it.");
                addHeat(4, "Ghost piggybacked on technician session");
            }
            kit.set("Door Bypass Token", true);
        } else if (pick == 2 && !breacherPrepDone) {
            breacherPrepDone = true;
            bootDevice(BREACHER, "Thermal Fuel & Loadout Bench");
            cout << "  " << C::RED << "Breacher's Problem: " << C::R << "The thermite fuel cell is leaking and standard bags hold only 12 kg:\n\n"
                 << "    1) " << C::RED << "Swap in backup fuel cell & weld steel bag frames" << C::R << " (+3 kg bag space, -2 min, 0% Alert)\n"
                 << "    2) " << C::YEL << "Tape the valve & stick with standard 12 kg bags" << C::R << " (0 min lost, +4% Alert)\n";
            if (readChoice(1, 2, 1, BREACHER) == 1) {
                bagCapacity += 3;
                say(BREACHER, "New fuel cell installed and steel frames welded—bag limit is now " + toStr(bagCapacity) + " kg.");
                spendTime(2, "Breacher swapped fuel cell & upgraded bags to 15 kg");
                missionLog.push("Breacher upgraded duffel capacity to 15 kg");
            } else {
                say(BREACHER, "Patched the valve quickly. Keep clear when I ignite it.");
                addHeat(4, "Breacher used patched thermite cell");
            }
            kit.set("Thermite Fuel Cell", true);
        } else if (pick == 3 && !wheelmanPrepDone) {
            wheelmanPrepDone = true;
            bootDevice(HANDLER, "Metro Police Frequency Scanner");
            cout << "  " << C::GRN << "Wheelman's Problem: " << C::R << "A Rangers pickup is parked outside, and bank guards are on unencrypted radios:\n\n"
                 << "    1) " << C::GRN << "Clone the guards' walkie-talkie channel & wait for shift rotation" << C::R << " (Unlocks Guard Radio, -2 min, 0% Alert)\n"
                 << "    2) " << C::YEL << "Call in a fake fender-bender two blocks away to lure them off" << C::R << " (0 min lost, +4% Alert)\n";
            if (readChoice(1, 2, 1, HANDLER) == 1) {
                guardRadioIntercepted = true;
                say(HANDLER, "Rangers unit just rotated out, and I cloned the bank guards' radio channel.");
                spendTime(2, "Wheelman cloned guard radio & waited out patrol");
                missionLog.push("Wheelman cloned bank guard walkie-talkie channel");
            } else {
                say(HANDLER, "Fake traffic report worked—the Rangers patrol sped off toward Clifton.");
                addHeat(4, "Wheelman lured Rangers away with fake call");
            }
            kit.set("Police Scanner", true);
        } else {
            cout << "  " << C::DIM << "That crew member's task is already resolved! Pick another pending task.\n" << C::R;
        }
    }
    pauseKey();

    // ===================== STAGE 2: BANK INFILTRATION =======================
    drawHUD(2, "Bank Infiltration");
    MapNetwork bank;
    int Street = bank.add("Street"), Front = bank.add("Front Door"), Alley = bank.add("Alley"),
        Roof = bank.add("Roof Vent"), Sewer = bank.add("Sewer"), Lobby = bank.add("Lobby"),
        Staff = bank.add("Staff Hall"), Server = bank.add("Server Room"),
        Tunnel = bank.add("Tunnel"), Office = bank.add("Office"),
        VaultHall = bank.add("Vault Hall"), Vault = bank.add("VAULT");

    bank.link(Street, Front, 3 + rnd(0, 2));  bank.link(Street, Alley, 3 + rnd(0, 2));
    bank.link(Street, Roof, 5 + rnd(0, 2));   bank.link(Street, Sewer, 5 + rnd(0, 2));
    bank.link(Front, Lobby, 4 + rnd(0, 2));   bank.link(Alley, Staff, 3 + rnd(0, 2));
    bank.link(Roof, Server, 3 + rnd(0, 2));   bank.link(Sewer, Tunnel, 2 + rnd(0, 2));
    bank.link(Lobby, Office, 3 + rnd(0, 2));  bank.link(Lobby, Staff, 4 + rnd(0, 2));
    bank.link(Staff, Office, 2 + rnd(0, 2));  bank.link(Server, VaultHall, 5 + rnd(0, 2));
    bank.link(Tunnel, VaultHall, 3 + rnd(0, 2)); bank.link(Office, VaultHall, 4 + rnd(0, 2));
    bank.link(VaultHall, Vault, 1);

    drawBankMap(bank, Street);
    cout << "  " << C::BOLD << "Choose which crew member's entry plan the syndicate executes:" << C::R << "\n"
         << "    1) " << C::CYN << "GHOST" << C::R << "    -> Rooftop & Camera Grid (Compare Safest Route vs. Direct Route)\n"
         << "    2) " << C::RED << "BREACHER" << C::R << " -> Underground Sewer Tunnel (Cut into a hidden private gold room)\n"
         << "    3) " << C::YEL << "BOSS" << C::R << "     -> Front Lobby Daylight Bluff (Confront supervisor with fake FIA papers)\n";

    int act2Who = readChoice(1, 3, 1, LEADER);
    vector<int> chosenRoute;
    int chosenRisk = 0;

    if (act2Who == 1) {
        bootDevice(HACKER, "Floorplan & Guard Patrol Scanner");
        int safeCost = 0;
        vector<int> safeRoute = bank.safestPath(Street, Vault, safeCost);
        vector<int> shortRoute = bank.fewestRoomsPath(Street, Vault);
        int shortCost = bank.routeRisk(shortRoute);

        cout << "  " << C::CYN << "Ghost's Problem: " << C::R << "Motion sensors cover every corridor. Pick your path to the vault:\n\n"
             << "    1) " << C::GRN << "Safest Route (Lowest Guard Risk): " << C::R << bank.pathStr(safeRoute) << "  (Risk: " << safeCost << ", -4 min)\n"
             << "    2) " << C::YEL << "Direct Route (Fewest Rooms):      " << C::R << bank.pathStr(shortRoute) << "  (Risk: " << shortCost << ", -2 min)\n";
        if (readChoice(1, 2, 1, HACKER) == 1) {
            chosenRoute = safeRoute; chosenRisk = safeCost; spendTime(4, "Ghost guided crew along safest route");
        } else {
            chosenRoute = shortRoute; chosenRisk = shortCost; spendTime(2, "Ghost rushed crew along direct route");
        }
    } else if (act2Who == 2) {
        bootDevice(BREACHER, "Seismic Wall Scanner");
        say(BREACHER, "We're in the Basement Tunnel. My scanner found a hollow brick wall next to the vault—it's a private gold room!");
        cout << "  " << C::RED << "Breacher's Problem: " << C::R << "Cutting into the private gold room takes extra time and makes noise:\n\n"
             << "    1) " << C::RED << "Cut open the hollow brick wall" << C::R << " (Unlocks Secret Platinum Bar, +9% Alert, -4 min)\n"
             << "    2) " << C::GRN << "Ignore the wall & quietly pry the Tunnel grate" << C::R << " (Clean entry, +2% Alert, -3 min)\n";
        chosenRoute.push_back(Street); chosenRoute.push_back(Sewer); chosenRoute.push_back(Tunnel); chosenRoute.push_back(VaultHall); chosenRoute.push_back(Vault);
        chosenRisk = 9;
        if (readChoice(1, 2, 1, BREACHER) == 1) {
            secretBullionRoomOpen = true;
            addHeat(9, "Breacher cut open secret gold room");
            spendTime(4, "Breached private gold room");
        } else {
            addHeat(2, "Breacher quietly opened Sewer Tunnel");
            spendTime(3, "Silent tunnel infiltration");
        }
    } else {
        bootDevice(LEADER, "Fake FIA Credentials");
        say(LEADER, "We walked right through the front doors. The floor supervisor is demanding to verify our FIA warrant!");
        cout << "  " << C::YEL << "Boss's Problem: " << C::R << "The supervisor is reaching for his desk phone to verify your badge number:\n\n"
             << "    1) " << C::YEL << "Bluff aggressively as a surprise FIA anti-corruption audit" << C::R << " (High chance of zero alert, -2 min)\n"
             << "    2) " << C::RED << "Draw weapons immediately & take over the lobby" << C::R << " (100% guaranteed entry, +10% Alert, -1 min)\n";
        chosenRoute.push_back(Street); chosenRoute.push_back(Front); chosenRoute.push_back(Lobby); chosenRoute.push_back(Office); chosenRoute.push_back(VaultHall); chosenRoute.push_back(Vault);
        if (readChoice(1, 2, 1, LEADER) == 1) {
            if (rnd(1, 100) <= 70) {
                say(LEADER, "He froze and handed over his master pass—bluff worked!");
                chosenRisk = 6;
                spendTime(2, "Bluffed past Front Lobby with fake FIA badges");
            } else {
                say(LEADER, "He spotted a typo on the stamp—guns up, secure the floor!");
                chosenRisk = 18;
                spendTime(2, "Cover blown at Front Lobby");
            }
        } else {
            say(LEADER, "Everybody on the ground! Nobody touch the counters!");
            chosenRisk = 18;
            spendTime(1, "Stormed Front Lobby directly");
        }
    }

    for (size_t i = 1; i + 1 < chosenRoute.size(); i++) {
        drawBankMap(bank, chosenRoute[i]);
        sleepMs(220);
    }
    addHeat(max(0, chosenRisk - 8), "Entry exposure level: " + toStr(chosenRisk));
    runNegotiatorCall();
    pauseKey();

    // ===================== STAGE 3: INSIDE THE BANK (ALL 3 SOLVED) ==========
    priority_queue<Hostage> hostages;
    Hostage h1 = {
        "Tariq Mahmood", "Branch Manager",
        "Keeps glancing at his waist and whispering numbers under his breath.",
        "Pat him down & demand his executive override card (-45 panic, -1 min)",
        "Tell him to sit still and breathe calmly (-60 panic, 0% Alert)",
        92
    };
    Hostage h2 = {
        "Farhan Qureshi", "Senior Guard",
        "Slowly sliding his hand toward a concealed walkie-talkie on his belt.",
        "Confiscate his hidden radio & zip-tie his wrists (-45 panic, -1 min)",
        "Order him to keep both hands flat on the floor (-60 panic, 0% Alert)",
        86
    };
    Hostage h3 = {
        "Ayesha Siddiqui", "Head Cashier",
        "Sitting right next to the under-desk silent alarm pedal.",
        "Move her away from the teller counter & check her pockets (-45 panic, -1 min)",
        "Reassure her nobody will be harmed if she stays put (-60 panic, 0% Alert)",
        78
    };
    Hostage h4 = {
        "Kamran Raza", "Corporate Lawyer",
        "Reaching into his coat pocket for his phone to call DIG Police.",
        "Take his phone & check his briefcase (-45 panic, -1 min)",
        "Warn him firmly to drop the phone and stay down (-60 panic, 0% Alert)",
        74
    };
    Hostage h5 = {
        "Haris Sethi", "Bullion Merchant",
        "Shaking nervously near the private safety deposit boxes.",
        "Question him about the vault layout (-45 panic, -1 min)",
        "Move him to the carpeted lounge area to calm down (-60 panic, 0% Alert)",
        65
    };
    Hostage h6 = {
        "Zainab Noor", "University Student",
        "Hyperventilating near the glass exit doors.",
        "Escort her away from the glass doors & check her bag (-45 panic, -1 min)",
        "Give her water and calm her breathing (-60 panic, 0% Alert)",
        58
    };
    hostages.push(h1); hostages.push(h2); hostages.push(h3);
    hostages.push(h4); hostages.push(h5); hostages.push(h6);

    bool lobbyDone = false, serverDone = false, stairwellDone = false;

    while (!lobbyDone || !serverDone || !stairwellDone) {
        drawHUD(3, "Inside the Bank (Coordinate All 3 Sectors)");
        cout << "  " << C::BOLD << "Three simultaneous crises are unfolding—switch to each member to resolve them:" << C::R << "\n"
             << "    1) " << (lobbyDone ? C::GRN + "[SECURED]  WHEELMAN " : C::GRN + "[ACTIVE]   WHEELMAN ") << C::R
             << "-> Main Lobby: 6 panicking hostages; guard reaching for a hidden radio\n"
             << "    2) " << (serverDone ? C::GRN + "[SECURED]  GHOST    " : C::CYN + "[ACTIVE]   GHOST    ") << C::R
             << "-> Server Room: 5 silent alarms counting down to auto-dial 15 Police & FIA\n"
             << "    3) " << (stairwellDone ? C::GRN + "[SECURED]  BREACHER " : C::RED + "[ACTIVE]   BREACHER ") << C::R
             << "-> Vault Stairwell: 2 armed guards rushing down toward the vault hall\n"
             << "    0) " << C::YEL << "Tell remaining crew to handle their sectors on comms" << C::R << " (0 min lost, +7% Alert per unplayed sector)\n";

        int act3Who = readChoice(0, 3, 1, LEADER);
        if (act3Who == 0) {
            if (!lobbyDone) {
                lobbyDone = true;
                addHeat(7, "Wheelman suppressed lobby loudly while on comms");
            }
            if (!serverDone) {
                serverDone = true;
                addHeat(7, "Ghost rushed alarm shutdown on comms");
            }
            if (!stairwellDone) {
                stairwellDone = true;
                addHeat(7, "Breacher got into a loud scuffle in stairwell");
            }
            break;
        } else if (act3Who == 1 && !lobbyDone) {
            lobbyDone = true;
            bootDevice(HANDLER, "Crowd Panic Monitor");
            for (int turn = 1; turn <= 2; turn++) {
                Hostage topH = hostages.top(); hostages.pop();
                cout << "  Highest Panic (#" << turn << "): " << C::YEL << topH.name << C::R
                     << " (" << topH.role << ")  |  Panic Level: " << C::RED << topH.panic << "/100" << C::R << "\n"
                     << "  What's happening: " << C::CYN << topH.observation << C::R << "\n"
                     << "    1) " << C::GRN << topH.checkPrompt << C::R << "\n"
                     << "    2) " << C::YEL << topH.calmPrompt << C::R << "\n";
                if (readChoice(1, 2, 1, HANDLER) == 1) {
                    spendTime(1, "Wheelman intervened with " + topH.name);
                    if (topH.name == "Tariq Mahmood") {
                        managerKeycardObtained = true; vaultFirstDigitKnown = true;
                        say(HANDLER, "Took Tariq's executive vault keycard—and he gave up the vault's first digit!");
                        missionLog.push("Seized executive keycard & 1st PIN digit from Tariq Mahmood");
                    } else if (topH.name == "Farhan Qureshi") {
                        guardRadioIntercepted = true;
                        say(HANDLER, "Snatched Farhan's concealed police radio right before he could key the mic.");
                        missionLog.push("Confiscated concealed radio from Guard Farhan Qureshi");
                    } else {
                        say(HANDLER, "Moved " + topH.name + " to a secure spot and cleared the risk.");
                    }
                    topH.panic = max(10, topH.panic - 45);
                } else {
                    say(HANDLER, "Easy now, " + topH.name + ". Stay calm and nobody gets hurt.");
                    topH.panic = max(10, topH.panic - 60);
                }
                hostages.push(topH);
                cout << "\n";
            }
        } else if (act3Who == 2 && !serverDone) {
            serverDone = true;
            bootDevice(HACKER, "Security Threat Override");
            SecurityNode sysArr[5] = {
                {"FIA Silent Link", 10}, {"15 Police Auto-Dialer", 9},
                {"Vault Seismic Grid", 8}, {"CCTV Camera Feed", 7}, {"Laser Hallway Traps", 6}
            };
            priority_queue<pair<int, string> > pq;
            for (int i = 0; i < 5; i++) pq.push(make_pair(sysArr[i].threat, sysArr[i].name));

            cout << "  " << C::CYN << "Ghost's Problem: " << C::R << "Five silent alarms are active—starting with "
                 << C::RED << pq.top().second << " (Danger 10)" << C::R << ":\n\n"
                 << "    1) " << C::GRN << "Shut down alarms in order of danger + read vault keypad voltage" << C::R << " (Reveals 1st PIN digit, -2 min)\n"
                 << "    2) " << C::CYN << "Fire EMP Pulse into the server rack" << C::R << " (Instant blackout, 0 min, uses EMP)\n";
            int gHack = readChoice(1, empAvailable ? 2 : 1, 1, HACKER);
            if (gHack == 2 && empAvailable) {
                empAvailable = false;
                say(HACKER, "EMP fired. All 5 security systems went dark immediately.");
                missionLog.push("Ghost wiped security systems with EMP");
            } else {
                spendTime(2, "Ghost disabled security alarms by danger level");
                while (!pq.empty()) {
                    cout << "    Disabled: " << left << setw(24) << pq.top().second << "(Danger " << pq.top().first << ")\n";
                    pq.pop(); sleepMs(130);
                }
                vaultFirstDigitKnown = true;
                say(HACKER, "I also read the keypad's voltage log—the vault's first digit is locked in.");
                missionLog.push("Ghost tapped vault keypad for 1st digit");
            }
        } else if (act3Who == 3 && !stairwellDone) {
            stairwellDone = true;
            bootDevice(BREACHER, "Proximity Motion Sensor");
            cout << "  " << C::RED << "Breacher's Problem: " << C::R << "Two armed guards just entered the Vault Corridor stairwell!\n\n"
                 << "    1) " << C::GRN << "Deploy tear gas & lock the steel fire door" << C::R << " (Traps guards silently, -2 min, 0% Alert)\n"
                 << "    2) " << C::RED << "Ambush & disarm them before they reach the corridor" << C::R << " (0 min lost, "
                 << (guardRadioIntercepted ? "0% Alert - Guard Radio intercepted!)" : "+6% Alert)") << "\n";
            if (readChoice(1, 2, 1, BREACHER) == 1) {
                say(BREACHER, "Popped a tear gas canister in the stairwell and bolted the fire door behind them.");
                spendTime(2, "Breacher sealed off stairwell guards with tear gas");
                missionLog.push("Breacher trapped patrol guards in stairwell");
            } else {
                say(BREACHER, "Both guards disarmed and zip-tied! Corridor is clear.");
                if (guardRadioIntercepted) {
                    say(HANDLER, "Good thing I seized Farhan's radio—they couldn't call for backup!");
                } else {
                    addHeat(6, "Stairwell guards triggered distress click on their radio");
                }
            }
        } else {
            cout << "  " << C::DIM << "That sector is already secured! Pick another active sector.\n" << C::R;
        }
    }
    runNegotiatorCall();
    pauseKey();

    // ===================== STAGE 4: VAULT BREACH ============================
    drawHUD(4, "The Titanium Vault");
    drawBankMap(bank, Vault);

    string secret;
    vector<int> digs;
    while (true) {
        vector<int> pool;
        for (int i = 0; i < 10; i++) pool.push_back(i);
        random_shuffle(pool.begin(), pool.end());
        digs.assign(pool.begin(), pool.begin() + 4);
        vector<int> perm = digs;
        random_shuffle(perm.begin(), perm.end());
        secret.clear();
        for (size_t i = 0; i < perm.size(); i++) secret += char('0' + perm[i]);
        if (codeOK(secret)) break;
    }
    sort(digs.begin(), digs.end());

    cout << "  " << C::BOLD << "Choose which crew member cracks the Titanium Vault:" << C::R << "\n"
         << "    1) " << C::CYN << "GHOST" << C::R << "    -> Digital Keypad Lock (Analyze heat signatures & crack the 4-digit PIN)\n"
         << "    2) " << C::RED << "BREACHER" << C::R << " -> Mechanical Steel Bolts (Cut through the 3-inch titanium locking bars)\n"
         << "    3) " << C::YEL << "BOSS" << C::R << "     -> Executive Override Panel (Use Tariq's keycard or bluff central security)\n";

    int act4Who = readChoice(1, 3, 1, LEADER);
    if (act4Who == 3) {
        bootDevice(LEADER, "Executive Override & Intercom");
        if (managerKeycardObtained) {
            cout << "  " << C::YEL << "Boss's Advantage: " << C::R << "You hold Branch Manager Tariq Mahmood's biometric keycard:\n\n"
                 << "    1) " << C::GRN << "Swipe Tariq's keycard & enter his override ID" << C::R << " (Instant silent open, 0 min, 0% Alert)\n";
            readChoice(1, 1, 1, LEADER);
            say(LEADER, "Swiping Tariq Mahmood's executive keycard... Vault unlocked silently!");
            sfxUnlock();
            missionLog.push("Boss unlocked vault silently using Tariq's keycard");
        } else {
            cout << "  " << C::YEL << "Boss's Problem: " << C::R << "You don't have the manager's keycard, and central security is asking for a voice code:\n\n"
                 << "    1) " << C::YEL << "Force Manager Tariq Mahmood onto the intercom at gunpoint" << C::R << " (-2 min, +6% Alert)\n"
                 << "    2) " << C::CYN << "Impersonate the regional auditor on the intercom" << C::R << " (-3 min, +3% Alert)\n";
            if (readChoice(1, 2, 1, LEADER) == 1) {
                say(LEADER, "Tariq read the daily authorization phrase—vault bolts just retracted!");
                spendTime(2, "Forced manager to authorize vault release");
                addHeat(6, "Manager sounded distressed on vault intercom");
            } else {
                say(LEADER, "Gave them the Karachi South audit code—central dispatch released the lock!");
                spendTime(3, "Bluffed central security over vault intercom");
                addHeat(3, "Auditor voice override logged by central security");
            }
            sfxUnlock();
        }
    } else if (act4Who == 2) {
        bootDevice(BREACHER, "High-Pressure Thermite Lance");
        cout << "  " << C::RED << "Breacher's Problem: " << C::R << "Four thick steel locking bars hold the vault door shut:\n\n"
             << "    1) " << C::RED << "Full-power thermite burn across all 4 bolts" << C::R << " (Fast breach, -3 min, +12% Alert)\n"
             << "    2) " << C::YEL << "Precision low-heat cut + hydraulic spreader" << C::R << " (Quieter, -5 min, +6% Alert)\n";
        if (readChoice(1, 2, 1, BREACHER) == 1) {
            say(BREACHER, "Visors down! Burning straight through all four locking bars!");
            spendTime(3, "Breacher melted vault locking bolts");
            addHeat(12, "Vibration sensors triggered by thermite lance");
        } else {
            say(BREACHER, "Scored the hinges cleanly and spread the frame with the hydraulic jack.");
            spendTime(5, "Breacher quietly spread vault door frame");
            addHeat(6, "Low-heat cut registered minor vibration");
        }
        sfxUnlock();
    } else {
        bootDevice(HACKER, "Smart Keypad Solver");
        cout << "  " << C::CYN << "Ghost's Problem: " << C::R << "The vault keypad requires a 4-digit PIN. Thermal scan shows 4 warm keys:\n"
             << "  Warm Keys Detected : ";
        for (size_t i = 0; i < digs.size(); i++) cout << C::YEL << "[" << digs[i] << "] " << C::R;
        cout << "\n  Keypad Clues       : " << C::CYN << "1st digit EVEN  |  2nd digit ODD  |  4th digit > 1st digit" << C::R << "\n";
        if (vaultFirstDigitKnown) {
            cout << "  " << C::GRN << "Intel Bonus        : Confirmed 1st digit is " << secret[0] << C::R << "\n";
        }

        string guess = readCodeInput();
        bool cracked = false;
        if (!guess.empty() && guess == secret) {
            cout << "  " << C::GRN << C::BOLD << "Exact match! Vault unlocked on your manual guess (-5% Alert).\n" << C::R;
            sfxUnlock();
            addHeat(-5, "Boss deduced vault PIN " + secret + " manually");
            cracked = true;
        } else {
            if (!guess.empty()) { cout << "  " << C::RED << "Incorrect PIN (" << guess << "). Eliminating invalid combinations...\n\n" << C::R; addHeat(2, "Wrong PIN guess " + guess); }
            vector<string> cands; vector<bool> used(4, false);
            cout << "  " << C::BOLD << C::CYN << "Step-by-Step Clue Elimination:" << C::R << "\n";
            findValidPins("", digs, used, cands, true);
            say(HACKER, "Narrowed 10,000 possible PINs down to just " + toStr((int)cands.size()) + " valid codes.");
            for (size_t i = 0; i < cands.size(); i++) {
                cout << "    Testing " << C::YEL << cands[i] << C::R << " -> ";
                sfxClick();
                sleepMs(180);
                if (cands[i] == secret) { cout << C::GRN << "UNLOCKED\n" << C::R; sfxUnlock(); cracked = true; break; }
                cout << C::RED << "denied\n" << C::R;
                addHeat(1, "Keypad rejected " + cands[i]);
            }
            spendTime(2, "Cracked vault keypad");
        }
    }
    runNegotiatorCall();
    pauseKey();

    // ===================== STAGE 5: VAULT TREASURY ==========================
    drawHUD(5, "Vault Treasury & Bag Packing");
    bootDevice(LEADER, "Loot Value Calculator");

    vector<Loot> items;
    Loot l1 = {"Saddar Diamond Pouch", 1, 55};   items.push_back(l1);
    Loot l2 = {"State Bearer Bonds",   3, 130};  items.push_back(l2);
    Loot l3 = {"Mughal Gold Mohurs",   2, 85};   items.push_back(l3);
    Loot l4 = {"Emerald Necklace",     4, 155};  items.push_back(l4);
    Loot l5 = {"24K Bullion Bricks",   6, 215};  items.push_back(l5);
    Loot l6 = {"Unmarked Dollar Bills",5, 165};  items.push_back(l6);
    if (secretBullionRoomOpen) {
        Loot l7 = {"Secret Room Platinum", 3, 185}; items.push_back(l7);
        say(BREACHER, "The hidden gold room paid off—added a 3 kg Platinum Bar worth $185K.");
    }

    int n = (int)items.size();
    vector<bool> picked(n, false);
    int pW = 0, pVal = 0;

    if (!FAST) {
        while (true) {
            cout << "\n  " << C::BOLD << "Boss's Problem: Your duffel bags can only hold " << bagCapacity
                 << " kg total. Pack the highest-value loot (Current: " << pW << "/" << bagCapacity
                 << " kg  |  $" << pVal << "K):" << C::R << "\n\n";
            for (int i = 0; i < n; i++) {
                cout << "    " << i + 1 << ") " << (picked[i] ? C::GRN + "[PACKED] " : C::DIM + "[      ] ") << C::R
                     << left << setw(23) << items[i].name << setw(6) << (toStr(items[i].w) + "kg")
                     << C::YEL << "$" << items[i].v << "K" << C::R << "\n";
            }
            cout << "    0) " << C::CYN << "Zip bags & verify if this is the highest-value combination" << C::R << "\n";
            int ch = readChoice(0, n, 0, LEADER);
            if (ch == 0) break;
            int idx = ch - 1;
            if (picked[idx]) { picked[idx] = false; pW -= items[idx].w; pVal -= items[idx].v; }
            else if (pW + items[idx].w <= bagCapacity) { picked[idx] = true; pW += items[idx].w; pVal += items[idx].v; }
            else cout << "  " << C::RED << "Exceeds your " << bagCapacity << " kg bag limit.\n" << C::R;
        }
    }

    vector<vector<int> > dp(n + 1, vector<int>(bagCapacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int c = 0; c <= bagCapacity; c++) {
            dp[i][c] = dp[i - 1][c];
            if (items[i - 1].w <= c) dp[i][c] = max(dp[i][c], dp[i - 1][c - items[i - 1].w] + items[i - 1].v);
        }
    }
    int bestVal = dp[n][bagCapacity];
    vector<int> bestItems;
    int remC = bagCapacity;
    for (int i = n; i >= 1; i--) {
        if (dp[i][remC] != dp[i - 1][remC]) { bestItems.push_back(i - 1); remC -= items[i - 1].w; }
    }

    vector<pair<int, Loot> > order;
    for (int i = 0; i < n; i++) order.push_back(make_pair(i, items[i]));
    sort(order.begin(), order.end(), ratioOrder);
    int gw = 0, gv = 0;
    for (int i = 0; i < n; i++) if (gw + order[i].second.w <= bagCapacity) { gw += order[i].second.w; gv += order[i].second.v; }

    if (FAST) pVal = bestVal;

    cout << "  " << C::BOLD << "Bag Packing Check:" << C::R << "\n"
         << "    Your Haul          : " << C::YEL << "$" << pVal << "K" << C::R << "\n"
         << "    Quick Grab Estimate: " << C::DIM << "$" << gv << "K" << C::R << "\n"
         << "    Best Possible Haul : " << C::GRN << "$" << bestVal << "K" << C::R << " (";
    for (size_t i = 0; i < bestItems.size(); i++) cout << items[bestItems[i]].name << (i + 1 < bestItems.size() ? ", " : "");
    cout << ")\n";

    int finalLoot = pVal;
    if (pVal < bestVal) {
        cout << "\n    1) Leave immediately with $" << pVal << "K (0 min)\n"
             << "    2) Repack bags to reach $" << bestVal << "K (-2 min)\n";
        if (readChoice(1, 2, 2, LEADER) == 2) { finalLoot = bestVal; spendTime(2, "Repacked bags for maximum haul"); }
    } else {
        say(HACKER, "Perfect packing—you grabbed the highest possible value your bags can hold.");
    }
    missionLog.push("Extracted $" + toStr(finalLoot) + "K from vault");
    pauseKey();

    // ===================== STAGE 6: KARACHI GETAWAY =========================
    drawHUD(6, "Karachi Getaway Drive");
    MapNetwork city;
    int Bk = city.add("Bank"), Sad = city.add("Saddar"), Twr = city.add("Tower"),
        Cli = city.add("Clifton Bridge"), Fai = city.add("Shahrah-e-Faisal"), Lya = city.add("Lyari Exp"),
        Kor = city.add("Korangi"), Byp = city.add("N. Bypass"), Hid = city.add("SAFEHOUSE");

    city.link(Bk, Sad, 3);  city.link(Bk, Twr, 4);  city.link(Sad, Fai, 6); city.link(Sad, Cli, 7);
    city.link(Twr, Lya, 5); city.link(Twr, Fai, 5); city.link(Cli, Fai, 5); city.link(Cli, Hid, 15);
    city.link(Fai, Kor, 6); city.link(Fai, Byp, 8); city.link(Fai, Hid, 14);
    city.link(Kor, Hid, 8); city.link(Lya, Byp, 6); city.link(Byp, Hid, 10); city.link(Lya, Kor, 9);

    drawCityMap(city, Bk);

    int cur = Bk, driveTime = 0, blocks = 0;
    int blockChance = (heat >= 50 || swatMins <= 6) ? 75 : 45;

    while (cur != Hid) {
        int cst;
        vector<int> p = city.safestPath(cur, Hid, cst);
        int nxt = p[1], w = city.getWeight(cur, nxt);

        if (blocks < 2 && rnd(1, 100) <= blockChance) {
            city.setBlocked(cur, nxt, true);
            int c2;
            vector<int> alt = city.safestPath(cur, Hid, c2);
            if (alt.empty()) {
                city.setBlocked(cur, nxt, false);
            } else {
                blocks++;
                sfxAlarm();
                drawCityMap(city, cur);
                cout << "  " << C::BOLD << "Pursuit Crisis! Choose which crew member handles it:" << C::R << "\n"
                     << "    1) " << C::CYN << "GHOST" << C::R << "    -> Police Roadblock Ahead (" << city.names[cur] << " to " << city.names[nxt] << ")\n"
                     << "    2) " << C::GRN << "WHEELMAN" << C::R << " -> Two Patrol Cruisers Tailing Your Bumper\n";
                if (empAvailable) cout << "    3) " << C::YEL << "BOSS" << C::R << "     -> Police Chopper Spotlight Locked on Van Roof\n";

                int eCall = readChoice(1, empAvailable ? 3 : 2, 1, LEADER);
                if (eCall == 3 && empAvailable) {
                    bootDevice(LEADER, "Remote EMP & Countermeasures");
                    cout << "  " << C::YEL << "Boss's Problem: " << C::R << "A police helicopter spotlight is tracking your Armored Vigo from above:\n\n"
                         << "    1) " << C::YEL << "Trigger remote EMP burst to scramble cruiser & chopper radar" << C::R << " (0 extra time, 0% Alert)\n";
                    readChoice(1, 1, 1, LEADER);
                    empAvailable = false; city.setBlocked(cur, nxt, false);
                    say(LEADER, "EMP triggered—patrol cruisers stalled and chopper lost radar lock!");
                    missionLog.push("Boss used EMP to lose police chopper & blockade");
                } else if (eCall == 2) {
                    bootDevice(HANDLER, "Pursuit Driving Telemetry");
                    city.setBlocked(cur, nxt, false);
                    cout << "  " << C::GRN << "Wheelman's Problem: " << C::R << "Two patrol cruisers are matching your speed right behind you:\n\n"
                         << "    1) " << C::GRN << "Cut sharply into narrow Saddar market lanes" << C::R << " (Shakes cruisers fast, +10% Alert)\n"
                         << "    2) " << C::YEL << "Weave through heavy highway traffic at 140 km/h" << C::R << " (+2 min drive time, +4% Alert)\n";
                    if (readChoice(1, 2, 1, HANDLER) == 1) {
                        say(HANDLER, "Hold onto the grab handles—cutting through the narrow market lane!");
                        addHeat(10, "Wheelman shook patrol cruisers in narrow alleys");
                    } else {
                        driveTime += 2;
                        say(HANDLER, "Lost them behind a convoy of freight trucks on the main road.");
                        addHeat(4, "Wheelman outmaneuvered cruisers in highway traffic");
                    }
                } else {
                    bootDevice(HACKER, "Live Traffic Rerouter");
                    cout << "  " << C::CYN << "Ghost's Problem: " << C::R << "Police blocked " << city.names[cur] << " to " << city.names[nxt] << ".\n"
                         << "  Alternate clear route found: " << C::GRN << city.pathStr(alt) << " (" << c2 << " min total)" << C::R << "\n\n"
                         << "    1) " << C::CYN << "Switch GPS to the alternate route & spoof traffic lights green" << C::R << " (+3% Alert)\n";
                    readChoice(1, 1, 1, HACKER);
                    say(HACKER, "Traffic lights overridden. Rerouting via " + city.pathStr(alt) + ".");
                    addHeat(3, "Ghost rerouted around blockade at " + city.names[nxt]);
                    continue;
                }
            }
        }
        driveTime += w;
        cur = nxt;
        drawCityMap(city, cur);
        cout << "  " << C::GRN << "Cleared " << city.names[cur] << C::R << " (+" << w << " min | Drive elapsed: " << driveTime << " min)\n\n";
        sleepMs(300);
    }
    missionLog.push("Reached Safehouse in " + toStr(driveTime) + " min");

    // ===================== STAGE 7: MISSION DEBRIEF =========================
    drawHUD(7, "Mission Debrief & Replay");
    bool busted = (heat >= 90 || swatMins <= 0);
    string rank;
    if (busted) rank = "BUSTED (SWAT Intercepted Crew)";
    else if (heat < 25 && finalLoot == bestVal) rank = "S-TIER MASTERMIND";
    else if (heat < 55) rank = "A-TIER CLEAN GETAWAY";
    else rank = "B-TIER HOT PURSUIT SURVIVOR";

    int recordedHaul = busted ? 0 : finalLoot;
    saveRecord(rank, recordedHaul, heat, driveTime);
    if (!busted) sfxUnlock();

    cout << "  " << C::BOLD << "Final Results:" << C::R << "\n"
         << "    Final Alert     : " << (heat >= 70 ? C::RED : C::YEL) << heat << "%" << C::R << "\n"
         << "    SWAT Time Left  : " << (swatMins <= 0 ? C::RED + "0 min (Breached)" : C::CYN + toStr(swatMins) + " min") << C::R << "\n"
         << "    Escape Drive    : " << driveTime << " min\n"
         << "    Final Haul      : " << (busted ? C::RED + "$0 (Confiscated)" : C::GRN + "$" + toStr(finalLoot) + "K") << C::R << "\n"
         << "    Mission Rank    : " << C::BOLD << C::YEL << rank << C::R << "\n\n"
         << "  " << C::BOLD << C::CYN << "Mission Timeline (Latest Event First):" << C::R << "\n";

    int step = 1;
    while (!missionLog.empty()) {
        cout << "    " << setw(2) << step++ << ". " << missionLog.top() << "\n";
        missionLog.pop();
    }

    showHallOfFame();
    cout << "\n";
    return 0;
}