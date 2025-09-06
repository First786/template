					
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//----------------------------------------------------------------------------------

long double EPS = 1e-9;
//точки
struct point_i {
	int x, y;									// координаты точки
	point_i() { x = y = 0; }
	point_i(int x, int y) : x(x), y(y) {}		// инициализация 
	bool operator <(point_i other) const {		// сравнение точек
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
	bool operator ==(point_i other)	{			// сравниваем 2 точки
		return (x == other.x && y == other.y);
	}
};
struct point {
	double x, y;								// координаты точки
	point() { x = y = 0; }
	point(double x, double y) : x(x), y(y) {}	// инициализация 
	bool operator <(point other) const {		// сравнение точек
		if (fabs(x - other.x) > EPS) return x < other.x;
		return y < other.y;
	}
	bool operator ==(point other) {				// сравниваем 2 точки
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS);
	}
};
double dist(point p1, point p2) {			// нахождение расстояния между точками
	return hypot(p1.x-p2.x, p1.y-p2.y);
}
point rotate(point p, double theta, point center = {0,0}) {		// поворот точки "p" вокруг точки "center", theta - градусы
	p.x -= center.x; p.y -= center.y;
	double rad = theta * asin(1) / 90;
	return point(p.x * cos(rad) - p.y * sin(rad) + center.x, 
		p.x * sin(rad) + p.y * cos(rad) + center.y);
}
//точки

//прямые
struct line { double a, b, c; };
void pointsToLine(point p1, point p2, line& l) {
	if (fabs(p1.x - p2.x) < EPS) {
		l.b = 0; l.a = 1; l.c = -p1.x;					// Если прямая вертикальная 
	}
	else {
		l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;										// ВАЖНО: мы приводим значение b к 1.0
		l.c = -(double)(l.a * p1.x) - p1.y;
	}
}
bool areParallel(line l1, line l2) {
	return (fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS);	// коэфициенты "a" и "b" равны
}
bool areSame(line l1, line l2) {
	return areParallel(l1, l2) && fabs(l1.c - l2.c) < EPS;			// если прямые параллельны и коэфициенты "c" равны
}
bool areIntersect(line l1, line l2, point& p) {		// возвращают true(+ точку пересечения) если линии не параллельны
	if (areParallel(l1, l2)) return false;			// если параллельны, то возвращаем false
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b); // метод крамера
	p.y = (l1.a * l2.c - l2.a * l1.c) / (l2.a * l1.b - l1.a * l2.b); // метод крамера
}
//прямые
////вектор
struct vec {
	double x, y;
	vec(double x, double y) :x(x), y(y) {}
	vec operator+ (vec p) {
		return vec(x + p.x, y + p.y);
	}
	vec operator* (int s) {
		return vec(x * s, y * s);
	}
	vec operator* (double s) {
		return vec(x * s, y * s);
	}
};
vec toVec(point a, point b)	{	// преобразрвание точек в вектор a->b
	return vec(b.x - a.x, b.y - a.y);
}
vec scale(vec v, double s) {			// умножение вектора на число "s"
	return vec(v.x * s, v.y * s);
}
point translate(point p, vec v) {   	// перемещение точки "p" по вектору "v"
	return point(p.x + v.x, p.y + v.y);
}
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
// возвращает расстояние от точки p до прямой, определенной двумя точками a и b
// (a и b обязательно должны быть различными точками)
// самая близкая точка сохраняется в 4–м параметре (переданном по ссылке)
double distToLine(point p, point a, point b, point& c) { // c - ближайшая точка на прямой к точке p
	// вычисление по формуле: c = a + u * ab
	vec ap = toVec(a, p), ab = toVec(a, b);
	double u = dot(ap, ab) / norm_sq(ab);
	c = translate(a, scale(ab, u)); // преобразование (перемещение) a в c
	return dist(p, c); // евклидово расстояние между точками p и c
}
double distToLine(point p, line l, point& c) {
	double u = -(l.a * p.x + l.b * p.y + l.c) / (l.a * l.a + l.b * l.b);
	c.x = p.x + u * l.a;
	c.y = p.y + u * l.b;
	return abs(u* sqrt(l.a * l.a + l.b * l.b));
}
double distToLineSegment(point p, point a, point b, point& c) {
	vec ab = toVec(a, b), ap = toVec(a, p);
	double u = dot(ab, ap) / norm_sq(ab);
	if (u < 0.0) {
		c = point(a.x, a.y);
		return dist(p, a);
	}
	if (u > 1.0) {
		c = point(b.x, b.y);
		return dist(p, b);
	}
	return distToLine(p, a, b, c);
}
double angle(point a, point o, point b) { // угол в радианах AoB
	vec oa = toVec(o, a), ob = toVec(o, b);
	return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}
