#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Calculate F1 Score
double calculateF1(double precision, double recall)
{
    if (precision + recall == 0)
        return 0.0;

    return (2 * precision * recall) /
           (precision + recall);
}

// Calculate E-Measure
double calculateE(double precision, double recall, double b)
{
    double numerator =
        (1 + b * b) * precision * recall;

    double denominator =
        (b * b * precision) + recall;

    if (denominator == 0)
        return 1.0;

    return 1 - (numerator / denominator);
}

int main()
{
    cout << "=============================================\n";
    cout << "     F-MEASURE AND E-MEASURE CALCULATION\n";
    cout << "=============================================\n\n";

    // Values obtained from Assignment No. 4
    double precision = 0.60;
    double recall = 0.75;

    cout << fixed << setprecision(4);

    cout << "Precision = " << precision << endl;
    cout << "Recall    = " << recall << endl;

    // Calculate F1
    double f1 = calculateF1(
        precision,
        recall);

    cout << "\n---------------------------------------------\n";
    cout << "F-MEASURE / F1 SCORE\n";
    cout << "---------------------------------------------\n";

    cout << "F1 = 2 * (P * R) / (P + R)\n";

    cout << "F1 = 2 * ("
         << precision
         << " * "
         << recall
         << ") / ("
         << precision
         << " + "
         << recall
         << ")\n";

    cout << "F1 = " << f1 << endl;
    cout << "F1 Percentage = "
         << f1 * 100
         << "%\n";

    // Calculate E for b = 1
    double b = 1.0;

    double e1 = calculateE(
        precision,
        recall,
        b);

    cout << "\n---------------------------------------------\n";
    cout << "E-MEASURE FOR b = 1\n";
    cout << "---------------------------------------------\n";

    cout << "E = 1 - ((1+b^2)*P*R) / "
            "(b^2*P + R)\n";

    cout << "E = "
         << e1
         << endl;

    cout << "E Percentage = "
         << e1 * 100
         << "%\n";

    // Calculate E for different b values
    cout << "\n=============================================\n";
    cout << "       E-MEASURE FOR DIFFERENT b VALUES\n";
    cout << "=============================================\n\n";

    cout << "b\tE-Measure\tPercentage\n";
    cout << "---------------------------------------------\n";

    double bValues[] =
    {
        0.5,
        1.0,
        2.0
    };

    for (double value : bValues)
    {
        double e =
            calculateE(
                precision,
                recall,
                value);

        cout << value
             << "\t"
             << e
             << "\t\t"
             << e * 100
             << "%\n";
    }

    // Final result
    cout << "\n=============================================\n";
    cout << "             FINAL RESULT\n";
    cout << "=============================================\n";

    cout << "\nPrecision = "
         << precision * 100
         << "%";

    cout << "\nRecall    = "
         << recall * 100
         << "%";

    cout << "\nF1 Score  = "
         << f1 * 100
         << "%";

    cout << "\nE Measure (b=1) = "
         << e1 * 100
         << "%";

    cout << "\n\n=============================================\n";

    return 0;
}