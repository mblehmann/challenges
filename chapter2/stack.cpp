#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const string VALUES = "23456789TJQKA";
const string SUITS = "CDHS";

int get_rank(char value, char suit) {
    for (int i = 0; i < SUITS.length(); i++) {
        if (suit == SUITS[i]) {
            for (int j = 0; j < VALUES.length(); j++) {
                if (value == VALUES[j]) {
                    return i*VALUES.size()+j;
                }
            }
        }
    }
    return -1;
}

int get_rank(string card) {
    return get_rank(card[0], card[1]);
}

int get_value(int rank) {
    return rank % VALUES.size();
}

int get_suit(int rank) {
    return rank / VALUES.size();
}

char value_to_string(int value) {
    return VALUES[value];
}

char suit_to_string(int suit) {
    return SUITS[suit];
}

string rank_to_string(int rank) {
    string card;
    char v = value_to_string(get_value(rank));
    switch (v) {
        case 'A': card = "Ace"; break;
        case 'K': card = "King"; break;
        case 'Q': card = "Queen"; break;
        case 'J': card = "Jack"; break;
        case 'T': card = "10"; break;
        default: card = v; break;
    }
    
    card += " of ";
    
    char s = suit_to_string(get_suit(rank));
    switch (s) {
        case 'C': card += "Clubs"; break;
        case 'D': card += "Diamonds"; break;
        case 'H': card += "Hearts"; break;
        case 'S': card += "Spades"; break;
        default: break;
    }
    
    return card;
}

int main() {
    int t;
    int n;
    
    int c;
    string s;
    
    cin >> t;
    while (t > 0) {
        cin >> n;
        // initialize deck
        vector<int> deck(52, 0);
        for (int i = 0; i < 52; i++) {
            deck[i] = i;
        }
        
        // record the shuffles
        vector<vector<int> > shuffles(n, vector<int>(52, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 52; j++) {
                cin >> c;
                shuffles[i][j] = c-1; // we use 0 - 51 values
            }
        }
        getline(cin, s);
        
        // get the shuffle action
        while (getline(cin, s)) {
            if (s == "") break;
            c = stoi(s)-1;
            vector<int> new_deck(52, 0);
            for (int i = 0; i < 52; i++) {
                new_deck[i] = deck[shuffles[c][i]];
            }
            deck = new_deck;
        }
        
        for (int i = 0; i < 52; i++) {
            cout << rank_to_string(deck[i]) << endl;
        }
        
        if (t > 1) cout << endl;
        
        // done with this instance
        t--;
    }
    
    return 0;
}
