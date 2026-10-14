#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

// Stop word list
unordered_set<string> stopWords = {
    "a", "an", "the", "and", "or", "but",
    "is", "are", "was", "were", "am",
    "of", "in", "on", "at", "to",
    "for", "from", "by", "with",
    "as", "this", "that", "these",
    "those", "it", "its", "be",
    "been", "being", "has", "have",
    "had", "do", "does", "did",
    "will", "would", "can", "could",
    "should", "may", "might",
    "you", "your", "we", "our",
    "they", "their", "he", "she"
};

// Convert word to lowercase
string toLowerCase(string word)
{
    for (char &c : word)
        c = tolower(static_cast<unsigned char>(c));

    return word;
}

// Remove punctuation
string removePunctuation(string word)
{
    string result;

    for (char c : word)
    {
        if (isalnum(static_cast<unsigned char>(c)))
            result += c;
    }

    return result;
}

// Suffix stripping
string suffixStrip(string word)
{
    int n = word.length();

    // Rule 1: Remove "ing"
    if (n > 5 && word.substr(n - 3) == "ing")
    {
        word.erase(n - 3);
    }

    // Rule 2: Remove "ed"
    else if (n > 4 && word.substr(n - 2) == "ed")
    {
        word.erase(n - 2);
    }

    // Rule 3: Remove "ly"
    else if (n > 4 && word.substr(n - 2) == "ly")
    {
        word.erase(n - 2);
    }

    // Rule 4: Remove "es"
    else if (n > 4 && word.substr(n - 2) == "es")
    {
        word.erase(n - 2);
    }

    // Rule 5: Remove "s"
    else if (n > 3 && word.back() == 's')
    {
        word.pop_back();
    }

    return word;
}

int main()
{
    string filename;

    cout << "Enter input text file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    string line;
    string word;

    map<string, int> frequency;

    while (getline(file, line))
    {
        stringstream ss(line);

        while (ss >> word)
        {
            // Convert to lowercase
            word = toLowerCase(word);

            // Remove punctuation
            word = removePunctuation(word);

            if (word.empty())
                continue;

            // Remove stop words
            if (stopWords.find(word) != stopWords.end())
                continue;

            // Apply suffix stripping
            word = suffixStrip(word);

            if (word.empty())
                continue;

            // Count frequency
            frequency[word]++;
        }
    }

    file.close();

    // Convert map to vector for sorting
    vector<pair<string, int>> words(
        frequency.begin(),
        frequency.end()
    );

    // Sort by frequency in descending order
    sort(words.begin(), words.end(),
        [](const pair<string, int> &a,
           const pair<string, int> &b)
        {
            if (a.second != b.second)
                return a.second > b.second;

            return a.first < b.first;
        });

    cout << "\n=====================================\n";
    cout << "       DOCUMENT REPRESENTATIVE\n";
    cout << "=====================================\n";

    cout << "\nSignificant Words and Frequency:\n\n";

    for (const auto &item : words)
    {
        cout << item.first
             << " : "
             << item.second
             << endl;
    }

    cout << "\n=====================================\n";
    cout << "       DOCUMENT REPRESENTATIVE\n";
    cout << "=====================================\n";

    for (const auto &item : words)
    {
        cout << item.first << " ";
    }

    cout << "\n";

    return 0;
}



Output:- 

File: Information retrieval is the process of obtaining
relevant information from a large collection of
documents. Information retrieval systems are used
for searching and retrieving useful documents.


Enter input text file name: input.txt

=====================================
       DOCUMENT REPRESENTATIVE
=====================================

Significant Words and Frequency:

information : 2
retriev     : 2
document    : 2
large       : 1
collection  : 1
process     : 1
obtain      : 1
relevant    : 1
system      : 1
use         : 1
search      : 1
useful      : 1

=====================================
       DOCUMENT REPRESENTATIVE
=====================================

information retriev document large collection process
obtain relevant system use search useful



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Structure for a document
struct Document
{
    string name;
    map<string, double> terms;
};

// Structure for a cluster
struct Cluster
{
    vector<int> documents;
    map<string, double> centroid;
};

// Convert string to lowercase
string toLowerCase(string word)
{
    for (char &c : word)
    {
        c = tolower(static_cast<unsigned char>(c));
    }

    return word;
}

// Remove punctuation
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

// Read document and calculate term frequency
map<string, double> readDocument(string filename)
{
    map<string, double> frequency;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file: " << filename << endl;
        return frequency;
    }

    string word;

    while (file >> word)
    {
        word = toLowerCase(word);
        word = cleanWord(word);

        if (!word.empty())
        {
            frequency[word]++;
        }
    }

    file.close();

    return frequency;
}

