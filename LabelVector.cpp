#include "stdafx.h"
#include "LabelVector.h"


LabelVector::LabelVector(string filePath) {
  ifstream file(filePath);
  string   line;

  getline(file, line);  // read file header

  while (getline(file, line)) {
    Label l(line);  // read the next label

    labels.emplace(l.id, l);  
  }
}


LabelVector::LabelVector(int patientIDMin, int patientIDMax, double testValue) {
  for (int i = patientIDMin; i <= patientIDMax; ++i) 
    labels.emplace(i, Label(i, testValue, testValue));
}


void
LabelVector::save(string filePath) {
  ofstream output(filePath);

  for (auto label: labels) {
    label.second.print(output);
    output << endl;
  }
}





