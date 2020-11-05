#include <iostream>
#include <array>
#include <time.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

string matchScore(string& team1, string& team2, bool groupStage);	//declaring functions
void eliminationMatches(vector<string> teams, int matches);
void groupStage(vector<string>& teams);
void groupMatch(string team1, string team2, map<string, int>& groupTeams);

bool sortByPairValue(const pair<string, int>& a, const pair<string, int>& b) {
	return a.second > b.second;
}

int main() {
	srand(time(NULL)); //sets a seed for any functions involving random values

	vector<string> firstRoundTeams = { "Belgium", "France", "Brazil", "England", "Portugal", "Uruguay", "Spain", "Croatia",
		"Argentina", "Colombia", "Mexico", "Italy", "Netherlands", "Germany", "Switzerland", "Denmark",
		"Chile", "Sweden", "Poland", "Senegal", "Wales", "Peru", "USA", "Ukraine",
		"Venezuela", "Tunisia", "Austria", "Japan", "Nigeria", "Iran", "Serbia", "Turkey" };

	cout << "The Teams In The Next World Cup Are: " << endl;
	for (auto team : firstRoundTeams)
		cout << "  " << team << endl; //outputs the name of each team in the vector firstRoundTeams

	cout << "\nPress Enter to Start Simulation..." << endl;

	cin.clear(); //clears the input stream
	cin.ignore(100000, '\n'); //ignores the next 100000 inputs from the user unless the enter key is pressed
	system("CLS"); //clears the console output window

	groupStage(firstRoundTeams);

	return 0;
}

void groupStage(vector<string>& teams) {

	string groupMatchWinner;
	vector<string> tempTeams;
	array<char, 8> groupNames = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

	for (int i = 0; i < 32; i += 4) {
		map<string, int> groupTeams{ //creates a map containing 4 teams in a group and an integers to contain their points earned in the group stage
			{teams[i], 0},
			{teams[i + 1], 0},
			{teams[i + 2], 0},
			{teams[i + 3], 0}
		};

		groupMatch(teams[i], teams[i + 1], groupTeams); //team 1 vs team 2			plays out each match in a group

		groupMatch(teams[i], teams[i + 2], groupTeams); //team 1 vs team 3

		groupMatch(teams[i], teams[i + 3], groupTeams); //team 1 vs team 4

		groupMatch(teams[i + 1], teams[i + 2], groupTeams); // team 2 vs team 3

		groupMatch(teams[i + 1], teams[i + 3], groupTeams); // team 2 vs team 4

		groupMatch(teams[i + 2], teams[i + 3], groupTeams); // team 3 vs team 4

		vector<pair<string, int>> sortedResults; // defines a new vector to contain the values from groupTeams as maps cannot be sorted directly

		cout << "Group " << groupNames[i / 4] << " Results: " << endl;

		for (auto& c : groupTeams)
			sortedResults.push_back(c); //adds each team in a group, and their points, to the new vector

		sort(sortedResults.begin(), sortedResults.end(), sortByPairValue); //sorts the vector by each pair's value from highest to lowest

		for (auto& c : sortedResults)
			cout << "  " << c.first << ": " << c.second << " pts" << endl; //outputs each team and their score with in order of their points

		cout << '\n';

		sortedResults.pop_back(); //removes the bottom 2 teams from the vector
		sortedResults.pop_back();

		string elimTeam1 = sortedResults[0].first; //stores the team name in a variable using the key from each pair
		string elimTeam2 = sortedResults[1].first;

		tempTeams.push_back(elimTeam1); //stores the team names in a temporary vector, ready to be added back to the list of teams in the next round
		tempTeams.push_back(elimTeam2);

		cout << elimTeam1 << " & " << elimTeam2 << " go through to the next round!\n" << endl; //tells the user which 2 teams make it out of the group stage
	}

	teams.clear(); //empties the original vector of teams, ready to be refilled with the winning teams

	for (int j = 0; j < 16; j++) {
		teams.push_back(tempTeams[j]); //refills the original vector 
	}

	cout << "View Remaining Teams & Start Elimination Rounds? (Press Enter To Continue)" << endl;
	cin.clear(); //pauses until the enter key is pressed, to give the user a chance to look at the scores and results of each round
	cin.ignore(100000, '\n');
	system("CLS");

	cout << "Teams Remaining: " << endl;
	for (auto c : teams) { //Outputs the full list of teams remaining in the tournament
		cout << "  " << c << endl;
	}

	cout << "\nView Round of 16 Results? (Press Enter To Continue)" << endl;

	cin.clear(); //pauses until the enter key is pressed, to give the user a chance to look at the scores and results of each round
	cin.ignore(100000, '\n');
	cout << '\n' << endl;
	system("CLS");

	random_shuffle(teams.begin(), teams.end()); //shuffles the order of the teams before the elimination stages
	eliminationMatches(teams, (teams.size() / 2));
}

