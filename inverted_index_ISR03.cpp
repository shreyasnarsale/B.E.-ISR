#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure for storing document information
struct Document
{
    string filename;
    string content;
};

// Convert a word to lowercase
string toLowerCase(string word)
{
    for (char &c : word)
    {
        c = tolower(static_cast<unsigned char>(c));
    }

    return word;
}

// Remove punctuation from a word
string cleanWord(string word)
{
    string result;

    for (char c : word)
    {
        if (isalnum(static_cast<unsigned char>(c)))
        {
            result += c;
        }
    }

    return result;
}

// Read document
string readFile(string filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening " << filename << endl;
        return "";
    }

    string line;
    string content;

    while (getline(file, line))
    {
        content += line + " ";
    }

    file.close();

    return content;
}

// Build inverted index
map<string, set<int>> buildInvertedIndex(
    const vector<Document> &documents)
{
    map<string, set<int>> invertedIndex;

    for (int i = 0; i < documents.size(); i++)
    {
        stringstream ss(documents[i].content);
        string word;

        while (ss >> word)
        {
            word = toLowerCase(word);
            word = cleanWord(word);

            if (!word.empty())
            {
                invertedIndex[word].insert(i);
            }
        }
    }

    return invertedIndex;
}

// Display inverted index
void displayInvertedIndex(
    const map<string, set<int>> &invertedIndex,
    const vector<Document> &documents)
{
    cout << "\n=============================================\n";
    cout << "             INVERTED INDEX\n";
    cout << "=============================================\n\n";

    cout << "Vocabulary\tOccurrences\n";
    cout << "---------------------------------------------\n";

    for (const auto &entry : invertedIndex)
    {
        cout << entry.first << "\t\t";

        for (int docID : entry.second)
        {
            cout << documents[docID].filename << " ";
        }

        cout << endl;
    }
}

// Search query in inverted index
void searchQuery(
    string query,
    const map<string, set<int>> &invertedIndex,
    const vector<Document> &documents)
{
    query = toLowerCase(query);
    query = cleanWord(query);

    cout << "\n=============================================\n";
    cout << "              SEARCH RESULT\n";
    cout << "=============================================\n";

    cout << "\nQuery: " << query << endl;

    auto it = invertedIndex.find(query);

    if (it == invertedIndex.end())
    {
        cout << "\nNo documents found for the query.\n";
        return;
    }

    cout << "\nDocuments containing '" << query << "':\n\n";

    for (int docID : it->second)
    {
        cout << "-> " << documents[docID].filename << endl;
    }
}

// Search multiple words using AND operation
void searchMultipleWords(
    string query,
    const map<string, set<int>> &invertedIndex,
    const vector<Document> &documents)
{
    stringstream ss(query);

    string word;

    set<int> result;

    bool firstWord = true;

    while (ss >> word)
    {
        word = toLowerCase(word);
        word = cleanWord(word);

        auto it = invertedIndex.find(word);

        if (it == invertedIndex.end())
        {
            result.clear();
            firstWord = false;
            break;
        }

        if (firstWord)
        {
            result = it->second;
            firstWord = false;
        }
        else
        {
            set<int> intersection;

            set_intersection(
                result.begin(),
                result.end(),
                it->second.begin(),
                it->second.end(),
                inserter(intersection, intersection.begin()));

            result = intersection;
        }
    }

    cout << "\n=============================================\n";
    cout << "          MULTI-WORD SEARCH RESULT\n";
    cout << "=============================================\n";

    cout << "\nQuery: " << query << endl;

    if (result.empty())
    {
        cout << "\nNo documents contain all query words.\n";
        return;
    }

    cout << "\nDocuments containing all query words:\n\n";

    for (int docID : result)
    {
        cout << "-> " << documents[docID].filename << endl;
    }
}

int main()
{
    cout << "=============================================\n";
    cout << "       DOCUMENT RETRIEVAL USING\n";
    cout << "             INVERTED FILE\n";
    cout << "=============================================\n";

    // Five documents
    vector<string> filenames =
    {
        "doc1.txt",
        "doc2.txt",
        "doc3.txt",
        "doc4.txt",
        "doc5.txt"
    };

    vector<Document> documents;

    // Read all documents
    for (string filename : filenames)
    {
        Document doc;

        doc.filename = filename;
        doc.content = readFile(filename);

        documents.push_back(doc);
    }

    // Build inverted index
    map<string, set<int>> invertedIndex =
        buildInvertedIndex(documents);

    // Display index
    displayInvertedIndex(
        invertedIndex,
        documents);

    // Single word query
    string query;

    cout << "\n\nEnter a search query: ";
    getline(cin >> ws, query);

    // Check if query contains multiple words
    if (query.find(' ') == string::npos)
    {
        searchQuery(
            query,
            invertedIndex,
            documents);
    }
    else
    {
        searchMultipleWords(
            query,
            invertedIndex,
            documents);
    }

    cout << "\n=============================================\n";
    cout << "       RETRIEVAL COMPLETED\n";
    cout << "=============================================\n";

    return 0;
}


Output:-

doc1.txt
Information retrieval uses indexing techniques.

doc2.txt
Information retrieval uses inverted index.

doc3.txt
Database indexing improves query search.

doc4.txt
Search engines use inverted files.

doc5.txt
Information search uses index.