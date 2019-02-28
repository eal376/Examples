/*  Elizabeth Lujan
	This is a game that learns as it is used more often. A user will input a animal. Based on a series of questions, the program 
	attempts to guess the animal inputed to the user. If the program is not able to guess correctly, it will ask the user
	for a question to ask for future use.
	
	included is "BinaryNode.h" -- while needed to run the progam I did not create it
*/

#include "BinaryNode.h" // no5 made by me: Courtesy of Prof Adam Carter
#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

// This function is called upon when we cannot guess the correct animal. 
//		It gathers the correct infomation from the user and adds the new nodes to the tree. 
void insert(BinaryNode<string> *node)
{
	if (node == nullptr)
	{
		return;
	}

	string animal, question, answer, guess = node->getValue();
	
	cout << "So, what was the animal you were thinking of? " << endl;
	getline(cin, animal);
	
	cout << "What question can we use to differntiate between a " << node->getValue() << " and a " << animal << endl;
	getline(cin, question);
	
	cout << "Is the answer to this question yes or no?" << endl;
	getline(cin, answer); 

	BinaryNode<string>* right = new BinaryNode<string>{};
	BinaryNode<string>* left = new BinaryNode<string>{};

	node->setValue(question); 

	if (answer == "yes" || answer == "Yes")
	{
		right->setValue(animal);
		left->setValue(guess);
	}

	else if (answer == "no" || answer == "No")
	{
		right->setValue(guess);
		left->setValue(animal); 
	}

	else
	{
		cout << "Cannot understand user input" << endl; 
	}
	
	node->setLeftChild(left);
	node->setRightChild(right); 
}

// This function sees if we were able to get the right animal.
bool CheckAnswer(BinaryNode <string> * node)
{
	if (node == nullptr)
	{
		return false;
	}

	string ans;
	cout << "Is it a " << node->getValue() << "? Enter yes or no." << endl;
	getline(cin, ans);

	if (ans == "yes" || ans == "Yes")
	{
		cout << " I won! " << endl;
		cout << "  | | " << endl;
		cout << " .    ." << endl;
		cout << "  . .  " << endl;
		return true;
	}
	else
	{
		insert(node);
	}
}

// This function should go through the binary tree asking questions
// and stop once we reach a leaf node 
bool Questions(BinaryNode <string> *node)
{
	string ans;

	if (node == nullptr)
	{
		return false;
	}

	if (node->isLeaf())
	{
		return CheckAnswer(node);
	}

	else
	{
		cout << node->getValue() << " Enter yes or no" << endl;
		getline(cin, ans);

		if (ans == "yes" || ans == "Yes")
		{
			return Questions(node->getRightChild());
		}

		else if (ans == "no" || ans == "No")
		{
			return Questions(node->getLeftChild());
		}

		else
		{
			cout << "Not an acceptable answer will retun false" << endl;
			return false;
		}
	}
}

// This function will take the node values (strings) and make them into
//		our binary tree
BinaryNode<string>* ReadfromFile(BinaryNode<string> *node, ifstream & input_file)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	if (input_file.is_open())
	{
		if (input_file.good())
		{
			string value;
			getline(input_file, value);

			if (value[0] == '*') // Leaf Node
			{
				node->setValue(value.substr(1, value.size()));
				return node;
			}
			else
			{
				BinaryNode <string> * left = new BinaryNode<string>{};
				node->setLeftChild(left);
				BinaryNode <string> * right = new BinaryNode<string>{};
				node->setRightChild(right);

				node->setValue(value);
				ReadfromFile(node->getLeftChild(), input_file);
				ReadfromFile(node->getRightChild(), input_file);
			}
		}
	}
	else
	{
		cout << "File cannot open" << endl;
	}
}

// This functions starts the binary tree without file load
BinaryNode<string> * StartTree()
{
	BinaryNode <string> * first = new BinaryNode<string>{ };
	first->setValue("Dog");
	return first;
}

// This functions starts the binary tree with file load
BinaryNode <string> * StartTree(ifstream & input)
{
	BinaryNode <string> * first = new BinaryNode<string>{ };
	ReadfromFile(first, input); 
	return first; 
}

//This Function puts users guess into an output file called "game.txt"
//	 using a pre-order traversal
void OutputPreOrder(BinaryNode<string> *node, ofstream & output_file)
{
	if (node == nullptr)
	{
		return;
	}

	if (output_file.is_open())
	{
		if (node->isLeaf())
		{
			output_file << "*" << node->getValue() << endl;

		}
		else
		{
			output_file << node->getValue() << endl;
		}

		OutputPreOrder(node->getLeftChild(), output_file);
		OutputPreOrder(node->getRightChild(), output_file);
	}
	else
	{
		cout << "File could not open" << endl;
	}
}

// This Function Runs Questions Function as many times as the user wants
//		can read from a text file called game.txt and will write the results to a text file named game.txt
void GuessingGame()
{
	string ans, past_game;
	cout << "Do you want to load the last game?" << endl; 
	getline(cin, past_game);

	BinaryNode<string> * root{};

	if (past_game == "yes" || past_game == "Yes")
	{

		ifstream input{ "game.txt" };
		root = StartTree(input);
		input.close();
	}

	else if (past_game == "no" || past_game == "No")
	{
		root = StartTree(); 
	}

	else
	{
		cout << "Did not understand -- guess you don't want to play game" << endl; 
	}
	

	cout << " Start Guessing Game!! " << endl << endl;
	do
	{
		Questions(root);
		cout << "Do you want to play again? If so, enter 'yes' anything else ends guessing game" << endl; 
		getline(cin, ans);
	} while (ans == "yes" || ans == "Yes"); 

	ofstream output{ "game.txt" };
	OutputPreOrder(root, output);
	output.close();
}

int main()
{
	GuessingGame(); 	
	return 0;
}
