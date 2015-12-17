#include "Definitions.h"

class Policy
{
 private:
  double **_policy;

 public:
  int _size;

  Policy(int size);
  ~Policy();
  Policy(const Policy& other);
  double* operator[](int i) const;
  bool operator!=(const Policy& other) const;
  bool operator==(const Policy& other) const;
};
