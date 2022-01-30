#include <iostream>
#include <cmath>
#include <string>

struct math_vector_t
{
  double x;
  double y;
};

math_vector_t add(const math_vector_t &vec1, const math_vector_t &vec2);
math_vector_t sub(const math_vector_t &vec1, const math_vector_t &vec2);
math_vector_t mul(const math_vector_t &vec1, const double m);
double vector_length(const math_vector_t &vec1);
void normalize(math_vector_t &vec1);

math_vector_t input_vector()
{
  math_vector_t res;
  std::cout << "Input vector: " << std::endl;
  std::cin >> res.x >> res.y;
  return res;
}
double input_double()
{
  std::cout << "Input a real number: " << std::endl;
  double res;
  std::cin >> res;
  return res;
}
void output_vector(const math_vector_t &vec)
{
  std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}

int main()
{
  std::string op;
  do
  {
    std::cout << "Input operation: " << std::endl;
    std::cin >> op;
    if (op == "add")
    {
      math_vector_t vec1 = input_vector();
      math_vector_t vec2 = input_vector();
      math_vector_t res = add(vec1, vec2);
      output_vector(res);
    } else if (op == "sub")
    {
      math_vector_t vec1 = input_vector();
      math_vector_t vec2 = input_vector();
      math_vector_t res = sub(vec1, vec2);
      output_vector(res);
    } else if (op == "mul")
    {
      math_vector_t vec = input_vector();
      double m = input_double();
      math_vector_t res = mul(vec, m);
      output_vector(res);
    } else if (op == "length")
    {
      math_vector_t vec = input_vector();
      double len = vector_length(vec);
      std::cout << len << std::endl;
    } else if (op == "norm")
    {
      math_vector_t vec = input_vector();
      normalize(vec);
      output_vector(vec);
    }
  }while (op != "exit");
  return 0;
}

math_vector_t add(const math_vector_t &vec1, const math_vector_t &vec2)
{
  math_vector_t res;
  res.x = vec1.x + vec2.x;
  res.y = vec1.y + vec2.y;
  return res;
}

math_vector_t sub(const math_vector_t &vec1, const math_vector_t &vec2)
{
  math_vector_t res;
  res.x = vec1.x - vec2.x;
  res.y = vec1.y - vec2.y;
  return res;
}
math_vector_t mul(const math_vector_t &vec1, const double m)
{
  math_vector_t res;
  res.x = vec1.x * m;
  res.y = vec1.y * m;
  return res;
}

double vector_length(const math_vector_t &vec1)
{
  return sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
}

void normalize(math_vector_t &vec1)
{
  double sqlen = vec1.x * vec1.x + vec1.y * vec1.y;
  vec1.x = sqrt((vec1.x * vec1.x) / sqlen);
  vec1.y = sqrt((vec1.y * vec1.y) / sqlen);
}
