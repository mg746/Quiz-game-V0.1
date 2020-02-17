/*

Osama Salah Abdelmoniem Hassan		20180039

Mahmoud Maarouf Abd elhalim			20180264

Marwan Galal Mohamed Abdallah		20180268

*/




#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


struct question
{
	string qs;
	string choices[4];
	string answer;
};

int results[20]; // array to store each  quiz result

//array to store all questions
question all_qs[1000];

//this variable to make sure that bank Qs is empty or not
bool loaded = false;


// this variable to store number of Qs
int num_of_qs = 0;

string uname = "USER"; //default name


bool if_file_found(string name)
{
	fstream file;
	file.open(name, ios::in);
	int i = 0;
	bool cond = false;
	while (!file.eof() && i <= 30)
	{
		string s;
		getline(file, s);
		i++;
		if (!cond && s != "\0")
			cond = true;
	}
	return cond;
}

//fun to read Qs from file
void reading_questions(string name)

{
	fstream file;
	file.open(name, ios::in);
	int count = 0, i = num_of_qs;
	string s;
	while (!file.eof())
	{
		getline(file, s);
		if (count == 0)
			all_qs[i].qs = s;
		else if (count == 1)
			all_qs[i].answer = s, all_qs[i].choices[0] = s;
		else if (count == 2)
			all_qs[i].choices[1] = s;
		else if (count == 3)
			all_qs[i].choices[2] = s;
		else if (count == 4)
			all_qs[i].choices[3] = s;
		count++;
		if (count == 5)
		{
			count = 0;
			i++;
		}
	}


}

/*
fun to get number of Qs
 it's used just one time ,when you read Qs from file for first time
 don't forget to increse it when used adds Qs or decrease when he deletes
 */


int num_qs(string name)
{
	fstream file;
	file.open(name, ios::in);
	int count = 0;
	string s;
	while (!file.eof())
	{
		getline(file, s);
		count++;
	}
	file.close();
	count /= 5;
	return count;
}




bool if_choice_valid(int n, int e)
{
	if (n<1 || n >e)
		return false;
	return true;
}



//this array to store every index which was printed so in the next random index
//if it will be here , it won't be printed again

int visited_choices[4];


//this fun to make make every element in array in a random number
void set_visited_choices_def()
{
	for (int i = 0; i < 4; i++)
		visited_choices[i] = rand() % (100 - 7 + 1) + 2;
}


//that fun to make the process of is the index is it was printed or not
bool if_visited_choices(int target)
{
	for (int i = 0; i < 4; i++)
	{
		if (visited_choices[i] == target)
			return true;
	}
	return false;
}


//fun to generate random number
int random(int limit, int ind)
{
	//rand()%((max+1)-min+1)+min			rand_equ
	int target;
	target = rand() % limit;
	while (if_visited_choices(target))
	{
		target = rand() % limit;
	}
	visited_choices[ind] = target;
	return target;
}


//fun to show Qs with answer randomly
void main_menu(); //a declearation to use it


void printing_questions_ans()
{
	for (int i = 0; i < num_of_qs; i++)
	{
		set_visited_choices_def();
		cout << "[" << i + 1 << "] " << all_qs[i].qs << endl;
		for (int r = 0; r < 4; r++)
		{
			int rand = random(4, r);
			char c = 97 + r;
			if (all_qs[i].choices[rand] == all_qs[i].answer)
				cout << "     " << "*[" << c << "] " << all_qs[i].choices[rand];
			else
				cout << "     " << "[" << c << "] " << all_qs[i].choices[rand];
		}
		cout << endl;
	}
	while (true)
	{
		cout << endl << "-------------------------------------------------------------------------------------" << endl;
		cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)." << endl;
		cout << "Press [b] if you want to go back to the main menu." << endl;
		cout << "My choice: ";
		int n;
		char c;
		cin >> c;
		while (c != 'b' && c != 'd')
		{
			cout << "Please enter a valid choice: ";
			cin >> c;
		}
		if (c == 'b')
		{
			main_menu();
			break;
		}
		else
		{
			cin >> n;
			while (n <= 0 || n > num_of_qs)
			{
				cout << "Please enter a valid number from 1 to " << num_of_qs << ": ";
				cin >> n;
			}
			swap(all_qs[num_of_qs - 1], all_qs[n - 1]);
			num_of_qs--;
			cout << "This question has been deleted successfully." << endl;
			printing_questions_ans();
		}
	}
}


