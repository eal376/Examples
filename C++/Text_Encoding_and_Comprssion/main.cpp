/* Elizabeth Lujan
	ID: 012505516
	Completetion Time: 2.5 hrs + 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <queue>
#include "StringSplitter.h" // not created by me -- taken from Adam Carter


using namespace std;

// RecordFrequency will record the frequency of each word ina given text file. Will ignore empty lines and spaces. 
unordered_map<string, int> RecordFrequency(string filename)
{
	ifstream input {filename};
	if (input.is_open())
	{
		string line;
		StringSplitter a;
		vector <string> all_the_words, some_words;

		while (input.good())
		{
			getline(input, line);
			some_words = a.split(line, " ");

			for (auto i : some_words)
			{
				all_the_words.push_back(i);
			}
		}
		
		unordered_map <string, int> frequency{};
		for (auto i : all_the_words)
		{
			frequency[i]++;
		}

		input.close();

		// Erase once you know function works: Start
		for (auto kvp : frequency)
		{
			cout << "'" << kvp.first << "': " << kvp.second << endl;
		}

		// End
		return frequency;
	}
	else
	{
		cout << "File did not open! Could not do anything =(" << endl;
	}

}

// BuildMaxHeap will use the frequency recorded in Record Frequency to build a Max Heap
// (We want the most occuring word to be at the top -- descending order)
class dict
{
private:
	string key = "";
	int value = 0; 
public:
	void setKey(string some_key)
	{
		key = some_key;
	}

	void setValue(int some_value)
	{
		value = some_value;
	}

	string getKey() const
	{
		return key;
	}

	int getValue() const
	{
		return value;
	}
};

bool operator < (const dict& left, const dict &right)
{
	return left.getValue() < right.getValue();
}

bool operator > (const dict& left, const dict &right)
{
	return left.getValue() > right.getValue();
}

bool operator == (const dict& left, const dict &right)
{
	return left.getValue() == right.getValue();
}
priority_queue <dict> BuildMaxHeap(unordered_map<string, int> frequency)
{
	priority_queue<dict> popularity{};

	for (auto i : frequency)
	{
		dict pairs{};
		pairs.setKey(i.first);
		pairs.setValue( i.second);
		popularity.push(pairs);
	}
	return popularity;
}

//  Helper Function to be called in BinaryString() to make individual "binary" strings
string task4(int n)
{
	if (n == 0)
	{
		return "0";
	}
	string output;
	while (n > 0)
	{
		int result = n & 1;
		if (result == 1)
		{
			output = "1" + output;
		}
		else
		{
			output = "0" + output;
		}
		n = n >> 1;
	}

	return output;
}

// BinaryString() will remove items from the heap -- in order of importance --
// and assign each word a unique binary string value
unordered_map<string, string> BinaryString(priority_queue<dict> popularity)
{
	unordered_map<string, string> conversion{};
	vector <string> words;
	string binary_string = "";
	int i = 0; 

	while (popularity.size() > 0)
	{
		binary_string = task4(i);
		dict word = popularity.top(); 
		string a = word.getKey(); 
		conversion[binary_string] = a; 
		popularity.pop();
		i++;
	}

	for (auto kvp : conversion)
	{
		cout << "'" << kvp.first << "': " << kvp.second << endl;
	}
	return conversion;
}

// BinaryFile() will write to the output file the "binary" representation of the file
void BinaryFile(unordered_map <string, string> a)
{
	ofstream output{ "output-file.txt" };
	if (output.is_open())
	{
		for (auto kvp : a)
		{
			output << kvp.first<< " ";
		}

		output.close();
	}

	else
	{
		cout << "So sorry -- file could not open" << endl;
	}
}

// BinaryMap() will write to an output file the "binary" mapping of our compression
void BinaryMap(unordered_map<string, string> b)
{
	ofstream output{ "output-file-bmap.txt" };
	if (output.is_open())
	{
		for (auto i : b)
		{
			output << "'" << i.first << "': " << i.second << endl;
		}

		output.close();
	}

	else
	{
		cout << "Could not open file -- #sorry" << endl; 
	}
}
int main()
{
	string filename = "words.txt";
	unordered_map <string,int> freq = RecordFrequency(filename);
	priority_queue <dict> a = BuildMaxHeap(freq);
	unordered_map<string,string> b = BinaryString(a);
	BinaryFile(b); 
	BinaryMap(b); 
 
	return 0;
}