#pragma once
#include "Label.h"
#include "Submission.h"

class LabelVector
{
public:
  const int volumeMax = 599;

  map<int, Label> labels;   // map has to be ordered for makeSubmission()

  LabelVector()  {};
  LabelVector(string filePath);
  LabelVector(int patientIDMin, int patientIDMax, double testValue);  // create test instance

  void       save          (string filePath);
  Submission makeSubmission(double step)           {return Submission(*this, step);};


  //double evaluateAgainst(LabelVector& labelVector);
  //void   makeSubmission1(string filePath);
};

