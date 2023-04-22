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
    RedBlack tree;
    set<string> genres;

    // Title,description,authors,image,previewLink,publisher,publishedDate,infoLink,categories,ratingsCount
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
    cout << " Preferred book genre?" << endl;
    
    ifstream inFile("Pipe_Goodreads100k.csv");

    /*
    readFile("Part1-GoodReads_100k_books.csv");
    readFile("Part2-GoodReads_100k_books.csv");
    readFile("Part3-GoodReads_100k_books.csv");
    readFile("Part4-GoodReads_100k_books.csv");
    readFile("Part5-GoodReads_100k_books.csv");
    readFile("Part6-GoodReads_100k_books.csv");
    readFile("Part7-GoodReads_100k_books.csv");
    readFile("Part8-GoodReads_100k_books.csv");
    readFile("Part9-GoodReads_100k_books.csv");
    readFile("Part10-GoodReads_100k_books.csv");
     */

    if (inFile.is_open()) {
        string book, title, author, desc, genre, format, IDstr, pagesStr, ratingStr, temp, genreTemp;
        int pages, ID;
        double rating;

        string lineFromFile;
        getline(inFile, lineFromFile);
        getline(inFile, lineFromFile);

        while (getline(inFile, lineFromFile)) {
            // author|bookformat|desc|genre|img|isbn|isbn13|link|pages|rating|reviews|title|totalratings
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

            while (getline(g, genreTemp, ',')) {
                genres.insert(genreTemp);
                getline(g, genreTemp, ',');
                genres.insert(genreTemp);
            }

            /*
            cout << "Author: " << author << endl;
            cout << "Format: " << format << endl;
            cout << "Desc: " << desc << endl;
            cout << "Genre: " << genre << endl;
            cout << "Pages: " << pagesStr << endl;
            cout << "Rating: " << ratingStr << endl;
            cout << "Title: " << title << endl;
            */

            /*
            if (!pagesStr.empty()) {
                pages = stoi(pagesStr);
            }
            if (!ratingStr.empty()) {
                rating = stoi(ratingStr);
            }
            */

            // vector<string> genre, string title, string description,int pages, string author, double rating
            // * Turn genre into a string, add format
            tree.insert(genre, title, desc, pages, author, rating, format);

        }
    }

}
