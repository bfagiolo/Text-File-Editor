#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <set>


using namespace std;

void Menu(){
    for (int i=0; i<26;i++){
        cout << "-";
    }
    cout << "MENU";
    for (int i=0; i<26;i++){
        cout << "-";
}
    cout << endl;
    cout << "1. Search         2. Replace" << endl;
    cout << "0. Exit" << endl; 
    for (int i=0; i<60;i++){
        cout << "-";
}
    cout << endl;
}

void search(string userFile){
    ifstream ifs;
    ifs.open(userFile.c_str());
    if(!ifs.is_open()) {
        // print error message
        cout << "could not open file" << endl;
        return;
    }
    string line;
    string userWord;
    cout << "Enter your search item = " << endl;
    cin >> userWord;
    set<int>New_set;
    int numLine = 0;
    int count = 0;
    while(!ifs.eof()) {
        getline(ifs, line);
        numLine++;
        size_t found = line.find(userWord);
        for (int i=0; i<line.size(); i++){
            if (found!=string::npos){
                count++;
                New_set.insert(numLine);
                found = line.find(userWord, found+1);
            }
        }
    }
    if (count==0){
        cout << "No matching found for " << userWord << endl;
        return;
    }

    cout << userWord << " appeared " << count << " times at the following line(s)" << endl;
    set<int>::iterator it;
    for (it= New_set.begin(); it != New_set.end(); ++it)     
        cout << ' ' << *it;
    cout << endl;

    ifs.close();
}

void replace2(string filename){
    string searchText, newText;
    cout << "Enter your search text = ";
    cin >> searchText;
    cout << "Enter the new text = ";
    cin >> newText;

    ostringstream oss;

    // open the file
    ifstream ifs;
    ifs.open(filename.c_str());
    if(!ifs.is_open()) {
        // print error message
        cout << "could not open file" << endl;
        return;
    }

    // using the ifs read the file line by line 
    string line;
    int count = 0;
    while(!ifs.eof()) {
        getline(ifs, line);
        // do the replace 
        size_t found = line.find(searchText);
        for (int i=0; i<line.size(); i++){
            if (found!=string::npos){
                count++;
                line.replace(found, searchText.size(), newText);
                found = line.find(searchText, found+1);
            }
        }
        oss << line << endl;    
    }

    ofstream output;
    output.open(filename.c_str());
    if(!output.is_open()) {
        // print error message
        cout << "could not open file" << endl;
        return;
    }
    output << oss.str();

    if (count>0){
    cout << "Successfully replaced \"" << searchText << "\" by " << newText << " in " << count << " different places." << endl;
    }
    else {
        cout << "No matches found for " << searchText << endl;
    }

    ifs.close();
    output.close();
}

int main() {
    string userFile;
    cout << "Enter your file name: ";
    cin >> userFile;
    ifstream ifs;
    ifs.open(userFile);
    
    if (!ifs.is_open()) {
        cout << "I couldn't open the file" << endl;
        return 0;
    }
    ifs.close();
    


    while (true){  
    Menu();
    int userChoice;
    cout << "Enter your choice = ";
    cin >> userChoice;
    cout << endl;
    
    switch (userChoice){
        case 1:
            search(userFile);
            break;
        case 2:
            replace2(userFile);
            break;
         case 0:
            return 0;
        default:
            cout << "Invalid choice." << endl;
    
    }

}

    return 0;
}