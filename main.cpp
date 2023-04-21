#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
//#include "RedBlack.h"
using namespace std;
using std::ofstream;

void readFile(string file) {
    ifstream inFile(file);

    if (inFile.is_open()) {
        // author, bookformat, desc, genre, img, isbn (ID), isbn13, link, pages, rating, reviews, title, totalratings
        // If a book has more than one term, it will have quotes
        // Possible quotes: author, desc, genre

        string book, temp1, title, author, desc, descTemp, genre, format, IDstr, pagesStr, ratingStr, temp, helper;
        int pages, ID;
        double rating;

        string lineFromFile;
        getline(inFile, lineFromFile);
        // cout << temp1 << endl;

        while (getline(inFile, lineFromFile)) {
            // Laurence M. Hauptman,Hardcover,"Reveals that several hundred thousand Indians were affected by the Civil War and that twenty thousand Indians enlisted on both sides in an attempt to gain legitimacy, autonomy, or simply land.","History,Military History,Civil War,American History,American Civil War,Nonfiction,North American Hi...,American History,Native Americans",https://i.gr-assets.com/images/S/compressed.photo.goodreads.com/books/1387738765l/1001053.jpg,002914180X,9.78E+12,https://goodreads.com/book/show/1001053.Between_Two_Fires,0,3.52,5,Between Two Fires: American Indians in the Civil War,33
            istringstream stream(lineFromFile);

            getline(stream, book);

            stringstream bk(book);

            cout << "Start Book: " << book << endl;

            if (book[0] == '"') {
                getline(bk, temp, '"');
                getline(bk, author, '"');
                getline(bk, temp, ',');
                getline(bk, format, ',');
                book = book.substr(author.size() + 3 + format.size() + 1, book.size()-1);
                cout << "Author: " << author << endl;
                if (format.empty()) {
                    format = "N/A";
                }
                cout << "Format: " << format << endl;
                // cout << "Book1: " << book << endl;
            }
            else {
                getline(bk, author, ',');
                getline(bk, format, ',');
                book = book = book.substr(author.size() + 1 + format.size() + 1, book.size()-1);
                if (format.empty()) {
                    format = "N/A";
                }
                cout << "Book1: " << book << endl;
                cout << "Author: " << author << endl;
                cout << "Format: " << format << endl;
            }

            if (book[0] == '"') {
                // "Charlotte Fiell,Emmanuelle Dirix",Paperback,"Fashion Sourcebook - 1920s is the first book in a brand-new series by Fiell Publishing that documents comprehensively the seasonal fashion styles of the 20th century, decade by decade. Sumptuously illustrated with over 600 original photographs, drawings and prints, this title is a must-have reference work for not only students of fashion, but for all fashionistas. Fashion Sourcebook - 1920s focuses on the Art Deco period with its beautiful beaded dresses, cloche hats and t-bar shoes as worn by the fashionable flappers and the ""bright young things"" of the time. An accompanying introduction outlines the major themes within fashion during this period and introduces its most famous designers and assesses their creative contributions. Text in English, French & German. Also Available: Fashion Sourcebook - 1930s ISBN: 9781906863586 24.95""","Couture,Fashion,Historical,Art,Nonfiction",https://i.gr-assets.com/images/S/compressed.photo.goodreads.com/books/1421011497l/10010552.jpg,1906863482,9.78E+12,https://goodreads.com/book/show/10010552-fashion-sourcebook-1920s,576,4.51,6,Fashion Sourcebook 1920s,41
                getline(bk, temp, '"');
                getline(bk, desc, '"');
                cout << "Desc1: " << desc << endl;
                helper = book;
                helper = helper.substr(desc.size() + 1, book.size());
                cout << "helper: " << helper << endl;
                if (helper[1] == '"' || desc.empty()) {
                    getline(bk, descTemp, '"');
                    getline(bk, descTemp, '"');
                    // cout << descTemp << "huh" << endl;
                    desc = desc + '"' + descTemp + '"';
                    getline(bk, descTemp, '"');
                    getline(bk, descTemp, '"');
                    // cout << "um" << descTemp << endl;
                    desc = desc + descTemp;
                    cout << "Desc2: " << desc << endl;
                    book = book.substr(desc.size() + 5, book.size() - 1);
                    cout << "Book2: " << book << endl;
                }
                else {
                    book = book.substr(desc.size() + 3, book.size() - 1);
                    // cout << "Book2: " << book << endl;
                }
            }
            else {
                cout << "Desc1: " << desc << endl;
                getline(bk, desc, ',');
                book = book.substr(desc.size() + 1, book.size() - 1);
                // cout << "Book2: " << book << endl;
            }

            if (book[0] == '"') {
                // "Charlotte Fiell,Emmanuelle Dirix",Paperback,"Fashion Sourcebook - 1920s is the first book in a brand-new series by Fiell Publishing that documents comprehensively the seasonal fashion styles of the 20th century, decade by decade. Sumptuously illustrated with over 600 original photographs, drawings and prints, this title is a must-have reference work for not only students of fashion, but for all fashionistas. Fashion Sourcebook - 1920s focuses on the Art Deco period with its beautiful beaded dresses, cloche hats and t-bar shoes as worn by the fashionable flappers and the ""bright young things"" of the time. An accompanying introduction outlines the major themes within fashion during this period and introduces its most famous designers and assesses their creative contributions. Text in English, French & German. Also Available: Fashion Sourcebook - 1930s ISBN: 9781906863586 24.95""","Couture,Fashion,Historical,Art,Nonfiction",https://i.gr-assets.com/images/S/compressed.photo.goodreads.com/books/1421011497l/10010552.jpg,1906863482,9.78E+12,https://goodreads.com/book/show/10010552-fashion-sourcebook-1920s,576,4.51,6,Fashion Sourcebook 1920s,41
                getline(bk, temp, '"');
                getline(bk, genre, '"');
                book = book.substr(genre.size() + 3, book.size() - 1);
                if (genre.empty()) {
                    genre = "N/A";
                }
                cout << "Genre: " << genre << endl;
                // cout << "Book4: " << book << endl;
            }
            else {
                getline(bk, genre, ',');
                book = book.substr(genre.size() + 1, book.size() - 1);
                if (genre.empty()) {
                    genre = "N/A";
                }
                cout << "Genre: " << genre << endl;
                // cout << "Book4: " << book << endl;
            }
            // author, bookformat, desc, genre, img, isbn (ID), isbn13, link, pages, rating, reviews, title, totalratings

            getline(bk, temp, ',');
            getline(bk, temp, ',');
            getline(bk, IDstr, ',');
            cout << "ID: " << IDstr << endl;
            getline(bk, temp, ',');
            getline(bk, temp, ',');
            getline(bk, pagesStr, ',');
            cout << "Pages: " << pagesStr << endl;
            /*
            if (!pagesStr.empty() || isdigit(pagesStr[0])) {
                pages = stoi(pagesStr);
            }
             */
            getline(bk, ratingStr, ',');
            cout << "Rating: " << ratingStr << endl;
            getline(bk, temp, ',');
            getline(bk, title, ',');
            cout << "Title: " << title << endl;
            getline(bk, temp, ',');

            // Change rating to be a string and genres to be a string
            // Add format?
            // tree.insertHelper(genre, title, desc, pages, author, ratingStr);
        }
    }
}

