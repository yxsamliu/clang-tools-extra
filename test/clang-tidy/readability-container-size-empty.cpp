// RUN: %check_clang_tidy %s readability-container-size-empty %t

namespace std {
template <typename T> struct vector {
  vector();
  bool operator==(const vector<T>& other) const;
  bool operator!=(const vector<T>& other) const;
  unsigned long size() const;
  bool empty() const;
};

template <typename T> struct basic_string {
  basic_string();
  bool operator==(const basic_string<T>& other) const;
  bool operator!=(const basic_string<T>& other) const;
  bool operator==(const char *) const;
  bool operator!=(const char *) const;
  basic_string<T> operator+(const basic_string<T>& other) const;
  unsigned long size() const;
  bool empty() const;
};

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;

inline namespace __v2 {
template <typename T> struct set {
  set();
  bool operator==(const set<T>& other) const;
  bool operator!=(const set<T>& other) const;
  unsigned long size() const;
  bool empty() const;
};
}

}

template <typename T>
class TemplatedContainer {
public:
  bool operator==(const TemplatedContainer<T>& other) const;
  bool operator!=(const TemplatedContainer<T>& other) const;
  int size() const;
  bool empty() const;
};

template <typename T>
class PrivateEmpty {
public:
  bool operator==(const PrivateEmpty<T>& other) const;
  bool operator!=(const PrivateEmpty<T>& other) const;
  int size() const;
private:
  bool empty() const;
};

struct BoolSize {
  bool size() const;
  bool empty() const;
};

struct EnumSize {
  enum E { one };
  enum E size() const;
  bool empty() const;
};

class Container {
public:
  bool operator==(const Container& other) const;
  int size() const;
  bool empty() const;
};

class Derived : public Container {
};

class Container2 {
public:
  int size() const;
  bool empty() const { return size() == 0; }
};

class Container3 {
public:
  int size() const;
  bool empty() const;
};

bool Container3::empty() const { return this->size() == 0; }

class Container4 {
public:
  bool operator==(const Container4& rhs) const;
  int size() const;
  bool empty() const { return *this == Container4(); }
};

std::string s_func() {
  return std::string();
}

