/* Made by Richard Sabrsula
 * A quick program made to find the probability found by the Naive Bayes with 
 * Laplace Smoothing algorithm. Be sure to change the number k (number of total
 * Y's you're finding the probability for, ie number of Y=1 or number of Y=0) 
 * and m (total possible results for Y, usually 2). For a simplified explanation
 * of Naive Bayes with Laplace Smoothing go to google or see
 * http://en.wikipedia.org/wiki/Additive_smoothing
 */
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    double n, k, m;
    k = 20; //number of total Y's
    m = 2; //2 unless dealing with non-binary results
    while(true){
        cout << "Enter the number of examples where x=1 in Y that exist" << endl;
        cin >> n;
        double prob1 = (n + 1)/(k + m);
        double prob2 = 1 - prob1; //true since P(x=1|y=1)+P(x=0|y=1)=1
        cout << "Prob x=1: " << prob1 << " prob x=0 " << prob2 << endl;
    }
    return 0;
}

