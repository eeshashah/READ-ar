#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "RedBlack.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
using std::ofstream;

// READ-ar
int main() {
    //Reading in Values and Making the Tree
    RedBlack tree;
    ifstream inFile("Pipe_Goodreads100k.csv");
    set<string> allGenresFound;

    if (inFile.is_open()) {
        string lineFromFile;
        getline(inFile, lineFromFile);
        getline(inFile, lineFromFile);

        while (getline(inFile, lineFromFile)) {
            // author|bookformat|desc|genre|img|isbn|isbn13|link|pages|rating|reviews|title|totalratings
            string book, title, author, desc, genre, format, IDstr, pagesStr, ratingStr, temp, genreTemp;
            int pages, ID;
            set<string> genres;

            istringstream stream(lineFromFile);

            getline(stream, author, '|');
            getline(stream, format, '|');
            getline(stream, desc, '|');
            getline(stream, genre, '|');
            getline(stream, temp, '|');
            getline(stream, IDstr, '|');
            getline(stream, temp, '|');
            getline(stream, temp, '|');
            getline(stream, pagesStr, '|');
            getline(stream, ratingStr, '|');
            getline(stream, temp, '|');
            getline(stream, title, '|');
            getline(stream, temp, '|');

            stringstream g(genre);

            //add it into the individual books genre set
            while (getline(g, genreTemp, ',')) {
                genres.insert(genreTemp);
                getline(g, genreTemp, ',');
                genres.insert(genreTemp);
            }

            //add into overall list of genres
            set<string>::iterator itr;
            for(itr = genres.begin(); itr != genres.end(); itr++){
                allGenresFound.insert(*itr);
            }

            bool use = true;
            if(!pagesStr.empty()){
                for(int i = 0; i < pagesStr.size(); i++){
                    if(!isdigit(pagesStr[0])){
                        use = false;
                    }
                }

                if(use && (stol(pagesStr) > 2000 || stol(pagesStr) == 0)){
                    use = false;
                }

                if(use){
                    pages = stoi(pagesStr);
                    tree.insert(genres, title, desc, pages, author, ratingStr, format);

                }
            }

        }
    }

    bool end = false;
    string userGenre;
    int userLength;
    string userFormat;
    int lengthMin, lengthMax;
    int BFSorDFS;


    while (end == false) {
        cout << endl;
        cout << "       █░█░█  █▀▀  █    █▀▀  █▀█  █▀▄▀█  █▀▀   ▀█▀  █▀█\n"
        "       ▀▄▀▄▀  ██▄  █▄▄  █▄▄  █▄█  █░▀░█  ██▄   ░█░  █▄█\n"
        "                                                                                     ██\n"
        "     ██████╗░███████╗░█████╗░██████╗░░░░░░░░█████╗░██████╗░                ░░░░░░  ██  ██\n"
        "     ██╔══██╗██╔════╝██╔══██╗██╔══██╗░░░░░░██╔══██╗██╔══██╗    ▄▀▀▀▀▀▀▄    ░░██░░    ██\n"
        "     ██████╔╝█████╗░░███████║██║░░██║█████╗███████║██████╔╝   █╗░░▐░░░╔█   ░░██░░ ░░░░░░░\n"
        "     ██╔══██╗██╔══╝░░██╔══██║██║░░██║╚════╝██╔══██║██╔══██╗   █║░░▐▄▄░║█   ░░██░░ ░░███░░\n"
        "     ██║░░██║███████╗██║░░██║██████╔╝░░░░░░██║░░██║██║░░██║   █╝░░░░░░╚█   ░░██░░ ░░███░░\n"
        "     ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░░░░░░░╚═╝░░╚═╝╚═╝░░╚═╝    ▀▄▄▄▄▄▄▀    ░░██░░ ░░███░░\n"
        "   ██████████████████████████████████████████████████████████████████████████████████████████\n"
        " ██████████████████████████████████████████████████████████████████████████████████████████████\n";
        cout << endl;
        cout << "       Answer a few short questions: \n"
                "\n"
                "       1) Preferred book genre? Here are some options:\n " << endl;

        cout << "       Academia, Academic, Accounting, Action, Activism, Adult, Adult Fiction, Adventure, Aeroplanes" << endl;
        cout << "       African American, Agriculture, Aircraft, Albanian Literature, Alchemy, American Civil War" << endl;
        cout << "       American Classics, American Fiction, American History, American Revolutionary War" <<endl;
        cout << "       Christianity, Family Law, Fandom, Fantasy, Fantasy Romance, Social Change" <<endl;
        cout << "       Social Justice, Social Media, Social Movements, Society, Sociology, Vaccines" << endl;
        cout << "       Vampires, Vegan, Vegetarian, Video Games, Womens Fiction, Womens Rights" << endl;
        cout << "       World History, World War I, Young Adult, Young Adult Contemporary, Young Adult Fantasy"  << endl;
        cout << "       ";

        getline(cin, userGenre);

        cout<<endl;
        cout << "       2) Preferred book length?\n" // Add more options depending on largest page length
                "       1. 0-50 pages 2. 50-100 pages 3. 100-200 pages 4. 200-300 pages 5. 300-400 pages 6. 400+ pages\n";
        cout << "       ";

        cin >> userLength;
        if(userLength == 1){
            lengthMin = 0;
            lengthMax = 50;
        }
        else if(userLength == 2){
            lengthMin = 50;
            lengthMax = 100;
        }
        else if(userLength == 3){
            lengthMin = 100;
            lengthMax = 200;
        }
        else if(userLength == 4){
            lengthMin = 200;
            lengthMax = 300;
        }
        else if(userLength == 5){
            lengthMin = 300;
            lengthMax = 400;
        }
        else if (userLength == 6){
            lengthMin = 500;
            lengthMax = 10000;
        }

        cout<<endl;

        cout << "       3) Hardcover or Paperback?\n";
        cout << "       ";
        cin >> userFormat;

        cout<<endl;
        cout << "       4) Would you like to solve your approach with Breadth-First Search or Depth-First Search?\n";
        cout << "       Enter 0 for BFS or 1 for DFS\n";
        cout << "       ";
        cin >> BFSorDFS;

        cout<<endl;
        cout << "       Thank you!";
        cout << endl;
        cout << endl;

        cout << "       █░░  █▀█  ▄▀█  █▀▄  █  █▄░█  █▀▀\n"
        "       █▄▄  █▄█  █▀█  █▄▀  █  █░▀█  █▄█\n"
        "       Finding your new favorite books!\n"
        "\n"
        "     ██████╗░███████╗░█████╗░██████╗░░░░░░░░█████╗░██████╗░\n"
        "     ██╔══██╗██╔════╝██╔══██╗██╔══██╗░░░░░░██╔══██╗██╔══██╗    ▄▀▀▀▀▀▀▄\n"
        "     ██████╔╝█████╗░░███████║██║░░██║█████╗███████║██████╔╝   █╗░░▐░░░╔█\n"
        "     ██╔══██╗██╔══╝░░██╔══██║██║░░██║╚════╝██╔══██║██╔══██╗   █║░░▐▄▄░║█\n"
        "     ██║░░██║███████╗██║░░██║██████╔╝░░░░░░██║░░██║██║░░██║   █╝░░░░░░╚█\n"
        "     ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░░░░░░░╚═╝░░╚═╝╚═╝░░╚═╝    ▀▄▄▄▄▄▄▀    ░░  ░░  ░░\n"
        "   ██████████████████████████████████████████████████████████████████████████████████████████\n"
        " ██████████████████████████████████████████████████████████████████████████████████████████████ ";
        cout << endl;
        cout << endl;

        string userStatus;

        cout << endl;
        cout << "            ██████\n"
        "          ██░░░░░░██\n"
        "        ██░░░░░░░░░░░██\n"
        "      ██░░▄▀▀▀▀▀▀▄     ██               █░█  █▀▀  █▀█  █▀▀  ▀  █▀     █░█░█  █░█  ▄▀█  ▀█▀\n"
        "    ██░░░█╗░░▐░░░╔█      ██             █▀█  ██▄  █▀▄  ██▄     ▄█     ▀▄▀▄▀  █▀█  █▀█   █\n"
        "  ██░░░░░█║░░▐▄▄░║█     ████\n"
        "██░░░░░░░█╝░░░░░░╚█   ██  ██            █░█░█  █▀▀     █▀▀  █▀█  █░█  █▄░█  █▀▄  █\n"
        "████░░░░░░▀▄▄▄▄▄▄▀  ██  ██              ▀▄▀▄▀  ██▄     █▀   █▄█  █▄█  █░▀█  █▄▀  ▄\n"
        "  ██░░██          ██  ██\n"
        "      ██░░████  ██  ██\n"
        "        ██    ██\n"
        "          ████\n"
        "  \n"
        "\n"
        "█▄█  █▀█  █░█  █▀█     █▀█  █▀▀  █▀▀  █▀  ▀\n"
        "░█░  █▄█  █▄█  █▀▄     █▀▄  ██▄  █▄▄  ▄█  ▄\n"
        "███████████████████████████████████████████\n";

        vector<Node*> bookRecs;
        //BFS
        if(BFSorDFS == 0 ) {
            int count = 0;
            auto startTime = high_resolution_clock::now();
            tree.BFS(tree.root, userGenre, lengthMin, lengthMax, userFormat, bookRecs,  count);
            auto stopTime = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stopTime - startTime);
            cout << endl << "BFS Time: " << duration.count()<< " microseconds" << endl;
        }
        //DFS
        if(BFSorDFS == 1) {
            int count = 0;
            auto startTime = high_resolution_clock::now();
            tree.DFS(tree.root,userGenre, lengthMin, lengthMax, userFormat, bookRecs, count);
            auto stopTime = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stopTime - startTime);
            cout <<  endl << "DFS Time: " << duration.count()<< " microseconds" << endl;
        }

        cout << endl;
        // Output from RedBlack/DFS/BFS with this format
        cout << "Here's what we found!" <<endl;
        for(int i = 0; i < bookRecs.size(); i++){
            cout << endl;
            cout<< (i+1) << ". " << bookRecs[i] ->title << endl;
            cout << "Author: " << bookRecs[i]->author << endl;
            cout << "Description: " << bookRecs[i]->description << endl;
            cout << "Genre(s): ";
            for(auto genre: bookRecs[i]->genre){
                cout << genre << ", ";
            }
            cout<< endl;
            cout << "Book Length: " << bookRecs[i]->pages << endl;
            cout << "Estimated Reading Time: " << (bookRecs[i]->pages*2) << " minutes" << endl;
            cout << "Average Rating: " << stod(bookRecs[i]->rating) <<endl ;
            long r = stol(bookRecs[i]->rating);
            int rr = r;
            for (int i = 0; i < rr; i++){
                cout<<"✰";
            }
            cout<<"/✰✰✰✰";

            cout << endl;

        }


        cout << endl;
        cout << "Are you happy with your recommendations? (Yes/No)\n";
        cin >> userStatus;

        if (userStatus == "Yes" || userStatus == "yes") {
            end = true;
            break;
        }

        cout << "Would you like to try again (Yes/No)\n";

        cin >> userStatus;
        if (userStatus == "No" || userStatus == "no") {
            end = true;
        }
        cin.get();

    }

    cout << endl;
    cout << "     ▀█▀  █░█  ▄▀█  █▄░█  █▄▀     █▄█  █▀█  █░█     █▀▀  █▀█  █▀█     █░█  █▀  █  █▄░█  █▀▀\n"
            "     ░█░  █▀█  █▀█  █░▀█  █░█     ░█░  █▄█  █▄█     █▀░  █▄█  █▀▄     █▄█  ▄█  █  █░▀█  █▄█\n"
            "\n"
            "     ██████╗░███████╗░█████╗░██████╗░░░░░░░░█████╗░██████╗░     ██╗\n"
            "     ██╔══██╗██╔════╝██╔══██╗██╔══██╗░░░░░░██╔══██╗██╔══██╗     ██║     ▄▀▀▀▀▀▀▄\n"
            "     ██████╔╝█████╗░░███████║██║░░██║█████╗███████║██████╔╝     ██║    █╗░░▐░░░╔█\n"
            "     ██╔══██╗██╔══╝░░██╔══██║██║░░██║╚════╝██╔══██║██╔══██╗     ╚═╝    █║░░▐▄▄░║█\n"
            "     ██║░░██║███████╗██║░░██║██████╔╝░░░░░░██║░░██║██║░░██║     ██╗    █╝░░░░░░╚█\n"
            "     ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░░░░░░░╚═╝░░╚═╝╚═╝░░╚═╝     ╚═╝     ▀▄▄▄▄▄▄▀\n"
            "   ██████████████████████████████████████████████████████████████████████████████████████████\n"
            " ██████████████████████████████████████████████████████████████████████████████████████████████ ";
    cout << endl;

}
