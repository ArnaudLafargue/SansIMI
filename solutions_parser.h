#pragma once
#include "solution.h"


struct solutions{
    solution solutions_list[40];
    int solutions_number;
};

solutions solutions_parser(string path);
