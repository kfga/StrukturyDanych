#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <vector>
#include <time.h>


using namespace std;

enum Kierunek
{
    lewo = -1,
    prawo = 1
};

struct Rule {
    public:
        char znakWejscia;
        int stanWejscia;
        char znakWyjscia;
        int stanWyjscia;
        Kierunek dir;

};

void wypelnienie(vector<char> &tasma, vector<char> dictionary, int iloscZnakow, char znakPusty)
{
    srand (time(NULL));
    tasma.push_back(znakPusty);
    for(int i = 0; i < iloscZnakow; i++)
    {
        tasma.push_back(dictionary[rand() % dictionary.size()]);
    }
    tasma.push_back(znakPusty);
}

void wypiszTasme(vector<char> tasma)
{
    for(int i = 0; i < tasma.size(); i++)
    {
        cout << tasma[i];
    }
}

bool findRule(vector<Rule> rules, Rule &currentRule)
{
    bool ret = false;
    for(int i = 0; i < rules.size(); i++)
    {
        if(rules[i].znakWejscia == currentRule.znakWejscia && rules[i].stanWejscia == currentRule.stanWejscia)
        {
            currentRule.znakWyjscia = rules[i].znakWyjscia;
            currentRule.stanWyjscia = rules[i].stanWyjscia;
            currentRule.dir = rules[i].dir;
            ret = true;
        }
    }
    return ret;
}

void Process(vector<Rule> rules, vector<char> &tasma, int stanPoczatkowy)
{

    int iter = tasma.size() - 2;
    Rule currentRule{tasma[iter], stanPoczatkowy, ' ', 0, Kierunek::lewo};
    while(findRule(rules, currentRule ))
    {

        tasma[iter] = currentRule.znakWyjscia;
        currentRule.stanWejscia = currentRule.stanWyjscia;
        iter += currentRule.dir;
        currentRule.znakWejscia = tasma[iter];
    }
}

int main()
{
    vector<char> dictionary{'0','1'};
    vector<int> stan{0, 1, 2};
    vector<char> tasma;

    wypelnienie(tasma, dictionary, 8, '#');

    vector<Rule> rules = {{dictionary[0], stan[0], dictionary[1], stan[2], Kierunek::lewo},
                         {dictionary[1], stan[0], dictionary[0], stan[1], Kierunek::lewo},
                         {dictionary[0], stan[1], dictionary[1], stan[2], Kierunek::lewo},
                         {dictionary[1], stan[1], dictionary[0], stan[1], Kierunek::lewo},
                         {'?', stan[1], dictionary[1], stan[2], Kierunek::lewo}};

    cout<< "Losowa liczba binarna:"<<endl;
    wypiszTasme(tasma);
    cout<< endl;
    Process(rules, tasma, 0);
    cout<< endl;
    cout<< "Liczba binarna zwiekszona o 1:"<<endl;
    wypiszTasme(tasma);
    return 0;
}
