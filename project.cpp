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
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return teams; // Return an empty list
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

// Function being used to generate fixtures 
vector<Match> generateFixtures(const vector<Team>& teams) {
    vector<Match> fixtures;
    int weekendCounter = 1;

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            if (teams[i].town != teams[j].town) {
                // First leg
                fixtures.push_back({teams[i].name, teams[j].name, teams[i].stadium, teams[i].town, 1, weekendCounter});
                // Second leg
                fixtures.push_back({teams[j].name, teams[i].name, teams[j].stadium, teams[j].town, 2, weekendCounter + 1});
                weekendCounter += 2;
            }
        }
    }

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            if (teams[i].town == teams[j].town) {
                // First leg
                fixtures.push_back({teams[i].name, teams[j].name, teams[i].stadium, teams[i].town, 1, weekendCounter});
                // Second leg
                fixtures.push_back({teams[j].name, teams[i].name, teams[j].stadium, teams[j].town, 2, weekendCounter + 1});
                weekendCounter += 2;
            }
        }
    }

    return fixtures;
}

// Function is used to schedule weekend fixtures
void scheduleFixtures(vector<Match>& fixtures) {
    int weekend = 1;
    for (size_t i = 0; i < fixtures.size(); i += 2) {
        fixtures[i].weekend = weekend;
        fixtures[i + 1].weekend = weekend;
        weekend++;
    }
}

// Function is used to output the fixtures onto the console and the file
void outputFixtures(const vector<Match>& fixtures) {
    ofstream outFile("C:\\Users\\jerem\\OneDrive\\Desktop\\Programming.bbit\\fixtures.csv");

    if (!outFile.is_open()) {
        cerr << "Error: Unable to open output file!" << endl;
        return;
    }

    outFile << "Gameweek,Home,Away,Location,Leg\n";  // Writing CSV headers

    for (const auto& match : fixtures) {
        // Output to console
        cout << "Weekend #" << match.weekend << ": "
             << match.home_team << " vs " << match.away_team
             << " at " << match.stadium << " (" << match.town << ")"
             << " Leg: " << match.leg << endl;

        // Output to CSV file
        outFile << match.weekend << "," << match.home_team << "," << match.away_team
                << "," << match.stadium << "," << match.leg << "\n";
    }

    outFile.close();
}

int main() {
    vector<Team> teams = loadTeamsFromCSV("C:\\Users\\jerem\\OneDrive\\Desktop\\Programming.bbit\\teams_csvFile.csv");

    if (teams.empty()) {
        cerr << "Error: No teams loaded!" << endl;
        return 1;
    }

    vector<Match> fixtures = generateFixtures(teams);

    scheduleFixtures(fixtures);

    outputFixtures(fixtures);

    return 0;
}
