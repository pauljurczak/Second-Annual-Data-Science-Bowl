#include "stdafx.h"
#include "PatternVector.h"


PatternVector::PatternVector(string path, int patientIDMin, int patientIDMax)
{
  using namespace experimental::filesystem;

  for (int i = patientIDMin; i <= patientIDMax; ++i) 
		for (auto& f: recursive_directory_iterator(path + to_string(i) + "\\study\\")) 
      if (f.path().extension() == ".dcm") {
        patterns.emplace(i, Pattern(f.path().string()));
        break;
  	  }
}


void
PatternVector::save(string filePath) {
  ofstream output(filePath);

  for (auto pattern: patterns) {
    pattern.second.print(output);
    output << endl;
  }
}

