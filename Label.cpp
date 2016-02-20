#include "stdafx.h"
#include "Label.h"


Label::Label(string &line) {
  istringstream inputStream(line);
  char          separator;

  inputStream >> id >> separator >> systole >> separator >> diastole;
}


void 
Label::print(ofstream& output) {
  const string separator = ",";

  output << id << separator << systole << separator << diastole;
}
