#include <lizy1/kurisu/exception.h>
#include <sstream>


using namespace lizy1::kurisu;


int main()
{
    /// exception - KurisuException
    {
        using T = KurisuException;
        std::string str;
        {
            std::ostringstream os;
            T t("This is KurisuException");
            dump(os, t);
            str = os.str();
        }
        {
            std::istringstream is(str);
            T t("");
            load(is, t);
        }
        {
            std::istringstream is(str);
            T t = construct<T>(is);
        }
    }
    /// exception - LoadException
    {
        using T = LoadException;
        std::string str;
        {
            std::ostringstream os;
            T t("This is LoadException");
            dump(os, t);
            str = os.str();
        }
        {
            std::istringstream is(str);
            T t("");
            load(is, t);
        }
        {
            std::istringstream is(str);
            T t = construct<T>(is);
        }
    }
    /// exception - DumpException
    {
        using T = DumpException;
        std::string str;
        {
            std::ostringstream os;
            T t("This is DumpException");
            dump(os, t);
            str = os.str();
        }
        {
            std::istringstream is(str);
            T t("");
            load(is, t);
        }
        {
            std::istringstream is(str);
            T t = construct<T>(is);
        }
    }
    return 0;
}
