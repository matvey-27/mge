cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(game_engine)

set(CMAKE_CXX_STANDARD 20)

#Укажите относительный путь к вашей папке с библиотеками
set(GRAPHICS_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")  # Запись текущего каталога с CMakeLists.txt

#Укажите путь к библиотеке .lib
set(GRAPHICS_LIBRARY "${GRAPHICS_LIBRARY_DIR}/GraphicsLibrary.lib")

#Создайте исполняемый файл
add_executable(game_engine src/main.cpp
                        src/math/point.cpp
                        src/math/vector.cpp
                        src/render/Model.cpp
                        src/render/RenderUtils.cpp)

#Линковка к библиотеке .lib
target_link_libraries(game_engine PRIVATE ${GRAPHICS_LIBRARY})

#Опционально: копирование .dll в выходной каталог при сборке
file(COPY "${GRAPHICS_LIBRARY_DIR}/GraphicsLibrary.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin")