void administration_menu(); //a declearation to use this funnction


//the next function is a functuion to allow the user to input his questions and thier answers
void add_new_qs() {
	string s;
	int j = 0, i = num_of_qs;
	cin.ignore();
	while (j < 5) {
		getline(cin, s);
		if (j == 0)
			all_qs[i].qs = s;
		else if (j == 1)
			all_qs[i].answer = s, all_qs[i].choices[0] = s;
		else if (j == 2)
			all_qs[i].choices[1] = s;
		else if (j == 3)
			all_qs[i].choices[2] = s;
		else if (j == 4)
			all_qs[i].choices[3] = s;
		j++;
	}
	num_of_qs += 1;
	loaded = true;
	administration_menu();
}
void go_back_to_main_menu() {
	main_menu();
}

// a function to store the name of the user
void update_your_name() {
	cout << "Enter your name please :" << endl;
	cin >> uname;
	main_menu();


}


int visited_qs[5];
void set_visited_qs_def()
{
	for (int i = 0; i < 5; i++)
		visited_qs[i] = rand() % (5000 - 3000 + 1) + 2;
}


bool if_visited_qs(int target)
{
	for (int i = 0; i < 5; i++)
	{
		if (visited_qs[i] == target)
			return true;
	}
	return false;
}



int random_qs(int ind)
{
	//rand()%((max+1)-min+1)+min			rand_equ
	int target;
	target = rand() % num_of_qs;
	while (if_visited_qs(target))
	{
		target = rand() % num_of_qs;
	}
	visited_qs[ind] = target;
	return target;
}



void printing_questions_quiz(int& right)
{
	set_visited_qs_def();
	int rand1;
	cin.ignore();
	for (int i = 0; i < 5; i++)
	{
		rand1 = random_qs(i);
		cout << '[' << i + 1 << "] " << all_qs[rand1].qs << endl;
		set_visited_choices_def();
		char right_c;
		for (int r = 0; r < 4; r++)
		{
			char C;
			if (r == 0)
				C = 'a';
			else if (r == 1)
				C = 'b';
			else if (r == 2)
				C = 'c';
			else if (r == 3)
				C = 'd';
			int rand2 = random(4, r);
			char c = 97 + r;
			cout << "     " << "[" << c << "] " << all_qs[rand1].choices[rand2];
			if (all_qs[rand1].choices[rand2] == all_qs[rand1].answer) {
				right_c = C;
			}

		}
		cout << endl;
		cout << "My answer: ";
		bool Choice = true;
		char choice;
		cin >> choice;
		while (Choice) {
			if (choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd') {
				Choice = false;
				break;
			}
			cout << "Your answer is not found between the choices of this question, Please enter a valid answer." << endl;
			cout << "My answer: ";
			cin >> choice;
		}
		if (choice != right_c)
		{
			cout << "Your answer is wrong." << endl;
			right--;
		}
		else
			cout << "Your answer is right." << endl;
		cout << endl;
	}

}

int num_of_quizzes = 0; // this variable will be a counter for the results array and a counter for the quizzes to know the number of quizzes the user had made


void start_new_quiz() {
	if (!loaded || num_of_qs < 5)
	{
		cout << "There are few questions to make a quiz, please enter new questions or load questions from file." << endl;
		main_menu();
	}
	int right = 5;
	printing_questions_quiz(right);
	cout << "You answerd " << right << " questions right and " << 5 - right << " wrong." << endl;
	results[num_of_quizzes] = right;
	num_of_quizzes++;
	main_menu();
}


