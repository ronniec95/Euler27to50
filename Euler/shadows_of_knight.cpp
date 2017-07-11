#include "stdafx.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <doctest/doctest.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename Out> void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) { *(result++) = item; }
}
template <typename Out> auto split(const std::string &s, char delim) -> Out {
    Out result;
    for (auto i = 0UL, start = 0UL; i < s.size(); i++) {
        if (s[i] == delim) {
            // Using emplace to directly construct the string 'in place', avoiding a temporary
            result.emplace_back(begin(s) + start, begin(s) + i);
            start = i + 1;
        }
        if (i == s.size() - 1) { result.emplace_back(begin(s) + start, end(s)); }
    }
    return result;
}
auto split_and_call(const std::string &s, char delim, std::function<void(const std::string &)> &f)
    -> void {
    for (auto i = 0UL, start = 0UL; i < s.size(); i++) {
        if (s[i] == delim) {
            f(std::string(std::begin(s) + start, std::begin(s) + i));
            start = i + 1;
        }
    }
}

/*2 2
3 1 5 4
5 1 2 8 9 3
0 1
1 3*/
void vla() {
    int n;
    cin >> n;
    cin.ignore();
    auto arr = vector<vector<int>>(n, vector<int>());
    for (auto i = 0; i < n; i++) {
        int count;
        cin >> count;
        copy_n(istream_iterator<int>(cin), count, back_inserter(arr[i]));
    }
}
void shadow_of_knights() {

    int W = 40; // width of the building.
    int H = 60; // height of the building.
    int N = 40; // maximum number of turns before game over.
    int x = 2;
    int y = 29;
    //                  x1 y1   x2     y2
    int search[][2] = {{0, 0}, {W - 1, H - 1}};
    // game loop
    while (1) {
        string bombDir =
            "UR"; // the direction of the bombs from batman's current location (U, UR, R, DR,
        if (bombDir.find('U') != string::npos) { search[1][1] = y - 1; }
        if (bombDir.find('D') != string::npos) { search[0][1] = y + 1; }
        if (bombDir.find('L') != string::npos) { search[1][0] = x - 1; }
        if (bombDir.find('R') != string::npos) { search[0][0] = x + 1; }
        x = search[0][0] + (search[1][0] - search[0][0]) / 2;
        y = search[0][1] + (search[1][1] - search[0][1]) / 2;
        fprintf(stderr, "x:%d y:%d search:%d %d %d %d", x, y, search[0][0], search[1][0],
                search[0][1], search[1][1]);
        printf("%d %d\n", x, y);
        break;
    }
}

class Person {
  public:
    Person(int id) : cur_id(id) {}
    virtual void putdata() = 0;
    virtual void getdata() {
        cin >> name;
        cin >> age;
    };

  protected:
    int    cur_id;
    int    age;
    string name;
};

class Professor : public Person {
  public:
    Professor() : Person(Professor::id_++) {}
    virtual void getdata() {
        Person::getdata();
        cin >> publications;
    }
    virtual void putdata() { printf("%s %d %d %d\n", name.c_str(), age, publications, cur_id); }

  private:
    int        publications;
    static int id_;
};
int Professor::id_ = 1;

class Student : public Person {
  public:
    Student() : Person(Student::id_++) {}
    virtual void getdata() {
        Person::getdata();
        for (int i = 0; i < 6; i++) cin >> marks[i];
    }
    virtual void putdata() {
        printf("%s %d %d %d\n", name.c_str(), age, accumulate(begin(marks), end(marks), 0), cur_id);
    }

  private:
    array<int, 6> marks;
    static int    id_;
};
int  Student::id_ = 1;
void string_stream() {
    // Complete this function
    string       str = "23,45,66";
    vector<int>  vec;
    stringstream ss(str);
    int          a;
    while (ss >> a) {
        if (ss.peek() == ',') ss.ignore();
        vec.push_back(a);
    }
}

int read_int(int N = INT_MIN) {
    if (N == INT_MIN) cin >> N;
    return N;
}

string read_line(istream &is) {
    string line;
    std::getline(is, line, '\n');
    return line;
}

#include <functional>
#include <regex>
#include <stack>
#include <unordered_map>

struct Tag {
    Tag(string name) : name_(name) {}
    string                                 name_;
    unordered_map<string, string>          attr_;
    unordered_map<string, shared_ptr<Tag>> children_;
};

