#include <iostream>
#include <HFMN.h>

using namespace std;

static void copyStream(istream& input, ostream& output)
{
	char value;
	while (!input.eof())
	{
		input >> value;
		output << value;
	}
}

void Encode(istream& original, ostream& compressed)
{
	copyStream(original, compressed);
}

void Decode(istream& compressed, ostream& original)
{
	copyStream(compressed, original);
}

int main()
{
	return 0;
}
