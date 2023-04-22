#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std::chrono;
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
            " ██████████████████████████████████████████████████████████████████████████████████████████████" << endl;


    cout << "Preferred book genre?" << endl;
    cout << "Preferred book length?" <<endl;
    cout << "Desired format?" << endl;

}