// Calculate Dice coefficient
double diceCoefficient(
    const map<string, double> &doc,
    const map<string, double> &cluster)
{
    double intersection = 0.0;
    double docTotal = 0.0;
    double clusterTotal = 0.0;

    // Total frequency of document
    for (const auto &p : doc)
    {
        docTotal += p.second;
    }

    // Total frequency of cluster centroid
    for (const auto &p : cluster)
    {
        clusterTotal += p.second;
    }

    // Minimum frequency of common words
    for (const auto &p : doc)
    {
        auto it = cluster.find(p.first);

        if (it != cluster.end())
        {
            intersection += min(p.second, it->second);
        }
    }

    if (docTotal + clusterTotal == 0)
    {
        return 0.0;
    }

    // Weighted Dice coefficient
    return (2.0 * intersection) /
           (docTotal + clusterTotal);
}

// Calculate centroid of a cluster
map<string, double> calculateCentroid(
    const vector<int> &clusterDocuments,
    const vector<Document> &documents)
{
    map<string, double> centroid;

    if (clusterDocuments.empty())
    {
        return centroid;
    }

    for (int index : clusterDocuments)
    {
        for (const auto &p : documents[index].terms)
        {
            centroid[p.first] += p.second;
        }
    }

    // Calculate average frequency
    for (auto &p : centroid)
    {
        p.second /= clusterDocuments.size();
    }

    return centroid;
}

// Display document terms
void displayDocument(const Document &doc)
{
    cout << doc.name << ": ";

    for (const auto &p : doc.terms)
    {
        cout << p.first << "(" << p.second << ") ";
    }

    cout << endl;
}

int main()
{
    cout << "=============================================\n";
    cout << "       SINGLE PASS CLUSTERING\n";
    cout << "=============================================\n\n";

    // Five input files
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

        doc.name = filename;
        doc.terms = readDocument(filename);

        documents.push_back(doc);
    }

    cout << "DOCUMENT REPRESENTATIVES\n";
    cout << "---------------------------------------------\n";

    for (const auto &doc : documents)
    {
        displayDocument(doc);
    }

    // Threshold
    double threshold = 0.35;

    cout << "\nThreshold = "
         << fixed << setprecision(2)
         << threshold << endl;

    cout << "\n=============================================\n";
    cout << "       SINGLE PASS PROCESSING\n";
    cout << "=============================================\n";

    vector<Cluster> clusters;

    // First document creates first cluster
    Cluster firstCluster;

    firstCluster.documents.push_back(0);

    firstCluster.centroid =
        calculateCentroid(
            firstCluster.documents,
            documents);

    clusters.push_back(firstCluster);

    cout << "\n"
         << documents[0].name
         << " -> Cluster 1 (First document)\n";

    // Process remaining documents
    for (int i = 1; i < documents.size(); i++)
    {
        double maxSimilarity = -1.0;
        int bestCluster = -1;

        cout << "\nProcessing "
             << documents[i].name << ":\n";

        // Compare document with every cluster
        for (int j = 0; j < clusters.size(); j++)
        {
            double similarity =
                diceCoefficient(
                    documents[i].terms,
                    clusters[j].centroid);

            cout << "Similarity with Cluster "
                 << j + 1
                 << " = "
                 << fixed
                 << setprecision(3)
                 << similarity
                 << endl;

            if (similarity > maxSimilarity)
            {
                maxSimilarity = similarity;
                bestCluster = j;
            }
        }

        // Check threshold
        if (maxSimilarity > threshold)
        {
            clusters[bestCluster].documents.push_back(i);

            clusters[bestCluster].centroid =
                calculateCentroid(
                    clusters[bestCluster].documents,
                    documents);

            cout << "Result: "
                 << documents[i].name
                 << " added to Cluster "
                 << bestCluster + 1
                 << endl;
        }
        else
        {
            Cluster newCluster;

            newCluster.documents.push_back(i);

            newCluster.centroid =
                calculateCentroid(
                    newCluster.documents,
                    documents);

            clusters.push_back(newCluster);

            cout << "Result: "
                 << documents[i].name
                 << " creates a new Cluster "
                 << clusters.size()
                 << endl;
        }
    }

    // Final output
    cout << "\n\n=============================================\n";
    cout << "             FINAL CLUSTERS\n";
    cout << "=============================================\n";

    for (int i = 0; i < clusters.size(); i++)
    {
        cout << "\nCluster " << i + 1 << ":\n";

        for (int docIndex : clusters[i].documents)
        {
            cout << "  -> "
                 << documents[docIndex].name
                 << endl;
        }
    }

    // Graphical representation
    cout << "\n\n=============================================\n";
    cout << "        GRAPHICAL REPRESENTATION\n";
    cout << "=============================================\n\n";

    for (int i = 0; i < clusters.size(); i++)
    {
        cout << "[Cluster " << i + 1 << "]\n";

        for (int docIndex : clusters[i].documents)
        {
            cout << "       |\n";
            cout << "       +---- "
                 << documents[docIndex].name
                 << endl;
        }

        cout << endl;
    }

    cout << "=============================================\n";
    cout << "Clustering completed successfully.\n";
    cout << "=============================================\n";

    return 0;
}


Output:-


1. doc1.txt
Artificial intelligence machine learning deep neural

2. doc2.txt
Machine learning neural networks artificial intelligence

3. doc3.txt
Database SQL DBMS query transaction

4. doc4.txt
SQL database query DBMS transaction

5. doc5.txt
Neural network deep learning artificial intelligence


