#ifndef COMMON_HPP
#define COMMON_HPP

#include "nanobench/nanobench.h"

void gen(std::string const& typeName, char const* mustacheTemplate,
         ankerl::nanobench::Bench const& bench) {

    std::ofstream templateOut("mustache.template." + typeName);
    templateOut << mustacheTemplate;

    std::ofstream renderOut("mustache.render." + typeName);
    ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
}

#endif