#include <iostream>
#include <vector>

using namespace std;

const int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Функция всегда возвращает true
bool f(const int &x, const int &y) {
    return 1 > 0;
}

// Функция возвращает true, если x > y или y > 7
bool f1(const int &x, const int &y) {
    return x >y || y > 7;
}

// Функция возвращает true, если число, составленное из 10*x + y, делится на 3
bool f2(const int &x, const int &y) {
    return (10 * x + y) % 3 == 0;
}

// Функция возвращает true, если x четное, а y нечетное
bool f3(const int &x, const int &y) {
    return x%2==0 && y%2!=0;
}


// Выводит пары отношений на экран
void print_relationship(const vector<pair<int, int> > &relationship) {
    for (const auto [fst, snd]: relationship) {
        printf("(%d, %d) \n", fst, snd);
    }
    cout << endl << endl;
}

// Проверяет, содержится ли пара pr в отношениях relationship
bool include_pair(const vector<pair<int, int> > &relationship, const pair<int, int> &pr) {
    for (const auto [fst, snd]: relationship)
        if (fst == pr.first && snd == pr.second)
            return true;
    return false;
}

// Проверяет, содержится ли значение val как первый или второй элемент в отношениях relationship
bool include_value(const vector<pair<int, int> > &relationship, const int val) {
    for (const auto [fst, snd]: relationship)
        if (fst == val || snd == val)
            return true;
    return false;
}

// Копирует отношения relationship в новый вектор
vector<pair<int, int> > copy_relationship(const vector<pair<int, int> > &relationship) {
    vector<pair<int, int> > result;
    for (auto [fst, snd]: relationship) {
        pair pr = {fst, snd};
        result.push_back(pr);
    }

    return result;
}

// Проверяет, что отношения relationship1 нестрого содержатся в relationship2
bool relationship_not_strictly_include(const vector<pair<int, int> > &relationship1,
                                       const vector<pair<int, int> > &relationship2) {
    for (auto pr: relationship1)
        if (!include_pair(relationship2, pr))
            return false;
    return true;
}

// Удаляет дубликаты пар в отношениях
vector<pair<int, int> > dism(const vector<pair<int, int> > &relationship) {
    vector<pair<int, int> > result;
    for (auto v: relationship)
        if (!include_pair(result, v))
            result.push_back(v);
    return result;
}

// Проверяет, равны ли два отношения
bool relationship_equal(const vector<pair<int, int> > &relationship1,
                        const vector<pair<int, int> > &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) &&
        relationship_not_strictly_include(relationship2, relationship1))
        return true;
    return false;
}

// Проверяет, содержатся ли отношения relationship1 строго в relationship2
bool relationship_strictly_include(const vector<pair<int, int> > &relationship1,
                                   const vector<pair<int, int> > &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) &&
        !relationship_equal(relationship1, relationship2))
        return true;
    return false;
}

// Объединяет два множества отношений
vector<pair<int, int> > union_relationship(const vector<pair<int, int> > &relationship1,
                                           const vector<pair<int, int> > &relationship2) {
    vector<pair<int, int> > result;
    for (auto v: relationship1)
        result.push_back(v);

    for (auto v: relationship2)
        if (!include_pair(relationship1, v))
            result.push_back(v);

    return result;
}

// Находит пересечение двух множеств отношений
vector<pair<int, int> > intersection_relationship(const vector<pair<int, int> > &relationship1,
                                                  const vector<pair<int, int> > &relationship2) {
    vector<pair<int, int> > result;
    for (auto v: relationship1)
        if (include_pair(relationship2, v))
            result.push_back(v);

    return result;
}

// Находит разность двух множеств отношений (relationship1 - relationship2)
vector<pair<int, int> > different_relationship(const vector<pair<int, int> > &relationship1,
                                               const vector<pair<int, int> > &relationship2) {
    vector<pair<int, int> > result;
    for (auto v: relationship1)
        if (!include_pair(relationship2, v))
            result.push_back(v);

    return result;
}

// Находит симметричную разность двух множеств отношений
vector<pair<int, int> > symmetric_different_relationship(const vector<pair<int, int> > &relationship1,
                                                         const vector<pair<int, int> > &relationship2) {
    vector<pair<int, int> > result;
    for (auto v: relationship1)
        if (!include_pair(relationship2, v))
            result.push_back(v);

    for (auto v: relationship2)
        if (!include_pair(relationship1, v))
            result.push_back(v);

    return result;
}

// Находит дополнение отношений к универсальному множеству
vector<pair<int, int> > complement_relationship(const vector<pair<int, int> > &relationship,
                                                const vector<pair<int, int> > &universum) {
    vector<pair<int, int> > result;
    for (auto v: universum)
        if (!include_pair(relationship, v))
            result.push_back(v);
    return result;
}

