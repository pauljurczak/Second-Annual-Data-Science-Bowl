#pragma once
#include "LabelVector.h"
#include "PatternVector.h"

class Model
{
public:
  static void getPatientData();

  array<int, 2>    fullGrownAge;
  array<double, 2> aSystole, bSystole, aDiastole, bDiastole, medianSystole, medianDiastole;

  Model()  {};
  Model(PatternVector& patternVector, LabelVector& labelVector, const array<int, 2>& fullGrownAge_);

  LabelVector predict(PatternVector& patternVector);
  void        print  (ostream& stream);
};

