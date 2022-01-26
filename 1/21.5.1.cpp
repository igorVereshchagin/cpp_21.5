#include <iostream>
#include <fstream>
#include <string>

struct record_t
{
  std::string name;
  int day;
  int month;
  int year;
  int amount;
};

bool input_date(record_t &rec)
{
  std::string str_date;
  std::cout << "Input date: " << std::endl;
  std::getline(std::cin, str_date); //dd.mm.yyyy dd\mm\yyyy dd/mm/yyyy dd-mm-yyyy
  if ((str_date.size() != 10) ||
      (str_date[2] != str_date[5]) ||
      ((str_date[2] != '.') && (str_date[2] != '\\') && str_date[2] != '/') && (str_date[2] != '-'))
    return false;
  int day = std::stoi(str_date.substr(0, 2));
  int month = std::stoi(str_date.substr(3, 2));
  int year = std::stoi(str_date.substr(6, 4));
  if ((day < 1) || (day > 31) || (month < 1) || (month > 12))
    return false;
  rec.day = day;
  rec.month = month;
  rec.year = year;
  return true;
}

bool input_amount(record_t &rec)
{
  std::cout << "Input amount: " << std::endl;
  std::cin >> rec.amount;
  return true;
}

int list() {
  std::ifstream payments(".\\payments.bin", std::ios::binary);
  if (!payments.is_open()) {
    std::cout << "Can't open file .\\payments.bin" << std::endl;
    return -1;
  }
  while (!payments.eof())
  {
    record_t rec;
    int name_len;
    payments.read((char*)&name_len, sizeof(name_len));
    if (sizeof(name_len) != payments.gcount())
      continue;
    rec.name.resize(name_len);
    payments.read((char*)rec.name.c_str(), name_len);
    if (name_len != payments.gcount())
      continue;
    payments.read((char*)&rec.day, sizeof(rec.day));
    if (sizeof(rec.day) != payments.gcount())
      continue;
    payments.read((char*)&rec.month, sizeof(rec.month));
    if (sizeof(rec.month) != payments.gcount())
      continue;
    payments.read((char*)&rec.year, sizeof(rec.year));
    if (sizeof(rec.year) != payments.gcount())
      continue;
    payments.read((char*)&rec.amount, sizeof(rec.amount));
    if (sizeof(rec.amount) != payments.gcount())
      continue;
    std::cout << rec.name << " " << rec.day << "." << rec.month << "." << rec.year << " " << rec.amount << std::endl;
  }
  payments.close();
  return 0;
}

int add()
{
  record_t rec;
  std::cout << "Input name: " << std::endl;
  std::cin >> std::ws;
  std::getline(std::cin, rec.name);
  if (!input_date(rec))
  {
    std::cout << "Invalid date" << std::endl;
    return -1;
  }
  input_amount(rec);

  std::ofstream payments(".\\payments.bin", std::ios::app | std::ios::binary);
  if (!payments.is_open())
  {
    std::cout << "Can't open file .\\payments.bin" << std::endl;
    return -1;
  }
  int name_len = rec.name.length();
  payments.write((char*)&name_len, sizeof(name_len));
  payments.write(rec.name.c_str(), name_len);
  payments.write((char*)&rec.day, sizeof(rec.day));
  payments.write((char*)&rec.month, sizeof(rec.month));
  payments.write((char*)&rec.year, sizeof(rec.year));
  payments.write((char*)&rec.amount, sizeof(rec.amount));
  payments.close();
  return 0;
}
int main()
{
  std::string op;
  std::cout << "Input operation: " << std::endl;
  std::cin >> op;
  if (op == "list")
    return list();
  else if (op == "add")
    return add();
  else
  {
    std::cout << "Invalid operation" << std::endl;
    return -1;
  }
}
