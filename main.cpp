#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "RedBlack.h"
using namespace std;
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

    set<string>::iterator itr;
    for(itr = allGenresFound.begin(); itr != allGenresFound.end(); itr++){
       // cout<< *itr << endl;
    }

    bool end = false;
    string userGenre;
    int userLength;
    string userFormat;

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
                "       1) Preferred book genre? Here's some options:\n";

        cout << "       Academia, Academic, Accounting, Action, Activism, Adult, Adult Fiction, Adventure, Aeroplanes" << endl;
        cout << "       African American, Agriculture, Aircraft, Albanian Literature, Alchemy, American Civil War" << endl;
        cout << "       American Classics, American Fiction, American History, American Revolutionary War" <<endl;
        cout<< "       Christianity, Family Law, Fandom, Fantasy, Fantasy Romance, Social Change" <<endl;
        cout<< "       Social Justice, Social Media, Social Movements, Society, Sociology, Vaccines" << endl;
        cout << "       Vampires, Vegan, Vegetarian, Video Games, Womens Fiction, Womens Rights" << endl;
        cout << "       World History, World War I, Young Adult, Young Adult Contemporary, Young Adult Fantasy"  << endl;

        cin >> userGenre;


        cout << "       2) Preferred book length?\n" // Add more options depending on largest page length
                "       1. 0-50 pages 2. 50-100 pages 3. 100-150 pages 4. 200-250 pages 5. 300-350 pages\n";
        cout << "       ";
        cin >> userLength;

        cout << "       3) Hardcover or Paperback?\n";
        cout << "       ";
        cin >> userFormat;

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

        //implement DFS and BFS
        //check if outputs are valid with different fucntions-  like make sure a link is not printing or something weird
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
                "███████████████████████████████████████████\n"
                // Output from RedBlack/DFS/BFS with this format
                "1. Book 1\n"
                "- Author:\n"
                "- Description:\n"
                "- Genre(s):\n"
                "- Book length:\n"
                // Multiply page # by 2 (b/c avg of 2 minutes per page) to get reading time
                "- Estimated reading time:\n"
                // Maybe round the rating double to an int & based on the int output however many stars?
                "- Average rating: ✰✰✰✰✰\n"
                "2. Book 2 ... ";

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
