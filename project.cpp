#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Structure to hold team information
struct Team {
    string name;   // Team's name
    string town;   // The town the team is based in
    string stadium; // The stadium where the team plays home games
};

// Structure to hold match information
struct Match {
    string home_team;  // Name of the team hosting the match
    string away_team;  // Name of the team visiting for the match
    string stadium;    // Stadium where the match is taking place
    string town;       // Town where the stadium is located
    int leg;           // 1 for the first leg, 2 for the second leg
    int weekend;       // Which weekend this match will take place on
};

// Function to load teams from CSV file
vector<Team> loadTeamsFromCSV(const string& filename) {
    vector<Team> teams;
    ifstream file(filename);
    string line;

    // Skip the first line (headers)
    getline(file, line);

    // Read each line from the CSV file
    while (getline(file, line)) {
        stringstream ss(line);
        string name, town, stadium;

        // Split by tabs
        getline(ss, name, '\t');
        getline(ss, town, '\t');
        getline(ss, stadium, '\t');

        teams.push_back({name, town, stadium});
    }
    return teams;
}

// Function to generate home and away matches
vector<Match> generateFixtures(const vector<Team>& teams) {
    vector<Match> fixtures;
    int weekend = 1;

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            // Home and away matches
            Match home_match = {teams[i].name, teams[j].name, teams[i].stadium, teams[i].town, 1, weekend};
            Match away_match = {teams[j].name, teams[i].name, teams[j].stadium, teams[j].town, 2, weekend};

            fixtures.push_back(home_match);
            fixtures.push_back(away_match);

            if (fixtures.size() % 2 == 0) weekend++; // Move to next weekend every two matches
        }
    }
    return fixtures;
}

/