#include <iostream>
#include <vector>

using namespace std;

const int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

bool f(const int &x, const int &y) {
    return 1>0;
}

bool f1(const int &x, const int &y) {
    return x > y || y > 7;
}

bool f2(const int &x, const int &y) {
    return (10*x + y) % 3 == 0;
}

bool f3(const int &x, const int &y) {
    return x % 2 == 0 && y % 2 != 0;
}


void print_relationship(const vector<pair<int, int>> &relationship) {
    int new_line = 0;
    for (const auto [fst, snd]: relationship)
        if (new_line < 3) {
            printf("(%2.d,%2.d)  |  ", fst, snd);
            new_line++;
        } else {
            new_line = 0;
            cout << endl;
        }
    cout << endl << endl;
}


bool include_pair(const vector<pair<int, int>> &relationship, const pair<int, int> &pr) {
    for (const auto [fst, snd]: relationship)
        if (fst == pr.first && snd == pr.second)
            return true;
    return false;
}


bool include_value(const vector<pair<int, int>> &relationship, const int val) {
    for (const auto [fst, snd]: relationship)
        if (fst == val || snd == val)
            return true;
    return false;
}


bool relationship_not_strictly_include(const vector<pair<int, int>> &relationship1,
                                       const vector<pair<int, int>> &relationship2) {
    for (auto pr: relationship1)
        if (!include_pair(relationship2, pr))
            return false;
    return true;
}


vector<pair<int, int>> dism(const vector<pair<int, int>> &relationship) {
    vector<pair<int, int>> result;
    for (auto v: relationship)
        if (!include_pair(result, v))
            result.push_back(v);
    return result;
}


bool relationship_equal(const vector<pair<int, int>> &relationship1,
                        const vector<pair<int, int>> &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) && \
         relationship_not_strictly_include(relationship2, relationship1))
        return true;
    return false;
}


bool relationship_strictly_include(const vector<pair<int, int>> &relationship1,
                                   const vector<pair<int, int>> &relationship2) {
    if (relationship_not_strictly_include(relationship1, relationship2) && \
        !relationship_equal(relationship1, relationship2))
            return true;
    return false;
}


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


vector<pair<int, int>> intersection_relationship(const vector<pair<int, int>> &relationship1,
                                                 const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        if (include_pair(relationship2, v))
            result.push_back(v);

    return result;
}


vector<pair<int, int>> different_relationship(const vector<pair<int, int>> &relationship1,
                                              const vector<pair<int, int>> &relationship2) {
    vector<pair<int, int>> result;
    for (auto v: relationship1)
        if (!include_pair(relationship2, v))
            result.push_back(v);

    return result;
}


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


vector<pair<int, int>> complement_relationship(const vector<pair<int, int>> &relationship,
                                               const vector<pair<int, int>> &universum) {
    vector<pair<int, int>> result;
    for (auto v: universum)
        if (!include_pair(relationship, v))
            result.push_back(v);
    return result;
}


vector<pair<int, int>> reverse_relationship(const vector<pair<int, int>> &relationship) {
    vector<pair<int, int>> result;
    for (auto v: relationship) {
        pair reverse_pr = {v.second, v.first};
        if (include_pair(relationship, reverse_pr))
            result.push_back(v);
    }

    return result;
}


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
                }
            }

    result = dism(result);
    return result;
}


vector<pair<int, int>> degree_relationship(vector<pair<int, int>> relationship, const int degree) {
    if (degree == 1) {
        return relationship;
    }

    if (degree > 1) {
        for (auto i = 0; i < degree; i++)
            relationship = compose_relationship(relationship, relationship);
        relationship = dism(relationship);
        return relationship;
    }

    vector<pair<int, int>> default_value;
    return default_value;
}


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

    print_relationship(a);

    const vector<pair<int, int>> comlement_a = complement_relationship(a, u);
    const vector<pair<int, int>> square_c = degree_relationship(c, 2);
    const vector<pair<int, int>> compose_a_b = compose_relationship(a, b);
    const vector<pair<int, int>> union_compose_and_squre = union_relationship(compose_a_b, square_c);
    const vector<pair<int, int>> sym_diff_union_and_complement = symmetric_different_relationship(union_compose_and_squre, comlement_a);
    print_relationship(sym_diff_union_and_complement);

    return 0;
}
