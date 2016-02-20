#include "stdafx.h"
#include "LabelVector.h"
#include "Submission.h"


Submission::Submission(LabelVector& labelVector, double scale) {
  constexpr double e = 2.7182818;

  auto erf = [](double x) {return x <= 2.2 ? 0.1*x*(4.4-x) : 0.5;};

  for (auto label: labelVector.labels) {
    Label& l = label.second;

    systoleCDFs .emplace(l.id, array<double, volumeMax+1>()); 
    diastoleCDFs.emplace(l.id, array<double, volumeMax+1>()); 

    for (int i = 0; i <= volumeMax; ++i) {
      //systoleCDFs [l.id][i] = i < l.systole  ? 0.5-erf((l.systole -i)*scale) : 0.5+erf((i-l.systole )*scale);
      //diastoleCDFs[l.id][i] = i < l.diastole ? 0.5-erf((l.diastole-i)*scale) : 0.5+erf((i-l.diastole)*scale);
      systoleCDFs [l.id][i] = 1/(1 + pow(e, scale*(i-l.systole))); 
      diastoleCDFs[l.id][i] = 1/(1 + pow(e, scale*(i-l.diastole))); 
    }
  }
}



Submission
Submission::write(string filePath) {
  ofstream submission(filePath);

  // Write submission header
  submission << "Id";

  for (int i = 0; i <= volumeMax; ++i)
    submission << ",P" << i;

  // Write results
  for (auto i: systoleCDFs) {
    int id = i.first;

    submission << endl << id << "_Systole";

    for (int i = 0; i <= volumeMax; ++i)
      submission << "," << systoleCDFs[id][i];

    submission << endl << id << "_Diastole";

    for (int i = 0; i <= volumeMax; ++i)
      submission << "," << diastoleCDFs[id][i];
  }

  return *this;
}


double 
Submission::evaluateAgainst(LabelVector& labelVector) {
  double crps = 0;

  for (auto e: labelVector.labels) {
    auto& label = e.second;

    for (int i = 0; i <= volumeMax; ++i)
      crps += square(systoleCDFs[label.id][i] - (i >= label.systole ? 1 : 0));

    for (int i = 0; i <= volumeMax; ++i)
      crps += square(diastoleCDFs[label.id][i] - (i >= label.diastole ? 1 : 0));
  }

  return crps/(2*labelVector.labels.size()*volumeMax);
}

