/* Made by Richard Sabrsula
 * A quick program made to find the information gain of each node in a decision
 * tree. Input the number of positive and negative cases of a proposed node 
 * branch and the program figures out the information gain. Be sure to change 
 * the number of good cases and bad cases (aka y=1 and y=0) for the proposed  
 * node before you run it each time. For a simplified explanation of information
 * gain see http://en.wikipedia.org/wiki/Information_gain_in_decision_trees
 */
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    double goodCases = 10, badCases = 2;   //CHANGE, based on node
    double size = goodCases + badCases; //total number of cases in node
    double entropy = (-goodCases/size)*log2(goodCases/size)-
                        (-badCases/size)*log2(badCases/size);
    //t = branch A, f = branch B
    //p = positive cases, n = negative cases
    double tp, tn, fp, fn, tsize, fsize;
    while(true){
        cout << "Enter # true (y=1) positive and negative cases:" << endl;
        cin >> tp >> tn;
        fp = goodCases - tp;              
        fn = badCases - tn;     
        tsize = tp + tn;
        fsize = fp + fn;
        double positive = ((-tp/(tp+tn)*log2(tp/(tp+tn))) - 
                            (tn/(tp+tn)*log2(tn/(tp+tn))))*((tp + tn)/size); 
        double negative = ((-fp/(fp+fn)*log2(fp/(fp+fn))) - 
                            (fn/(fp+fn)*log2(fn/(fp+fn))))*((fp + fn)/size);  
        double gain = entropy - positive - negative;
        cout << "IG: " << gain << endl;
    }
    return 0;
}