int main() {
  std::set<int> intSet;
  std::string str;
  std::string str2;
  std::wstring wstr;
  str.size() + 0;
  str.size() - 0;
  0 + str.size();
  0 - str.size();
  if (intSet.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used to check for emptiness instead of 'size' [readability-container-size-empty]
  // CHECK-FIXES: {{^  }}if (intSet.empty()){{$}}
  // CHECK-MESSAGES: :32:8: note: method 'set<int>'::empty() defined here
  if (intSet == std::set<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used to check for emptiness
  // CHECK-FIXES: {{^  }}if (intSet.empty()){{$}}
  // CHECK-MESSAGES: :32:8: note: method 'set<int>'::empty() defined here
  if (s_func() == "")
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (s_func().empty()){{$}}
  if (str.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (str.empty()){{$}}
  if ((str + str2).size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if ((str + str2).empty()){{$}}
  if (str == "")
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (str.empty()){{$}}
  if (str + str2 == "")
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if ((str + str2).empty()){{$}}
  if (wstr.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (wstr.empty()){{$}}
  if (wstr == "")
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (wstr.empty()){{$}}
  std::vector<int> vect;
  if (vect.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (vect == std::vector<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (vect.size() != 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (vect != std::vector<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (0 == vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (0 != vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (std::vector<int>() == vect)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (std::vector<int>() != vect)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (vect.size() > 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (0 < vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:11: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (vect.size() < 1)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (1 > vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:11: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (vect.size() >= 1)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (1 <= vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}
  if (vect.size() > 1) // no warning
    ;
  if (1 < vect.size()) // no warning
    ;
  if (vect.size() <= 1) // no warning
    ;
  if (1 >= vect.size()) // no warning
    ;
  if (!vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect.empty()){{$}}
  if (vect.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect.empty()){{$}}

  if (vect.empty())
    ;

  const std::vector<int> vect2;
  if (vect2.size() != 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!vect2.empty()){{$}}

  std::vector<int> *vect3 = new std::vector<int>();
  if (vect3->size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect3->empty()){{$}}
  if ((*vect3).size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if ((*vect3).empty()){{$}}
  if ((*vect3) == std::vector<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect3->empty()){{$}}
  if (*vect3 == std::vector<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect3->empty()){{$}}

  delete vect3;

  const std::vector<int> &vect4 = vect2;
  if (vect4.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect4.empty()){{$}}
  if (vect4 == std::vector<int>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (vect4.empty()){{$}}

  TemplatedContainer<void> templated_container;
  if (templated_container.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (templated_container == TemplatedContainer<void>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (templated_container.size() != 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (templated_container != TemplatedContainer<void>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (0 == templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (TemplatedContainer<void>() == templated_container)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (0 != templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (TemplatedContainer<void>() != templated_container)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (templated_container.size() > 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (0 < templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:11: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (templated_container.size() < 1)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (1 > templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:11: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (templated_container.size() >= 1)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (1 <= templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:12: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (templated_container.size() > 1) // no warning
    ;
  if (1 < templated_container.size()) // no warning
    ;
  if (templated_container.size() <= 1) // no warning
    ;
  if (1 >= templated_container.size()) // no warning
    ;
  if (!templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (templated_container.empty()){{$}}
  if (templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}

  if (templated_container.empty())
    ;

  // No warnings expected.
  PrivateEmpty<void> private_empty;
  if (private_empty.size() == 0)
    ;
  if (private_empty == PrivateEmpty<void>())
    ;
  if (private_empty.size() != 0)
    ;
  if (private_empty != PrivateEmpty<void>())
    ;
  if (0 == private_empty.size())
    ;
  if (PrivateEmpty<void>() == private_empty)
    ;
  if (0 != private_empty.size())
    ;
  if (PrivateEmpty<void>() != private_empty)
    ;
  if (private_empty.size() > 0)
    ;
  if (0 < private_empty.size())
    ;
  if (private_empty.size() < 1)
    ;
  if (1 > private_empty.size())
    ;
  if (private_empty.size() >= 1)
    ;
  if (1 <= private_empty.size())
    ;
  if (private_empty.size() > 1)
    ;
  if (1 < private_empty.size())
    ;
  if (private_empty.size() <= 1)
    ;
  if (1 >= private_empty.size())
    ;
  if (!private_empty.size())
    ;
  if (private_empty.size())
    ;

  // Types with weird size() return type.
  BoolSize bs;
  if (bs.size() == 0)
    ;
  EnumSize es;
  if (es.size() == 0)
    ;

  Derived derived;
  if (derived.size() == 0)
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (derived.empty()){{$}}
  if (derived == Derived())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (derived.empty()){{$}}
}

#define CHECKSIZE(x) if (x.size())
// CHECK-FIXES: #define CHECKSIZE(x) if (x.size())

template <typename T> void f() {
  std::vector<T> v;
  if (v.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used to check for emptiness instead of 'size' [readability-container-size-empty]
  // CHECK-FIXES: {{^  }}if (!v.empty()){{$}}
  if (v == std::vector<T>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used to check for emptiness instead of comparing to an empty object [readability-container-size-empty]
  // CHECK-FIXES: {{^  }}if (v.empty()){{$}}
  // CHECK-FIXES-NEXT: ;
  CHECKSIZE(v);
  // CHECK-MESSAGES: :[[@LINE-1]]:13: warning: the 'empty' method should be used
  // CHECK-MESSAGES: CHECKSIZE(v);

  TemplatedContainer<T> templated_container;
  if (templated_container.size())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  if (templated_container != TemplatedContainer<T>())
    ;
  // CHECK-MESSAGES: :[[@LINE-2]]:7: warning: the 'empty' method should be used
  // CHECK-FIXES: {{^  }}if (!templated_container.empty()){{$}}
  // CHECK-FIXES-NEXT: ;
  CHECKSIZE(templated_container);
  // CHECK-MESSAGES: :[[@LINE-1]]:13: warning: the 'empty' method should be used
  // CHECK-MESSAGES: CHECKSIZE(templated_container);
}

void g() {
  f<int>();
  f<double>();
  f<char *>();
}
