#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct Team {
    string name;
    string town;
    string stadium;
};

struct Match {
    string home_team;
    string away_team;
    string stadium;
    string town;
    int leg;
    int weekend;
};

vector<Team> loadTeamsFromCSV(const string& filename) {
    vector<Team> teams;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, town, stadium;

        getline(ss, name, '\t');
        getline(ss, town, '\t');
        getline(ss, stadium, '\t');

        teams.push_back({name, town, stadium});
    }
    return teams;
}

vector<Match> generateFixtures(const vector<Team>& teams) {
    vector<Match> fixtures;
    int weekend = 1;

    for (size_t n = 0; n < teams.size(); ++n) {
        for (size_t m = n + 1; m < teams.size(); ++m) {
            Match home_match = {teams[n].name, teams[m].name, teams[n].stadium, teams[n].town, 1, weekend};
            Match away_match = {teams[m].name, teams[n].name, teams[m].stadium, teams[m].town, 2, weekend};

            fixtures.push_back(home_match);
            fixtures.push_back(away_match);

            if (fixtures.size() % 2 == 0) weekend++;
        }
    }
    return fixtures;
}

int main() {
    vector<Team> teams = loadTeamsFromCSV("teams.csv");

    vector<Match> fixtures = generateFixtures(teams);

    for (const auto& match : fixtures) {
        cout << "Weekend: " << match.weekend << " | "
             << match.home_team << " vs " << match.away_team << " at "
             << match.stadium << ", " << match.town << " (Leg " << match.leg << ")" << endl;
    }

    return 0;
}
