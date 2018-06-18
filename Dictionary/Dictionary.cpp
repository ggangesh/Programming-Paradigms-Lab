/*Extra features included :
    1)case insensitive :even if inputed word contains any upercase letter it will first get converted to lowercase and then searched
    2)provision for adding new word from the terminal itself
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;



struct word
{
    string meaning;
};



int main()
{

    ifstream infile("Dictionary.txt");

    map<string, word> Meaning_map;

    cout<<"Enter the word to be searched or else just press enter to proceed store new word or end"<<endl<<endl;

    if (infile.is_open())
    {
        string name1;
        word w1;

        while(getline(infile, name1, ','))
        {

            string meaning1;
            getline(infile, meaning1,'\n');//read meaning of word till newline occurs

            w1.meaning = meaning1;

            Meaning_map[name1] = w1;
        }

        while((getline(cin, name1))&&(name1!=""))//loop to go on showing meanings till user enters nothing
        {
            std::transform(name1.begin(), name1.end(), name1.begin(), ::tolower);//to make case-insensitive

            if (Meaning_map.count(name1)>0)
            {
                cout<<endl<<Meaning_map[name1].meaning<<endl<<endl;
            }

            else
            {
                cout<<endl<<"Invalid word or word not stored in the memory"<<endl<<endl;
            }

        }
    }


    else
    {
        cout<<"Could not open the file Dictionary.txt";
        return -1;
    }

    infile.close();//closing the input file

    cout<<endl<<"Do you wish to store new word ? (y/n)"<<endl;
    char choice;
    cin>>choice;
    string name1;
    getline(cin,name1);//just to neglect extra newlineline character entered

    if((choice=='y')||(choice=='Y'))//code to store a new word in the file dictionary.txt
    {
        ofstream myfile ("Dictionary.txt",ios::app);
        if (myfile.is_open())
        {
            string name1,meaning1;
            cout<<endl<<"Enter the name of the word"<<endl;
            getline(cin,name1);
            myfile << name1;
            myfile << ",";

            cout<<endl<<"Enter the meaning of the word"<<endl;
            getline(cin,meaning1);
            myfile << meaning1;
            myfile << "\n";
        }



        else
        {
            cout << "Unable to open file";
            return -1;
        }

        myfile.close();

    }//end of the case user wishes to store new word


    return 0;

}
