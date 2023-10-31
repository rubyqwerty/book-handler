#include "book_handler.h"
#include "../models/Books.h"

using namespace users_handler;


Json::Value Book_to_json(drogon_model::users::Books book) {
    Json::Value result;
    result["name"] = *book.getName();
    result["genre"] = *book.getGenre();
    result["autor"] = *book.getAutor();
    return result;
}

void users_handler::User::Add_book(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& name,
    const std::string& genre,
    const std::string& autor)
{
    auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);
    auto book = drogon_model::users::Books();
    book.setAutor(autor);
    book.setGenre(genre);
    book.setName(name);
    mp.insert(book);
    Json::Value jsonbody;
    jsonbody["status"] = "ok";
    auto response = HttpResponse::newHttpJsonResponse(jsonbody);
    callback(response);
}

void users_handler::User::Get_book_by_autor(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& autor)
{
    auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);
    auto book = mp.findBy(drogon::orm::Criteria("autor", drogon::orm::CompareOperator::EQ, autor));
    Json::Value jsonbody;
    for (auto i : book)
        jsonbody[(*i.getId())].append(Book_to_json(i));
    auto response = HttpResponse::newHttpJsonResponse(jsonbody);
    callback(response);
}

void users_handler::User::Get_book_by_genre(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& genre)
{
     auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);
    auto book = mp.findBy(drogon::orm::Criteria("genre", drogon::orm::CompareOperator::EQ, genre));
    Json::Value jsonbody;
    for (auto i : book)
        jsonbody[(*i.getId())].append(Book_to_json(i));
    auto response = HttpResponse::newHttpJsonResponse(jsonbody);
    callback(response);
}


void users_handler::User::Get_books(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);

    auto books = mp.limit(25).offset(0).findAll();
    Json::Value jsonBody;
    
    for (auto book : books) {
        jsonBody[*book.getId()].append(Book_to_json(book));
    }

    auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    callback(response);

}

void users_handler::User::Delete_book(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& id_book)
{
    auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);
    mp.deleteBy(drogon::orm::Criteria("id", drogon::orm::CompareOperator::EQ, id_book));
    Json::Value jsonbody;
    jsonbody["status"] = "ok";
    auto response = HttpResponse::newHttpJsonResponse(jsonbody);
    callback(response);
}

void users_handler::User::Update_book(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& id_book,
    const std::string& name,
    const std::string& genre,
    const std::string& autor)
{
     auto clientPtr = app().getDbClient();
    orm::Mapper<drogon_model::users::Books> mp(clientPtr);
    mp.updateBy(Json::Value::Members({"name", "genre", "autor"}), drogon::orm::Criteria("id",
    drogon::orm::CompareOperator::EQ, id_book), name, genre, autor);

    Json::Value jsonbody;
    jsonbody["status"] = "ok";
    auto response = HttpResponse::newHttpJsonResponse(jsonbody);
    callback(response);
}

void users_handler::User::Help(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value jsonBody;
    jsonBody["добавить книгу"] = "/addBook?name={1}&genre={2}&autor={3}";
    jsonBody["получить книги от определенного автора"] = "/getBookByAutor?name={1}";
    jsonBody["получить книги от определенного жанра"] = "/getBookByGenre?genre={1}";
    jsonBody["получить все книги в базе"] = "/getBooks";
    jsonBody["удалить книгу по id"] = "/deleteBook?id_book={1}";
    jsonBody["обновить книгу по id"] = "/updateBook?id_book={1}&name={2}&genre={3}&autor={4}";

     auto response = HttpResponse::newHttpJsonResponse(jsonBody);
     callback(response);
}
