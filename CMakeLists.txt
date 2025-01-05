cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(game_engine)

set(CMAKE_CXX_STANDARD 20)

#Укажите относительный путь к вашей папке с библиотеками
set(GRAPHICS_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GraphicsLibrarry")  # Запись текущего каталога с CMakeLists.txt
#Укажите путь к библиотеке .lib
set(GRAPHICS_LIBRARY "${GRAPHICS_LIBRARY_DIR}/GraphicsLibrary.lib")	

#Создайте исполняемый файл
add_executable(game_engine libs/MGE/render/model.cpp
                            src/main.cpp )

#Линковка к библиотеке .lib
target_link_libraries(game_engine PRIVATE ${GRAPHICS_LIBRARY})

#Опционально: копирование .dll в выходной каталог при сборке
file(COPY "${GRAPHICS_LIBRARY_DIR}/GraphicsLibrary.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