void attribute_parser() {
    string s = "<tag1 value = \" HelloWorld \">\n"
               "<tag2 name = \" Name1 \">\n"
               "<tag3 name = \" Name3 \">\n"
               "</tag3>\n"
               "<tag4 name = \" Name4 \" text = \" Super \">\n"
               "<tag6 buzz = \" Buzz6 \">\n"
               "</tag6>\n"
               "</tag4>\n"
               "<tag5>\n"
               "</tag5>\n"
               "</tag2>\n"
               "</tag1>";
    string                 line;
    stringstream           ss(s);
    stack<shared_ptr<Tag>> tag_stack;
    auto                   current = make_shared<Tag>("");
    tag_stack.push(current);
    // Lex stream
    regex re_open_tag("<([\\w\\-]+)(.*)>");
    regex re_attribute("\\s*(\\w*) = \\\"(.*)\\\"");
    regex re_close_tag("</([\\w\\-]+)>");
    while (getline(ss, line, '\n')) {
        smatch sm_open;
        regex_match(line, sm_open, re_open_tag);
        if (sm_open.ready() && sm_open.size() > 1) {
            auto       tag        = make_shared<Tag>(sm_open[1]);
            const auto attributes = sm_open.size() > 2 ? sm_open[2].str() : string();
            auto       it = begin(attributes), it_end = begin(attributes);
            while (it != end(attributes)) {
                it_end = find(it, end(attributes), '"');
                it_end = find(it_end + 1, end(attributes), '"');
                smatch attr_match;
                regex_match(it, it_end + 1, attr_match, re_attribute);
                if (attr_match.ready() && attr_match.size() > 1) {
                    tag->attr_.insert(make_pair(attr_match[1].str(), attr_match[2].str()));
                }
                it = it_end + 1;
            }
            current->children_.insert(make_pair(tag->name_, tag));
            current = tag;
            tag_stack.push(current);
        }
        smatch sm_close;
        regex_match(line, sm_close, re_close_tag);
        if (sm_close.ready() && sm_close.size() > 1) {
            // Pure close tag, no attributes
            tag_stack.pop();
            current = tag_stack.top();
        }
    }
    // Query parser
    auto curr = current;
    // tag1.tag2~name
    //    tag1~name
    //    tag1~value
    //    tag1.tag2.tag3~name
    //    tag1.tag2.tag3~value
    //    tag1.tag2.tag4~text
    //    tag1.tag2.tag4.tag6~text
    //    tag1.tag2.tag4.tag6~buzz
    ;
    std::string query("tag1.tag2.tag5");
// const auto  tags = split<vector<string>>(query, '.');
// string      value;
// if (all_of(begin(tags), end(tags), [&curr, &value](const auto &str) {
//        const auto &it = curr->children_.find(str);
//        if (it == curr->children_.end()) {
//            const auto attr = split<vector<string>>(str, '~');
//            if (attr.size() == 2) {
//                const auto &it = curr->children_.find(attr[0]);
//                if (it != curr->children_.end()) {
//                    curr           = it->second;
//                    const auto &it = curr->attr_.find(attr[1]);
//                    if (it == curr->attr_.end())
//                        return false;
//                    else {
//                        value = it->second;
//                        return true;
//                    }
//                }
//            }
//        } else
//            curr = it->second;
//        return true;
//    })) {
//    printf("%s\n", value.c_str());
//} else {
//    printf("Not Found!\n");
//}
#if 0
    bool   found = true;
    string path;
    for (auto ch : query) {
        if (ch == '.' || ch == '~') {
            const auto &it = curr->children_.find(path);
            if (it != curr->children_.end())
                curr = it->second;
            else {
                printf("Not Found!\n");
                found = false;
            }
            path.clear();
            continue;
        }
        path += ch;
    }
    const auto &it = curr->children_.find(path);
    if (it != curr->children_.end())
        curr = it->second;
    if (found && !path.empty()) {
        const auto &it = curr->attr_.find(path);
        if (it != curr->attr_.end())
            printf("%s\n", it->second.c_str());
        else
            printf("Not Found!\n");
    } else
        printf("Not Found!\n");
#endif
}

static bool exists(int ints[], int size, int k) {
    vector<int> v(&ints[0], &ints[0] + size);
    std::sort(begin(v), end(v), std::less<int>());
    binary_search(begin(v), end(v), k);
    return find(begin(v), end(v), k) != std::end(v);
}

void int_check() {
    int ints[] = {-9, 14, 37, 102};
    exists(ints, 4, 102);
}

