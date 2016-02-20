#pragma once

class Pattern
{
public:
  bool isMale;
  int  id;
  double age;

  Pattern() {};
  Pattern(string filePath);

  void print(ofstream& output);
};

