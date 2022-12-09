#include <algorithm>
#include <iostream>
#include <string>

class MyString
{
public:
    template<typename... Args>
    MyString(Args&&... args) : m_str(std::forward<Args>(args)...) { }

    const char* c_str() const & noexcept { return m_str.c_str(); }
    void c_str() const && = delete;

private:
    std::string m_str;
};

namespace MyStringComparison::CaseInsensitive
{
    bool operator<(const MyString& a, const MyString& b)
    {
        std::string lowerA(a.c_str());
        std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), [](unsigned char c){ return std::tolower(c); });
        std::string lowerB(b.c_str());
        std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), [](unsigned char c){ return std::tolower(c); });
        const bool result =  lowerA < lowerB;
        std::cout << __PRETTY_FUNCTION__ << ": '" << lowerA << "' < '" << lowerB << "' = " << result << std::endl;
        return result;
    }
    bool operator>(const MyString& a, const MyString& b)
    {
        return b < a;
    }
}

namespace MyStringComparison::CaseSensitive
{
    bool operator<(const MyString& a, const MyString& b)
    {
        std::string lowerA(a.c_str());
        std::string lowerB(b.c_str());
        const bool result =  lowerA < lowerB;
        std::cout << __PRETTY_FUNCTION__ << ": '" << lowerA << "' < '" << lowerB << "' = " << result << std::endl;
        return result;
    }
    bool operator>(const MyString& a, const MyString& b)
    {
        return b < a;
    }
}

int main()
{
    const MyString r("Resting");
    const MyString s("Testing");
    const MyString t("TestING");

    {
        using namespace MyStringComparison::CaseSensitive;
        r < s;
        r > s;

        r < t;
        r > t;

        s < t;
        s > t;
    }
    {
        using namespace MyStringComparison::CaseInsensitive;
        r < s;
        r > s;

        r < t;
        r > t;

        s < t;
        s > t;
    }

    return 0;
}

