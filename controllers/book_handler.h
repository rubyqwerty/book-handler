#pragma once

#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>

using namespace drogon;

namespace users_handler
{
class User : public drogon::HttpController<User>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(User::Add_book, "/addBook?name={1}&genre={2}&autor={3}", Post);
    METHOD_ADD(User::Get_book_by_autor, "/getBookByAutor?name={1}", Get);
    METHOD_ADD(User::Get_book_by_genre, "/getBookByGenre?genre={1}", Get);
    METHOD_ADD(User::Get_books, "/getBooks", Get);
    METHOD_ADD(User::Delete_book, "/deleteBook?id_book={1}", Delete);
    METHOD_ADD(User::Update_book, "/updateBook?id_book={1}&name={2}&genre={3}&autor={4}", Put);
    METHOD_ADD(User::Help, "/help", Get);
    METHOD_LIST_END
    void Add_book(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               const std::string &name,
               const std::string &genre,
               const std::string &autor);

    void Get_book_by_autor(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               const std::string &autor);

    void Get_book_by_genre(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               const std::string &genre);

    void Get_books(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback);
    
    void Delete_book(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
                const std::string &id_book);

     void Update_book(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               const std::string &id_book,
               const std::string &name,
               const std::string &genre,
               const std::string &autor);

      void Help(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback);

    
};
}


