#include "stdafx.h"
#include "Model.h"
#include "LabelVector.h"
#include "PatternVector.h"
#include "Submission.h"

#include "imebra/imebra.h"

int main()
{
  try {
    double scaleMin, errorMin = DBL_MAX;
    Model  modelMin;

    //for (double scale = 0.027; scale < 0.032; scale += 0.001) 
    for (double scale = -0.06; scale < -0.04; scale += 0.001) 
      for (int i = 14; i < 20; ++i)
        for (int j = 14; j < 20; ++j) {
        //{ double scale = 0.028; 
        //  int    i    = 16;
        //  int    j    = 16;

          Model    model (PatternVector("E:\\Heart\\train\\", 1, 500), LabelVector("E:\\Heart\\train.csv"), array<int, 2>{i, j});
          double   error = model
            .predict        (PatternVector("E:\\Heart\\train\\", 1, 500))
            .makeSubmission (scale)
            .evaluateAgainst(LabelVector("E:\\Heart\\train.csv"));

          if (error < errorMin) {
            errorMin = error;
            modelMin = model;
            scaleMin = scale;
          }

          cout << "*";
        }

    string   stamp = "-erf-square-sigma-" + to_string(scaleMin) + "-" + to_string(modelMin.fullGrownAge[0]) + "-" + 
                     to_string(modelMin.fullGrownAge[1]) + "-" + to_string(errorMin);
    ofstream report("C:\\Heart\\documents\\report" + stamp + ".txt");

    cout << "\n\n\a";
    modelMin.print(report);
    modelMin.print(cout);
    report << "error:\t" << setprecision(6) << errorMin << endl << "scale:\t" << scaleMin << endl;
    cout << "error:\t" << setprecision(6) << errorMin << endl << "scale:\t" << scaleMin << endl;

    modelMin.predict       (PatternVector("E:\\Heart\\validate\\", 501, 700))
            .makeSubmission(scaleMin)
            .write         ("C:\\Heart\\documents\\submission" + stamp + ".txt");
  }
  catch (exception& e) {
    cout << e.what();
  }

  return 0;
}