// READ-ar
int main() {
    // RedBlack tree;
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

    // Fasion, Richard Wiseman
    readFile("GoodReads_100k_books.csv");
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

}

/*

       █░█░█  █▀▀  █    █▀▀  █▀█  █▀▄▀█  █▀▀   ▀█▀  █▀█
       ▀▄▀▄▀  ██▄  █▄▄  █▄▄  █▄█  █░▀░█  ██▄   ░█░  █▄█
                                                                                     ██
     ██████╗░███████╗░█████╗░██████╗░░░░░░░░█████╗░██████╗░                ░░░░░░  ██  ██
     ██╔══██╗██╔════╝██╔══██╗██╔══██╗░░░░░░██╔══██╗██╔══██╗    ▄▀▀▀▀▀▀▄    ░░██░░    ██
     ██████╔╝█████╗░░███████║██║░░██║█████╗███████║██████╔╝   █╗░░▐░░░╔█   ░░██░░ ░░░░░░░
     ██╔══██╗██╔══╝░░██╔══██║██║░░██║╚════╝██╔══██║██╔══██╗   █║░░▐▄▄░║█   ░░██░░ ░░███░░
     ██║░░██║███████╗██║░░██║██████╔╝░░░░░░██║░░██║██║░░██║   █╝░░░░░░╚█   ░░██░░ ░░███░░
     ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░░░░░░░╚═╝░░╚═╝╚═╝░░╚═╝    ▀▄▄▄▄▄▄▀    ░░██░░ ░░███░░
   ██████████████████████████████████████████████████████████████████████████████████████████
 ██████████████████████████████████████████████████████████████████████████████████████████████



       █░░  █▀█  ▄▀█  █▀▄  █  █▄░█  █▀▀
       █▄▄  █▄█  █▀█  █▄▀  █  █░▀█  █▄█

     ██████╗░███████╗░█████╗░██████╗░░░░░░░░█████╗░██████╗░
     ██╔══██╗██╔════╝██╔══██╗██╔══██╗░░░░░░██╔══██╗██╔══██╗    ▄▀▀▀▀▀▀▄
     ██████╔╝█████╗░░███████║██║░░██║█████╗███████║██████╔╝   █╗░░▐░░░╔█
     ██╔══██╗██╔══╝░░██╔══██║██║░░██║╚════╝██╔══██║██╔══██╗   █║░░▐▄▄░║█
     ██║░░██║███████╗██║░░██║██████╔╝░░░░░░██║░░██║██║░░██║   █╝░░░░░░╚█
     ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░░░░░░░╚═╝░░╚═╝╚═╝░░╚═╝    ▀▄▄▄▄▄▄▀    ░░  ░░  ░░
   ██████████████████████████████████████████████████████████████████████████████████████████
 ██████████████████████████████████████████████████████████████████████████████████████████████


            ██████
          ██░░░░░░██                 Here's what we found!
        ██░░░░░░░░░░░██
      ██░░▄▀▀▀▀▀▀▄     ██
    ██░░░█╗░░▐░░░╔█      ██
  ██░░░░░█║░░▐▄▄░║█     ████
██░░░░░░░█╝░░░░░░╚█   ██  ██
████░░░░░░▀▄▄▄▄▄▄▀  ██  ██
  ██░░██          ██  ██
      ██░░████  ██  ██
        ██    ██
          ████


 */

