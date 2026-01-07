#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <any>
#include <variant>
#include <utility>

namespace fs = std::filesystem;
namespace SearchSpec{
    using StructTypeVariant = std::variant<fs::path,std::vector<std::string>,bool,int>;

    struct SearchSpecification {
        fs::path search_path;
        fs::path delivery_path;
        std::vector<std::string> match_terms;
        std::vector<std::string> week_dir_names;
        std::vector<std::string> term_dir_names;
        std::vector<std::string> course_dir_names;
        std::vector<std::string> additional_nested_dir_names;
        bool match_case_sensitive;
        int investigatory_search_depth;

    };

    std::shared_ptr<SearchSpecification> build_search_specification(
        fs::path search_path,
        fs::path delivery_path,
        std::vector<std::string> match_terms,
        std::vector<std::string> week_dir_names,
        std::vector<std::string> term_dir_names,
        std::vector<std::string> course_dir_names,
        std::vector<std::string> additional_nested_dir_names,
        bool match_case_sensitive,
        int investigatory_search_depth
        );

    std::map<std::string, StructTypeVariant> asVariantMap(SearchSpec::SearchSpecification spec);

}