void deque_max() {
    int arr[] = {9541, 9249, 2291, 1094, 768, 6517, 4804, 8510, 4443, 5243, 3382, 6046, 4102, 6210};
    /*, 4102, 6210,
                 2152, 376,  9220, 3645, 3689, 4182, 4770, 9653, 1054, 4208, 9714, 84,   8825, 392,
                 5522, 296,  5417, 2290, 1735, 3413, 7308, 2043, 2812, 4532, 3531, 3060, 8257, 682,
                 6454, 870,  7003, 4380, 9492, 1430, 6010, 2389, 3501, 1516, 4246, 2434, 3963, 2541,
                 6468, 8527, 2213, 2708, 7436, 4909, 398,  3076, 3889, 909,  9640, 8736, 7566, 5013,
                 80,   5188, 9445, 6889, 149,  1823, 8716, 7403, 5800, 4648, 5419, 4239, 8937, 9342,
                 8490, 269,  8475, 1424, 3810, 7761, 8259, 3254, 1782, 8818, 3762, 1082, 7697, 9595,
                 7972, 9515, 6562, 9772, 9985, 5673, 8088, 2580, 415,  3891, 7774, 1942, 3841, 9597,
                 3328, 5529, 1248, 628,  9183, 3055, 1621, 6537, 1598, 5374, 4068, 8262, 9357, 2910,
                 8805, 427,  6724, 4558, 4777, 435,  3764, 4044, 1982, 2285, 5343, 5878, 4950, 8759,
                 2740, 9311, 8707, 4060, 3570, 6958, 8757, 1069, 4751, 7915, 5046, 8200, 797,  6939,
                 1321, 787,  441,  7234, 253,  3474, 3158, 5030, 3331, 1996, 4334, 1319, 584,  4339,
                 8204, 3052, 3583, 5264, 2816, 316,  9857, 7658, 7380, 7607, 5073, 5570, 154,  180,
                 8488, 1941, 6907, 9859, 6570, 1573, 4416, 4724, 3523, 222,  9370, 498,  1354, 9254,
                 6338, 9141, 5181, 5582, 8943, 9393, 4671, 27,   6288, 8393, 9022, 1229, 2377, 519,
                 1841, 4997, 6254, 2529, 7699, 5928, 6379, 8567, 3739, 5056, 1262, 1984, 2248, 2054,
                 3939, 8118, 5856, 1747, 9875, 1287, 590,  461,  407,  9903, 2526, 4719, 7201, 6894,
                 9601, 1277, 6368, 5202, 2197, 3775, 8954, 9108, 1869, 458,  9421, 4250, 5302, 3569,
                 1919, 1374, 9523, 3139, 521,  3572, 3570, 1349, 370,  9884, 858,  2587, 73,   8768,
                 2727, 3066, 4043, 1065, 7733, 9112, 9511, 9067, 6271, 8677, 7170, 1509, 8740, 2969,
                 8746, 7176, 7687, 4229, 9972, 3525, 1098, 3706, 4612, 5823, 8912, 8018, 6008, 3287,
                 8818, 1937, 727,  8458, 531,  8290, 7816, 4460, 2711, 2867, 8124, 1201, 9934, 4938,
                 1948, 8230, 7138, 9043, 6710, 2624, 2969, 9529, 9689, 6982, 4542, 7235, 1620, 7314,
                 5268, 3899, 4024, 6893, 2535, 9408, 8591, 1927, 5198, 8525, 4598, 1827, 3122, 8058,
                 6987, 9428, 128,  4906, 616,  613,  9399, 1722, 3704, 9845, 8358};
    */ // int arr[] = {3, 4, 5, 8, 6, 4, 2, 1, 9, 9, 2, 9, 5, 3, 2, 10};
    // 4,4,5,5,9,9,9,9,5,6,6,6
    int        n = sizeof(arr) / sizeof(arr[0]);
    int        k = 10;
    deque<int> d;
    // Init deque
    // Kadane algorithm with a deque holding the positions of the best
    // Remove everything to the left of the newest number lower than it
    // Position of max number is stored until it falls off window
    for (int i = 0; i < k; i++) {
        while (!d.empty() && arr[i] > arr[d.front()]) d.pop_front();
        while (!d.empty() && arr[i] > arr[d.back()]) d.pop_back();
        d.push_back(i);
    }
    for (int i = k; i < n; i++) {
        printf("%d ", arr[d.front()]);
        if (d.front() - i + k == 0) d.pop_front();
        while (!d.empty() && arr[i] > arr[d.front()]) d.pop_front();
        while (!d.empty() && arr[i] > arr[d.back()]) d.pop_back();
        d.push_back(i);
    }
    printf("%d\n", arr[d.front()]);
}

