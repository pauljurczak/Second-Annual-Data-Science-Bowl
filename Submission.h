#pragma once

class LabelVector;

class Submission
{
public:
  static const int volumeMax = 599;

  map<int, array<double, volumeMax+1>> systoleCDFs;
  map<int, array<double, volumeMax+1>> diastoleCDFs;

  Submission(LabelVector& labelVector, double scale);

  Submission write          (string filePath);
  double     evaluateAgainst(LabelVector& labelVector);
};