double cross(vec a, vec b) {								// определитель матрицы 2x2
	return a.x * b.y - a.y * b.x;
}
bool ccw(point p, point q, point r)	{						// проверка, что pr левее чем pq
	return cross(toVec(p, q), toVec(p, r)) > 0;
}
bool collinear(point p, point q, point r) {					// проверка, что p, q, r лежат на одной прямой
	return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}
////вектор
////окружность
bool insideCircle(point p, point center, double r) {		// приналежит ли точка "p" окружности с центром "center" и радиусом "r"
	return (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) <= r * r;
}
bool circle2PtsRad(point p1, point p2, double r, point& c) { // по двум точкам и радиусу возвращает центр окружности
	double d2 = dot(toVec(p2, p1), toVec(p2, p1));				// норма вектора p2-p1 в квадрате
	double det = r * r / d2 - 0.25;								// поиск катета прямоуг. треуг. делённую на норму (p2-p1) в квадрате
	if (det < 0.0) return false;								// если квадрат катета меньше нуля, то такой окружности не существует
	c.x = 0.5 * (p1.x + p2.x) + sqrt(det) * (p1.y - p2.y);		// иначе 0.5 * (p1+p2) + sqrt(det) * rotate(p2-p1,90)
	c.y = 0.5 * (p1.y + p2.y) + sqrt(det) * (p2.x - p1.x);
	return true;
}
////окружность
////треугольник
double perimeter(double a, double b, double c) {
	return a + b + c;
}
double area(double a, double b, double c) {        // площадь треугольника
	double p = perimeter(a, b, c) / 2.0;					// полупериметр
	return sqrt(p * (p - a) * (p - b) * (p - c));			// формула Герона
}
double rInCircle(double ab, double bc, double ca) { // радиус вписанной окружности 
	return area(ab, bc, ca) * 2 / perimeter(ab, bc, ca);
}
double rInCircle(point a, point b, point c) {       // Радиус вписанной окружности по точкам
	return rInCircle(dist(a, b), dist(b, c), dist(c, a));
}
bool inCircle(point p1, point p2, point p3, point& ctr, double& r) { // по заданным точкам строим вписанную окружность. Её радиус сохраняем в ctr, а радиус в r
	r = rInCircle(p1, p2, p3);
	if (r < EPS) return false;

	line l1, l2;

	point p = translate(p1, toVec(p1, p2)*(1.0/dist(p1,p2)) + toVec(p1, p3)*(1.0/dist(p1,p3)));
	pointsToLine(p1, p, l1);

	p = translate(p2, toVec(p2, p1)*(1.0/dist(p2,p1)) + toVec(p2, p3)*(1.0/dist(p2,p3)));
	pointsToLine(p2, p, l2);

	areIntersect(l1, l2, ctr);
	return true;
}
////треугольник
////многоугольники
double area(vector<point> P) { // площадь многоугольника методом "шнуровка Гаусса"
	double result = 0;
	for (int i = 0; i < (int)P.size() - 1; i++)
		result += P[i].x * P[i + 1].y - P[i].y * P[i + 1].x;

	return result / 2;
}
bool isConvex(vector<point> P) { // Проверка многоугольника на выпуклость 
	int n = P.size();
	if (n < 3) return false;
	bool isLeft = ccw(P[0], P[1], P[2]);
	for (int i = 0; i < n - 1; i++)
		if (ccw(P[i], P[i + 1], P[i + 2 < n ? i + 2 : 1]) != isLeft) return false;
	return true;
}
bool inPolygon(vector<point> P, point pt) { // проверяет находится ли точка pt внутри многоугольника P
	int n = P.size();
	if (n == 0)return false;
	double sum = 0;
	for (int i = 0; i < n - 1; i++)
		if (pt == P[i] || pt == P[i + 1])
			return true;
		else if (ccw(P[i], pt, P[i + 1]))
			sum -= angle(P[i], pt, P[i + 1]);
		else 
			sum += angle(P[i], pt, P[i + 1]);
	//cout << sum * 180 / acos(-1)<<"\n";
	return fabs(sum - 2 * acos(-1)) < EPS;
}
////многоугольники

