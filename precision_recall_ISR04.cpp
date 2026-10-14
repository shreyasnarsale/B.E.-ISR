#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;

int main()
{
    cout << "=============================================\n";
    cout << "       PRECISION AND RECALL CALCULATION\n";
    cout << "=============================================\n\n";

    // Answer set A - documents retrieved by IR system
    set<string> answerSet =
    {
        "D1",
        "D2",
        "D3",
        "D5",
        "D7"
    };

    // Relevant documents for query q1
    set<string> relevantSet =
    {
        "D1",
        "D2",
        "D4",
        "D5"
    };

    // Find intersection A ∩ R
    set<string> relevantRetrieved;

    for (const string &doc : answerSet)
    {
        if (relevantSet.find(doc) != relevantSet.end())
        {
            relevantRetrieved.insert(doc);
        }
    }

    // Calculate values
    double relevantRetrievedCount =
        relevantRetrieved.size();

    double retrievedCount =
        answerSet.size();

    double relevantCount =
        relevantSet.size();

    double precision =
        relevantRetrievedCount / retrievedCount;

    double recall =
        relevantRetrievedCount / relevantCount;

    double f1Score = 0.0;

    if (precision + recall != 0)
    {
        f1Score =
            (2 * precision * recall) /
            (precision + recall);
    }

    // Display Answer Set
    cout << "Answer Set A (Retrieved Documents):\n";

    for (const string &doc : answerSet)
    {
        cout << doc << " ";
    }

    cout << "\n\n";

    // Display Relevant Set
    cout << "Relevant Documents Rq1:\n";

    for (const string &doc : relevantSet)
    {
        cout << doc << " ";
    }

    cout << "\n\n";

    // Display intersection
    cout << "Relevant and Retrieved (A ∩ Rq1):\n";

    for (const string &doc : relevantRetrieved)
    {
        cout << doc << " ";
    }

    cout << "\n\n";

    cout << "=============================================\n";
    cout << "              CALCULATION\n";
    cout << "=============================================\n\n";

    cout << "Total Retrieved Documents = "
         << retrievedCount << endl;

    cout << "Total Relevant Documents = "
         << relevantCount << endl;

    cout << "Relevant & Retrieved Documents = "
         << relevantRetrievedCount << endl;

    cout << fixed << setprecision(2);

    cout << "\nPrecision = "
         << relevantRetrievedCount
         << " / "
         << retrievedCount
         << endl;

    cout << "Precision = "
         << precision
         << " = "
         << precision * 100
         << "%\n";

    cout << "\nRecall = "
         << relevantRetrievedCount
         << " / "
         << relevantCount
         << endl;

    cout << "Recall = "
         << recall
         << " = "
         << recall * 100
         << "%\n";

    cout << "\nF1-Score = "
         << f1Score
         << " = "
         << f1Score * 100
         << "%\n";

    cout << "\n=============================================\n";
    cout << "              FINAL RESULT\n";
    cout << "=============================================\n";

    cout << "\nPrecision : "
         << precision * 100
         << "%";

    cout << "\nRecall    : "
         << recall * 100
         << "%";

    cout << "\nF1-Score  : "
         << f1Score * 100
         << "%";

    cout << "\n\n=============================================\n";

    return 0;
}



