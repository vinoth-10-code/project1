#include <iostream>
#include <iomanip>
using namespace std;

// Each unit stores its conversion factor relative to one meter.
struct Meter { static constexpr double factor = 1.0; };
struct Kilometer { static constexpr double factor = 1000.0; };
struct Centimeter { static constexpr double factor = 0.01; };

template <typename Unit>
class Quantity {
private:
    double value;
public:
    constexpr explicit Quantity(double v) : value(v) {}
    constexpr double getValue() const { return value; }
};

// Generic conversion function: source unit -> target unit.
template <typename ToUnit, typename FromUnit>
constexpr Quantity<ToUnit> convert(const Quantity<FromUnit>& quantity) {
    double valueInMeters = quantity.getValue() * FromUnit::factor;
    return Quantity<ToUnit>(valueInMeters / ToUnit::factor);
}

void convertFromMeter(double value, int to) {
    Quantity<Meter> input(value);
    if (to == 1) cout << input.getValue() << " m\n";
    else if (to == 2)
        cout << convert<Kilometer>(input).getValue() << " km\n";
    else
        cout << convert<Centimeter>(input).getValue() << " cm\n";
}

void convertFromKilometer(double value, int to) {
    Quantity<Kilometer> input(value);
    if (to == 1)
        cout << convert<Meter>(input).getValue() << " m\n";
    else if (to == 2) cout << input.getValue() << " km\n";
    else
        cout << convert<Centimeter>(input).getValue() << " cm\n";
}

void convertFromCentimeter(double value, int to) {
    Quantity<Centimeter> input(value);
    if (to == 1)
        cout << convert<Meter>(input).getValue() << " m\n";
    else if (to == 2)
        cout << convert<Kilometer>(input).getValue() << " km\n";
    else cout << input.getValue() << " cm\n";
}

int main() {
    double value;
    int from, to;

    cout << "Unit choices: 1. Meter  2. Kilometer  3. Centimeter\n";
    cout << "Enter value: ";
    cin >> value;
    cout << "Convert from (1/2/3): ";
    cin >> from;
    cout << "Convert to (1/2/3): ";
    cin >> to;

    if (from < 1 || from > 3 || to < 1 || to > 3) {
        cout << "Invalid unit choice.\n";
        return 0;
    }

    cout << fixed << setprecision(4) << "Converted value: ";
    if (from == 1) convertFromMeter(value, to);
    else if (from == 2) convertFromKilometer(value, to);
    else convertFromCentimeter(value, to);

    return 0;
}
