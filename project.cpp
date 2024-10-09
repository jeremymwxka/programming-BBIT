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

// Function to load teams from a CSV file
vector<Team> loadTeamsFromCSV(const string& filename) {
    vector<Team> teams;
    ifstream file("C:\\Users\\jerem\\OneDrive\\Desktop\\Programming.bbit\\teams_csvFile.csv");
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
    }

    getline(file, line);  // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        Team team;
        getline(ss, team.name, '\t');
        getline(ss, team.town, '\t');
        getline(ss, team.stadium, '\t');
        teams.push_back(team);
    }

    return teams;
}

// Function to generate fixtures
vector<Match> generateFixtures(const vector<Team>& teams) {
    vector<Match> fixtures;
    int weekendCounter = 1;

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            if (teams[i].town != teams[j].town) {
                fixtures.push_back({teams[i], teams[j], 1, weekendCounter});
                fixtures.push_back({teams[j], teams[i], 2, weekendCounter + 1});
                weekendCounter += 2;
            }
        }
    }

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            if (teams[i].town == teams[j].town) {
                fixtures.push_back({teams[i], teams[j], 1, weekendCounter});
                fixtures.push_back({teams[j], teams[i], 2, weekendCounter + 1});
                weekendCounter += 2;
            }
        }
    }

    return fixtures;
}

// Function to schedule fixtures into weekends
void scheduleFixtures(vector<Match>& fixtures) {
    int weekend = 1;
    for (size_t i = 0; i < fixtures.size(); i += 2) {
        fixtures[i].weekend = weekend;
        fixtures[i + 1].weekend = weekend;
        weekend++;
    }
}

// Function to output fixtures to console and file
void outputFixtures(const vector<Match>& fixtures) {
    ofstream outFile("C:\\Users\\jerem\\OneDrive\\Desktop\\Programming.bbit\\fixtures.csv");

    int i = 1;
    for (const auto& match : fixtures) {
        cout << "Weekend #" << match.weekend << ": "
             << match.home.name << " vs " << match.away.name
             << " at " << match.home.stadium << " (" << match.home.town << ")"
             << " Leg: " << match.leg << endl;

        if (i == 1) {
            outFile << "Gameweek,Home,Away,Location,Leg\n";
            i++;
        }
        outFile << match.weekend << "," << match.home.name << "," << match.away.name
                << "," << match.home.stadium << "," << match.leg << "\n";
    }

    outFile.close();
}

int main() {
    vector<Team> teams = loadTeamsFromCSV("C:\\Users\\jerem\\OneDrive\\Desktop\\Programming.bbit\\teams_csvFile.csv");

    vector<Match> fixtures = generateFixtures(teams);

    scheduleFixtures(fixtures);

    outputFixtures(fixtures);

    return 0;
}
