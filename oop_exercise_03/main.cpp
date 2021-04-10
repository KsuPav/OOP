/*
* Фамилия Имя Группа
* ========================
* Вариант 16:
* 8-угольник
* Треугольник
* Квадрат
*/

#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.14159265f

//точка многоугольника
using point = std::pair<float, float>;

//родительский класс для всех фигур
class Figure
{
public:
	//вычисление геометрического центра фигуры
	point getCenter()
	{
		point center = std::make_pair(0.0f, 0.0f);
		for (point p : m_points)
		{
			center.first += p.first;
			center.second += p.second;
		}
		center.first /= m_points.size();
		center.second /= m_points.size();
		return center;
	}

	//вывод координат вершин фигуры
	void print()
	{
		bool comma = false; //печатать запятую перед точкой или нет
		for (point p : m_points)
		{
			if (comma) std::cout << ", ";
			comma = true;

			std::cout << "(" << p.first << ", " << p.second << ")";
		}
	}

	//вычисление площади
	float size()
	{
		float S = 0.0f;
		for (int i = 0; i < m_points.size() - 1; i++)
			S += triag(m_points[0], m_points[i], m_points[i + 1]);
		return S;
	}

protected:
	//точки многоугольника
	std::vector<point> m_points;

	//площадь треугольника по координатам вершин
	//S = 1/2 * abs(det(x1 - x3, y1 - y3; x2 - x3, y2 - y3))
	float triag(point& a, point& b, point& c)
	{
		return 0.5f * abs((a.first - c.first) * (b.second - c.second) -
			(b.first - c.first) * (a.second - c.second));
	}
};

//Любую фигуру вращения можно задать координатами центра, радиусом описанной окружности и углом поворота
//8-угольник
class Octagon : public Figure
{
public:
	//заполняем вектор вершин
	Octagon(float x, float y, float r, float a)
	{
		for (int i = 0; i < 8; i++)
		{
			float phi = a + i * PI / 4.0f;
			m_points.push_back(std::make_pair(r * cosf(phi) + x, r * sinf(phi) + y));
		}
	}
};
//Квадрат
class Square : public Figure
{
public:
	//заполняем вектор вершин
	Square(float x, float y, float r, float a)
	{
		for (int i = 0; i < 4; i++)
		{
			float phi = a + i * PI / 2.0f;
			m_points.push_back(std::make_pair(r * cosf(phi) + x, r * sinf(phi) + y));
		}
	}
};
//Треугольник
class Triangle : public Figure
{
public:
	//заполняем вектор вершин
	Triangle(float x, float y, float r, float a)
	{
		for (int i = 0; i < 3; i++)
		{
			float phi = a + i * PI / 1.5f;
			m_points.push_back(std::make_pair(r * cosf(phi) + x, r * sinf(phi) + y));
		}
	}
};

//список команд
void showCommands()
{
	std::cout <<
		"1. Show commands" << std::endl <<
		"2. Add figure" << std::endl <<
		"3. Delete figure" << std::endl <<
		"4. Center point" << std::endl <<
		"5. Print points" << std::endl <<
		"6. Size of figure" << std::endl <<
		"7. Total size" << std::endl <<
		"0. Exit" << std::endl;
}

int main()
{
	//вектор фигур
	std::vector<Figure*> figures;

	showCommands();

	//цикл программы
	bool loop = true;
	while (loop)
	{
		//читаем введённую команду
		std::cout << "> ";

		int command;
		std::cin >> command;

		switch (command)
		{
		case 0:
			loop = false;
			break;

		case 1:
			showCommands();
			break;

		case 2:
		{
			std::cout << "Choose type:" << std::endl <<
				"1 - Octagon" << std::endl <<
				"2 - Square" << std::endl <<
				"3 - Triangle" << std::endl <<
				"Type: ";

			int type;
			std::cin >> type;

			if (type < 1 || type > 3)
				std::cout << "Unknown type" << std::endl;
			else
			{
				float x, y, r, a;
				std::cout << "Coordinates of center: ";
				std::cin >> x >> y;

				std::cout << "Radius: ";
				std::cin >> r;

				std::cout << "Angle: ";
				std::cin >> a;

				switch (type)
				{
				case 1:
					figures.push_back(new Octagon(x, y, r, a));
					break;
				case 2:
					figures.push_back(new Square(x, y, r, a));
					break;
				case 3:
					figures.push_back(new Triangle(x, y, r, a));
					break;
				}
			}
			break;
		}
		case 3:
		{
			std::cout << "Index: ";

			int index;
			std::cin >> index;
			if (index < 0 || index >= figures.size())
				std::cout << "Index out of bounds" << std::endl;
			else
			{
				delete figures[index];
				figures.erase(figures.begin() + index);
			}
			break;
		}
		case 4:
		{
			std::cout << "Index (-1 to call for all figures): ";

			int index;
			std::cin >> index;

			if (index == -1)
				for (int i = 0; i < figures.size(); i++)
				{
					point center = figures[i]->getCenter();
					std::cout << i << ": (" << center.first << ", " << center.second << ")" << std::endl;
				}
			else if (index < -1 || index >= figures.size())
				std::cout << "Index out of bounds" << std::endl;
			else
			{
				point center = figures[index]->getCenter();
				std::cout << index << ": (" << center.first << ", " << center.second << ")" << std::endl;
			}
			break;
		}

		case 5:
		{
			std::cout << "Index (-1 to call for all figures): ";

			int index;
			std::cin >> index;

			if (index == -1)
				for (int i = 0; i < figures.size(); i++)
				{
					std::cout << i << ": ";
					figures[i]->print();
					std::cout << std::endl;
				}
			else if (index < -1 || index >= figures.size())
				std::cout << "Index out of bounds" << std::endl;
			else
			{
				std::cout << index << ": ";
				figures[index]->print();
				std::cout << std::endl;
			}
			break;
		}

		case 6:
		{
			std::cout << "Index (-1 to call for all figures): ";

			int index;
			std::cin >> index;

			if (index == -1)
				for (int i = 0; i < figures.size(); i++)
				{
					std::cout << i << ": " << figures[i]->size() << std::endl;
				}
			else if (index < -1 || index >= figures.size())
				std::cout << "Index out of bounds" << std::endl;
			else
			{
				std::cout << index << ": " << figures[index]->size() << std::endl;
			}
			break;
		}

		case 7:
		{
			float total = 0.0f;
			for (Figure* f : figures)
				total += f->size();
			std::cout << "Total size of all figures: " << total << std::endl;
			break;
		}

		default:
			std::cout << "Unknown command" << std::endl;
			break;
		}
	}
    return 0;
}