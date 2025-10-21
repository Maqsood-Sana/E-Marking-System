#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <thread>
#include <limits>
using namespace std;

const string admin_name="Maqsood";
const int admin_pass=12345;

void DisplayMenu();
void AdminMenu();
void StudentMenu(const string &username);
void StudentRegister();
void LoginStudent();
void LoginAdmin();
int getValidatedInput();
string getPasswordInput();
void logo(const string &text, int num);
void AddQuestion();
void AttemptQuiz(const string &username);
void ViewResults(const string &username);
void ViewStudents();
void ForgotPassword();

struct Question {
    string question;
    string options[4];
    int correctOption;
};

const int MAX_QUESTIONS = 100;
Question quiz[MAX_QUESTIONS];
int quizCount = 0;

const int MAX_STUDENTS = 100;
string studentNames[MAX_STUDENTS];
int studentScores[MAX_STUDENTS];
int studentCount = 0;

void logo(const string &text, int num) {
    for (char c : text) {
        cout<<c;
        this_thread::sleep_for(chrono::milliseconds(num));
    }
}

int getValidatedInput() {
    int choice;
    while(true) {
        cin>>choice;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid input. Please enter a valid number: ";
        } else {
            return choice;
        }
    }
}

string getPasswordInput() {
    string password;
    char ch;
    cout << "Enter Password: ";
    while ((ch = getch()) != '\r') { 
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout<<"\b \b";
            }
        }else{
            password.push_back(ch);
            cout<<'*';
        }
    }
    cout<<endl;
    return password;
}


void DisplayMenu() {
    logo("==================================================================\n", 1);
    logo("                           _     _                 __             \n", 1);
    logo("          |   E L C O M E  | O  |_ -M A R K I N G |__ Y S T E M   \n", 1);
    logo("          |/\\|             |    |_                 __|            \n", 1);
    logo("==================================================================\n", 1);
    cout<<"1. Student \n2. Admin \n3. Exit" << endl;
    cout<<"Enter Your Choice: ";
    int choice = getValidatedInput();

    switch(choice) {
        case 1:
		    LoginStudent();
            break;
        case 2:
            LoginAdmin();
            break;
        case 3:
            cout<<"Exiting the system. Goodbye!\n";
            exit(0);
        default:
            cout<<"Invalid choice! Try again.\n";
            DisplayMenu();
            break;
    }
}

