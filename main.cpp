#include <iostream>
#include <vector>

using namespace std;

const int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Функция всегда возвращает true
bool f(const int &x, const int &y) {
    return 1>0;
}

// Функция возвращает true, если x > y или y > 7
bool f1(const int &x, const int &y) {
    return x > y || y > 7;
}

// Функция возвращает true, если число, составленное из 10*x + y, делится на 3
bool f2(const int &x, const int &y) {
    return (10*x + y) % 3 == 0;
}

// Функция возвращает true, если x четное, а y нечетное
bool f3(const int &x, const int &y) {
    return x % 2 == 0 && y % 2 != 0;
}

// Выводит пары отношений на экран
void print_relationship(const vector<pair<int, int>> &relationship) {
    int new_line = 0;
    for (const auto [fst, snd]: relationship) {
        printf("(%d, %d) \n", fst, snd);
    }
    cout << endl << endl;
}

// Проверяет, содержится ли пара pr в отношениях relationship
bool include_pair(const vector<pair<int, int>> &relationship, const pair<int, int> &pr) {
    for (const auto [fst, snd]: relationship)
        if (fst == pr.first && snd == pr.second)
            return true;
    return false;
}

// Проверяет, содержится ли значение val как первый или второй элемент в отношениях relationship
bool include_value(const vector<pair<int, int>> &relationship, const int val) {
    for (const auto [fst, snd]: relationship)
        if (fst == val || snd == val)
            return true;
    return false;
}

// Копирует отношения relationship в новый вектор
vector<pair<int, int>> copy_relationship(const vector<pair<int, int>> &relationship) {
    vector<pair<int, int>> result;
    for (auto [fst, snd]: relationship) {
        pair pr = {fst, snd};
        result.push_back(pr);
    }

    return result;
}

// Проверяет, что отношения relationship1 нестрого содержатся в relationship2
bool relationship_not_strictly_include(const vector<pair<int, int>> &relationship1,
                                       const vector<pair<int, int>> &relationship2) {
    for (auto pr: relationship1)
        if (!include_pair(relationship2, pr))
            return false;
    return true;
}

// Удаляет дубликаты пар в отношениях
vector<pair<int, int>> dism(const vector<pair<int, int>> &relationship) {
    vector<pair<int, int>> result;
    for (auto v: relationship)
        if (!include_pair(result, v))
            result.push_back(v);
    return result;
}

// Проверяет, равны ли два отношения
bool relationship_equal(const vector<pair<int, int>> &relationship1,
                        const vector<pair<int, int>> &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) && \
         relationship_not_strictly_include(relationship2, relationship1))
        return true;
    return false;
}

// Проверяет, содержатся ли отношения relationship1 строго в relationship2
bool relationship_strictly_include(const vector<pair<int, int>> &relationship1,
                                   const vector<pair<int, int>> &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) && \
        !relationship_equal(relationship1, relationship2))
            return true;
    return false;
}

// Объединяет два множества отношений
vector<pair<int, int>> union_relationship(const vector<pair<int, int>> &relationship1,
                                          const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        result.push_back(v);

    for (auto v: relationship2)
        if (!include_pair(relationship1, v))
            result.push_back(v);

    return result;
}

// Находит пересечение двух множеств отношений
vector<pair<int, int>> intersection_relationship(const vector<pair<int, int>> &relationship1,
                                                 const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        if (include_pair(relationship2, v))
            result.push_back(v);

    return result;
}

// Находит разность двух множеств отношений (relationship1 - relationship2)
vector<pair<int, int>> different_relationship(const vector<pair<int, int>> &relationship1,
                                              const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        if (!include_pair(relationship2, v))
            result.push_back(v);

    return result;
}

// Находит симметричную разность двух множеств отношений
vector<pair<int, int>> symmetric_different_relationship(const vector<pair<int, int>> &relationship1,
                                                        const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        if (!include_pair(relationship2, v))
            result.push_back(v);

    for (auto v: relationship2)
        if (!include_pair(relationship1, v))
            result.push_back(v);

    return result;
}

// Находит дополнение отношений к универсальному множеству
vector<pair<int, int>> complement_relationship(const vector<pair<int, int>> &relationship,
                                               const vector<pair<int, int>> &universum) {
    vector<pair<int, int>> result;
    for (auto v: universum)
        if (!include_pair(relationship, v))
            result.push_back(v);
    return result;
}

// Возвращает обратные отношения (меняет местами элементы пар)
vector<pair<int, int>> reverse_relationship(const vector<pair<int, int>> &relationship) {
    vector<pair<int, int>> result;
    for (auto [fst, snd]: relationship) {
        pair reverse_pr = {snd, fst};
        result.push_back(reverse_pr);
    }

    return result;
}

// Композиция двух множеств отношений
vector<pair<int, int>> compose_relationship(const vector<pair<int, int>> &relationship1,
                                            const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (int x: m)
        for (int y: m)
            for (int z: m) {
                pair pr1 = {x, z};
                pair pr2 = {z, y};

                if (include_pair(relationship1, pr1) && include_pair(relationship2, pr2)) {
                    pair pr = {x, y};
                    result.push_back(pr);
                    break;
                }
            }

    result = dism(result);
    return result;
}

// Возводит отношения в степень (композиция отношений несколько раз)
vector<pair<int, int>> degree_relationship(const vector<pair<int, int>> &relationship, const int degree) {
    if (degree == 1) {
        return relationship;
    }

    if (degree > 1) {
        vector<pair<int, int>> result = copy_relationship(relationship);
        for (auto i = 0; i < degree; i++)
            result = compose_relationship(result, relationship);
        result = dism(result);
        return result;
    }

    vector<pair<int, int>> default_value;
    return default_value;
}

// Создает матрицу отношений на основе функции f
vector<vector<int>> create_matrix_relationship(bool (*f)(const int&, const int&)) {
    vector<vector<int>> matrix;

    for (auto _: m) {
        vector<int> row;
        for (auto _: m)
            row.push_back(0);
        matrix.push_back(row);
    }

    for (int x: m)
        for (int y: m)
            if (f(x,y))
                matrix[x-1][y-1] = 1;

    return matrix;
}

// Генерирует отношения в виде набора пар на основе функции f
vector<pair<int, int>> generate_relationship(bool (*f)(const int&, const int&)) {
    vector<pair<int, int>> result;
    for (int x: m)
        for (int y: m)
            if (f(x, y)) {
                pair pr = {x, y};
                result.push_back(pr);
            }
    return result;
}

int main() {
    const vector<pair<int, int>> u = generate_relationship(f);
    const vector<pair<int, int>> a = generate_relationship(f1);
    const vector<pair<int, int>> b = generate_relationship(f2);
    const vector<pair<int, int>> c = generate_relationship(f3);

    const vector<pair<int, int>> comlement_a = complement_relationship(a, u);
    const vector<pair<int, int>> square_c = degree_relationship(c, 2);
    const vector<pair<int, int>> compose_a_b = compose_relationship(a, b);
    const vector<pair<int, int>> union_compose_and_squre = union_relationship(compose_a_b, square_c);
    const vector<pair<int, int>> sym_diff_union_and_complement = symmetric_different_relationship(union_compose_and_squre, comlement_a);
    print_relationship(sym_diff_union_and_complement);

    return 0;
}
