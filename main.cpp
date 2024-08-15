#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/dom/table.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/screen.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

vector<vector<int>> initializeMatrix(int a) {
  vector<vector<int>> x(a + 1, vector<int>(13));
  return x;
}

void inputMatrixData(vector<vector<int>> &x, int a) {
  for (int i = 0; i < a + 1; i++) {
    for (int j = 0; j < 13; j++) {
      x[i][j] = 0;
    }
  }

  for (int i = 1; i <= a; i++) {
    for (int j = 1; j <= 9; j++) {
      cin >> x[i][j];
    }
  }
}

void calculateMatrixValues(vector<vector<int>> &x, int a) {
  for (int b = 1; b <= a; b++) {

    x[b][10] = -9;
    x[b][12] = -9;

    for (int j = 1; j <= 9; j++) {
      for (int i = 1; i <= a; i++) {
        if (x[b][j] > x[i][j]) {
          x[b][10] = x[b][10] + 2;
          x[b][11]++;
        } else {
          if (x[b][j] == x[i][j]) {
            x[b][10]++;
            x[b][12]++;
          } else {
            x[b][13]++;
          }
        }
      }
    }
  }
}

void printMatrix(const vector<vector<int>> &x, int a, vector<int> &z) {
  for (int i = 1; i <= a; i++) {
    for (int j = 1; j <= 13; j++) {
      if (j == 1 or j == 10 or j == 11 or j == 12 or j == 13) {
        if (j == 10) {
          z[i] = x[i][j];
        }
      }
    }
  }
}

void displayResultList(vector<vector<int>> &x, int a, int *it_list) {
  for (int f = 1; f <= a; f++) {
    int maxx = -1;
    int it = 0;

    for (int i = 1; i <= a; i++) {
      if (x[i][10] > maxx) {
        maxx = x[i][10];
        it = i;
      }
    }

    it_list[f] = it;
    x[it][10] = -1;
  }
}

int main() {

  int a = 0;

  cin >> a;

  vector<vector<int>> x = initializeMatrix(a);
  vector<int> z(a + 1);
  int *it_list = new int[a + 1];

  inputMatrixData(x, a);
  calculateMatrixValues(x, a);
  printMatrix(x, a, z);
  displayResultList(x, a, it_list);

  vector<vector<Element>> table_data = {
      {text(" # "), text(" # Team "), text(" Position "), text(" Score "),
       text(" Win "), text(" Draw "), text(" Lose ")}};

  for (int i = 1; i <= a; i++) {
    std::string numbers;
    for (int j = 1; j < 10; j++) {
      numbers += j < 9 ? to_string(x[i][j]) + " " : to_string(x[i][j]);
    }
    table_data.push_back({text(to_string(i)), text(to_string(it_list[i])),
                          text(" " + numbers + " "), text(to_string(z[i])),
                          text(to_string(x[i][11])), text(to_string(x[i][12])),
                          text(to_string(x[i][13]))});
  }

  auto table = Table(table_data);

  table.SelectAll().Border(DOUBLE);

  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(DOUBLE);
  table.SelectRow(0).Border(DOUBLE);

  for (int i = 0; i < 7; i++) {
    table.SelectColumn(i).Border(DOUBLE);
    table.SelectColumn(i).DecorateCells(center);

    if (i % 2 == 0) {
      table.SelectColumn(i).DecorateCells(color(Color::Yellow));
    } else {
      table.SelectColumn(i).DecorateCells(color(Color::Blue));
    }
  }

  auto document = table.Render();
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();

  delete[] it_list;

  return 0;
}
