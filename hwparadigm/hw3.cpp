#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <map>
class SqlSelectQueryBuilder {
protected:
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> wheres;
    std::vector<std::string> sign_where;
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
        sign_where.push_back("=");
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
            query += wheres[i].first + sign_where[i] + wheres[i].second;
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
            sign_where.push_back("=");
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
class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
public:
    AdvancedSqlSelectQueryBuilder& AddWheremore(std::string lv, std::string rv) {
        wheres.push_back(std::make_pair(lv, rv));
        sign_where.push_back(">");
        return *this;
    }
    AdvancedSqlSelectQueryBuilder& AddWhereless(std::string lv, std::string rv) {
        wheres.push_back(std::make_pair(lv, rv));
        sign_where.push_back("<");
        return *this;
    }
};
int main() {

    AdvancedSqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({"name", "phone"});
    query_builder.AddFrom("students");
    query_builder.AddWheremore("id", "42"); // Добавляем условие id > 42
    query_builder.AddWhereless("id", "52"); // Добавляем условие id < 52
    std::cout << query_builder.BuildQuery() << std::endl;
    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id>42 AND id<52;");
    return 0;
}