// Отрезок прямой p–q пересекается с прямой линией A–B
point lineIntersectSeg(point p, point q, point A, point B) { // находит точку пересеченияотрезка pq с прямой AB
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);

	auto j = point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
	//cout << j.x << " " << j.y << "\n";
	line l1, l2;
	pointsToLine(p, q, l1);
	pointsToLine(A, B, l2);
	point i;
	areIntersect(l1, l2, i);
	//cout << i.x <<" "<< i.y << "\n\n";

	return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}

// Разделение многоугольника Q по прямой, проходящей через точки a –> b.
// (Примечание: последняя точка обязательно должна совпадать с первой точкой.) 
vector<point> cutPolygon(point a, point b, const vector<point>& Q) { // возвращает только левую часть многоугольника
	vector<point> P;
	for (int i = 0; i < (int)Q.size(); i++) {
		double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
		if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i + 1]));
		if (left1 < -EPS) P.push_back(Q[i]); // Q[i] находится слева от прямой ab
		if (left1 * left2 < -EPS) // сторона (Q[i], Q[i+1]) пересекается с прямой ab
			P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
	}
	if (!P.empty() && !(P.back() == P.front()))
		P.push_back(P.front()); // сделать первую точку P = последней точке P
	return P;
}

bool compair_p(point& a, point& b) { // сравнивает точки относительно (0, 0) сортирует пары (угол между Ox,  -(длина вектора)   )
	if (b.x == 0 && b.y == 0 && a.x == 0 && a.y == 0) return false;
	if (a.x == 0 && a.y == 0) return true;
	if (b.x == 0 && b.y == 0) return false;
	double det = cross(toVec({ 0,0 }, a), toVec({ 0,0 }, b));
	if (det > 0) return true;
	else if (det == 0) return dist({ 0,0 }, a) < dist({ 0,0 }, b);
	return false;
}
vector<point> graham(vector<point> P) { // Строит выпуклую оболочку
	int n = P.size();
	if (n < 4 ) return P;
	point min_p = P[0];
	for (int i = 1; i < n; i++) min_p = std::min(min_p, P[i]);
	for (int i = 0; i < n; i++) P[i] = point(P[i].x - min_p.x, P[i].y - min_p.y);
	sort(P.begin(), P.begin() + n, compair_p);
	for (int i = 0; i < n; i++) P[i] = point(P[i].x + min_p.x, P[i].y + min_p.y);
	//for (auto i : P) cout << i.x << " " << i.y << "\n";
	//cout << "\n";
	vector<point> convex{P[n-1], P[0], P[1]};
	for (int i = 2; i < n; i++) {
		while (convex.size() > 2 && ccw(convex[convex.size() - 2], convex[convex.size() - 1], P[i]) <= 0) convex.pop_back();
		convex.push_back(P[i]);
	}
	return convex;
}

