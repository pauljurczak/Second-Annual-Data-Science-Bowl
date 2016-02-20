#pragma once
#include "Pattern.h"

class PatternVector
{
public:
  map<int, Pattern> patterns;

  PatternVector(string path, int patientIDMin, int patientIDMax);

  void save(string filePath);
};

