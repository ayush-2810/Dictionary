#include<bits/stdc++.h>
using namespace std;

class DictionaryNode{               // Class DictionaryNode for making nodes for each character.
    public:
    DictionaryNode** children;
    char data;
    bool isTerminal;
    string meaning;

    DictionaryNode(char data){      // Constructor of the node.
        this -> data = data;
        children = new DictionaryNode*[26];
        for(int i=0;i<26;++i)
            children[i] = NULL;
        isTerminal = false;
        meaning = "";
    }
};

class Dictionary{                            // Class Dictionary

    DictionaryNode* root;
    public:
    Dictionary(){                            // Constructor of the dictionary. Making root of the dictionary empty.
        root = new DictionaryNode('\0');
    }

    void InsertWord(DictionaryNode* root, string word, string meaning){      // Function for inserting the word.

        if(word.size()==0){                                 // Base case.
            root -> isTerminal = true;
            root -> meaning = meaning;
            return ;}

        int index = word[0] - 'a';                          // Small calculation.

        DictionaryNode* child;
        if(root -> children[index]!=NULL)
            child = root->children[index];
        else{
            child = new DictionaryNode(word[0]);
            root -> children[index] = child;
        }
        InsertWord(child, word.substr(1), meaning);                  // Recursively inserting all the characters.
    }

    string SearchWord(DictionaryNode* root, string word){    // Function for searching a word.

        if(word.size()==0){                                 // Base case.
            if(root -> isTerminal == true)
                return root -> meaning;
            return "0";
        }

        int index =  word[0] - 'a';                         // Small calculation.

        if(root -> children[index]!=NULL){
            if(root -> children[index] -> data == word[0])
                return SearchWord(root -> children[index],word.substr(1));}
        else
            return "0";
    }

    // For user.
    void InsertWord(string word,string meaning){
        return InsertWord(root, word, meaning);
    }

    string SearchWord(string word){
        return SearchWord(root, word);
    }
};

void InsertHelp(string s, Dictionary t){
    string mean;
    cout<<("Enter the meaning: ");
    cin.ignore();
    getline(cin, mean);
    t.InsertWord(s, mean);
}

int main(){
    Dictionary t;       // Object of the dictionary.
    cout<<("Menu:\n1.Insert a word.\n2.Search a word.\n3.Exit");
    int choice;
    string s;
    while(true){
        cout<<("\n\nEnter the choice: ");
        cin>>choice;
        switch(choice){

            case 1: {
                    cout<<("Enter the word: ");
                    cin>>s;
                    string check = t.SearchWord(s);
                    if(check == "0"){
                        InsertHelp(s, t);
                        cout<<("Word added.\n");}
                    else{
                        cout<<("Word already exists. Do you want to change its existing meaning?\nEnter 0 or 1: ");
                        int check;
                        cin>>check;
                        if(check == 1){
                            InsertHelp(s, t);
                            cout<<("Meaning updated.\n");}
                    }
            }
                    break;

            case 2: {
                    cout<<("Enter the word: ");
                    cin>>s;
                    string check;
                    check = t.SearchWord(s);
                    if(check == "0"){
                        cout<<("Word does not exist.\nDo you want to insert this new word?\nEnter 0 or 1.\n\n");
                        int check;
                        cin>>check;
                        if(check==1){
                            InsertHelp(s, t);
                            cout<<("New word added.\n");}
                    }
                    else
                        cout<<"Word meaning: "<<check<<"\n";
            }
                    break;

            case 3: exit(0);

            default : cout<<("Enter the correct choice.\n");
                      break;
        }
    }
    return 0;
}