//this function displays th score of the user and his stat
void display_score_stat() {
	int sum = 0;
	int high = 0, low = 5;
	float average = 0.0;
	cout << "Your score statistics :" << endl;
	cout << "Number of Quizzes taken : " << num_of_quizzes << endl;
	if (num_of_quizzes == 0) {
		cout << "You didn's start any quizzes, you should start a quiz to display your score." << endl;
	}
	else if (num_of_quizzes == 1) {
		cout << "Highest score : " << results[0] << " ." << endl;
		cout << "Average score : " << results[0] << " ." << endl;
	}
	else {
		for (size_t i = 0; i < num_of_quizzes; i++)
		{
			if (results[i] > high) high = results[i];
			if (results[i] < low) low = results[i];
			sum += results[i];
			average = sum / num_of_quizzes;
		}
		cout << "Highest score : " << high << " ." << endl;
		cout << "Lowest score : " << low << " ." << endl;
		cout << "Average score : " << average << " ." << endl;
	}
	cout << "Press [b] if you want to go back to the main menu or [e] to exit." << endl;
	char cchoice;
	bool ch = true;
	while (ch) {
		cout << "My choice :";
		cin >> cchoice;
		if (cchoice == 'b') {
			main_menu();
			ch = false;
		}
		else if (cchoice == 'e') {
			break;
		}
		else {
			cout << "Please enter 'b' or 'e' ." << endl;
			ch = true;
		}
	}
}


void Display_all_scores() {
	cout << "The total number of quizzes that you made is : " << num_of_quizzes << endl;
	for (size_t i = 0; i < num_of_quizzes; i++)
	{
		cout << "quiz " << i + 1 << " : right answers : " << results[i] << " , wrong answers : " << 5 - results[i] << endl;
		cout << "quiz " << i + 1 << " score : " << results[i] << "/5" << endl;
		cout << endl;
	}
	cout << "Press [b] if you want to go back to the main menu or [e] to exit." << endl;
	char cchoice;
	bool ch = true;
	while (ch) {
		cout << "My choice :";
		cin >> cchoice;
		if (cchoice == 'b') {
			main_menu();
			ch = false;
		}
		else if (cchoice == 'e') {
			break;
		}
		else {
			cout << "Please enter 'b' or 'e' :" << endl;
			ch = true;
		}
	}

}
int exit() {
	return 0;
}



void main_menu()
{
	cout << "Welcome " << uname << ", please choose from the following options:" << endl;
	cout << "\t" << "[1] Go to administration menu" << endl;
	cout << "\t" << "[2] Update your name" << endl;
	cout << "\t" << "[3] Start a new quiz" << endl;
	cout << "\t" << "[4] Display your scores statistics" << endl;
	cout << "\t" << "[5] Display all your scores" << endl;
	cout << "\t" << "[6] Exit" << endl;
	cout << "My choice: ";
	int n;
	cin >> n;

	while (!if_choice_valid(n, 6))
	{
		cout << "Please enter a valid choice" << endl;
		cout << "My choice: ";
		cin >> n;
	}
	if (n == 1)
		administration_menu();
	else if (n == 2)
		update_your_name();
	else if (n == 3)
		start_new_quiz();
	else if (n == 4)
		display_score_stat();
	else if (n == 5)
		Display_all_scores();
	else if (n == 6)
		exit();
}

// this functions takes the name of the file from the user and store it in our array of struct
void load_questins()
{
	string s;
	cin.ignore();
	cout << "Please add \".txt\" at the end of the file name" << endl << "The file name: ";
	getline(cin, s);
	while (!if_file_found(s))
	{
		cout << "This file is not found, Please enter a valid name of file" << endl << "The file name: ";
		getline(cin, s);
	}
	reading_questions(s);
	num_of_qs += num_qs(s);
	loaded = true;
	main_menu();
}
void administration_menu()
{
	cout << "\t" << "Welcome to the administration menu, please choose from the following options :" << endl;
	cout << "\t" << "[1] View all questions" << endl;
	cout << "\t" << "[2] Add new question" << endl;
	cout << "\t" << "[3] Load questions from file" << endl;
	cout << "\t" << "[4] Go back to main menu" << endl;
	cout << "My choice : ";
	int n;
	cin >> n;
	while (!if_choice_valid(n, 4))
	{
		cout << "Please enter a valid choice" << endl;
		cout << "My choice: ";
		cin >> n;
	}
	if (n == 1)
	{
		if (!loaded)
		{
			cout << "You entered no questions, please add question or load from a file" << endl;
			administration_menu();
		}
		else
		{
			printing_questions_ans();
		}
	}
	else if (n == 2) {
		add_new_qs();
	}
	else if (n == 3)
	{
		load_questins();
	}
	else if (n == 4) {
		go_back_to_main_menu();
	}
}
int main()
{
	srand(time(0));
	main_menu();
	return 0;
	system("pause");
}
