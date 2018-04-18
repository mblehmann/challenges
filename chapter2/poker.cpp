#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const string VALUES = "23456789TJQKA";
const string SUITS = "CDHS";

const int STRAIGHTFLUSH = 400;
const int FLUSH = 250;
const int STRAIGHT = 200;
const int FOURKIND = 350;
const int FULLHOUSE = 300;
const int THREEKIND = 150;
const int TWOPAIS = 100;
const int ONEPAIR = 50;
const int HIGHCARD = 0;

int get_rank(char value, char suit) {
    for (int i = 0; i < VALUES.length(); i++) {
        if (value == VALUES[i]) {
            for (int j = 0; j < SUITS.size(); j++) {
                if (suit == SUITS[j]) {
                    return i*SUITS.size()+j;
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
    return rank / SUITS.size();
}

int get_suit(int rank) {
    return rank % SUITS.size();
}

char value_to_string(int value) {
    return VALUES[value];
}

char suit_to_string(int suit) {
    return SUITS[suit];
}

int compare_hands(vector<int> hand1, vector<int> hand2) {
    for (int i = hand1.size()-1; i >= 0; i--) {
        if (get_value(hand1[i]) > get_value(hand2[i])) return 1;
        if (get_value(hand1[i]) < get_value(hand2[i])) return -1;
    }
    return 0;
}

int flush(vector<int> hand) {
    for (int i = 0; i < hand.size()-1; i++) {
        if (get_suit(hand[i]) != get_suit(hand[i+1])) return 0;
    }
    return FLUSH;
}

int straight(vector<int> hand) {
    for (int i = 0; i < hand.size()-1; i++) {
        if (abs(get_value(hand[i])-get_value(hand[i+1])) != 1) return 0;
    }
    return STRAIGHT;
}

int straight_flush(vector<int> hand) {
    if (flush(hand) && straight(hand)) {
        return STRAIGHTFLUSH;
    }
    return 0;
}

map<int, int> count_cards(vector<int> hand) {
    map<int, int> p;
    int v;
    for (int i = 0; i < hand.size(); i++) {
        v = get_value(hand[i]);
        if (p.count(v) == 0) {
            p[v] = 0;
        }
        p[v]++;
    }
    return p;
}

int compare_cards(vector<int> hand1, vector<int> hand2) {
    map<int, int> h1 = count_cards(hand1);
    map<int, int> h2 = count_cards(hand2);
    int c1, c2;
    int m1, m2;
    while (!h1.empty()) {
        m1 = m2 = 0;
        for (map<int, int>::iterator card1 = h1.begin(); card1 != h1.end(); ++card1) {
            if (card1->second > m1 || (card1->second == m1 && card1->first > c1)) {
                m1 = card1->second;
                c1 = card1->first;
            }
        }
        for (map<int, int>::iterator card2 = h2.begin(); card2 != h2.end(); ++card2) {
            if (card2->second > m2 || (card2->second == m2 && card2->first > c2)) {
                m2 = card2->second;
                c2 = card2->first;
            }
        }
        if (c1 > c2) return 1;
        if (c1 < c2) return -1;

        h1.erase(c1);
        h2.erase(c2);
    }
    return 0;
}

int four_of_a_kind(map<int, int> hand) {
    for (map<int, int>::iterator card = hand.begin(); card != hand.end(); ++card) {
        if (card->second == 4) return FOURKIND;
    }
    return 0;
}

int full_house(map<int, int> hand) {
    if (hand.size() == 2) return FULLHOUSE;
    return 0;
}

int three_of_a_kind(map<int, int> hand) {
    for (map<int, int>::iterator card = hand.begin(); card != hand.end(); ++card) {
        if (card->second == 3) return THREEKIND;
    }
    return 0;
}

int two_pairs(map<int, int> hand) {
    if (hand.size() == 3) return TWOPAIS;
    return 0;
}

int one_pair(map<int, int> hand) {
    for (map<int, int>::iterator card = hand.begin(); card != hand.end(); ++card) {
        if (card->second == 2) return ONEPAIR;
    }
    return 0;
}

int evaluate_hand(vector<int> hand) {
    int score = HIGHCARD;
    
    score = straight_flush(hand);
    if (score > 0) return score;

    score = flush(hand);
    if (score > 0) return score;

    score = straight(hand);
    if (score > 0) return score;

    map<int, int> h = count_cards(hand);
    
    score = four_of_a_kind(h);
    if (score > 0) return score;

    score = full_house(h);
    if (score > 0) return score;

    score = three_of_a_kind(h);
    if (score > 0) return score;

    score = two_pairs(h);
    if (score > 0) return score;

    score = one_pair(h);
    if (score > 0) return score;

    return score;
}

int main() {
    vector<vector<int> > game(2, vector<int>(5, 0));
    vector<int> score(2, 0);
    string card;
    int t;
    
    while (cin >> card) {
        game[0][0] = get_rank(card);
        for (int i = 1; i < 5; i++) {
            cin >> card;
            game[0][i] = get_rank(card);
        }
        for (int i = 0; i < 5; i++) {
            cin >> card;
            game[1][i] = get_rank(card);
        }
        
        for (int i = 0; i < score.size(); i++) {
            sort(game[i].begin(), game[i].end());
            score[i] = evaluate_hand(game[i]);
        }
        
        if (score[0] > score[1]) {
            cout << "Black wins." << endl;
        } else if (score[0] < score[1]) {
            cout << "White wins." << endl;
        } else {
            if (score[0] == STRAIGHTFLUSH || score[0] == FLUSH || score[0] == STRAIGHT || score[0] == HIGHCARD) {
                t = compare_hands(game[0], game[1]);
            } else {
                t = compare_cards(game[0], game[1]);
            }
            if (t > 0) {
                cout << "Black wins." << endl;
            } else if (t < 0) {
                cout << "White wins." << endl;
            } else {
                cout << "Tie." << endl;
            }
        }
    }
    
    return 0;
}
