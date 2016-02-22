#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

class Utils
{
    public:
        Utils();
        virtual ~Utils();

        static std::vector<std::string> findFilesIn(std::string pFolder);

    protected:
    private:
};

#endif // UTILS_H