// Возвращает обратные отношения (меняет местами элементы пар)
vector<pair<int, int> > reverse_relationship(const vector<pair<int, int> > &relationship) {
    vector<pair<int, int> > result;
    for (auto [fst, snd]: relationship) {
        pair reverse_pr = {snd, fst};
        result.push_back(reverse_pr);
    }

    return result;
}

// Композиция двух множеств отношений
vector<pair<int, int> > compose_relationship(const vector<pair<int, int> > &relationship1,
                                             const vector<pair<int, int> > &relationship2) {
    vector<pair<int, int> > result;
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
vector<pair<int, int> > degree_relationship(const vector<pair<int, int> > &relationship, const int degree) {
    if (degree == 1) {
        return relationship;
    }

    if (degree > 1) {
        vector<pair<int, int> > result = copy_relationship(relationship);
        for (auto i = 0; i < degree; i++)
            result = compose_relationship(result, relationship);
        result = dism(result);
        return result;
    }

    vector<pair<int, int> > default_value;
    return default_value;
}

// Создает матрицу отношений на основе функции f
vector<vector<int> > create_matrix_relationship(bool (*f)(const int &, const int &)) {
    vector<vector<int> > matrix;

    for (auto _: m) {
        vector<int> row;
        for (auto _: m)
            row.push_back(0);
        matrix.push_back(row);
    }

    for (int x: m)
        for (int y: m)
            if (f(x, y))
                matrix[x - 1][y - 1] = 1;

    return matrix;
}

// Генерирует отношения в виде набора пар на основе функции f
vector<pair<int, int> > generate_relationship(bool (*f)(const int &, const int &)) {
    vector<pair<int, int> > result;
    for (int x: m)
        for (int y: m)
            if (f(x, y)) {
                pair pr = {x, y};
                result.push_back(pr);
            }
    return result;
}


bool is_relationship_reflexive(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (int i: m) {
        pair pr = {i, i};
        if (!include_pair(relationship, pr)) {
            if (print_report)
                printf("Отношение не рефлексивно потому, что пара (%d, %d) не принадлежит отношению \n",\
                       pr.first, pr.second);
            return false;
        }
    }

    if (print_report)
        printf("Отношение рефлексивно\n");
    return true;
}


bool is_relationship_antireflexive(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (int i: m) {
        pair pr = {i, i};
        if (include_pair(relationship, pr)) {
            if (print_report)
                printf("Отношение не антирефлексивно потому, что пара (%d, %d) принадлежит отношению \n",\
                       pr.first, pr.second);
            return false;
        }
    }

    if (print_report)
        printf("Отношение антирефлексивно\n");
    return true;
}


bool is_relationship_symmetric(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (int i: m) {
        for (int j: m) {
            if (i ==j)
                continue;

            pair pr1 = {i, j};
            pair pr2 = {j, i};
            if (include_pair(relationship, pr1) && !include_pair(relationship, pr2)) {
                if (print_report)
                    printf("Отношение не симметрично потому, что пара (%d, %d) принадлежит отношению, а пара (%d, %d) - не принадлежит \n",\
                           pr1.first, pr1.second, pr2.first, pr2.second);
                return false;
            }
        }
    }

    if (print_report)
        printf("Отношение симметрично\n");
    return true;
}


bool is_relationship_antisymmetric(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (int i: m) {
        for (int j: m) {
            if (i == j)
                continue;

            pair pr1 = {i, j};
            pair pr2 = {j, i};
            if (include_pair(relationship, pr1) && include_pair(relationship, pr2)) {
                if (print_report)
                    printf("Отношение не антисимметрично потому, что пара (%d, %d) принадлежит отношению и пара (%d, %d) тоже принадлежит отношению \n",\
                           pr1.first, pr1.second, pr2.first, pr2.second);
                return false;
            }
        }
    }

    if (print_report)
        printf("Отношение антисимметрично\n");
    return true;
}


bool is_relationship_transitive(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (const auto &[i, j1] : relationship) {
        for (const auto &[j2, k] : relationship) {
            if (j1 == j2) {
                if (!include_pair(relationship, {i, k})) {
                    if (print_report)
                        printf("Отношение не транзитивно потому, что пара (%d, %d) принадлежит отношению, пара (%d, %d) принадлежит отношению, а пара (%d, %d) не принадлежит отношению \n", i, j1, j2, k, i, k);
                    return false;
                }
            }
        }
    }
    if (print_report)
        printf("Отношение транзитивно\n");
    return true;
}


bool is_relationship_antitransitive(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (const auto &[i, j1] : relationship) {
        for (const auto &[j2, k] : relationship) {
            if (j1 == j2) {
                if (include_pair(relationship, {i, k})) {
                    if (print_report)
                        printf("Отношение не антитранзитивно потому, что пара (%d, %d) принадлежит отношению, пара (%d, %d) принадлежит отношению и пара (%d, %d) тоже принадлжеит отношению\n", i, j1, j2, k, i, k);
                    return false;
                }
            }
        }
    }
    if (print_report)
        printf("Отношение антитранзитивно\n");
    return true;
}



bool is_relationship_complete(const vector<pair<int, int>> &relationship, const bool print_report) {
    for (int i: m) {
        for (int j: m) {
            if (i == j)
                continue;

            pair pr1 = {i, j};
            pair pr2 = {j, i};
            if (!include_pair(relationship, pr1) && !include_pair(relationship, pr2)) {
                if (print_report)
                    printf("Отношение не полно потому, что в нём нет пары (%d, %d) и нет пары (%d, %d) \n", \
                        pr1.first, pr1.second, pr2.first, pr2.second);
                return false;
            }
        }
    }

    if (print_report)
        printf("Отношение полно\n");
    return true;
}


void print_derived_properties_relationship(const vector<pair<int, int>> &relationship) {
    constexpr bool print_error = false;
    const bool tolerance = is_relationship_reflexive(relationship, print_error) && is_relationship_symmetric(relationship, print_error);
    const bool equivalence = is_relationship_reflexive(relationship, print_error) \
    && is_relationship_symmetric(relationship, print_error) \
    && is_relationship_transitive(relationship, print_error);
    const bool order = is_relationship_antisymmetric(relationship, print_error) && is_relationship_transitive(relationship, print_error);
    const bool non_strict_order = order && is_relationship_reflexive(relationship, print_error);
    const bool strict_order = order && is_relationship_antireflexive(relationship, print_error);
    const bool linear_order = order && is_relationship_complete(relationship, print_error);
    const bool non_strict_linear_order = non_strict_order && is_relationship_complete(relationship, print_error);
    const bool strict_linear_order = strict_order && is_relationship_complete(relationship, print_error);

    printf("Обладает ли отношение свойством: \n");
    printf("Толерантности: %d \n", tolerance);
    printf("Эквивалентности: %d \n", equivalence); //
    printf("Порядка: %d \n", order);
    printf("Нестрого порядка: %d \n", non_strict_order);
    printf("Строгого порядка: %d \n", strict_order);
    printf("Линейного порядка: %d \n", linear_order);
    printf("Нестрогого линейного порядка: %d \n", non_strict_linear_order);
    printf("Строгого линейного порядка: %d \n", strict_linear_order);
}


int main() {
    const vector<pair<int, int> > u = generate_relationship(f);
    const vector<pair<int, int> > a = generate_relationship(f1);
    const vector<pair<int, int> > b = generate_relationship(f2);
    const vector<pair<int, int> > c = generate_relationship(f3);

    // const vector<pair<int, int> > comlement_a = complement_relationship(a, u);
    // const vector<pair<int, int> > square_c = degree_relationship(c, 2);
    // const vector<pair<int, int> > compose_a_b = compose_relationship(a, b);
    // const vector<pair<int, int> > union_compose_and_squre = union_relationship(compose_a_b, square_c);
    // const vector<pair<int, int> > sym_diff_union_and_complement = symmetric_different_relationship(union_compose_and_squre, comlement_a);
    // print_relationship(sym_diff_union_and_complement);

    constexpr bool print_report = true;

    printf("a\n");
    cout << is_relationship_reflexive(a, print_report) << endl;
    cout << is_relationship_antireflexive(a, print_report) << endl;
    cout << is_relationship_symmetric(a, print_report) << endl;
    cout << is_relationship_antisymmetric(a, print_report) << endl;
    cout << is_relationship_transitive(a, print_report) << endl;
    cout << is_relationship_antitransitive(a, print_report) << endl;
    cout << is_relationship_complete(a, print_report) << endl;
    cout << endl;
    print_derived_properties_relationship(a);
    cout << endl << endl;

    printf("b\n");
    cout << is_relationship_reflexive(b, print_report) << endl;
    cout << is_relationship_antireflexive(b, print_report) << endl;
    cout << is_relationship_symmetric(b, print_report) << endl;
    cout << is_relationship_antisymmetric(b, print_report) << endl;
    cout << is_relationship_transitive(b, print_report) << endl;
    cout << is_relationship_antitransitive(b, print_report) << endl;
    cout << is_relationship_complete(b, print_report) << endl;
    cout << endl;
    print_derived_properties_relationship(b);
    cout << endl << endl;

    printf("c\n");
    cout << is_relationship_reflexive(c, print_report) << endl;
    cout << is_relationship_antireflexive(c, print_report) << endl;
    cout << is_relationship_symmetric(c, print_report) << endl;
    cout << is_relationship_antisymmetric(c, print_report) << endl;
    cout << is_relationship_transitive(c, print_report) << endl;
    cout << is_relationship_antitransitive(c, print_report) << endl;
    cout << is_relationship_complete(c, print_report) << endl;
    cout << endl;
    print_derived_properties_relationship(c);
    cout << endl << endl;
    return 0;
}