void read_double() {

    vector<int> arr{1, 2, 3, 4, 45, 6};

    const auto count = arr.size();
    const auto pos   = accumulate(begin(arr), end(arr), 0,
                                [](auto acc, const auto n) { return (n > 0) ? ++acc : acc; });
    const auto neg   = accumulate(begin(arr), end(arr), 0,
                                [](auto acc, const auto n) { return n < 0 ? ++acc : acc; });
    const auto zeros = accumulate(begin(arr), end(arr), 0,
                                  [](auto acc, const auto n) { return n == 0 ? acc : acc; });
    printf("%d %d %d %d\n", pos, neg, zeros, count);

    printf("%.6lf\n%.6lf\n%.6lf\n", double(pos) / count, double(neg) / count,
           (double)zeros / count);
}

#include <iomanip>

void stair_case() {
    auto n = int(6);
    for (auto row = 0; row < n; row++) {
        // Write n-row-1 spaces
        for (int i = 0; i < n - row - 1; i++) printf(".");
        // Write row+1 #
        for (int i = 0; i < row + 1; i++) printf("#");
        printf("\n");
    }

    stringstream ss("07:05:45PM"), output;
    std::tm      tm;
    ss >> std::get_time(&tm, "%I:%M:%S%p");
    output << std::put_time(&tm, "%H:%M:%S");
}

void min_dist_pair() {
    array<int, 12> arr{35, 5, 2, -7, -86, 52, 75, 99, 5, 86, 43, 74};
    sort(begin(arr), end(arr));
    adjacent_difference(begin(arr), end(arr), begin(arr));
    auto min_e = min_element(begin(arr), end(arr));
    printf("%d", *min_e);
}

void bm_findunique() {
    array<int, 9> arr{4, 9, 95, 93, 57, 4, 57, 93, 9};
    int           ans = 0;
    for (int i = 0; i < arr.size(); i++) { ans = arr[i] ^ ans; }
    printf("%d", ans);
}

void max_hourglass() {
    // int arr[] = {1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
    //             0, 0, 2, 4, 4, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 2, 4, 0};

    int arr[] = {3,  7, -3, 0, 1, 8, 1, -4, -7, -8, -6, 5, -8, 1,  3, 3, 5, 7,
                 -2, 4, 3,  1, 2, 7, 2, 4,  -5, 1,  8,  4, 5,  -7, 6, 5, 2, 8};

    const auto h_width = 3;
    static_assert(h_width % 2 == 1, "h_width must be an odd number for an hourglass");
    const auto x_width = 6, y_height = 6;

    const auto start      = x_width + (h_width - 1) / 2;
    const auto end        = x_width * (y_height - 1) - (h_width - 1) / 2;
    int        max_val    = numeric_limits<int>::min();
    const auto bar_offset = (h_width - 1) / 2;

    for (int i = start; i < end; i++) {
        if ((i + bar_offset) % x_width == 0) {
            i += bar_offset * 2;
            continue;
        }
        const auto prev_row = i - x_width;
        const auto next_row = i + x_width;

        const auto top_row = accumulate(begin(arr) + prev_row - bar_offset,
                                        begin(arr) + prev_row + bar_offset + 1, 0);
        const auto bot_row = accumulate(begin(arr) + next_row - bar_offset,
                                        begin(arr) + next_row + bar_offset + 1, 0);
        const auto sum     = arr[i] + top_row + bot_row;

        if (sum > max_val) max_val = sum;
    }
    printf("%d", max_val);
}
TEST_CASE("Shadow_Knights") { shadow_of_knights(); }
TEST_CASE("Vla") { /*vla();*/
}
TEST_CASE("Stringstream") { string_stream(); }
TEST_CASE("AttributeParser") { attribute_parser(); }
TEST_CASE("int check") { int_check(); }
TEST_CASE("deque ") { deque_max(); }
TEST_CASE("read_double") { read_double(); }
TEST_CASE("stair_case") { stair_case(); }
TEST_CASE("min_dist_pair") { min_dist_pair(); }
TEST_CASE("bm_findunique") { bm_findunique(); }
TEST_CASE("max_hourglass") { max_hourglass(); }