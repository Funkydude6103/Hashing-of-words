#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
#include <cctype>
#include<string>
using namespace std;
int index = 0;
int arr[] = {10,19, 41, 79, 163, 317, 641, 1279, 2557, 5119, 10243,20479, 40961, 81919, 163841};
class node 
{
public:
	string data;
	node* next;
	int freq;
	node()
	{
		freq = 1;
		data = "";
		next = NULL;
	}
	node(string a)
	{
		freq = 1;
		data = a;
		next = NULL;
	}
};
class Hashmap
{
private:
	int size;
	vector <node*> HashTable;
	double load_factor;
	int items;
public:
	void rehashing()
	{
		vector <string> tempo;
		for (int i = 0; i < size; i++)
		{
			node* temp = HashTable[i];
			while (temp)
			{
				if (temp->data != "")
				{
					for(int j=0;j<temp->freq;j++)
					tempo.push_back(temp->data);
				}
				temp = temp->next;
			}
		}
		index++;
		if (index <= 13)
		{
			size = arr[index];
			HashTable.clear();
			items = 0;
			for (int i = 0; i < size; i++)
			{
				node* temp2 = new node();
				HashTable.push_back(temp2);
			}
			for (int j = 0; j < tempo.size(); j++)
			{
				int k = 0;
				for (int i = 0; i < tempo[j].size(); i++)
				{
					k = k + tempo[j][i];

				}
				put(k, tempo[j]);
			}
		}
	}
	Hashmap()
	{
		size = 10;
		load_factor = 0;
		items = 0;
		for (int i = 0; i < size; i++)
		{
			node* temp = new node();
			HashTable.push_back(temp);
		}
	}
	int func2(string value)
	{
		int key = 0;
		for (int i = 0; i < value.size(); i++)
		{
			key = key + value[i];

		}
		return key%size;
	}
	bool delete_(string value)
	{
		int i = func2(value);
		if (HashTable[i]->next != NULL)
		{
			if (HashTable[i]->next->data == value)
			{
				node* temp = HashTable[i]->next;
				HashTable[i]->next = temp->next;
				free(temp);
				items--;
				return true;
			}
			else
			{
				node* current = HashTable[i];
				while (current->next != NULL)
				{
					if (current->next->data == value)
					{
						node *temp = current->next;
						current->next = current->next->next;
						free(temp);
						items--;
						return true;
						break;
					}
					else
					current = current->next;
				}
			}
			return false;
		}
		return false;

	}
	node* get(string value)
	{
		int i = func2(value);
		if (HashTable[i]->next != NULL)
		{
			if (HashTable[i]->next->data == value)
			return HashTable[i]->next;

			else
			{
				node* temp = HashTable[i];
				while (temp)
				{
					if (temp->data == value)
					{
						return temp;
					}
					temp = temp->next;
				}
			}

			return NULL;
		}
		else
		{
			return NULL;
		}

		
	}
	int size_()
	{
		return items;
	}
	int Hashing_Function(int key)
	{
		return (key % size);
	}
	void put(int key, string value)
	{
		int i = Hashing_Function(key);
		if (HashTable[i]->next==NULL)
		{
			node* temp2 = new node(value);
			HashTable[i]->next= temp2;
			items++;
		}
		else
		{
			node* temp = HashTable[i];
			bool check = true;
			if (temp->data == value)
			{
				temp->freq++;
				check = false;
			}
			while (temp->next)
			{
				if (temp->data == value)
				{
				   temp->freq++;
				   check=false;
				}
				temp = temp->next;
			}
			if (check)
			{
				if (temp->data == value)
				{
					temp->freq++;
					check = false;
				}
			}
			if (check)
			{
				node* temp2 = new node(value);
				temp->next = temp2;
				items++;
			}
		}
		
		double j = (double)items / (double)size;
		if (j > 0.75)
		{
			rehashing();
		}

	}
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			node* temp = HashTable[i];
			while (temp)
			{
				cout << temp->data <<" " << "freq :" << temp->freq << "->";
				temp = temp->next;
			}
			cout << endl;
		}
	}
};
int main()
{
	vector<string> words;
	fstream fin;
	fin.open("k.txt");
	while (!fin.eof())
	{
		string line;
		string word = "";
		getline(fin, line);
		for (auto x : line)
		{
			if (x == ' ' || x == '-' || x=='?')
			{
				if(word!="")
				words.push_back(word);
				word = "";
			}
			else
			{
				if (x >= 'A' && x <= 'Z' || x >= 'a' && x < 'z' || x == 39 || x>='0'&& x<='9'  || x==95)
					word = word + x;
			}
		}
		words.push_back(word);
	}
	//cout << words.size();
	//for (int i = 0; i < words.size(); i++)
	//	cout << words[i] << endl;	

		Hashmap obj;

	for (int j = 0; j < words.size(); j++)
	{
		int k=0;
		transform(words[j].begin(), words[j].end(), words[j].begin(), ::toupper);
		for (int i = 0; i < words[j].size(); i++)
		{
			k = k + words[j][i];

		}
		if(words[j]!="")
		obj.put(k,words[j]);
	}
	obj.print();
	string in;
	cout << "This text contains Total " << obj.size_() << " distinct words" << endl;
	while (1)
	{
		cout << "Please enter a word to get its frequency, or enter - 1 to leave." << endl;
		cin >> in;
		if (in != "-1")
		{
			if (in[0] == '-')
			{
				in = in.substr(1, in.size());
				transform(in.begin(), in.end(), in.begin(), ::toupper);
				if (obj.delete_(in))
					cout << in << " has been deleted." << endl;
				else
					cout << in << " does not appear." << endl;

				continue;

			}
			transform(in.begin(), in.end(), in.begin(), ::toupper);
			node* temp = obj.get(in);
			if (temp != NULL)
			cout << in << " appears " << temp->freq << " times." << endl;
			else
			cout << in << " does not appear." << endl;

		}
		else
		{
			break;
		}

	}

	return 0;
}