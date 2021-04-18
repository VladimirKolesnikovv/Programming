#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

const auto PI = 3.141592653589793;

enum class coord_system
{
    Cartesian,
    Polar
};

bool aresame(const double q, const double w, int accuracy_signs = 10)
{
    return !int(abs(q - w) * pow(10,accuracy_signs));
}

class Point
{
private:
    double a1, a2;
    coord_system system;
public:
    Point()
    {
        this->a1 = 0;
        this->a2 = 0;
        this->system = coord_system::Cartesian;
    }
    Point(double a1, double a2, coord_system system)
    {
        this->a1 = a1;
        this->a2 = a2;
        this->system = system;
    }
    double get_x()
    {
        if (this->system == coord_system::Cartesian)
        {
            return a1;
        }
        else
        {
            return a1 * cos(a2);
        }
    }
    double get_y()
    {
        if (this->system == coord_system::Cartesian)
        {
            return a2;
        }
        else
        {
            return a1 * sin(a2);
        }
    }
    double get_r()
    {
        if (this->system == coord_system::Cartesian)
        {
            return sqrt(pow(a1, 2) + pow(a2, 2));
        }
        else
        {
            return a1;
        }
    }
    double get_phi()
    {
        if (this->system == coord_system::Cartesian)
        {
            return acos(a1/(sqrt(pow(a1, 2) + pow(a2, 2))));
        }
        else
        {
            return a2;
        }
    }
    void set_x(double x)
    {
        if (this->system == coord_system::Cartesian)
        {
            this->a1 = x;
        }
        else
        {
            double r = sqrt(x * x + this->get_y() * this->get_y());
            double phi = atan(this->get_y() / x);
            this->a1 = r;
            this->a2 = phi;
        }
    }
    void set_y(double y)
    {
        if (this->system == coord_system::Cartesian)
        {
            this->a2 = y;
        }
        else
        {
            double r = sqrt(y * y + this->get_x() * this->get_x());
            double phi = atan(this->get_x() / y);
            this->a1 = r;
            this->a2 = phi;
        }
    }
    void set_r(double r)
    {
        if (this->system == coord_system::Cartesian)
        {
            double x = r * cos(this->get_phi());
            double y = r * sin(this->get_phi());
            this->a1 = x;
            this->a2 = y;
        }
        else
        {
            this->a1 = r;
        }
    }
    void set_phi(double phi)
    {
        if (this->system == coord_system::Cartesian)
        {
            double x = this->get_r() * cos(phi);
            double y = this->get_r() * sin(phi);
            this->a1 = x;
            this->a2 = y;
        }
        else
        {
            this->a2 = phi;
        }
    }
    bool operator==( Point p2)
    {


        return aresame(this->get_r(), p2.get_r()) && aresame(this->get_phi(), p2.get_phi());
    };
    bool operator!=(Point p2)
    {
        return *this != p2;
    };

    friend std::ostream& operator<<(std::ostream& sout, Point& point)
    {
        sout <<"("<< point.get_x() <<"," << point.get_y() <<"), ";
        return sout;
    }
    friend std::istream& operator>> (std::istream& input_stream, Point& point)
    {
        std::string temp;
        input_stream >> temp;
        if (temp[0] == '(') {
            temp = temp.substr(1);
        }

        auto endPointer = temp.find(')');
        temp = temp.substr(0, endPointer);
        auto x = temp.substr(0, temp.find(','));
        auto y = temp.substr(temp.find(',') + 1);

        point.a1 = std::stod(x);
        point.a2 = std::stod(y);

        return input_stream;
    }
};

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof())
        {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum)
    {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
    {
        std::cout << "\nIt works!\n";
    }
    else
    {
        std::cout << "\nIt not works!\n";
    }
}
