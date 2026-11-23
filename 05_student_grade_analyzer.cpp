#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int mark;
    char grade;
};

int main() {
    int n, threshold;
    cout << "Enter number of students: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of students must be positive.\n";
        return 0;
    }

    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> ws;
        getline(cin, students[i].name);

        cout << "Enter mark (0 to 100): ";
        cin >> students[i].mark;
        if (students[i].mark < 0 || students[i].mark > 100) {
            cout << "Invalid mark. Enter marks between 0 and 100.\n";
            return 0;
        }
    }

    cout << "\nEnter the mark threshold to search above: ";
    cin >> threshold;

    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.mark > b.mark;
         });

    transform(students.begin(), students.end(), students.begin(),
              [](Student s) {
                  if (s.mark >= 90) s.grade = 'A';
                  else if (s.mark >= 75) s.grade = 'B';
                  else if (s.mark >= 50) s.grade = 'C';
                  else s.grade = 'F';
                  return s;
              });

    auto it = find_if(students.begin(), students.end(),
                      [threshold](const Student& s) {
                          return s.mark > threshold;
                      });

    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student& s) {
                               return sum + s.mark;
                           });

    cout << "\nName\tMark\tGrade\n";
    for (const Student& s : students)
        cout << s.name << "\t" << s.mark << "\t" << s.grade << '\n';

    if (it != students.end())
        cout << "\nFirst student scoring above " << threshold
             << ": " << it->name << '\n';
    else
        cout << "\nNo student scored above " << threshold << ".\n";

    cout << "Total Marks: " << total << '\n';
    cout << "Average Mark: " << static_cast<double>(total) / n << '\n';
    return 0;
}