void LoginStudent() {
	system("cls");
       
    cout<<"1. Login \n2. Sign Up \n3. Forgot Password" << endl;
    cout<<"Enter your choice: ";

    int choice = getValidatedInput();

    if (choice==1){
    	system("cls");
        logo("==========================================================================\n",1);
	    logo("                                                                          \n",1);
	    logo("                    |   O G I N    |__ E R E                              \n",1);
	    logo("                    |__            |  |                                   \n",1);
	    logo("===========================================================================\n",1);
        string username, password;
        cout<<"Enter your username: ";
        cin>>username;
        password = getPasswordInput();

        ifstream infile("student_database.txt");
        string file_user, file_pass;
        bool found = false;

        while(infile>>file_user>>file_pass) {
            if(file_user == username && file_pass == password) {
                found = true;
                break;
            }
        }
        infile.close();

        if (found){
            cout<<"Login successful!\n";
            StudentMenu(username);
        } else{
            cout<<"Invalid username or password. Try again.\n";
            LoginStudent();
        }

    } else if (choice == 2) {
        StudentRegister();
    } else if (choice == 3) {
        ForgotPassword();
    } else{
        cout<<"Invalid choice! Please try again.\n";
        LoginStudent();
    }
}
void ForgotPassword(){
system("cls");
	logo("======================================================-====================\n",1);
	logo("                    __                __                                   \n",1);
	logo("                   |_  O R G O T     |__A S S W O R D                    \n",1);
	logo("                   |                 |                                     \n",1);
	logo("===========================================================================\n",1);
    string username;
    cout << "Enter your username: ";
    cin >> username;


    ifstream infile("student_database.txt");
    string file_user, file_pass;
    bool found = false;
    while (infile>>file_user>>file_pass) {
        if (file_user == username) {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout<<"Username not found! Please try again.\n";
        ForgotPassword();
        return;
    }

    string new_password;
    cout << "Enter your new password: ";
    new_password = getPasswordInput();

    ifstream infile_read("student_database.txt");
    ofstream tempfile("temp_database.txt");
    bool updated = false;

    while(infile_read>>file_user>>file_pass) {
        if(file_user == username && !updated){
            tempfile<<file_user<<" "<<new_password<<endl;
            updated = true;
        } else{
            tempfile<<file_user<<" "<<file_pass<<endl;
        }
    }
    infile_read.close();
    tempfile.close();

    remove("student_database.txt");
    rename("temp_database.txt", "student_database.txt");

    cout << "Password updated successfully!\n";
    DisplayMenu();
}

void LoginAdmin(){
	system("cls");
	logo("==========================================================================\n",1);
	logo("                                                                              \n",1);
	logo("                    |   O G I N     /_D M I N                                 \n",1);
	logo("                    |__            /   \                                      \n",1);
	logo("==============================================================================\n",1);
    string name;
    int password;

    cout<<"Enter Admin Name: ";
    cin>>name;
    password=stoi(getPasswordInput());

    if (name!=admin_name || password!=admin_pass) {
        cout << "Invalid Login! Try again.\n";
        LoginAdmin();
    } else {
        cout<<"Login successful!\n";
        AdminMenu();
    }
}

void AdminMenu() {
	system("cls");
    logo("===============================================================================\n",1);
    logo("                        _     _                           _                    \n",1);
    logo("       |   E L C O M E  | O  |_ - M. M. S.  /\\  D M I N  |_| O R T A L        \n",1);
    logo("       |/\\|             |    |_            /--\\          |                   \n",1);
    logo("===============================================================================\n",1); 
	logo("1. Add Questions\n2. View Students\n3. Logout \n",1);
    getch();  
    cout<<"Enter your choice: ";
    int choice=getValidatedInput();

    switch (choice){
        case 1:
            AddQuestion();
            break;
        case 2:
            ViewStudents();
            break;
        case 3:
            DisplayMenu();
            break;
        default:
            cout<<"Invalid choice! Try again.\n";
            AdminMenu();
            break;
    }
}
void StudentMenu(const string &username) {
	system("cls");
    logo("==============================================================================\n",1);
    logo("                        _     _             _               _                   \n",1);
    logo("       |   E L C O M E  | O  |_ - M. M. S. |_ T U D E N T  |_| O R T A L        \n",1);
    logo("       |/\\|             |    |_             _|             |                    \n",1);
    logo("==============================================================================\n",1);
    logo("1. Attempt Quiz\n2. View Results\n3. Pending Papers",1); 
    getch();
    cout<<"Enter your choice: ";
    int choice=getValidatedInput();

    switch(choice){
        case 1:
            AttemptQuiz(username);
            break;
        case 2:
            ViewResults(username);
            break;
        case 3:
            DisplayMenu();
            break;
        default:
            cout<<"Invalid choice! Try again.\n";
            StudentMenu(username);
            break;
    }
}

void StudentRegister(){
	system("cls");
	logo("===================================================================================\n",1);  
    logo("                _                         _                                        \n",1);
    logo("               |_  T U D E N T           | E G I S T R A T I O N                   \n",1);
    logo("                _|                       | \\                                       \n",1);
    logo("===================================================================================\n",1);
    string username, password; 
    cout<<"Enter your username: ";
    cin>>username;
    password=getPasswordInput();

    ofstream outfile("student_database.txt", ios::app);
    outfile<<username<<" "<<password<<endl;
    outfile.close();

    cout<<"\nCongrats! Your account has been created successfully.\n";
    DisplayMenu();
}

void AddQuestion(){
    if (quizCount>=MAX_QUESTIONS) {
        cout<<"Quiz storage is full! Cannot add more questions.\n";
        AdminMenu();
        return;
    }

    Question q;
    cout<<"Enter the question: ";
    cin.ignore();
    getline(cin, q.question);

    for(int i=0; i<4; ++i) {
        cout<<"Enter option "<<i+1<<": ";
        getline(cin, q.options[i]);
    }
    cout<<"Enter the correct option number (1-4): ";
    q.correctOption=getValidatedInput();

    while (q.correctOption<1 || q.correctOption>4) {
        cout<<"Invalid option. Enter a number between 1 and 4: ";
        q.correctOption = getValidatedInput();
    }

    quiz[quizCount++]=q;
    cout<<"Question added successfully!\n";
    AdminMenu();
}

void AttemptQuiz(const string &username) {
    if (quizCount == 0) {
        cout<<"No quiz available at the moment.\n";
        StudentMenu(username);
        return;
    }

    int score =0;
    for(int i=0; i<quizCount; ++i) {
        cout<<"Question "<<i+1<<": "<<quiz[i].question<<endl;
        for (int j=0; j<4; ++j){
            cout<<j+1<<". "<<quiz[i].options[j]<<endl;
        }

        cout<<"Enter your answer (1-4): ";
        int answer=getValidatedInput();

        if (answer==quiz[i].correctOption) {
            ++score;
        }
    }

    bool found = false;
    for(int i=0; i<studentCount; ++i) {
        if(studentNames[i]==username) {
            studentScores[i]=score;
            found = true;
            break;
        }
    }
    
    if (!found && studentCount<MAX_STUDENTS) {
        studentNames[studentCount]= username;
        studentScores[studentCount]= score;
        ++studentCount;
    }
    cout<<"Quiz completed! Your score: "<<score<<"\n";
    StudentMenu(username);
}

void ViewResults(const string &username) {
    for (int i=0; i<studentCount; ++i) {
        if (studentNames[i] == username) {
            cout<<"Your score: "<<studentScores[i]<<"\n";
            StudentMenu(username);
            return;
        }
    }
    cout<<"No results found for you.\n";
    StudentMenu(username);
}
void ViewStudents() {
    ifstream infile("student_database.txt");
    string username, password;

    cout<<"Registered Students:\n";
    while(infile>>username>>password) {
        cout<<"- "<<username<<endl;
    }

    infile.close();
    AdminMenu();
}


int main() {
    DisplayMenu();
    return 0;
}

