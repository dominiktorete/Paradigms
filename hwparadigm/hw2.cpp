#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <map>
class SqlSelectQueryBuilder {
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> wheres;
public:
    SqlSelectQueryBuilder& AddColumn(std::string column) {
        columns.push_back(column);
        return *this;
    }
    SqlSelectQueryBuilder& AddFrom(std::string table_name) {
        table = table_name;
        return *this;
    }
    SqlSelectQueryBuilder& AddWhere(std::string lv, std::string rv) {
        wheres.push_back(std::make_pair(lv, rv));
        return *this;
    }
    std::string BuildQuery() {
        std::string query = "SELECT";
        if (columns.empty()) {
            query += " *";
        }
        else {
            for (int i = 0; i < columns.size(); i++) {
                query += " " + columns[i];
                if ( i < columns.size() - 1 ) query += ",";
            }
        }
        query += " FROM " + table;
        query += " WHERE ";
        for (int i = 0; i < wheres.size(); i++) {
            query += wheres[i].first + "=" + wheres[i].second;
            if (i < wheres.size() - 1) {
                query += " AND ";
            }
        }
        query += ";";
        return query;
    }
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& key_value : kv) {
            wheres.push_back(key_value);
        }
        return *this;
    }
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns_) noexcept {
        for (const auto& value : columns_) {
            columns.push_back(value);
        }
        return *this;
    }
};

int main() {
    SqlSelectQueryBuilder query_builder;
    std::vector<std::string> columns{"name", "phone"};
    query_builder.AddColumns(columns);
    std::map<std::string, std::string> where{{"id", "42"}, {"name", "John"}};
    query_builder.AddFrom("students");

    query_builder.AddWhere(where);
    std::cout << query_builder.BuildQuery();
    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;");
    return 0;
}