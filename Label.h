#pragma once
#include <string>

class Label {
public:
  int    id;
  double systole, diastole;
   
  Label()  {};
  Label(int id, double systole, double diastole) : id(id), systole(systole), diastole(diastole)  {};
  Label(string &line);

  void print(ofstream& output);
};

