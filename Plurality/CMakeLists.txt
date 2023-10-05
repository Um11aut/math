# CMakeList.txt: проект CMake для Plurality; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Plurality "Plurality.cpp" "Plurality.h" "Helper.h" "Plurality_bit.h" "Matrix.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Plurality PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
