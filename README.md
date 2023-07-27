<h1 align="center">Описание</h1>
<hr></hr>
<body>Это чат сервер реализованный на С++. 
<p>В данной работе реализованно:</p>
<p><li>Отправка публичных сообщений</p>
<p><li>Отправка приватных сообщений</p>
<p><li>Смена имени пользователя в чате</p>
<p><li>Выдача списка онлайн пользователей в чате при подключение к серверу</p>
<p><h1 align="center">Структура проекта</h1></p>
<hr></hr>
<img src="struct.png">
<p><h1 align="center">JSON файлы</h1></p>
<hr></hr>
<p>Для работы c JSON файлами используется <a href="https://github.com/nlohmann/json">JSON for Modern C++</a>(установлен с помощью <a href="https://github.com/microsoft/vcpkg">vcpkg</a>).</p>
<p><h1 align="center">WebSockets</h1></p>
<hr></hr>
<p>Для организации работы с WebSockets используется <a href="https://github.com/uNetworking/uWebSockets">uWebSockets</a>(установлен с помощью <a href="https://github.com/microsoft/vcpkg">vcpkg</a>).</p>
<h1 align="center">Установка библиотек с помощью <a href="https://github.com/microsoft/vcpkg">vcpkg</a></h1>
<hr></hr>
<p><a href ="https://blog.jetbrains.com/clion/2023/01/support-for-vcpkg-in-clion/">Данный пример реализован с помощью IDE JetBrains version 2023.1 и выше</a></p>
<p><h1 align="center">Установка на примере IDE Clion</h1></p>
<hr></hr>
<p>1. С помощью инструмента для загрузки из удаленного репозитория, разместим исходные файлы в удобный каталог. <a href="https://github.com/Sereys13/ChatServer">Ссылка на репозиторий</a> </p>
<p><img src="img_1.png" width="500" height="500"></p>
<p>2. Выполняем сборку проекта, сформировываем исполняемый файл search_engine.exe </p>
<p><img src="img_2.png"></p>
<p><h1 align="center">Настройка и запуск</h1></p>
<hr></hr>
<p>1. Перенесите исполняемый файл в рабочий каталог.</p>
<p>2. Запустите исполняемый файл</p>
<p>3. В любом удобном вам браузере открываем http://localhost:9001/ </p>
<p>4. Открываем на данной странице консоль JavaScript </p>
<p>5. С помощью команды <cite>ws = new WebSocket ("ws://localhost:9001"); ws.onmessage = ({data}) => console.log(data);</cite> подключаемся к серверу </p>
<p>6. На данный момент реализованы следующие команды:</p>
<p><li>Отправка публичных сообщений  <cite>ws.send('{"command":"publicMsg" , "text" : "Hi"}');</cite></p>
<p><li>Отправка приватных сообщений <cite>ws.send('{"command":"privateMsg" , "userTo" : 10 , "text" : "Hi"}');</cite></p>
<p><li>Смена имени пользователя в чате <cite>ws.send('{"command":"setName" , "name" : "Johnny Silverhand"}');</cite></p>
