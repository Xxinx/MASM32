#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;
//message print design
void pmessage(string m)
{
    bool front;
    for (int i = m.length(); i <33; i++)
    {
        if (front)
        {
            m = " " + m;
        }
        else
        {
            m = m + " ";
        }
        front = !front;
    }
    cout<<m.c_str();
    cout<<endl;
}
//hang man will be drawed when the alphabet input is wrong
//hang man design
void draw(int guessC=0)
{      
	if(guessC == 1)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |                           \n"
                "\t    |                           \n"
                "\t    |                           \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
    if (guessC == 2)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |      0                    \n"
                "\t    |                           \n"
                "\t    |                           \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
 
    if (guessC == 3)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |      0                    \n"
                "\t    |      |                    \n"
                "\t    |                          \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
   
    if (guessC == 4)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |      0                     \n"
                "\t    |     /|                   \n"
                "\t    |                           \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
   
    if (guessC == 5)
        pmessage("\t   ________                  \n"
                "\t    |      |                    \n"
                "\t    |      0                    \n"
                "\t    |     /|\\                    \n"
                "\t    |                           \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
    
    if (guessC == 6)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |      0                    \n"
                "\t    |     /|\\                    \n"
                "\t    |     /                     \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");
    
    if (guessC == 7)
        pmessage("\t   ________                   \n"
                "\t    |      |                    \n"
                "\t    |      0                    \n"
                "\t    |     /|\\                    \n"
                "\t    |     / \\                   \n"
                "\t ___|___                        \n"
				"\t |     |_____                   \n"
				"\t |__________|                   \n");

}

//search the word linearly, user-defined search function
int findString(string wordToFind, char i){
	for(int j=0;j < wordToFind.size();j++){
		if(wordToFind[j] == i){
			return j;
		}
	}
	return -1;
}

//alphabet desin
void pletters(string input, char from, char to)
{
    string s;
    for (char i=from; i<=to; i++)
    {
        if(findString(input,i)==-1)
        {
            s+=i;
            s+=" ";
        }
        else
            s+=" ";
    }
    pmessage(s);
}

//alphabet design, when input any alphabet, the alphabet will disappeared
void pletterdesign(string taken)
{
    pmessage("Alphabet must be Capital\n");
    pletters(taken, 'A', 'M');
    pletters(taken, 'N', 'Z');
}

//create file and open file
string rword(string path)
{
	//initialize the line 
    int lineC = 0;
    string word;
    //file create
    ofstream myfile("words.txt");
    if(myfile.is_open())
    {
    	myfile<<"PROGRAM\n";
    	myfile<<"CAT\n";
    	myfile<<"APPLE\n";
    	myfile<<"HAPPY\n";
    	myfile<<"CHAMPIONSHIP\n";
	    myfile.close();
	}
    else
        cout<<"Unable open file";
    //search  in file linearly
    //read file
	ifstream file("words.txt");
	ifstream file2("words.txt");
    if (file.is_open())
    {
        //search and count linearly each words contain how many lines
        //load the word randomly
		long i=std::count(std::istreambuf_iterator<char>(file), 
             std::istreambuf_iterator<char>(), '\n');
		 int randomLine = rand() % i;
		 i=0;
		 
    	//go through the file each time run
        while (std::getline(file2, word)){
        	if(i == randomLine ){
        		file2.close();
        		return word;
			}
        	i++;
		}
        
    }
    return word;
}

//count the users still have how many trying oppotunity
int tryc(string word, string guessed)
{
    int e = 0;
    for (int i = 0; i<guessed.length(); i++)
    {
    	
    	// if user input wrongly, error will continue added
        if (findString(word,guessed[i])==-1)
            e++;
    }
    return e;
}

//checking whether match the word in file
bool wordwincheck(string word, string guessed)
{
    bool lose = true;
    string s;
    //check all the characters of words that user input whether match the word that written in file
    for (int i = 0; i < word.length(); i++)
    {
        if (findString(guessed,word[i])==-1)
        {
        	//if user guess wrong,placeholder will remain, letter will not show
            lose = false;
            s += "_ ";
        }
        else
        {
        	//if characters match with the character in file, it will show
            s += word[i];
            s += " ";
        }
    }
    pmessage(s);
    return lose;
}

//main program
int main()
{
	char ans;
	do{
    srand(time(0));
    string guess;
    string wordguess;
    //function call, path of file
    wordguess = rword("words.txt");
    int t = 0;
    bool win = false;
    do
    {
    	//clear the screen 
        system("cls");
        pmessage("Hangman Game\n");
        draw(t);
        pletterdesign(guess);
        pmessage("Let's guess !\n");
        win = wordwincheck(wordguess, guess);
        //if win program will break
        char z;
        if (win)
            break;
        cout<<endl;
        //input the alphabet
        cout<<"Input alphabet : ";
		cin >> z;
		cout<<endl;
        if (findString(guess,z)==-1){
            guess += z;  
		}  
		if(findString(wordguess,z)==-1)  
		    ++t;	 
    } while(t<8);//it have 7 times to try
 
    if(win)
        pmessage("You won the game!\n");
    else
        pmessage("Try again next time\n");
    
    //ask user whether want to continue or not
    cout<<"Do you want to continue : \n";
    cin>>ans;
    
    }while(ans=='y'|| ans=='Y');//if input 'y' or 'Y' user can play again
    
    system("pause");
    getchar();
}
