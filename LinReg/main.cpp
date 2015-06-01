/* Made by Richard Sabrsula
 * My attempt to apply logistic regression, give it a minute to find convergence
 * (it finds it at around 10 seconds for me). Change 'm' to accommodate how many
 * training sets you give it and 'alpha' to what you think the learning rate 
 * should be. Read-in file is provided and is your data set, just scrubbed to 
 * make it easier to read in. Made in NetBeans using the MinGW tool collection. 
 * Should work with any IDE or C++ compiler. For a simplified explanation of 
 * logistic regression see http://en.wikipedia.org/wiki/Logistic_regression
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

//Global variables
const int m = 150; //number of points read in
const double alpha = .0001; //learning rate

//user define structures
struct set { //set used for training data
    double x1, x2; //x1 is petal length, x2 is width
    double sx1, sx2; //standardized values
    string type;
};
struct weight{ //container for the weights for the formula
    double w0, w1, w2;
};
struct stdVal{ //used to store data used in standardizing the set, & to 
               //standardize user-given points with the same values
    double minX1, maxX1, minX2, maxX2;
};

//Standardizes the given set
stdVal standardizeSet(set b[m]) {
    stdVal std = {100, 0, 100, 0};
    for(int i = 0; i < m; i++){
        if(b[i].x1 > std.maxX1){ //replaces maxX
            std.maxX1 = b[i].x1;
        }
        if(b[i].x1 < std.minX1){ //replaces minX
            std.minX1 = b[i].x1;
        }
        if(b[i].x2 > std.maxX2){ //replaces maxY
            std.maxX2 = b[i].x2;
        }
        if(b[i].x2 < std.minX2){ //replaces minY
            std.minX2 = b[i].x2;
        }
    }
    
    //Now we have the min and max values, we can standardize
    for(int i = 0; i < m; i++){
        b[i].sx1 = ((b[i].x1 - std.minX1)/(std.maxX1 - std.minX1));
        b[i].sx2 = ((b[i].x2 - std.minX2)/(std.maxX2 - std.minX2));
    }
    
    return std;
}

//standardization of user-given point under same parameters as set
//uses same mix/max's as the set data for standardization
set standardizePoint(set a, stdVal std){
    a.sx1 = ((a.x1 - std.minX1)/(std.maxX1 - std.minX1));
    a.sx2 = ((a.x2 - std.minX2)/(std.maxX2 - std.minX2));
    return a;
}

//does the h(x) formula 1/(1+e^(-weight*x))
double h(set a, weight b){
    double e = exp(1); //calculate e
    double z = b.w0 + a.sx1*b.w1 + a.sx2*b.w2; //weights*x
    double h = 1 + pow(e, -z); //(1+e^(-weights*x)
    return (1/h); //1/(1+e^(-weight*x))
}

//applies the linear regression algorithm to find the weights 
//of the line(s) dividing the different classes
void linReg(set a[m], weight b[3], stdVal std){
    string classification = "";
    double y = 0, correct = 0;
    for(int j = 0; j < 1000000; j++){
        for(int z = 0; z < 3; z++){//run through each class
            if(z==0){
                classification = "Iris-setosa";
            }else if(z==1){
                classification = "Iris-versicolor";
            }else{
                classification = "Iris-virginica";
            }
            //cout << classification << endl;
            //run through each sample data
            for(int i = 0; i < m; i++){
                if(a[i].type.compare(classification) == 0)
                   y = 1;
                else
                   y = 0;

                //for each sample data, take a step in the right direction
                b[z].w0 = b[z].w0 + alpha*(y - h(a[i], b[z]))*1; //x0 is 1
                b[z].w1 = b[z].w1 + alpha*(y - h(a[i], b[z]))*a[i].sx1;
                b[z].w2 = b[z].w2 + alpha*(y - h(a[i], b[z]))*a[i].sx2;
            }
        }

        //test for convergence
        for(int i = 0; i < m; i++){
                if(a[i].type.compare("Iris-setosa")==0){
                    //if the predicted result matches the actual result, 
                    //count it as a success
                    if(h(a[i], b[0]) > h(a[i], b[1]) && 
                        h(a[i], b[0]) > h(a[i], b[2])){
                        correct++;
                    }
                } else if(a[i].type.compare("Iris-versicolor")==0){
                    if(h(a[i], b[1]) > h(a[i], b[0]) && 
                        h(a[i], b[1]) > h(a[i], b[2])){
                        correct++;
                    }
                } else if(a[i].type.compare("Iris-virginica")==0){
                    if(h(a[i], b[2]) > h(a[i], b[1]) && 
                        h(a[i], b[2]) > h(a[i], b[0])){
                        correct++;
                    }
                } else {
                    cout << "Error found at " << i<< endl; 
                }
        }
        
        double threshold = m * .9; //accuracy of 90%
        if(correct >= threshold){
            cout << "Accuracy of 90% or greater found after " << j << 
                    " iterations." <<endl << endl;
            j = 1000000;
        }
        correct = 0;
    }
}

//finds and sets class for given point based off of weights found
//from logistic regression
set findClass(weight b[3], set given){
    double y[3] = {0,0,0};
    y[0] = h(given, b[0]);
    y[1] = h(given, b[1]);
    y[2] = h(given, b[2]);
    //cout << y[0] << " " << y[1] << " " << y[2] << endl;
    if(y[0] > y[1] && y[0] > y[2])
        given.type = "Iris-setosa";
    else if(y[1] > y[0] && y[1] > y[2])
        given.type = "Iris-versicolor";
    else if(y[2] > y[0] && y[2] > y[1])
        given.type = "Iris-virginica";
    else
        given.type = "unknown";
    
    return given;
}

//for debugging purposes, outputs the current values of the weights
void printWeight(weight a){
    cout << a.w0 << " " << a.w1 << " " << a.w2 << endl << endl;
}

//prints set for debugging purposes
void printSet(set b[m]) {
    for(int i = 0; i < m; i++){
        cout << b[i].x1 << " " << b[i].x2 << " " << b[i].type << endl;
        cout << b[i].sx1 << " " << b[i].sx2 << endl << endl;
    }
}

int main() {
    set array[m]; //array containing training set (read in from file))
    weight b[3] = {{0,0,0},{0,0,0},{0,0,0}}; //weight values
    stdVal std; //holds the min and max values used for standardization
    bool cont = true;
    set given; //point given by user
    
    //read in array
    ifstream fin("iris2.arff");
    for(int i = 0; i < m; i++){
        fin >> array[i].x1 >> array[i].x2 >> array[i].type;
        fin.ignore();
    }

    //printSet(array); //for debugging purposes
    
    std = standardizeSet(array);
    //for debugging purposes, to check if array was correctly standardized
    //cout << std.maxX << " " << std.minX << " " << std.maxY << " " << 
    //            std.minY << endl;
    //printSet(array); 
    

    //apply linear regression to find weights of lines
    linReg(array, b, std);
    
    do{
        //asks the user for the point to test
        cout << "Please enter the point you wish to find the classification for."
                << endl << "The proper format is XX YY, both variables being doubles and"
                << endl << "XX being the petal length, YY being the petal width." << endl;
        
        cin >> given.x1 >> given.x2;
        
        //standardize the user given point
        given = standardizePoint(given, std);
       
        //use linear regression values to find classification
        given = findClass(b, given);
        
        cout << endl << "Based on the multiple-class classifier point " << 
                given.x1 << ", " << given.x2 << endl << "best fits in class " <<
                given.type << "." << endl << endl;
        
    }while(cont == true);
    
    return 0;
}
