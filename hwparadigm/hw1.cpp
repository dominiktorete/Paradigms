#include <iostream>
#include <vector>
#include <string>
#include <cassert>
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
};

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    std::cout << query_builder.BuildQuery();
    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;");
    return 0;
}