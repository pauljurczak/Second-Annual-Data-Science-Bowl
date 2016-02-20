#include "stdafx.h"
#include "imebra/imebra.h"
#include "Pattern.h"

using namespace imebra;

Pattern::Pattern(string filePath)
{
  DataSet dataSet = CodecFactory::load(filePath, 1000000);
  char    ageUnit = dataSet.getString(0x0010, 0, 0x1010, 0, 0, "000Y")[3];

  isMale = dataSet.getString    (0x0010, 0, 0x0040, 0, 0, "M") == "M";
  id     = dataSet.getSignedLong(0x0010, 0, 0x0020, 0, 0, 0);
  age    = stoi(dataSet.getString(0x0010, 0, 0x1010, 0, 0, "0")) / (ageUnit == 'W' ? 52.14 : ageUnit == 'M' ? 12.0 : 1);
}


void 
Pattern::print(ofstream& output) {
  const string separator = ",";

  output << id << separator << isMale << separator << age;
}


