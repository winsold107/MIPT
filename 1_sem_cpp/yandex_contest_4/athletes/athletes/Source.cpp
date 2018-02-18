#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Athletes {
public:
	long Mass;
	long Power;

	Athletes() : Mass(0), Power(0) {}
	Athletes(long mass, long power) : Mass(mass), Power(power) {}

	Athletes& operator=(const Athletes& athlete_probe) {
		if (this == &athlete_probe) {
			return *this;
		}
		Mass = athlete_probe.Mass;
		Power = athlete_probe.Power;
		return *this;
	}
};
ostream& operator<<(ostream& os, const Athletes& man)
{
	os << man.Mass << " " << man.Power;
	return os;
}

istream& operator>>(istream& F, Athletes* man)
{
	F >> man->Mass >> man->Power;
	return F;
}

long pyramid (const vector <Athletes>& team)
{
	long curMass = 0;
	int height = 0;
	for (int i = 0; i < team.size(); i++)
	{
		if (team[i].Power >= curMass)
		{
			curMass = team[i].Mass + curMass;
			height++;
		}
	}
	return height;
}

int main() 
{
	ifstream F("input.txt");
	long mass;
	long power;
	vector<Athletes> team;
	Athletes* man = new Athletes;

	while (!F.eof()) 
	{
		F >> man;
		team.push_back(Athletes (man->Mass, man->Power));
	}

	long n = team.size();
	sort(team.begin(), team.end(), [](const Athletes& a1, const Athletes& a2)
	{
		return a1.Power < a2.Power;
	});
	/*for (long i = 0; i < n; i++)
	{
		cout << team[i] << endl;
	}*/
	
	cout << pyramid(team);
	//system("pause");
	return 0;
}