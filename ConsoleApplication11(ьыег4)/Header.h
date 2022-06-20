#include <iostream>

using namespace std;

int str_to_int(char* str, int left, int right)
{
	char* answer = new char[right - left + 2];
	for (int i = 0; i < right - left + 1; ++i)
		answer[i] = str[i + left];
	answer[right - left + 1] = '\0';
	return atoi(answer);
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

template <typename T> class Set
{
private:
	T* m_data;
	int m_size;
	int m_capacity;

	int bin_search(T elem)
	{
		int left = 0, right = m_size, mid;
		while (right - left > 1)
		{
			mid = (left + right) / 2;
			if (m_data[mid] < elem)
				left = mid;
			else
				right = mid;
		}
		return left;
	}

public:
	Set()
	{
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	Set(T elem)
	{
		m_data = new T[1];
		m_capacity = 1;
		m_size = 1;
		m_data[0] = T;
	}

	Set(const Set<T>& s)
	{
		m_size = s.m_size;
		m_capacity = s.m_size;
		if (s.m_size > 0)
			m_data = new T[m_size];
		else
			m_data = nullptr;
		for (int i = 0; i < m_size; ++i)
			m_data[i] = s.m_data[i];
	}

	void resize(int new_size)
	{
		if (new_size > m_capacity)
		{
			int new_capacity = max(new_size, m_size * 2);
			T* new_data = new T[new_capacity];
			for (int i = 0; i < m_size; ++i)
				new_data[i] = m_data[i];
			if (m_data)
				delete[] m_data;
			m_data = new_data;
			m_capacity = new_capacity;
		}
		m_size = new_size;
	}

	void add_element(T elem)
	{
		int index = bin_search(elem);
		if (m_size > 0)
		{
			if (m_data[index] == elem || index + 1 < m_size && m_data[index + 1] == elem)
				return;
			else if (m_data[index] < elem)
				index++;
		}
		resize(m_size + 1);
		for (int i = m_size - 1; i > index; --i)
			m_data[i] = m_data[i - 1];
		m_data[index] = elem;

	}

	void delete_element(T elem)
	{
		int index = bin_search(elem);
		if (m_data[index] != elem)
			index += 1;
		if (m_data[index] == elem)
		{
			for (int i = index; i < m_size - 1; ++i)
				m_data[i] = m_data[i + 1];
			m_size--;
		}
	}

	int find_element(T elem)
	{
		int index = bin_search(elem);
		if (m_data[index] == elem)
			return index;
		else if (index + 1 < m_size && m_data[index + 1] == elem)
			return index + 1;
		return -1;
	}

	int size()
	{
		return m_size;
	}

	T& operator [] (const int index)
	{
		return m_data[index];
	}

	Set<T>& operator = (const Set<T>& s)
	{
		if (this == &s)
			return *this;
		m_size = s.m_size;
		m_capacity = s.m_size;
		if (s.m_size > 0)
			m_data = new T[m_size];
		else
			m_data = nullptr;
		for (int i = 0; i < m_size; ++i)
			m_data[i] = s.m_data[i];
		return *this;
	}
};

template <class FRIEND> class Term
{
private:
	int coef;
	int pow;
	friend FRIEND;

public:
	Term(int c = 0, int p = 0)
	{
		coef = c;
		pow = p;
	}

	Term(const Term<FRIEND>& t)
	{
		coef = t.coef;
		pow = t.pow;
	}

	int get_coef()
	{
		return coef;
	}

	int get_pow()
	{
		return pow;
	}

	Term<FRIEND>& operator = (const Term<FRIEND>& t)
	{
		coef = t.coef;
		pow = t.pow;
		return *this;
	}

	friend bool operator < (Term<FRIEND>& t1, Term<FRIEND>& t2)
	{
		return t1.pow < t2.pow;
	}

	friend bool operator == (Term<FRIEND>& t1, Term<FRIEND>& t2)
	{
		return t1.pow == t2.pow;
	}

	friend bool operator != (Term<FRIEND>& t1, Term<FRIEND>& t2)
	{
		return t1.pow != t2.pow;
	}

	friend Term<FRIEND> operator + (Term<FRIEND>& t1, Term<FRIEND>& t2)
	{
		if (t1.coef == 0)
			return t2;
		if (t2.coef == 0)
			return t1;
		if (t1.pow != t1.pow)
			return Term<FRIEND>();
		return Term<FRIEND>(t1.coef + t2.coef, t1.pow);
	}

	friend Term<FRIEND> operator * (Term<FRIEND>& t1, Term<FRIEND>& t2)
	{
		return Term<FRIEND>(t1.coef * t2.coef, t1.pow + t2.pow);
	}

	friend istream& operator >> (istream& in, Term<FRIEND>& t)
	{
		char buf[20];
		in >> buf;
		int n = strlen(buf), sign = -1, x = -1;
		for (int i = 0; i < n; ++i)
			if (buf[i] == '^')
				sign = i;
			else if (buf[i] == 'x')
				x = i;
		if (x == -1)
		{
			if (buf[0] != '-')
				t.coef = str_to_int(buf, 0, n - 1);
			else
				t.coef = -str_to_int(buf, 1, n - 1);
			t.pow = 0;
		}
		else
		{
			if (x == 0)
				t.coef = 1;
			else if (x == 1 && buf[0] == '-')
				t.coef = -1;
			else if (buf[0] != '-')
				t.coef = str_to_int(buf, 0, x - 1);
			else
				t.coef = -str_to_int(buf, 1, x - 1);
			if (sign != -1)
				t.pow = str_to_int(buf, sign + 1, n - 1);
			else
				t.pow = 1;
		}
		return in;
	}

	friend ostream& operator << (ostream& out, Term<FRIEND> t)
	{
		if (t.coef == 0 || t.pow == 0)
		{
			out << t.coef;
			return out;
		}
		if (t.coef == 1)
			out << 'x';
		else if (t.coef == -1)
			out << "-x";
		else
			out << t.coef << 'x';
		if (t.pow != 1)
			out << '^' << t.pow;
		return out;
	}
};

class Polynom
{
private:
	Set<Term<Polynom>> data;
	int order;

public:
	Polynom(int coef = 0)
	{
		data.resize(1);
		data[0] = Term<Polynom>(coef, 0);
		order = 1;
	}

	Polynom(Term<Polynom> t)
	{
		data.resize(1);
		data[0] = t;
		order = 1;
	}

	Polynom(const Polynom& p)
	{
		data = p.data;
		order = p.order;
	}

	void set_order(int new_order)
	{
		order = new_order;
	}

	Polynom& operator = (const Polynom& p)
	{
		data = p.data;
		order = p.order;
		return *this;
	}

	Polynom& operator += (Term<Polynom> t)
	{
		int index = data.find_element(t);
		if (index == -1)
			data.add_element(t);
		else
			data[index] = data[index] + t;
		return *this;
	}

	Polynom& operator += (Polynom& p)
	{
		for (int i = 0; i < p.data.size(); ++i)
			*this += p.data[i];
		return *this;
	}

	friend Polynom operator + (Polynom& p1, Polynom& p2)
	{
		Polynom p = p1;
		p += p2;
		return p;
	}

	friend Polynom operator * (Polynom& p1, Polynom& p2)
	{
		Polynom p;
		for (int i = 0; i < p1.data.size(); ++i)
			for (int j = 0; j < p2.data.size(); ++j)
				p += (p1.data[i] * p2.data[j]);
		return p;
	}

	Polynom& operator *= (Polynom& p)
	{
		*this = *this * p;
		return *this;
	}

	friend ostream& operator << (ostream& out, Polynom& p)
	{
		if (p.order == 1)
		{
			for (int i = p.data.size() - 1; i >= 0; --i)
			{
				if (p.data[i].get_coef() == 0)
					continue;
				int sign = 1;
				if (p.data[i].get_coef() < 0)
					sign = -1;
				if (i != p.data.size() - 1)
				{
					if (sign == 1)
						cout << " + ";
					else
						cout << " - ";
				}
				else if (sign == -1)
					cout << '-';
				cout << Term<Polynom>(p.data[i].get_coef() * sign, p.data[i].get_pow());
			}
		}
		else
		{
			for (int i = 0; i < p.data.size(); ++i)
			{
				if (p.data[i].get_coef() == 0)
					continue;
				int sign = 1;
				if (p.data[i].get_coef() < 0)
					sign = -1;
				if (i != 0)
				{
					if (sign == 1)
						cout << " + ";
					else
						cout << " - ";
				}
				else if (sign == -1)
					cout << '-';
				cout << Term<Polynom>(p.data[i].get_coef() * sign, p.data[i].get_pow());
			}
		}
		return out;
	}
};