void groupMatch(string team1, string team2, map<string, int>& groupTeams) {
	string groupMatchWinner;
	groupMatchWinner = matchScore(team1, team2, true);

	if (groupMatchWinner == team1) //asigns point to each team in the match based on the results determined in the matchScore function
		groupTeams[team1] += 3;

	else if (groupMatchWinner == team2)
		groupTeams[team2] += 3;

	else {
		groupTeams[team1] += 1;
		groupTeams[team2] += 1;
	}
}

string matchScore(string& team1, string& team2, bool groupStage) {
	int score1;
	int score2;

	if (groupStage == true) { //group stages only
		score1 = rand() % 5 + 0; //generates to random values between 0 and 5 as the score for each team
		score2 = rand() % 5 + 0;
		if (score1 > score2)
			return team1; //returns the name of the winning team of the match
		else if (score2 > score1)
			return team2;
		else
			return "draw"; //returns "draw" if the scores are equal. can only happen in the group stages
	}

	else { //elimination stages only
		do {
			score1 = rand() % 5 + 0;
			score2 = rand() % 5 + 0;
		} while (score1 == score2); //repeats until the game is not a draw, if needed

		cout << "  " << team1 << " vs " << team2 << endl;
		cout << "  Final Result: " << team1 << ": " << score1 << " : " << team2 << ": " << score2 << '\n' << endl;

		if (score1 > score2)
			return team1; //returns the name of the winning team
		else if (score2 > score1)
			return team2;
	}
}

void eliminationMatches(vector<string> teams, int matches) {
	int determineRound = teams.size(); //determines the number of teams remaining in the current round

	if (determineRound > 1) { //checks if there are 2 or more teams to play against each other
		switch (determineRound) {
		case 16:
			cout << "Round of 16: \n" << endl; //outputs the round name, bsed on the number of teams remaining
			break;
		case 8:
			cout << "Quarterfinals: \n" << endl;
			break;
		case 4:
			cout << "Semifinals: \n" << endl;
			break;
		case 2:
			cout << "Finals!: \n" << endl;
			break;
		}

		vector<string> winningTeams;
		vector<string>::iterator itr;

		matches = (determineRound / 2); // works out how many matches will be played based on how many teams are left

		for (int i = 0; i < matches; i++) { //calls the matchScore function for each match
			string matchWinner = matchScore(teams[((i + 1) * 2) - 2], teams[((i + 1) * 2) - 1], false);
			winningTeams.insert(winningTeams.end(), matchWinner); //adds the winner of the match to a new vector, containing all the teams in the next round
		}

		teams.clear(); //empties the original vector containing teams going into the round

		for (int i = 0; i < winningTeams.size(); i++)
			teams.insert(teams.end(), winningTeams[i]); //refills the original vector with the winning teams, ready to be passed to the next round

		if (determineRound > 2) { //pauses until the enter key is pressed, to give the user a chance to look at the scores and results of each round
			cout << "View next round results? (Press Enter To Continue)" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
			system("CLS");
		} //skips this if it is the finals, and outputs a final message to declare the winner of the tournament

		eliminationMatches(teams, matches); //the function calls itself recursively until only 1 team remains 
	}

	else
		cout << "The winner is: " << teams[0] << "!" << endl;
}