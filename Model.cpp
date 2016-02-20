#include "stdafx.h"
#include "PatternVector.h"
#include "LabelVector.h"
#include "Model.h"


void
Model::getPatientData() {
  constexpr int patientIDMin = 1;
  constexpr int patientIDMax = 500;

  PatternVector pv    ("E:\\Heart\\train\\", patientIDMin, patientIDMax);
  LabelVector   lv    ("E:\\Heart\\train.csv");
  ofstream      report("patientData.txt");

  for (int i = patientIDMin; i <= patientIDMax; ++i) 
    report << i << "," << pv.patterns[i].age << "," << pv.patterns[i].isMale << "," << lv.labels[i].systole << "," << lv.labels[i].diastole << endl;
}


Model::Model(PatternVector& patternVector, LabelVector& labelVector, const array<int, 2>& fullGrownAge_) {
  array<vector<pair<int, double>>, 2> childSystoles, childDiastoles;  // (age, volume) datum
  array<vector<double>, 2>            adultSystoles, adultDiastoles;

  fullGrownAge = fullGrownAge_;

  for (auto e: patternVector.patterns) {
    auto& pattern = e.second;
    auto& label   = labelVector.labels[pattern.id];

    if (pattern.age < fullGrownAge[pattern.isMale]) {
      childSystoles [pattern.isMale].push_back(make_pair(pattern.age, label.systole));
      childDiastoles[pattern.isMale].push_back(make_pair(pattern.age, label.diastole));
    }
    else {
      adultSystoles [pattern.isMale].push_back(label.systole);
      adultDiastoles[pattern.isMale].push_back(label.diastole);
    }
  }
  
  // Find medians
  for (int i: {0, 1}) {
    sort(adultSystoles [i].begin(), adultSystoles [i].end());
    sort(adultDiastoles[i].begin(), adultDiastoles[i].end());

    medianSystole [i] = adultSystoles [i][adultSystoles [i].size()/2];   
    medianDiastole[i] = adultDiastoles[i][adultDiastoles[i].size()/2];
  }

  // Find the best linear approximations of child data range
  constexpr int bMax = 99;

  auto approximateLAV = [](vector<pair<int, double>>& v, double a, double b) {
    double error = 0;

    for (auto& p: v)
      error += abs(a*p.first+b - p.second);

    return error;
  };

  auto approximate = [](vector<pair<int, double>>& v, double a, double b) {
    double error = 0;

    for (auto& p: v)
      error += square(a*p.first+b - p.second);

    return error;
  };

  array<double, 2> errorSystole{DBL_MAX, DBL_MAX}, errorDiastole{DBL_MAX, DBL_MAX};

  for (int i: {0, 1}) {
    for (double b = 0; b <= medianSystole[i]; ++b) 
      if (approximate(childSystoles[i], (medianSystole[i]-b)/fullGrownAge[i], b) < errorSystole[i]) {
        aSystole    [i] = (medianSystole[i]-b)/fullGrownAge[i];
        bSystole    [i] = b;
        errorSystole[i] = approximate(childSystoles[i], (medianSystole[i]-b)/fullGrownAge[i], b);
      }

    for (double b = 0; b <= medianDiastole[i]; ++b) 
      if (approximate(childDiastoles[i], (medianDiastole[i]-b)/fullGrownAge[i], b) < errorDiastole[i]) {
        aDiastole    [i] = (medianDiastole[i]-b)/fullGrownAge[i];
        bDiastole    [i] = b;
        errorDiastole[i] = approximate(childDiastoles[i], (medianDiastole[i]-b)/fullGrownAge[i], b);
      }
  }
}


LabelVector
Model::predict(PatternVector& patternVector) {
  LabelVector labelVector;

  for (auto& p: patternVector.patterns) {
    bool  isMale = p.second.isMale;
    int   age    = p.second.age;
    Label label;

    label.id = p.second.id;

    if (age <= fullGrownAge[isMale]) {
      label.systole  = aSystole [isMale]*age + bSystole [isMale];
      label.diastole = aDiastole[isMale]*age + bDiastole[isMale];
    }
    else {
      label.systole  = medianSystole [isMale];
      label.diastole = medianDiastole[isMale];
    }

    labelVector.labels.emplace(label.id, label);
  }

  return labelVector;
}


void        
Model::print(ostream& stream) {
  for (int i: {0, 1}) {
    stream << (i ? "male" : "female") << " child systole: \t\t" << setprecision(3) << aSystole[i] << "x + " << bSystole[i] << endl;
    stream << (i ? "male" : "female") << " child diastole: \t\t" << setprecision(3) << aDiastole[i] << "x + " << bDiastole[i] << endl;
    stream << (i ? "male" : "female") << " adult median systole: \t" << medianSystole[i] << endl;
    stream << (i ? "male" : "female") << " adult median diastole: \t" << medianDiastole[i] << endl;
    stream << (i ? "male" : "female") << " adult age: \t\t" << fullGrownAge[i] << endl;
  }
}


