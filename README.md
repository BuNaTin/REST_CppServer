# REST_CppServer #

## 1. Small info: ## 
Небольшой REST сервер, реализованный на QTcpServer. Система сборки - cmake, для написания и отладки использовался QT Creator. Проект собирался на Windows, с использованием компилятора MinGW версии 9.0.0 под 64 бита.

## 2. API: ##
### 2.1 GET ###
Запрос GET запрашивает представление ресурса (значения) для указанного id, или представление всех ресурсов и истории их изменений. Имеет формат GET {ip}/api/{id} или GET {ip}/test например:
1) GET 127.0.0.1:1234/api/3 - выводит представление ресурса с id = 3
Сервер возвращает статус "200 OK" и сообщение "Item id <>, item value <>.", где в первых квадратных скобках указан id, а во вторых - значение, соответствующие этому id. 
В случае отсутствия элемента id возвращает статус "404 Not found" и сообщение "Don't have item with id <>.", где в первых квадратных скобках указан id.
В случае отсутствия id в команде возвращает статус "400 Bad request"
2) GET 127.0.0.1:1234/test - возвращает статус "200 OK" и выводит простую таблицу с id и значением, а после неё список совершенных над таблицей изменений
### 2.2 PUT ###
Запрос PUT создаёт новый ресурс или заменяет представление целевого ресурса, данными представленными в теле запроса. При каждом вызове PUT перезаписывает данные ресурса под указанным id и добавляет пункт в историю изменений. Имеет формат PUT {ip}/api/{id}, например:
PUT 127.0.0.1:1234/api/2
Сервер возвращает статус "201 Created" без сообщения.
В случае отсутствия id в команде возвращает статус "400 Bad request"
### 2.3 POST ###
Запрос PUT предназначен для отправки данных на сервер При каждом вызове POST обновляет данные ресурса под указанным id. Если ресурса с таким id нет - создаёт его, а если ресурс существует - модифицирует его (увеличивает значение на 1) и добавляет пункт в историю изменений. Имеет формат POST {ip}/api/{id}, например:
POST 127.0.0.1:1234/api/1
Сервер возвращает статус "200 OK" без сообщения.
В случае отсутствия id в команде возвращает статус "400 Bad request"
### 2.4 DELETE ###
Запрос DELETE удаляет ресурс с указанным id. Имеет формат DELETE {ip}/api/{id}, например:
DELETE 127.0.0.1:1234/api/2
Сервер возвращает статус "200 OK" без сообщения.
В случае отсутствия на сервере ресурса с указанным id, сервер возвращает статус "204 No content".
В случае отсутствия id в команде возвращает статус "400 Bad request"
## 3. Test ##
Тесты сервера производились при помощи pytest и файла test.py, расположенного в папке Test. В тестах были задействованы различные виды запросов, которые может обработать сервер.