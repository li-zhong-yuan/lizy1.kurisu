#include <lizy1/kurisu.h>
#include <lizy1/kurisu/std/array>
#include <lizy1/kurisu/std/deque>
#include <lizy1/kurisu/std/forward_list>
#include <lizy1/kurisu/std/list>
#include <lizy1/kurisu/std/map>
#include <lizy1/kurisu/std/set>
#include <lizy1/kurisu/std/string>
#include <lizy1/kurisu/std/tuple>
#include <lizy1/kurisu/std/unordered_map>
#include <lizy1/kurisu/std/unordered_set>
#include <lizy1/kurisu/std/utility>
#include <lizy1/kurisu/std/vector>
#include <lizy1/kurisu/std/stdexcept>
#include <utility>
#include <memory>
#include <sstream>


using namespace lizy1::kurisu;


class Obj1
{
public:
    int i;
    Obj1(int i) :i(i) {}
};


struct Obj2
{
    int i;
    Obj2()            :i(0) {}
    Obj2(int i)       :i(i) {}
    // Obj2(Obj2 const&) = delete;
};


template<> struct lizy1::kurisu::Case<Obj1>
{
    static void __load__(std::istream &is, Obj1      & v) { load(is, v.i); }
    static void __dump__(std::ostream &os, Obj1 const& v) { dump(os, v.i); }
    static Obj1 __construct__(std::istream &is) { Obj1 ret(0); __load__(is, ret); return ret; }
};


template<> struct lizy1::kurisu::Case<Obj2>
{
    static void __load__(std::istream &is, Obj2      & v) { load(is, v.i); }
    static void __dump__(std::ostream &os, Obj2 const& v) { dump(os, v.i); }
};


int main()
{
    /// pair
    {
        using T = std::pair<float, Obj1>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 3.0f, -5 };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = { 1.0f, -3 };
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// tuple - Obj1
    {
        using T = std::tuple<float, Obj1, float, Obj1>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 3.0f, -5, 4.0f, -9 };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = { 1.0f, -2, 5.0f, -9122 };
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// tuple - Obj2
    {
        using T = std::tuple<float, Obj2, float, Obj2>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 3.0f, -5, 4.0f, -9 };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = { 1.0f, -2, 5.0f, -9122 };
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// tuple - Empty
    {
        using T = std::tuple<>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t{};
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t{};
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// tuple - no_load
    {
        using T = std::tuple<float, const double, bool>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 3.0f, 4.0f, true };
            dump(*os, t);
            str = os->str();
        }
        {
            static_assert(!IsLoadable<T>::value, "");
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// tuple - no_construct
    {
        using T = std::tuple<float &&, double, bool>;
        std::string str;
        float f = 7.0f;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { std::move(f), 4.0f, true };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            float f = 999.0f;
            T t = { std::move(f), 888.0f, false };
            load(*is, t);
        }
        {
            static_assert(!IsConstructible<T>::value, "");
        }
    }
    /// tuple - no_load & no_construct
    {
        using T = std::tuple<float const&, double, bool>;
        std::string str;
        float f = 7.0f;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { std::move(f), 4.0f, true };
            dump(*os, t);
            str = os->str();
        }
        {
            static_assert(!IsLoadable<T>::value, "");
        }
        {
            static_assert(!IsConstructible<T>::value, "");
        }
    }
    /// string
    {
        using T = std::string;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = "aabbcc";
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// wstring
    {
        using T = std::wstring;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = L"aabbcc";
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// dequeue<string>
    {
        using T = std::deque<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// vector<string>
    {
        using T = std::vector<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// set<string>
    {
        using T = std::set<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// multiset<string>
    {
        using T = std::multiset<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef", "ab", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// map<string, const string>
    {
        using T = std::map<std::string, const std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { {"ab", "cd"}, {"ef", "gh"} };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// unordered_set<string>
    {
        using T = std::unordered_set<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// unordered_map<string, const string>
    {
        using T = std::unordered_map<std::string, const std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { {"ab", "cd"}, {"ef", "gh"} };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// list<string>
    {
        using T = std::list<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// forward_list<string>
    {
        using T = std::forward_list<std::string>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { "ab", "cd", "ef" };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// array - Obj1
    {
        using T = std::array<Obj1, 3>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 1, 2, 3 };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = { 0, 0, 0 };
            load(*is, t);
        }
        {
            static_assert(!IsConstructible<T>::value, "");
        }
    }
    /// array - Obj2
    {
        using T = std::array<Obj2, 3>;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t = { 1, 2, 3 };
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = { 0, 0, 0 };
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// exception - std::exception
    {
        using T = std::exception;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t;
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t;
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    /// exception - std::logic_error
    {
        using T = std::logic_error;
        std::string str;
        {
            std::unique_ptr<std::ostringstream> os(new std::ostringstream());
            T t("This is logic_error");
            dump(*os, t);
            str = os->str();
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t("");
            load(*is, t);
        }
        {
            std::unique_ptr<std::istringstream> is(new std::istringstream(str));
            T t = construct<T>(*is);
        }
    }
    return 0;
}
